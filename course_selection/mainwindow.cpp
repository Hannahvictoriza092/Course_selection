#include "mainwindow.h"
#include <QJsonArray>
#include <QJsonObject>
#include "coursedialog.h"
#include "ui_mainwindow.h"
#include "courseparser.h"
#include "scheduleexporter.h"
#include "coursealgorithm.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    courseParser(new CourseParser(this)),
    scheduleExporter(new ScheduleExporter(this)),
    courseAlgorithm(new CourseAlgorithm(this)),
    currentEditingCourseId("") // 初始化为空字符串
{
    ui->setupUi(this);

    // 设置垂直表头右键菜单
    ui->courseTableWidget->verticalHeader()->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->courseTableWidget->verticalHeader(), &QHeaderView::customContextMenuRequested,
            this, &MainWindow::onCourseTableContextMenu);
    // 连接菜单动作
    connect(ui->actionAddCourse, &QAction::triggered, this, &MainWindow::showAddCourseDialog);


}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::loadCourseData(const QString &filePath)
{
    courseData = courseParser->parseCourseFile(filePath);
    if (!courseData.isEmpty()) {
        displayCourseData();
        QMessageBox::information(this, "成功", "课程数据导入成功");
    } else {
        QMessageBox::warning(this, "错误", "课程数据导入失败");
    }
}

