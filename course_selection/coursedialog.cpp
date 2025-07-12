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
        on_pushButton_addClass_clicked();
        
        int row = ui->tableWidget_classes->rowCount() - 1;
        ui->tableWidget_classes->item(row, 0)->setText(obj["teacher"].toString());
        
        // 设置时间数据（简化示例）
        QString timeStr;
        QJsonArray times = obj["times"].toArray();
        for (const auto &time : times) {
            timeStr += QString::number(time.toInt()) + ",";
        }
        if (!timeStr.isEmpty()) timeStr.chop(1);
        ui->tableWidget_classes->item(row, 1)->setText(timeStr);
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
    
    connect(deleteButton, &QPushButton::clicked, [this, row]() {
        ui->tableWidget_classes->removeRow(row);
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