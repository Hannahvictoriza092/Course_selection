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
    QStringList headers = {"课程ID", "名称", "学分(两倍)", "开课学期", "类型", "前置课程", "教师", "上课时间"};
    ui->courseTableWidget->setColumnCount(headers.size());
    ui->courseTableWidget->setHorizontalHeaderLabels(headers);
    ui->courseTableWidget->horizontalHeader()->setStretchLastSection(true);
    ui->courseTableWidget->resizeColumnsToContents();
}

void MainWindow::initScheduleTable()
{
    QStringList headers = {"课程ID", "名称", "选课学期", "上课时间", "教师"};
    ui->scheduleTableWidget->setColumnCount(headers.size());
    ui->scheduleTableWidget->setHorizontalHeaderLabels(headers);
    ui->scheduleTableWidget->horizontalHeader()->setStretchLastSection(true);
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
    for (int i = 0; i < courses.size(); ++i) {
        QJsonObject course = courses[i].toObject();
        ui->courseTableWidget->insertRow(i);
        ui->courseTableWidget->setItem(i, 0, new QTableWidgetItem(course["id"].toString()));
        ui->courseTableWidget->setItem(i, 1, new QTableWidgetItem(course["name"].toString()));
        ui->courseTableWidget->setItem(i, 2, new QTableWidgetItem(QString::number(course["credit"].toInt())));
        ui->courseTableWidget->setItem(i, 3, new QTableWidgetItem(QString::number(course["semester"].toInt())));
        ui->courseTableWidget->setItem(i, 4, new QTableWidgetItem(course["required"].toBool() ? "必修" : "选修"));

        QJsonArray prereqs = course["prerequisites"].toArray();
        QString prereqStr;
        for (const auto &prereq : prereqs) {
            prereqStr += prereq.toString() + ", ";
        }
        if (!prereqStr.isEmpty()) prereqStr.chop(2);
        ui->courseTableWidget->setItem(i, 5, new QTableWidgetItem(prereqStr));

        // 获取教师信息
        QJsonArray offerings = course["offerings"].toArray();
        QString teacher = offerings.size() > 0 ? offerings[0].toObject()["teacher"].toString() : "";
        ui->courseTableWidget->setItem(i, 6, new QTableWidgetItem(teacher));


        // 格式化上课时间
        if (offerings.size() > 0) {
            QJsonArray times = offerings[0].toObject()["times"].toArray();
            QString timeStr;
            for (const auto &time : times) {
                timeStr += QString::number(time.toInt()) + ", ";
            }
            if (!timeStr.isEmpty()) timeStr.chop(2);
            ui->courseTableWidget->setItem(i, 7, new QTableWidgetItem(timeStr));

        } else {
            ui->courseTableWidget->setItem(i, 7, new QTableWidgetItem(""));
        }
    }
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