void MainWindow::displayCourseData(const QJsonArray &filterCourses)
{
    // 1. 确定要显示的课程数据 - 修复逻辑错误
    QJsonArray displayCourses;
    
    // 如果有过滤结果，使用过滤结果
    if (!filterCourses.isEmpty()) {
        displayCourses = filterCourses;
    } 
    // 如果没有过滤结果，但提供了过滤参数（搜索操作），使用空数组
    else if (!ui->lineEdit_searchId->text().isEmpty() ||
             !ui->lineEdit_searchTeacher->text().isEmpty() ||
             !ui->lineEdit_searchName->text().isEmpty()) {
        displayCourses = QJsonArray();
    }
    // 否则（初始状态或没有搜索条件），使用全部课程
    else if (courseData.contains("courses") && courseData["courses"].isArray()) {
        displayCourses = courseData["courses"].toArray();
    }
    
    // 2. 更新UI状态：显示/隐藏标签和表格
    bool hasResults = !displayCourses.isEmpty();
    ui->label_noResults->setVisible(!hasResults);  // 没有结果时显示标签
    ui->courseTableWidget->setVisible(hasResults); // 有结果时显示表格
    
    // 3. 清除表格内容
    ui->courseTableWidget->clearContents();
    ui->courseTableWidget->setRowCount(0);
    
    // 4. 添加调试信息
    qDebug() << "=== 显示课程数据 ===";
    qDebug() << "传入过滤课程数:" << filterCourses.size();
    qDebug() << "实际显示课程数:" << displayCourses.size();
    qDebug() << "标签可见性:" << ui->label_noResults->isVisible();
    qDebug() << "表格可见性:" << ui->courseTableWidget->isVisible();
    
    // 5. 如果没有结果，提前返回
    if (!hasResults) {
        qDebug() << "没有匹配结果，提前返回";
        return;
    }
    
    // 6. 填充表格数据
    qDebug() << "开始填充表格数据...";
    int currentRow = 0;
    
    for (int i = 0; i < displayCourses.size(); ++i) {
        QJsonObject course = displayCourses[i].toObject();
        QJsonArray offerings = course["offerings"].toArray();
        
        // 为每个教学班添加一行
        for (int j = 0; j < offerings.size(); ++j) {
            ui->courseTableWidget->insertRow(currentRow);
            QJsonObject offering = offerings[j].toObject();
            
            // 开课学期 (第0列) - 只在第一行设置
            if (j == 0) {
                ui->courseTableWidget->setItem(currentRow, 0, new QTableWidgetItem(course["semester"].toString()));
            }
            
            // 课程ID (第1列) - 只在第一行设置
            if (j == 0) {
                ui->courseTableWidget->setItem(currentRow, 1, new QTableWidgetItem(course["id"].toString()));
            }
            
            // 课程名称 (第2列) - 只在第一行设置
            if (j == 0) {
                ui->courseTableWidget->setItem(currentRow, 2, new QTableWidgetItem(course["name"].toString()));
            }
            
            // 课程类别 (第3列) - 只在第一行设置
            if (j == 0) {
                QString required = course["required"].toString();
                ui->courseTableWidget->setItem(currentRow, 3, new QTableWidgetItem(
                    required == "Compulsory" ? "必修" : 
                    required == "Elective" ? "选修" : required));
            }
            
            // 教师信息 (第4列) - 每个教学班单独设置
            ui->courseTableWidget->setItem(currentRow, 4, new QTableWidgetItem(offering["teacher"].toString()));
            
            // 上课时间 (第5列) - 每个教学班单独设置
            QJsonArray times = offering["times"].toArray();
            QStringList dayStrings = {"周一", "周二", "周三", "周四", "周五", "周六", "周日"};
            QStringList timeStrings;
            
            for (int k = 0; k < times.size(); k++) {
                int timeMask = times[k].toInt();
                if (timeMask != 0) {
                    QStringList periods;
                    for (int m = 0; m < 14; m++) { // 每天14节课
                        if (timeMask & (1 << m)) {
                            periods << QString::number(m + 1);
                        }
                    }
                    timeStrings << dayStrings[k] + ": 第" + periods.join(",") + "节";
                }
            }
            ui->courseTableWidget->setItem(currentRow, 5, new QTableWidgetItem(timeStrings.join("\n")));
            
            // 学分(两倍) (第6列) - 只在第一行设置
            if (j == 0) {
                ui->courseTableWidget->setItem(currentRow, 6, new QTableWidgetItem(QString::number(course["credit"].toInt())));
            }
            
            // 前置课程 (第7列) - 只在第一行设置
            if (j == 0) {
                QJsonArray prereqs = course["prerequisites"].toArray();
                QStringList prereqList;
                for (const auto &prereq : prereqs) {
                    prereqList << prereq.toString();
                }
                ui->courseTableWidget->setItem(currentRow, 7, new QTableWidgetItem(prereqList.join(", ")));
            }
            
            // 设置行高
            ui->courseTableWidget->setRowHeight(currentRow, 60);
            currentRow++;
        }
        
        // 合并单元格
        if (offerings.size() > 1) {
            int startRow = currentRow - offerings.size();
            for (int col : {0, 1, 2, 3, 6, 7}) {
                ui->courseTableWidget->setSpan(startRow, col, offerings.size(), 1);
            }
            
            // 调整合并单元格的行高
            int totalHeight = 0;
            for (int r = startRow; r < startRow + offerings.size(); r++) {
                totalHeight += ui->courseTableWidget->rowHeight(r);
            }
            ui->courseTableWidget->setRowHeight(startRow, totalHeight);
        }
    }
    
    // 8. 调整列宽
    ui->courseTableWidget->resizeColumnsToContents();
    
    // 9. 再次刷新UI
    ui->courseTableWidget->update();
    QApplication::processEvents();
    qDebug() << "表格填充完成";
}

void MainWindow::displayScheduleData()
{
    // 待实现：显示选课方案数据到表格
}

void MainWindow::on_actionImportCourse_triggered()
{
    QString filePath = QFileDialog::getOpenFileName(this, "选择课程数据文件", ".", "JSON文件 (*.json)");
    if (!filePath.isEmpty()) {
        loadCourseData(filePath);
    }
}

