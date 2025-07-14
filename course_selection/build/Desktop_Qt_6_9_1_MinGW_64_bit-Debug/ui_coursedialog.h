/********************************************************************************
** Form generated from reading UI file 'coursedialog.ui'
**
** Created by: Qt User Interface Compiler version 6.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_COURSEDIALOG_H
#define UI_COURSEDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CourseDialog
{
public:
    QVBoxLayout *verticalLayout;
    QTabWidget *tabWidget;
    QWidget *basicInfoTab;
    QFormLayout *formLayout;
    QLabel *label_courseId;
    QLineEdit *lineEdit_courseId;
    QLabel *label_courseName;
    QLineEdit *lineEdit_courseName;
    QLabel *label_semester;
    QComboBox *comboBox_semester;
    QLabel *label_courseType;
    QComboBox *comboBox_courseType;
    QLabel *label_credits;
    QDoubleSpinBox *doubleSpinBox_credits;
    QWidget *classesTab;
    QVBoxLayout *verticalLayout_2;
    QTableWidget *tableWidget_classes;
    QPushButton *pushButton_addClass;
    QWidget *prerequisitesTab;
    QVBoxLayout *verticalLayout_3;
    QListWidget *listWidget_prerequisites;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton_addPrerequisite;
    QPushButton *pushButton_removePrerequisite;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *CourseDialog)
    {
        if (CourseDialog->objectName().isEmpty())
            CourseDialog->setObjectName("CourseDialog");
        CourseDialog->resize(600, 500);
        verticalLayout = new QVBoxLayout(CourseDialog);
        verticalLayout->setObjectName("verticalLayout");
        tabWidget = new QTabWidget(CourseDialog);
        tabWidget->setObjectName("tabWidget");
        basicInfoTab = new QWidget();
        basicInfoTab->setObjectName("basicInfoTab");
        formLayout = new QFormLayout(basicInfoTab);
        formLayout->setObjectName("formLayout");
        label_courseId = new QLabel(basicInfoTab);
        label_courseId->setObjectName("label_courseId");

        formLayout->setWidget(0, QFormLayout::ItemRole::LabelRole, label_courseId);

        lineEdit_courseId = new QLineEdit(basicInfoTab);
        lineEdit_courseId->setObjectName("lineEdit_courseId");

        formLayout->setWidget(0, QFormLayout::ItemRole::FieldRole, lineEdit_courseId);

        label_courseName = new QLabel(basicInfoTab);
        label_courseName->setObjectName("label_courseName");

        formLayout->setWidget(1, QFormLayout::ItemRole::LabelRole, label_courseName);

        lineEdit_courseName = new QLineEdit(basicInfoTab);
        lineEdit_courseName->setObjectName("lineEdit_courseName");

        formLayout->setWidget(1, QFormLayout::ItemRole::FieldRole, lineEdit_courseName);

        label_semester = new QLabel(basicInfoTab);
        label_semester->setObjectName("label_semester");

        formLayout->setWidget(2, QFormLayout::ItemRole::LabelRole, label_semester);

        comboBox_semester = new QComboBox(basicInfoTab);
        comboBox_semester->setObjectName("comboBox_semester");

        formLayout->setWidget(2, QFormLayout::ItemRole::FieldRole, comboBox_semester);

        label_courseType = new QLabel(basicInfoTab);
        label_courseType->setObjectName("label_courseType");

        formLayout->setWidget(3, QFormLayout::ItemRole::LabelRole, label_courseType);

        comboBox_courseType = new QComboBox(basicInfoTab);
        comboBox_courseType->setObjectName("comboBox_courseType");

        formLayout->setWidget(3, QFormLayout::ItemRole::FieldRole, comboBox_courseType);

        label_credits = new QLabel(basicInfoTab);
        label_credits->setObjectName("label_credits");

        formLayout->setWidget(4, QFormLayout::ItemRole::LabelRole, label_credits);

        doubleSpinBox_credits = new QDoubleSpinBox(basicInfoTab);
        doubleSpinBox_credits->setObjectName("doubleSpinBox_credits");
        doubleSpinBox_credits->setMinimum(0.500000000000000);
        doubleSpinBox_credits->setMaximum(10.000000000000000);
        doubleSpinBox_credits->setSingleStep(0.500000000000000);

        formLayout->setWidget(4, QFormLayout::ItemRole::FieldRole, doubleSpinBox_credits);

        tabWidget->addTab(basicInfoTab, QString());
        classesTab = new QWidget();
        classesTab->setObjectName("classesTab");
        verticalLayout_2 = new QVBoxLayout(classesTab);
        verticalLayout_2->setObjectName("verticalLayout_2");
        tableWidget_classes = new QTableWidget(classesTab);
        if (tableWidget_classes->columnCount() < 3)
            tableWidget_classes->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget_classes->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget_classes->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget_classes->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        tableWidget_classes->setObjectName("tableWidget_classes");
        tableWidget_classes->setColumnCount(3);

        verticalLayout_2->addWidget(tableWidget_classes);

        pushButton_addClass = new QPushButton(classesTab);
        pushButton_addClass->setObjectName("pushButton_addClass");

        verticalLayout_2->addWidget(pushButton_addClass);

        tabWidget->addTab(classesTab, QString());
        prerequisitesTab = new QWidget();
        prerequisitesTab->setObjectName("prerequisitesTab");
        verticalLayout_3 = new QVBoxLayout(prerequisitesTab);
        verticalLayout_3->setObjectName("verticalLayout_3");
        listWidget_prerequisites = new QListWidget(prerequisitesTab);
        listWidget_prerequisites->setObjectName("listWidget_prerequisites");

        verticalLayout_3->addWidget(listWidget_prerequisites);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        pushButton_addPrerequisite = new QPushButton(prerequisitesTab);
        pushButton_addPrerequisite->setObjectName("pushButton_addPrerequisite");

        horizontalLayout->addWidget(pushButton_addPrerequisite);

        pushButton_removePrerequisite = new QPushButton(prerequisitesTab);
        pushButton_removePrerequisite->setObjectName("pushButton_removePrerequisite");

        horizontalLayout->addWidget(pushButton_removePrerequisite);


        verticalLayout_3->addLayout(horizontalLayout);

        tabWidget->addTab(prerequisitesTab, QString());

        verticalLayout->addWidget(tabWidget);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        buttonBox = new QDialogButtonBox(CourseDialog);
        buttonBox->setObjectName("buttonBox");
        buttonBox->setStandardButtons(QDialogButtonBox::Ok|QDialogButtonBox::Cancel);

        horizontalLayout_2->addWidget(buttonBox);


        verticalLayout->addLayout(horizontalLayout_2);


        retranslateUi(CourseDialog);
        QObject::connect(buttonBox, &QDialogButtonBox::accepted, CourseDialog, qOverload<>(&QDialog::accept));
        QObject::connect(buttonBox, &QDialogButtonBox::rejected, CourseDialog, qOverload<>(&QDialog::reject));

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(CourseDialog);
    } // setupUi

    void retranslateUi(QDialog *CourseDialog)
    {
        CourseDialog->setWindowTitle(QCoreApplication::translate("CourseDialog", "\350\257\276\347\250\213\347\274\226\350\276\221", nullptr));
        label_courseId->setText(QCoreApplication::translate("CourseDialog", "\350\257\276\347\250\213ID:", nullptr));
        label_courseName->setText(QCoreApplication::translate("CourseDialog", "\350\257\276\347\250\213\345\220\215\347\247\260:", nullptr));
        label_semester->setText(QCoreApplication::translate("CourseDialog", "\345\255\246\346\234\237:", nullptr));
        label_courseType->setText(QCoreApplication::translate("CourseDialog", "\350\257\276\347\250\213\347\261\273\345\236\213:", nullptr));
        label_credits->setText(QCoreApplication::translate("CourseDialog", "\345\255\246\345\210\206:", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(basicInfoTab), QCoreApplication::translate("CourseDialog", "\345\237\272\346\234\254\344\277\241\346\201\257", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget_classes->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("CourseDialog", "\346\225\231\345\270\210", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget_classes->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("CourseDialog", "\344\270\212\350\257\276\346\227\266\351\227\264", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget_classes->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("CourseDialog", "\344\270\212\350\257\276\345\221\250\346\225\260", nullptr));
        pushButton_addClass->setText(QCoreApplication::translate("CourseDialog", "\346\267\273\345\212\240\346\225\231\345\255\246\347\217\255", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(classesTab), QCoreApplication::translate("CourseDialog", "\346\225\231\345\255\246\347\217\255", nullptr));
        pushButton_addPrerequisite->setText(QCoreApplication::translate("CourseDialog", "\346\267\273\345\212\240\345\211\215\347\275\256\350\257\276\347\250\213", nullptr));
        pushButton_removePrerequisite->setText(QCoreApplication::translate("CourseDialog", "\347\247\273\351\231\244\345\211\215\347\275\256\350\257\276\347\250\213", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(prerequisitesTab), QCoreApplication::translate("CourseDialog", "\345\211\215\347\275\256\350\257\276\347\250\213", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CourseDialog: public Ui_CourseDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_COURSEDIALOG_H
