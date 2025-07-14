/********************************************************************************
** Form generated from reading UI file 'classtimedialog.ui'
**
** Created by: Qt User Interface Compiler version 6.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CLASSTIMEDIALOG_H
#define UI_CLASSTIMEDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ClassTimeDialog
{
public:
    QVBoxLayout *verticalLayout;
    QFormLayout *formLayout;
    QLabel *label_teacher;
    QLineEdit *lineEdit_teacher;
    QLabel *label_weekday;
    QTabWidget *tabWidget_weekdays;
    QWidget *tab_monday;
    QVBoxLayout *verticalLayout_monday;
    QScrollArea *scrollArea_monday;
    QWidget *scrollAreaWidgetContents_monday;
    QGridLayout *gridLayout_monday;
    QWidget *tab_tuesday;
    QVBoxLayout *verticalLayout_tuesday;
    QScrollArea *scrollArea_tuesday;
    QWidget *scrollAreaWidgetContents_tuesday;
    QGridLayout *gridLayout_tuesday;
    QWidget *tab_wednesday;
    QVBoxLayout *verticalLayout_wednesday;
    QScrollArea *scrollArea_wednesday;
    QWidget *scrollAreaWidgetContents_wednesday;
    QGridLayout *gridLayout_wednesday;
    QWidget *tab_thursday;
    QVBoxLayout *verticalLayout_thursday;
    QScrollArea *scrollArea_thursday;
    QWidget *scrollAreaWidgetContents_thursday;
    QGridLayout *gridLayout_thursday;
    QWidget *tab_friday;
    QVBoxLayout *verticalLayout_friday;
    QScrollArea *scrollArea_friday;
    QWidget *scrollAreaWidgetContents_friday;
    QGridLayout *gridLayout_friday;
    QWidget *tab_saturday;
    QVBoxLayout *verticalLayout_saturday;
    QScrollArea *scrollArea_saturday;
    QWidget *scrollAreaWidgetContents_saturday;
    QGridLayout *gridLayout_saturday;
    QWidget *tab_sunday;
    QVBoxLayout *verticalLayout_sunday;
    QScrollArea *scrollArea_sunday;
    QWidget *scrollAreaWidgetContents_sunday;
    QGridLayout *gridLayout_sunday;
    QLabel *label_classes;
    QScrollArea *scrollArea_classes;
    QWidget *scrollAreaWidgetContents_classes;
    QGridLayout *gridLayout_classes;
    QLabel *label_weeks;
    QScrollArea *scrollArea_weeks;
    QWidget *scrollAreaWidgetContents_weeks;
    QGridLayout *gridLayout_weeks;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *ClassTimeDialog)
    {
        if (ClassTimeDialog->objectName().isEmpty())
            ClassTimeDialog->setObjectName("ClassTimeDialog");
        ClassTimeDialog->resize(500, 400);
        verticalLayout = new QVBoxLayout(ClassTimeDialog);
        verticalLayout->setObjectName("verticalLayout");
        formLayout = new QFormLayout();
        formLayout->setObjectName("formLayout");
        label_teacher = new QLabel(ClassTimeDialog);
        label_teacher->setObjectName("label_teacher");

        formLayout->setWidget(0, QFormLayout::ItemRole::LabelRole, label_teacher);

        lineEdit_teacher = new QLineEdit(ClassTimeDialog);
        lineEdit_teacher->setObjectName("lineEdit_teacher");

        formLayout->setWidget(0, QFormLayout::ItemRole::FieldRole, lineEdit_teacher);


        verticalLayout->addLayout(formLayout);

        label_weekday = new QLabel(ClassTimeDialog);
        label_weekday->setObjectName("label_weekday");

        verticalLayout->addWidget(label_weekday);

        tabWidget_weekdays = new QTabWidget(ClassTimeDialog);
        tabWidget_weekdays->setObjectName("tabWidget_weekdays");
        tab_monday = new QWidget();
        tab_monday->setObjectName("tab_monday");
        verticalLayout_monday = new QVBoxLayout(tab_monday);
        verticalLayout_monday->setObjectName("verticalLayout_monday");
        scrollArea_monday = new QScrollArea(tab_monday);
        scrollArea_monday->setObjectName("scrollArea_monday");
        scrollArea_monday->setWidgetResizable(true);
        scrollAreaWidgetContents_monday = new QWidget();
        scrollAreaWidgetContents_monday->setObjectName("scrollAreaWidgetContents_monday");
        gridLayout_monday = new QGridLayout(scrollAreaWidgetContents_monday);
        gridLayout_monday->setObjectName("gridLayout_monday");
        scrollArea_monday->setWidget(scrollAreaWidgetContents_monday);

        verticalLayout_monday->addWidget(scrollArea_monday);

        tabWidget_weekdays->addTab(tab_monday, QString());
        tab_tuesday = new QWidget();
        tab_tuesday->setObjectName("tab_tuesday");
        verticalLayout_tuesday = new QVBoxLayout(tab_tuesday);
        verticalLayout_tuesday->setObjectName("verticalLayout_tuesday");
        scrollArea_tuesday = new QScrollArea(tab_tuesday);
        scrollArea_tuesday->setObjectName("scrollArea_tuesday");
        scrollArea_tuesday->setWidgetResizable(true);
        scrollAreaWidgetContents_tuesday = new QWidget();
        scrollAreaWidgetContents_tuesday->setObjectName("scrollAreaWidgetContents_tuesday");
        gridLayout_tuesday = new QGridLayout(scrollAreaWidgetContents_tuesday);
        gridLayout_tuesday->setObjectName("gridLayout_tuesday");
        scrollArea_tuesday->setWidget(scrollAreaWidgetContents_tuesday);

        verticalLayout_tuesday->addWidget(scrollArea_tuesday);

        tabWidget_weekdays->addTab(tab_tuesday, QString());
        tab_wednesday = new QWidget();
        tab_wednesday->setObjectName("tab_wednesday");
        verticalLayout_wednesday = new QVBoxLayout(tab_wednesday);
        verticalLayout_wednesday->setObjectName("verticalLayout_wednesday");
        scrollArea_wednesday = new QScrollArea(tab_wednesday);
        scrollArea_wednesday->setObjectName("scrollArea_wednesday");
        scrollArea_wednesday->setWidgetResizable(true);
        scrollAreaWidgetContents_wednesday = new QWidget();
        scrollAreaWidgetContents_wednesday->setObjectName("scrollAreaWidgetContents_wednesday");
        gridLayout_wednesday = new QGridLayout(scrollAreaWidgetContents_wednesday);
        gridLayout_wednesday->setObjectName("gridLayout_wednesday");
        scrollArea_wednesday->setWidget(scrollAreaWidgetContents_wednesday);

        verticalLayout_wednesday->addWidget(scrollArea_wednesday);

        tabWidget_weekdays->addTab(tab_wednesday, QString());
        tab_thursday = new QWidget();
        tab_thursday->setObjectName("tab_thursday");
        verticalLayout_thursday = new QVBoxLayout(tab_thursday);
        verticalLayout_thursday->setObjectName("verticalLayout_thursday");
        scrollArea_thursday = new QScrollArea(tab_thursday);
        scrollArea_thursday->setObjectName("scrollArea_thursday");
        scrollArea_thursday->setWidgetResizable(true);
        scrollAreaWidgetContents_thursday = new QWidget();
        scrollAreaWidgetContents_thursday->setObjectName("scrollAreaWidgetContents_thursday");
        gridLayout_thursday = new QGridLayout(scrollAreaWidgetContents_thursday);
        gridLayout_thursday->setObjectName("gridLayout_thursday");
        scrollArea_thursday->setWidget(scrollAreaWidgetContents_thursday);

        verticalLayout_thursday->addWidget(scrollArea_thursday);

        tabWidget_weekdays->addTab(tab_thursday, QString());
        tab_friday = new QWidget();
        tab_friday->setObjectName("tab_friday");
        verticalLayout_friday = new QVBoxLayout(tab_friday);
        verticalLayout_friday->setObjectName("verticalLayout_friday");
        scrollArea_friday = new QScrollArea(tab_friday);
        scrollArea_friday->setObjectName("scrollArea_friday");
        scrollArea_friday->setWidgetResizable(true);
        scrollAreaWidgetContents_friday = new QWidget();
        scrollAreaWidgetContents_friday->setObjectName("scrollAreaWidgetContents_friday");
        gridLayout_friday = new QGridLayout(scrollAreaWidgetContents_friday);
        gridLayout_friday->setObjectName("gridLayout_friday");
        scrollArea_friday->setWidget(scrollAreaWidgetContents_friday);

        verticalLayout_friday->addWidget(scrollArea_friday);

        tabWidget_weekdays->addTab(tab_friday, QString());
        tab_saturday = new QWidget();
        tab_saturday->setObjectName("tab_saturday");
        verticalLayout_saturday = new QVBoxLayout(tab_saturday);
        verticalLayout_saturday->setObjectName("verticalLayout_saturday");
        scrollArea_saturday = new QScrollArea(tab_saturday);
        scrollArea_saturday->setObjectName("scrollArea_saturday");
        scrollArea_saturday->setWidgetResizable(true);
        scrollAreaWidgetContents_saturday = new QWidget();
        scrollAreaWidgetContents_saturday->setObjectName("scrollAreaWidgetContents_saturday");
        gridLayout_saturday = new QGridLayout(scrollAreaWidgetContents_saturday);
        gridLayout_saturday->setObjectName("gridLayout_saturday");
        scrollArea_saturday->setWidget(scrollAreaWidgetContents_saturday);

        verticalLayout_saturday->addWidget(scrollArea_saturday);

        tabWidget_weekdays->addTab(tab_saturday, QString());
        tab_sunday = new QWidget();
        tab_sunday->setObjectName("tab_sunday");
        verticalLayout_sunday = new QVBoxLayout(tab_sunday);
        verticalLayout_sunday->setObjectName("verticalLayout_sunday");
        scrollArea_sunday = new QScrollArea(tab_sunday);
        scrollArea_sunday->setObjectName("scrollArea_sunday");
        scrollArea_sunday->setWidgetResizable(true);
        scrollAreaWidgetContents_sunday = new QWidget();
        scrollAreaWidgetContents_sunday->setObjectName("scrollAreaWidgetContents_sunday");
        gridLayout_sunday = new QGridLayout(scrollAreaWidgetContents_sunday);
        gridLayout_sunday->setObjectName("gridLayout_sunday");
        scrollArea_sunday->setWidget(scrollAreaWidgetContents_sunday);

        verticalLayout_sunday->addWidget(scrollArea_sunday);

        tabWidget_weekdays->addTab(tab_sunday, QString());

        verticalLayout->addWidget(tabWidget_weekdays);

        label_classes = new QLabel(ClassTimeDialog);
        label_classes->setObjectName("label_classes");

        verticalLayout->addWidget(label_classes);

        scrollArea_classes = new QScrollArea(ClassTimeDialog);
        scrollArea_classes->setObjectName("scrollArea_classes");
        scrollArea_classes->setWidgetResizable(true);
        scrollAreaWidgetContents_classes = new QWidget();
        scrollAreaWidgetContents_classes->setObjectName("scrollAreaWidgetContents_classes");
        gridLayout_classes = new QGridLayout(scrollAreaWidgetContents_classes);
        gridLayout_classes->setObjectName("gridLayout_classes");
        scrollArea_classes->setWidget(scrollAreaWidgetContents_classes);

        verticalLayout->addWidget(scrollArea_classes);

        label_weeks = new QLabel(ClassTimeDialog);
        label_weeks->setObjectName("label_weeks");

        verticalLayout->addWidget(label_weeks);

        scrollArea_weeks = new QScrollArea(ClassTimeDialog);
        scrollArea_weeks->setObjectName("scrollArea_weeks");
        scrollArea_weeks->setWidgetResizable(true);
        scrollAreaWidgetContents_weeks = new QWidget();
        scrollAreaWidgetContents_weeks->setObjectName("scrollAreaWidgetContents_weeks");
        gridLayout_weeks = new QGridLayout(scrollAreaWidgetContents_weeks);
        gridLayout_weeks->setObjectName("gridLayout_weeks");
        scrollArea_weeks->setWidget(scrollAreaWidgetContents_weeks);

        verticalLayout->addWidget(scrollArea_weeks);

        buttonBox = new QDialogButtonBox(ClassTimeDialog);
        buttonBox->setObjectName("buttonBox");
        buttonBox->setStandardButtons(QDialogButtonBox::Ok|QDialogButtonBox::Cancel);

        verticalLayout->addWidget(buttonBox);


        retranslateUi(ClassTimeDialog);

        QMetaObject::connectSlotsByName(ClassTimeDialog);
    } // setupUi

    void retranslateUi(QDialog *ClassTimeDialog)
    {
        ClassTimeDialog->setWindowTitle(QCoreApplication::translate("ClassTimeDialog", "\350\256\276\347\275\256\344\270\212\350\257\276\346\227\266\351\227\264\345\222\214\345\221\250\346\225\260", nullptr));
        label_teacher->setText(QCoreApplication::translate("ClassTimeDialog", "\346\225\231\345\270\210:", nullptr));
        label_weekday->setText(QCoreApplication::translate("ClassTimeDialog", "\351\200\211\346\213\251\346\257\217\345\244\251\350\257\276\346\227\266:", nullptr));
        tabWidget_weekdays->setTabText(tabWidget_weekdays->indexOf(tab_monday), QCoreApplication::translate("ClassTimeDialog", "\345\221\250\344\270\200", nullptr));
        tabWidget_weekdays->setTabText(tabWidget_weekdays->indexOf(tab_tuesday), QCoreApplication::translate("ClassTimeDialog", "\345\221\250\344\272\214", nullptr));
        tabWidget_weekdays->setTabText(tabWidget_weekdays->indexOf(tab_wednesday), QCoreApplication::translate("ClassTimeDialog", "\345\221\250\344\270\211", nullptr));
        tabWidget_weekdays->setTabText(tabWidget_weekdays->indexOf(tab_thursday), QCoreApplication::translate("ClassTimeDialog", "\345\221\250\345\233\233", nullptr));
        tabWidget_weekdays->setTabText(tabWidget_weekdays->indexOf(tab_friday), QCoreApplication::translate("ClassTimeDialog", "\345\221\250\344\272\224", nullptr));
        tabWidget_weekdays->setTabText(tabWidget_weekdays->indexOf(tab_saturday), QCoreApplication::translate("ClassTimeDialog", "\345\221\250\345\205\255", nullptr));
        tabWidget_weekdays->setTabText(tabWidget_weekdays->indexOf(tab_sunday), QCoreApplication::translate("ClassTimeDialog", "\345\221\250\346\227\245", nullptr));
        label_classes->setText(QCoreApplication::translate("ClassTimeDialog", "\351\200\211\346\213\251\350\257\276\346\227\266 (1-14\350\212\202):", nullptr));
        label_weeks->setText(QCoreApplication::translate("ClassTimeDialog", "\351\200\211\346\213\251\345\221\250\346\225\260 (1-18\345\221\250):", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ClassTimeDialog: public Ui_ClassTimeDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CLASSTIMEDIALOG_H
