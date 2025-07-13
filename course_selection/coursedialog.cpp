#include "coursedialog.h"
#include "ui_coursedialog.h"
#include <QTableWidgetItem>
#include <QPushButton>
#include <QHeaderView>
#include <QInputDialog>
#include <QJsonArray>

CourseDialog::CourseDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CourseDialog),
    isEditMode(false)
{
    ui->setupUi(this);
    setupTimeSlotWidgets();
    classSections.clear();
    
    // 设置学期选项
    ui->comboBox_semester->addItems({"Spring", "Autumn"});
    
    // 设置课程类型选项
    ui->comboBox_courseType->addItems({"必修", "选修"});
    
    // 连接课程类型变化信号以控制优先级SpinBox显示
    connect(ui->comboBox_courseType, &QComboBox::currentTextChanged, this, [this](const QString &type){
    bool isElective = (type == "选修");
    ui->spinBox_priority->setVisible(isElective);
    if (!isEditMode) { // 添加模式下根据课程类型设置默认优先级
        ui->spinBox_priority->setValue(isElective ? 1 : 0);
    }
});
    
    // 设置表格双击编辑
    connect(ui->tableWidget_classes, &QTableWidget::itemDoubleClicked, this, &CourseDialog::on_tableWidget_classes_itemDoubleClicked);
    
    // 确保按钮连接正确
    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &CourseDialog::accept);
    connect(ui->buttonBox, &QDialogButtonBox::rejected, this, &CourseDialog::reject);
}

CourseDialog::~CourseDialog()
{
    delete ui;
}

void CourseDialog::setupTimeSlotWidgets()
{
    // 设置时间表格列宽
    ui->tableWidget_classes->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    
    
}

void CourseDialog::setAddMode() {
    isEditMode = false;
    ui->spinBox_priority->setValue(0); // 默认必修，优先级0
    on_pushButton_addClass_clicked();  // 手动调用
}

void CourseDialog::accept()
{
    // 验证必填字段
    if (ui->lineEdit_courseId->text().isEmpty()) {
        QMessageBox::warning(this, "错误", "课程ID不能为空");
        return;
    }
    
    if (ui->lineEdit_courseName->text().isEmpty()) {
        QMessageBox::warning(this, "错误", "课程名称不能为空");
        return;
    }
    
    // 验证教学班
    for (int i = 0; i < ui->tableWidget_classes->rowCount(); i++) {
        QTableWidgetItem* teacherItem = ui->tableWidget_classes->item(i, 0);
        if (!teacherItem || teacherItem->text().isEmpty()) {
            QMessageBox::warning(this, "错误", "教师名称不能为空");
            return;
        }
    }
    
    // 调用基类 accept 关闭对话框
    QDialog::accept();
}

void CourseDialog::setCourseData(const QJsonObject &course)
{
    isEditMode = true;
    classSections.clear();
    
    // 填充基本课程信息
    ui->lineEdit_courseId->setText(course["id"].toString());
    ui->lineEdit_courseId->setReadOnly(true); // 编辑模式下课程ID不可修改
    ui->lineEdit_courseName->setText(course["name"].toString());
    ui->comboBox_semester->setCurrentText(course["semester"].toString());
    
    QString required = course["required"].toString();
    ui->comboBox_courseType->setCurrentText(required == "Compulsory" ? "必修" : "选修");
    
    // 设置优先级SpinBox
    if (ui->comboBox_courseType->currentText() == "选修") {
        ui->spinBox_priority->setVisible(true);
        ui->spinBox_priority->setValue(course["priority"].toInt());
    } else {
        ui->spinBox_priority->setVisible(false);
    }
    
    ui->doubleSpinBox_credits->setValue(course["credit"].toInt());
    
    // 填充前置课程
    QJsonArray prereqs = course["prerequisites"].toArray();
    for (const auto &prereq : prereqs) {
        ui->listWidget_prerequisites->addItem(prereq.toString());
    }
    
    // 填充教学班
    QJsonArray offerings = course["offerings"].toArray();
    for (const auto &offering : offerings) {
        QJsonObject obj = offering.toObject();
        ClassSection section;
        section.teacher = obj["teacher"].toString();
        
        // 加载7个13位的节次掩码
        QJsonArray timesArray = obj["times"].toArray();
        memset(section.times, 0, sizeof(section.times));
        for (int i = 0; i < qMin(7, timesArray.size()); ++i) {
            section.times[i] = timesArray[i].toInt();
        }
    
        section.weekMask = obj["weeks"].toInt();
        classSections.append(section);
    }
    updateClassTable();
}

QJsonObject CourseDialog::getCourseData() const
{
    QJsonObject course;
    course["id"] = ui->lineEdit_courseId->text();
    course["name"] = ui->lineEdit_courseName->text();
    course["semester"] = ui->comboBox_semester->currentText();
    course["required"] = ui->comboBox_courseType->currentText() == "必修" ? "Compulsory" : "Elective";
    course["credit"] = ui->doubleSpinBox_credits->value();
    
    // 添加优先级（选修课程）
    course["priority"] = (ui->comboBox_courseType->currentText() == "选修") ? ui->spinBox_priority->value() : 0;
    
    // 教学班数据
    QJsonArray offerings;
    for (const auto &section : classSections) {
        QJsonObject offering;
        offering["teacher"] = section.teacher;
        
        // 存储7个13位的节次掩码
        QJsonArray timesArray;
        for (int i = 0; i < 7; ++i) {
            timesArray.append(section.times[i]);
        }
        offering["times"] = timesArray;
        
        // 统一字段名称（weekMaskB → weekMask）
        offering["weeks"] = section.weekMask;
        offerings.append(offering);
    }
    course["offerings"] = offerings;
    
    // 前置课程
    QJsonArray prereqs;
    for (int i = 0; i < ui->listWidget_prerequisites->count(); i++) {
        prereqs.append(ui->listWidget_prerequisites->item(i)->text());
    }
    course["prerequisites"] = prereqs;
    qDebug() << "教学班数量:" << classSections.size();
    return course;
}