void MainWindow::on_actionExportSchedule_triggered()
{
    QString filePath = QFileDialog::getSaveFileName(this, "保存选课方案", ".", "JSON文件 (*.json)");
    if (!filePath.isEmpty()) {
        bool success = scheduleExporter->exportSchedule(filePath, scheduleData);
        if (success) {
            QMessageBox::information(this, "成功", "选课方案导出成功");
        } else {
            QMessageBox::warning(this, "错误", "选课方案导出失败");
        }
    }
}
// 右键菜单处理
void MainWindow::onCourseTableContextMenu(const QPoint &pos)
{
    // 获取右键点击的行号
    int row = ui->courseTableWidget->verticalHeader()->logicalIndexAt(pos);
    if (row < 0) return; // 未点击有效行
    
    QMenu menu(this);
    QAction *editAction = menu.addAction("编辑课程");
    QAction *deleteAction = menu.addAction("删除课程");
    
    connect(editAction, &QAction::triggered, this, [this, row]() {
        showEditCourseDialog(row);
    });
    connect(deleteAction, &QAction::triggered, this, [this, row]() {
        ui->courseTableWidget->selectRow(row);
        onDeleteCourseAction();
    });
    
    // 在表头点击位置显示菜单
    menu.exec(ui->courseTableWidget->verticalHeader()->mapToGlobal(pos));
}
// 显示添加课程对话框
void MainWindow::showAddCourseDialog()
{
    CourseDialog dialog(this);
    if (dialog.exec() == QDialog::Accepted) {
        addCourseToData(dialog.getCourseData());
        displayCourseData();
    }
}

// 显示编辑课程对话框
void MainWindow::showEditCourseDialog(int row)
{
    if (row < 0) return;
    
    // 获取合并单元格中的实际课程行
    int actualRow = findActualCourseRow(row);
    if (actualRow < 0) return;
    
    // 获取课程ID
    QTableWidgetItem* idItem = ui->courseTableWidget->item(actualRow, 1);
    if (!idItem) return;
    QString courseId = idItem->text();
    
    // 保存当前编辑的课程ID
    currentEditingCourseId = courseId;
    
    // 从数据结构中获取课程完整信息
    QJsonObject course = findCourseById(courseId);
    if (course.isEmpty()) {
        qWarning() << "编辑失败: 未找到课程" << courseId;
        return;
    }
    
    CourseDialog dialog(this);
    dialog.setCourseData(course);
    
    if (dialog.exec() == QDialog::Accepted) {
        QJsonObject updatedCourse = dialog.getCourseData();
        QString newCourseId = updatedCourse["id"].toString();
        
        // 检查ID是否被修改
        if (currentEditingCourseId != newCourseId) {
            qDebug() << "课程ID已修改:" << currentEditingCourseId << "->" << newCourseId;
            
            // 检查新ID是否已存在
            QJsonObject existingCourse = findCourseById(newCourseId);
            if (!existingCourse.isEmpty()) {
                QMessageBox::warning(this, "错误", 
                    "课程ID " + newCourseId + " 已存在，请使用不同的ID");
                return;
            }
        }
        
        updateCourseInData(updatedCourse);
        displayCourseData();
        qDebug() << "课程更新成功";
    } else {
        qDebug() << "用户取消了编辑";
    }
}

// 添加辅助函数：查找实际课程行
int MainWindow::findActualCourseRow(int row) const
{
    if (row < 0 || row >= ui->courseTableWidget->rowCount()) {
        return -1;
    }
    
    // 检查当前行是否有课程ID
    if (ui->courseTableWidget->item(row, 1)) {
        return row;
    }
    
    // 向上查找直到找到有课程ID的行
    for (int i = row; i >= 0; i--) {
        if (ui->courseTableWidget->item(i, 1)) {
            return i;
        }
    }
    
    // 向下查找作为后备方案
    for (int i = row + 1; i < ui->courseTableWidget->rowCount(); i++) {
        if (ui->courseTableWidget->item(i, 1)) {
            return i;
        }
    }
    
    return -1;
}

