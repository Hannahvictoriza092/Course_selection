#ifndef CLASSTIMEDIALOG_H
#define CLASSTIMEDIALOG_H

#include <QDialog>
#include <QCheckBox>
#include <QMessageBox>
#include <QJsonObject>

namespace Ui {
class ClassTimeDialog;
}

class ClassTimeDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ClassTimeDialog(QWidget *parent = nullptr);
    explicit ClassTimeDialog(const QJsonObject &classData, QWidget *parent = nullptr);
    ~ClassTimeDialog();

    QJsonObject getClassData() const;
    void clearLayout(QLayout* layout);

private slots:
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();

private:
    Ui::ClassTimeDialog *ui;
    QList<QList<QCheckBox*>> dailyClassCheckBoxes; // [0-6][0-12] 对应周一至周日，每节课的复选框
    QList<QCheckBox*> weekCheckboxes;

    void initUI();
    void setupCheckboxes();
    QList<int> getSelectedDailyPeriodsMasks() const;
    int getSelectedWeeksMask() const;
    void loadClassData(const QJsonObject &classData);
};

#endif // CLASSTIMEDIALOG_H