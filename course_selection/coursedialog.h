// coursedialog.h
#include <QDialog>
#include <QMessageBox>
#include <QJsonObject>
#include <QList>
#include <QTableWidgetItem>
#include <QString>
#include "classtimedialog.h"

namespace Ui {
class CourseDialog;
}

class CourseDialog : public QDialog {
    Q_OBJECT

public:
    explicit CourseDialog(QWidget *parent = nullptr);
    ~CourseDialog();
    
    void setCourseData(const QJsonObject &course);
    QJsonObject getCourseData() const;

    void accept() override;  // 重写 accept 函数

    void setAddMode();  // 设置为添加模式


private slots:
    void on_pushButton_addClass_clicked();
    void on_pushButton_addPrerequisite_clicked();
    void on_pushButton_removePrerequisite_clicked();
    // 修正QTableWidgetItem拼写
    void on_tableWidget_classes_itemDoubleClicked(QTableWidgetItem *item);
    


private:
    Ui::CourseDialog *ui;
    QJsonObject courseData;
    bool isEditMode;
    struct ClassSection {
        QString teacher;
        int times[7];
        int weekMask;
    };

    QList<ClassSection> classSections;
    void updateClassTable();
    QString formatTimeString(const int times[7], int weekMask);
    void setupTimeSlotWidgets();
};
