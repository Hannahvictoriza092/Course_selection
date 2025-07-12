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

    void on_actionGenerateSchedule_triggered();
    // 添加右键菜单槽函数
    void onCourseTableContextMenu(const QPoint &pos);
    void onEditCourseAction();
    void onDeleteCourseAction();
    
    // 添加课程对话框槽函数
    void onAddCourseDialogAccepted();

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
    // 添加课程对话框
    void showAddCourseDialog();
    void showEditCourseDialog(int row);
    
    // 课程操作函数
    void addCourseToData(const QJsonObject &newCourse);
    void updateCourseInData(const QJsonObject &updatedCourse);
    void removeCourseFromData(const QString &courseId);
    QJsonObject findCourseById(const QString &id);
};

#endif // MAINWINDOW_H