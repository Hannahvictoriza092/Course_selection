#include "coursedialog.h"
#include "ui_coursedialog.h"
#include <QTableWidgetItem>
#include <QPushButton>
#include <QHeaderView>
#include <QInputDialog>
#include <QJsonArray>

CourseDialog::CourseDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CourseDialog)
{
    ui->setupUi(this);
    setupTimeSlotWidgets();
    
    // 设置学期选项
    ui->comboBox_semester->addItems({"Spring", "Autumn"});
    
    // 设置课程类型选项
    ui->comboBox_courseType->addItems({"必修", "选修"});
    
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
    
    // 添加初始行
    on_pushButton_addClass_clicked();
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
    // 填充基本课程信息
    ui->lineEdit_courseId->setText(course["id"].toString());
    ui->lineEdit_courseName->setText(course["name"].toString());
    ui->comboBox_semester->setCurrentText(course["semester"].toString());
    
    QString required = course["required"].toString();
    ui->comboBox_courseType->setCurrentText(required == "Compulsory" ? "必修" : "选修");
    
    ui->doubleSpinBox_credits->setValue(course["credit"].toInt());
    
    // 填充前置课程
    QJsonArray prereqs = course["prerequisites"].toArray();
    for (const auto &prereq : prereqs) {
        ui->listWidget_prerequisites->addItem(prereq.toString());
    }
    
    // 填充教学班
    QJsonArray offerings = course["offerings"].toArray();
    ui->tableWidget_classes->setRowCount(0);
    
    for (const auto &offering : offerings) {
        QJsonObject obj = offering.toObject();
        int row = ui->tableWidget_classes->rowCount();
        ui->tableWidget_classes->insertRow(row);
        
        // 教师
        QTableWidgetItem *teacherItem = new QTableWidgetItem(obj["teacher"].toString());
        ui->tableWidget_classes->setItem(row, 0, teacherItem);
        
        // 上课时间
        QString timeStr;
        QJsonArray times = obj["times"].toArray();
        for (const auto &time : times) {
            timeStr += QString::number(time.toInt()) + ",";
        }
        if (!timeStr.isEmpty()) timeStr.chop(1);
        QTableWidgetItem *timeItem = new QTableWidgetItem(timeStr);
        ui->tableWidget_classes->setItem(row, 1, timeItem);
        
        // 删除按钮
        QPushButton *deleteButton = new QPushButton("删除");
        ui->tableWidget_classes->setCellWidget(row, 2, deleteButton);
        connect(deleteButton, &QPushButton::clicked, [this, row]() {
            ui->tableWidget_classes->removeRow(row);
        });
    }
}

QJsonObject CourseDialog::getCourseData() const
{
    QJsonObject course;
    course["id"] = ui->lineEdit_courseId->text();
    course["name"] = ui->lineEdit_courseName->text();
    course["semester"] = ui->comboBox_semester->currentText();
    course["required"] = ui->comboBox_courseType->currentText() == "必修" ? "Compulsory" : "Elective";
    course["credit"] = ui->doubleSpinBox_credits->value();
    
    // 教学班数据
    QJsonArray offerings;
    for (int i = 0; i < ui->tableWidget_classes->rowCount(); i++) {
        QJsonObject offering;
        offering["teacher"] = ui->tableWidget_classes->item(i, 0)->text();
        
        // 解析时间数据（简化示例）
        QString timeStr = ui->tableWidget_classes->item(i, 1)->text();
        QStringList timeList = timeStr.split(",");
        QJsonArray times;
        for (const auto &time : timeList) {
            times.append(time.toInt());
        }
        offering["times"] = times;
        
        offerings.append(offering);
    }
    course["offerings"] = offerings;
    
    // 前置课程
    QJsonArray prereqs;
    for (int i = 0; i < ui->listWidget_prerequisites->count(); i++) {
        prereqs.append(ui->listWidget_prerequisites->item(i)->text());
    }
    course["prerequisites"] = prereqs;
    
    return course;
}

// 添加教学班行
void CourseDialog::on_pushButton_addClass_clicked()
{
    int row = ui->tableWidget_classes->rowCount();
    ui->tableWidget_classes->insertRow(row);
    
    // 教师
    QTableWidgetItem *teacherItem = new QTableWidgetItem;
    ui->tableWidget_classes->setItem(row, 0, teacherItem);
    
    // 上课时间
    QTableWidgetItem *timeItem = new QTableWidgetItem;
    ui->tableWidget_classes->setItem(row, 1, timeItem);
    
    // 删除按钮
    QPushButton *deleteButton = new QPushButton("删除");
    ui->tableWidget_classes->setCellWidget(row, 2, deleteButton);
    
    // 连接删除信号
    connect(deleteButton, &QPushButton::clicked, [this, row]() {
        if (row >= 0 && row < ui->tableWidget_classes->rowCount()) {
            ui->tableWidget_classes->removeRow(row);
        }
    });
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
