#include "mainwindow.h"
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
    courseAlgorithm(new CourseAlgorithm(this))
{
    ui->setupUi(this);
    initCourseTable();
    initScheduleTable();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initCourseTable()
{
    // 修改表头顺序和内容
    QStringList headers = {"开课学期", "课程ID", "课程名称", "课程类别", "教师", "上课时间", "学分(两倍)", "前置课程"};
    ui->courseTableWidget->setColumnCount(headers.size());
    ui->courseTableWidget->setHorizontalHeaderLabels(headers);
    
    // 设置列宽均衡
    ui->courseTableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Interactive);
    ui->courseTableWidget->horizontalHeader()->setMinimumSectionSize(100);
    // 设置上课时间列(索引7)宽度为其他列的1.5倍
    ui->courseTableWidget->horizontalHeader()->resizeSection(7, 200);
    ui->courseTableWidget->horizontalHeader()->resizeSection(8, 80);
    ui->courseTableWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    // 设置像素级滚动以提高流畅度
    ui->courseTableWidget->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);
    ui->courseTableWidget->horizontalHeader()->setStretchLastSection(false);
    // 启用单元格文本自动换行
    ui->courseTableWidget->setWordWrap(true);
    // 设置行高根据内容自动调整
    ui->courseTableWidget->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    
    // 设置交替行背景色和表头样式
      ui->courseTableWidget->setAlternatingRowColors(true);
      ui->courseTableWidget->setStyleSheet(
          "QTableWidget { color: #333333; font-weight: 500; }"
          "QTableWidget::item { background-color:rgb(153, 181, 222); }"
          "QTableWidget::item:alternate { background-color:rgb(179, 198, 222); }"
          "QHeaderView::section { background-color: #f0f0f0; color: #333333; padding: 4px; border: 1px solid #dddddd; }"
      );
}

void MainWindow::initScheduleTable()
{
    // 设置行标签（1-14节课）
    QStringList rowLabels;
    for (int i = 1; i <= 14; ++i) {
        rowLabels << QString::number(i);
    }
    ui->scheduleTableWidget->setVerticalHeaderLabels(rowLabels);
    
    // 设置列标签（周一到周日）
    QStringList headers = {"周一", "周二", "周三", "周四", "周五", "周六", "周日"};
    ui->scheduleTableWidget->setHorizontalHeaderLabels(headers);
    
    // 将表头移到下方
    ui->scheduleTableWidget->horizontalHeader()->setSectionPosition(QHeaderView::Bottom);
    
    // 添加滚动条
    ui->scheduleTableWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    ui->scheduleTableWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    
    // 设置列宽自适应
    ui->scheduleTableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
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

void MainWindow::displayCourseData()
{
    ui->courseTableWidget->setRowCount(0);
    if (!courseData.contains("courses") || !courseData["courses"].isArray()) return;

    QJsonArray courses = courseData["courses"].toArray();
    int currentRow = 0;
    
    for (int i = 0; i < courses.size(); ++i) {
        QJsonObject course = courses[i].toObject();
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
            
            // 设置行高适应内容 - 使用固定行高
            ui->courseTableWidget->setRowHeight(currentRow, 60); // 设置为60像素
            
            currentRow++;
        }
        
        // 合并课程基本信息单元格
        if (offerings.size() > 1) {
            int startRow = currentRow - offerings.size();
            for (int col : {0, 1, 2, 3, 6, 7}) { // 需要合并的列
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
    
    // 调整列宽以适应内容
    ui->courseTableWidget->resizeColumnsToContents();
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

void MainWindow::on_actionAddCourse_triggered()
{
    // 待实现：打开添加课程对话框
}

void MainWindow::on_actionEditCourse_triggered()
{
    // 待实现：打开编辑课程对话框
}

void MainWindow::on_actionDeleteCourse_triggered()
{
    // 待实现：删除选中课程
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