// 添加教学班行
void CourseDialog::on_pushButton_addClass_clicked()
{
    ClassTimeDialog dialog(this);
    if (dialog.exec() == QDialog::Accepted) {
        QJsonObject classJson = dialog.getClassData();
        ClassSection section;
        section.teacher = classJson["teacher"].toString();
        QJsonArray timesArray = classJson["times"].toArray();
        for (int i = 0; i < 7; ++i) {
            section.times[i] = timesArray[i].toInt();
        }
        section.weekMask = classJson["weekMask"].toInt();
        classSections.append(section);
        updateClassTable();
    }
}

void CourseDialog::on_tableWidget_classes_itemDoubleClicked(QTableWidgetItem *item)
{
    int row = item->row();
    if (row >= 0 && row < classSections.size()) {
        // 将ClassSection转换为QJsonObject
        QJsonObject classJson;
        classJson["teacher"] = classSections[row].teacher;
        QJsonArray timesArray;
        for (int i = 0; i < 7; ++i) {
            timesArray.append(classSections[row].times[i]);
        }
        classJson["times"] = timesArray;
        classJson["weekMask"] = classSections[row].weekMask;

        ClassTimeDialog dialog(classJson, this);
        if (dialog.exec() == QDialog::Accepted) {
            QJsonObject updatedJson = dialog.getClassData();
            ClassSection updatedSection;
            updatedSection.teacher = updatedJson["teacher"].toString();
            QJsonArray updatedTimes = updatedJson["times"].toArray();
            for (int i = 0; i < 7; ++i) {
                updatedSection.times[i] = updatedTimes[i].toInt();
            }
            updatedSection.weekMask = updatedJson["weekMask"].toInt();
            classSections[row] = updatedSection;
            updateClassTable();
        }
    }
}

void CourseDialog::updateClassTable()
{
    ui->tableWidget_classes->setRowCount(0);
    for (int i = 0; i < classSections.size(); ++i) {
        const ClassSection &section = classSections[i];
        int row = ui->tableWidget_classes->rowCount();
        ui->tableWidget_classes->insertRow(row);

        // 教师
        QTableWidgetItem *teacherItem = new QTableWidgetItem(section.teacher);
        teacherItem->setFlags(teacherItem->flags() & ~Qt::ItemIsEditable);
        ui->tableWidget_classes->setItem(row, 0, teacherItem);

        // 上课时间
        QString timeStr = formatTimeString(section.times, section.weekMask);
        QTableWidgetItem *timeItem = new QTableWidgetItem(timeStr);
        timeItem->setFlags(timeItem->flags() & ~Qt::ItemIsEditable);
        ui->tableWidget_classes->setItem(row, 1, timeItem);

        // 删除按钮
        QPushButton *deleteButton = new QPushButton("删除");
        ui->tableWidget_classes->setCellWidget(row, 2, deleteButton);
        
        int rowIndex = i;  // 捕获用临时变量
        connect(deleteButton, &QPushButton::clicked, this, [this, rowIndex]() {
            classSections.removeAt(rowIndex);
            updateClassTable();
        });
    }
}

// 修正formatTimeString参数类型
QString CourseDialog::formatTimeString(const int times[7], int weekMask)
{
    QStringList weekdays = {"周一", "周二", "周三", "周四", "周五", "周六", "周日"};
    QString timeStr;

    // 解析每日节次
    for (int day = 0; day < 7; ++day) {
        if (times[day] == 0) continue;

        QStringList classes;
        for (int period = 0; period < 13; ++period) {
            if (times[day] & (1 << period)) {
                classes.append(QString::number(period + 1));
            }
        }

        if (!classes.isEmpty()) {
            timeStr += QString("%1: 节次%2; ").arg(weekdays[day]).arg(classes.join(","));
        }
    }

    // 解析周数
    QStringList weeks;
    for (int i = 0; i < 18; ++i) {
        if (weekMask & (1 << i)) {
            weeks.append(QString::number(i + 1));
        }
    }
    timeStr += "周数: " + weeks.join(",");

    return timeStr;
}

// 添加前置课程
void CourseDialog::on_pushButton_addPrerequisite_clicked()
{
    QString courseId = QInputDialog::getText(this, "添加前置课程", "请输入课程ID:");
    if (!courseId.isEmpty()) {
        ui->listWidget_prerequisites->addItem(courseId);
    }
}

// 移除前置课程
void CourseDialog::on_pushButton_removePrerequisite_clicked()
{
    QListWidgetItem *item = ui->listWidget_prerequisites->currentItem();
    if (item) {
        delete ui->listWidget_prerequisites->takeItem(ui->listWidget_prerequisites->row(item));
    }
}
