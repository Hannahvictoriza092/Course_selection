#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidget>
#include <QSpinBox>
#include <QJsonObject>

namespace Ui {
class MainWindow;
}

class CourseParser;
class ScheduleExporter;
class CourseAlgorithm;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionImportCourse_triggered();
    void on_actionExportSchedule_triggered();
    void on_actionAddCourse_triggered();
    void on_actionEditCourse_triggered();
    void on_actionDeleteCourse_triggered();
    void on_actionGenerateSchedule_triggered();

private:
    Ui::MainWindow *ui;
    CourseParser *courseParser;
    ScheduleExporter *scheduleExporter;
    CourseAlgorithm *courseAlgorithm;
    QJsonObject courseData;
    QJsonObject scheduleData;

    void initCourseTable();
    void initScheduleTable();
    void loadCourseData(const QString &filePath);
    void displayCourseData();
    void displayScheduleData();
};

#endif // MAINWINDOW_H