void MainWindow::filterCourseData(const QString &id, const QString &teacher, const QString &name)
{
    QJsonArray filteredCourses;
    QJsonArray allCourses = courseData["courses"].toArray();
    // 添加调试输出
    qDebug() << "开始过滤课程 - ID:" << id << "教师:" << teacher << "名称:" << name;
    qDebug() << "总课程数:" << allCourses.size();
    for (const QJsonValue &value : allCourses) {
        QJsonObject course = value.toObject();
        bool idMatch = id.isEmpty() || course["id"].toString().contains(id, Qt::CaseInsensitive);
        bool nameMatch = name.isEmpty() || course["name"].toString().contains(name, Qt::CaseInsensitive);
        
        if (!idMatch || !nameMatch) {
            continue;
        }
        
        QJsonArray offerings = course["offerings"].toArray();
        QJsonArray matchingOfferings;
        
        if (teacher.isEmpty()) {
            matchingOfferings = offerings;
        } else {
            for (const QJsonValue &offering : offerings) {
                if (offering.toObject()["teacher"].toString().contains(teacher, Qt::CaseInsensitive)) {
                    matchingOfferings.append(offering);
                }
            }
        }
        
        if (!matchingOfferings.isEmpty()) {
            QJsonObject filteredCourse = course;
            filteredCourse["offerings"] = matchingOfferings;
            filteredCourses.append(filteredCourse);
        }
    }
    // 添加调试输出
    qDebug() << "过滤后课程数:" << filteredCourses.size();
    displayCourseData(filteredCourses);
}

void MainWindow::on_pushButton_search_clicked()
{
    QString id = ui->lineEdit_searchId->text().trimmed();
    QString teacher = ui->lineEdit_searchTeacher->text().trimmed();
    QString name = ui->lineEdit_searchName->text().trimmed();
    
    qDebug() << "搜索参数 - ID:" << id << "教师:" << teacher << "名称:" << name;
    
    filterCourseData(id, teacher, name);
}

void MainWindow::onAddCourseDialogAccepted()
{
    CourseDialog *dialog = qobject_cast<CourseDialog*>(sender());
    if (dialog)
    {
        addCourseToData(dialog->getCourseData());
        displayCourseData();
        dialog->deleteLater();
    }
}

void MainWindow::onEditCourseAction()
{
    int row = ui->courseTableWidget->currentRow();
    if (row >= 0) showEditCourseDialog(row);
}

