#include "classtimedialog.h"
#include "ui_classtimedialog.h"
#include <QJsonArray>
#include <QDebug>

ClassTimeDialog::ClassTimeDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ClassTimeDialog)
{
    ui->setupUi(this);
    initUI();
    setupCheckboxes();
}

ClassTimeDialog::ClassTimeDialog(const QJsonObject &classData, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ClassTimeDialog)
{
    ui->setupUi(this);
    initUI();
    setupCheckboxes();
    loadClassData(classData);
    this->update(); // 强制刷新 UI 显示勾选状态
}

ClassTimeDialog::~ClassTimeDialog()
{
    delete ui;
}

void ClassTimeDialog::initUI()
{
    // 设置窗口固定大小
    setFixedSize(500, 400);
}

void ClassTimeDialog::setupCheckboxes()
{
    // 准备 layout 数组
    QGridLayout* dayLayouts[7] = {
        ui->gridLayout_monday, ui->gridLayout_tuesday, ui->gridLayout_wednesday,
        ui->gridLayout_thursday, ui->gridLayout_friday, ui->gridLayout_saturday, ui->gridLayout_sunday
    };

    // 清空旧控件
    for (int i = 0; i < 7; ++i) clearLayout(dayLayouts[i]);
    clearLayout(ui->gridLayout_weeks);

    // 生成节次复选框
    dailyClassCheckBoxes.clear();
    for (int day = 0; day < 7; ++day) {
        QList<QCheckBox*> dayCheckBoxes;
        for (int period = 1; period <= 13; ++period) {
            QCheckBox *checkbox = new QCheckBox(QString::number(period), this);
            dayCheckBoxes.append(checkbox);
            dayLayouts[day]->addWidget(checkbox, (period-1)/7, (period-1)%7);
        }
        dailyClassCheckBoxes.append(dayCheckBoxes);
    }

    // 生成周数复选框
    weekCheckboxes.clear();
    for (int i = 1; i <= 18; ++i) {
        QCheckBox *checkbox = new QCheckBox(QString::number(i), this);
        weekCheckboxes.append(checkbox);
        ui->gridLayout_weeks->addWidget(checkbox, (i-1)/9, (i-1)%9);
    }
}

void ClassTimeDialog::clearLayout(QLayout* layout) {
    while (QLayoutItem* item = layout->takeAt(0)) {
        if (QWidget* widget = item->widget()) {
            layout->removeWidget(widget);
            delete widget;
        }
        delete item;
    }
}

QList<int> ClassTimeDialog::getSelectedDailyPeriodsMasks() const
{
    QList<int> masks;
    for (int day = 0; day < 7; ++day) {
        int mask = 0;
        for (int period = 0; period < 13; ++period) {
            if (dailyClassCheckBoxes[day][period]->isChecked()) {
                mask |= (1 << period); // 第period个复选框对应2^period
            }
        }
        masks.append(mask);
    }
    return masks;
}

int ClassTimeDialog::getSelectedWeeksMask() const
{
    int mask = 0;
    for (int i = 0; i < weekCheckboxes.size(); ++i) {
        if (weekCheckboxes[i]->isChecked()) {
            mask |= (1 << i); // 第i个复选框对应2^i
        }
    }
    return mask;
}

void ClassTimeDialog::loadClassData(const QJsonObject &classData)
{
    // 加载教师名称
    ui->lineEdit_teacher->setText(classData["teacher"].toString());

    // 加载每日课时选择
    QJsonArray timesArray = classData["times"].toArray();
    for (int day = 0; day < qMin(7, timesArray.size()); ++day) {
        int periodsMask = timesArray[day].toInt();
        for (int period = 0; period < 13; ++period) {
            if (periodsMask & (1 << period)) {
                dailyClassCheckBoxes[day][period]->setChecked(true);
            }
        }
    }

    // 加载周数选择
    int weeksMask = classData["weekMask"].toInt();
    for (int i = 0; i < weekCheckboxes.size(); ++i) {
        if (weeksMask & (1 << i)) {
            weekCheckboxes[i]->setChecked(true);
        }
    }
}

QJsonObject ClassTimeDialog::getClassData() const
{
    QJsonObject data;
    data["teacher"] = ui->lineEdit_teacher->text();

    // 存储每日课时掩码
    QJsonArray timesArray;
    QList<int> masks = getSelectedDailyPeriodsMasks();
    for (int mask : masks) {
        timesArray.append(mask);
    }
    data["times"] = timesArray;

    // 存储周数掩码
    data["weekMask"] = getSelectedWeeksMask();
    return data;
}

void ClassTimeDialog::on_buttonBox_accepted()
{
    // 验证教师名称不为空
    if (ui->lineEdit_teacher->text().trimmed().isEmpty()) {
        QMessageBox::warning(this, "错误", "教师名称不能为空");
        return;
    }

    // 验证至少选择一个课时
    bool hasClassSelected = false;
    QList<int> masks = getSelectedDailyPeriodsMasks();
    for (int mask : masks) {
        if (mask != 0) {
            hasClassSelected = true;
            break;
        }
    }

    if (!hasClassSelected) {
        QMessageBox::warning(this, "错误", "请至少选择一个上课时间");
        return;
    }

    accept();
}

void ClassTimeDialog::on_buttonBox_rejected()
{
    reject();
}