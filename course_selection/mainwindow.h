#ifndef MAINWINDOW_H
#include <QJsonArray>
#include <QJsonObject>
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
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

    //进行选课
    void on_actionGenerateSchedule_triggered();
    // 添加右键菜单槽函数
    void onCourseTableContextMenu(const QPoint &pos);
    void onEditCourseAction();
    void onDeleteCourseAction();
    
    // 添加课程对话框槽函数
    void onAddCourseDialogAccepted();
    void on_pushButton_search_clicked();
    void filterCourseData(const QString &id, const QString &teacher, const QString &name);

private:
    Ui::MainWindow *ui;
    CourseParser *courseParser;
    ScheduleExporter *scheduleExporter;
    CourseAlgorithm *courseAlgorithm;
    QJsonObject courseData;
    QJsonObject scheduleData;
    QString currentEditingCourseId;  // 用于编辑课程时记录当前编辑的课程ID

    void loadCourseData(const QString &filePath);
    void displayCourseData(const QJsonArray &filterCourses = QJsonArray());
    void displayScheduleData();
    // 添加课程对话框
    void showAddCourseDialog();
    void showEditCourseDialog(int row);
    
    
    // 课程操作函数
    void addCourseToData(const QJsonObject &newCourse);
    void updateCourseInData(const QJsonObject &updatedCourse);
    void removeOfferingFromData(const QString &courseId, const QString &teacher);
    int findActualCourseRow(int row) const;
    QJsonObject findCourseById(const QString &id);
};

#endif // MAINWINDOW_H