void MainWindow::onDeleteCourseAction()
{
    int row = ui->courseTableWidget->currentRow();
    if (row < 0) return;
    
    // 获取当前行的教师名称 - 直接从第4列获取
    QTableWidgetItem* teacherItem = ui->courseTableWidget->item(row, 4);
    if (!teacherItem) {
        qWarning() << "无法获取教师名称: 行" << row;
        return;
    }
    QString teacher = teacherItem->text();
    
    // 获取课程ID - 使用 findActualCourseRow 函数
    int actualRow = findActualCourseRow(row);
    if (actualRow < 0) {
        qWarning() << "无法找到实际课程行: 行" << row;
        return;
    }
    
    QTableWidgetItem* idItem = ui->courseTableWidget->item(actualRow, 1);
    if (!idItem) {
        qWarning() << "无法获取课程ID: 行" << actualRow;
        return;
    }
    QString courseId = idItem->text();
    
    QTableWidgetItem* nameItem = ui->courseTableWidget->item(actualRow, 2);
    QString courseName = nameItem ? nameItem->text() : "未知课程";
    
    // 确认对话框
    if (QMessageBox::question(this, "确认删除", 
        "确定要删除 " + teacher + " 老师的教学班吗？\n课程: " + courseName, 
        QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes) {
        
        // 从数据结构中删除指定教学班
        removeOfferingFromData(courseId, teacher);
        displayCourseData();
    }
}

void MainWindow::removeOfferingFromData(const QString &courseId, const QString &teacher)
{
    QJsonArray courses = courseData["courses"].toArray();
    
    for (int i = 0; i < courses.size(); i++) {
        QJsonObject course = courses[i].toObject();
        if (course["id"].toString() == courseId) {
            QJsonArray offerings = course["offerings"].toArray();
            QJsonArray newOfferings;
            bool found = false;
            
            // 过滤掉要删除的教学班
            for (const auto &offering : offerings) {
                QJsonObject obj = offering.toObject();
                if (obj["teacher"].toString() != teacher) {
                    newOfferings.append(obj);
                } else {
                    found = true;
                }
            }
            
            if (!found) {
                qWarning() << "未找到匹配的教学班: 课程" << courseId << "教师" << teacher;
                return;
            }
            
            // 如果删除后没有教学班，则删除整个课程
            if (newOfferings.size() == 0) {
                courses.removeAt(i);
                qDebug() << "删除整个课程:" << courseId;
            } else {
                course["offerings"] = newOfferings;
                courses[i] = course;
                qDebug() << "删除教学班:" << courseId << "教师" << teacher;
            }
            
            courseData["courses"] = courses;
            return;
        }
    }
    
    qWarning() << "未找到课程:" << courseId;
}

// 添加到数据结构
void MainWindow::addCourseToData(const QJsonObject &newCourse)
{
    QJsonArray courses = courseData["courses"].toArray();
    courses.append(newCourse);
    courseData["courses"] = courses;
}

// 更新数据结构
void MainWindow::updateCourseInData(const QJsonObject &updatedCourse)
{
    if (!updatedCourse.contains("id") || !updatedCourse["id"].isString()) {
        qWarning() << "更新失败: 无效的课程数据";
        return;
    }
    
    QString newCourseId = updatedCourse["id"].toString();
    QJsonArray courses = courseData["courses"].toArray();
    bool found = false;
    int foundIndex = -1;
    
    // 首先尝试用原始ID查找课程
    for (int i = 0; i < courses.size(); i++) {
        QJsonObject course = courses[i].toObject();
        if (course.contains("id") && course["id"].isString() && 
            course["id"].toString() == currentEditingCourseId) {
            found = true;
            foundIndex = i;
            qDebug() << "找到课程(原始ID):" << currentEditingCourseId;
            break;
        }
    }
    
    // 如果原始ID没找到，尝试用新ID查找
    if (!found) {
        for (int i = 0; i < courses.size(); i++) {
            QJsonObject course = courses[i].toObject();
            if (course.contains("id") && course["id"].isString() && 
                course["id"].toString() == newCourseId) {
                found = true;
                foundIndex = i;
                qDebug() << "找到课程(新ID):" << newCourseId;
                break;
            }
        }
    }
    
    if (found) {
        // 更新现有课程
        courses[foundIndex] = updatedCourse;
        qDebug() << "更新课程:" << (currentEditingCourseId != newCourseId ? 
                  currentEditingCourseId + " -> " + newCourseId : newCourseId);
    } else {
        // 添加为新课程
        courses.append(updatedCourse);
        qDebug() << "添加为新课程:" << newCourseId;
    }
    
    // 如果ID发生变化，需要确保没有重复的旧ID
    if (currentEditingCourseId != newCourseId) {
        // 再次遍历删除旧ID的课程（如果有）
        for (int i = 0; i < courses.size(); i++) {
            QJsonObject course = courses[i].toObject();
            if (course.contains("id") && course["id"].isString() && 
                course["id"].toString() == currentEditingCourseId && i != foundIndex) {
                courses.removeAt(i);
                qDebug() << "移除重复的旧ID课程:" << currentEditingCourseId;
                break;
            }
        }
    }
    
    courseData["courses"] = courses;
    qDebug() << "课程数据已更新";
}




// 根据ID查找课程
QJsonObject MainWindow::findCourseById(const QString &courseId)
{
    if (courseId.isEmpty()) {
        return QJsonObject();
    }
    
    if (!courseData.contains("courses") || !courseData["courses"].isArray()) {
        return QJsonObject();
    }
    
    QJsonArray courses = courseData["courses"].toArray();
    
    for (int i = 0; i < courses.size(); i++) {
        if (!courses[i].isObject()) continue;
        
        QJsonObject course = courses[i].toObject();
        if (course.contains("id") && course["id"].isString() && 
            course["id"].toString() == courseId) {
            return course;
        }
    }
    
    return QJsonObject();
}

void MainWindow::on_actionGenerateSchedule_triggered()
{
    int creditLimit = ui->creditSpinBox->value();
    scheduleData = courseAlgorithm->generateSchedule(courseData, creditLimit);
    if (!scheduleData.isEmpty()) {
        displayScheduleData();
        QMessageBox::information(this, "成功", "选课方案生成成功");
    } else {
        QMessageBox::warning(this, "错误", "无法生成满足条件的选课方案");
    }
}
