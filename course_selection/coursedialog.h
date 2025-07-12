// coursedialog.h
#include <QDialog>
#include <QJsonObject>

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

private slots:
    void on_pushButton_addClass_clicked();
    void on_pushButton_addPrerequisite_clicked();
    void on_pushButton_removePrerequisite_clicked();


private:
    Ui::CourseDialog *ui;
    void setupTimeSlotWidgets();
};
