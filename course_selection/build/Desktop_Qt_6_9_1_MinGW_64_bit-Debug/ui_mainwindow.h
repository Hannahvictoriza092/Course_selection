/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionImportCourse;
    QAction *actionExportSchedule;
    QAction *actionExit;
    QAction *actionAddCourse;
    QAction *actionEditCourse;
    QAction *actionDeleteCourse;
    QAction *actionGenerateSchedule;
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    QTabWidget *tabWidget;
    QWidget *courseTab;
    QVBoxLayout *verticalLayout_2;
    QTableWidget *courseTableWidget;
    QWidget *scheduleTab;
    QVBoxLayout *verticalLayout_3;
    QTableWidget *scheduleTableWidget;
    QWidget *settingsTab;
    QVBoxLayout *verticalLayout_4;
    QGroupBox *creditGroupBox;
    QFormLayout *formLayout;
    QLabel *label;
    QSpinBox *creditSpinBox;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuCourse;
    QMenu *menuSchedule;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1024, 768);
        MainWindow->setStyleSheet(QString::fromUtf8("QMainWindow { background-color:rgba(255, 255, 255, 0.72); }"));
        actionImportCourse = new QAction(MainWindow);
        actionImportCourse->setObjectName("actionImportCourse");
        actionExportSchedule = new QAction(MainWindow);
        actionExportSchedule->setObjectName("actionExportSchedule");
        actionExit = new QAction(MainWindow);
        actionExit->setObjectName("actionExit");
        actionAddCourse = new QAction(MainWindow);
        actionAddCourse->setObjectName("actionAddCourse");
        actionEditCourse = new QAction(MainWindow);
        actionEditCourse->setObjectName("actionEditCourse");
        actionDeleteCourse = new QAction(MainWindow);
        actionDeleteCourse->setObjectName("actionDeleteCourse");
        actionGenerateSchedule = new QAction(MainWindow);
        actionGenerateSchedule->setObjectName("actionGenerateSchedule");
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName("centralWidget");
        centralWidget->setStyleSheet(QString::fromUtf8("background-color:rgba(255, 255, 255, 0.59);"));
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName("verticalLayout");
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName("tabWidget");
        tabWidget->setStyleSheet(QString::fromUtf8("QTabBar::tab { background-color: #87abdd; color: white; padding: 8px; min-width: 80px; } QTabBar::tab:selected { background-color: #504cc4; }"));
        courseTab = new QWidget();
        courseTab->setObjectName("courseTab");
        verticalLayout_2 = new QVBoxLayout(courseTab);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName("verticalLayout_2");
        courseTableWidget = new QTableWidget(courseTab);
        courseTableWidget->setObjectName("courseTableWidget");
        courseTableWidget->setStyleSheet(QString::fromUtf8("QHeaderView::section { background-color: #ade6c5; padding: 4px; border: 1px solid #dddddd; } QTableWidget { background-color: white; alternate-background-color: #f5f5f5; }"));

        verticalLayout_2->addWidget(courseTableWidget);

        tabWidget->addTab(courseTab, QString());
        scheduleTab = new QWidget();
        scheduleTab->setObjectName("scheduleTab");
        verticalLayout_3 = new QVBoxLayout(scheduleTab);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName("verticalLayout_3");
        scheduleTableWidget = new QTableWidget(scheduleTab);
        scheduleTableWidget->setObjectName("scheduleTableWidget");
        scheduleTableWidget->setStyleSheet(QString::fromUtf8("QHeaderView::section { background-color: #ade6c5; padding: 4px; border: 1px solid #dddddd; } QTableWidget { background-color: white; alternate-background-color: #f5f5f5; }"));

        verticalLayout_3->addWidget(scheduleTableWidget);

        tabWidget->addTab(scheduleTab, QString());
        settingsTab = new QWidget();
        settingsTab->setObjectName("settingsTab");
        verticalLayout_4 = new QVBoxLayout(settingsTab);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName("verticalLayout_4");
        creditGroupBox = new QGroupBox(settingsTab);
        creditGroupBox->setObjectName("creditGroupBox");
        creditGroupBox->setStyleSheet(QString::fromUtf8("QGroupBox { color: #438b73; font-weight: bold; border: 1px solid #ade6c5; border-radius: 4px; margin-top: 1ex; padding-top: 0.5ex; } QGroupBox::title { subcontrol-origin: margin; left: 10px; padding: 0 3px 0 3px; }"));
        formLayout = new QFormLayout(creditGroupBox);
        formLayout->setSpacing(6);
        formLayout->setContentsMargins(11, 11, 11, 11);
        formLayout->setObjectName("formLayout");
        label = new QLabel(creditGroupBox);
        label->setObjectName("label");

        formLayout->setWidget(0, QFormLayout::ItemRole::LabelRole, label);

        creditSpinBox = new QSpinBox(creditGroupBox);
        creditSpinBox->setObjectName("creditSpinBox");
        creditSpinBox->setMinimum(100);
        creditSpinBox->setMaximum(300);
        creditSpinBox->setValue(100);

        formLayout->setWidget(0, QFormLayout::ItemRole::FieldRole, creditSpinBox);


        verticalLayout_4->addWidget(creditGroupBox);

        tabWidget->addTab(settingsTab, QString());

        verticalLayout->addWidget(tabWidget);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName("menuBar");
        menuBar->setGeometry(QRect(0, 0, 1024, 17));
        menuBar->setStyleSheet(QString::fromUtf8("background-color: #438b73; color: white;"));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName("menuFile");
        menuCourse = new QMenu(menuBar);
        menuCourse->setObjectName("menuCourse");
        menuSchedule = new QMenu(menuBar);
        menuSchedule->setObjectName("menuSchedule");
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName("mainToolBar");
        mainToolBar->setStyleSheet(QString::fromUtf8("QToolButton { background-color: #6acbac; color: white; border: none; padding: 6px 12px; border-radius: 4px; margin: 2px; } QToolButton:hover { background-color: #438b73; }"));
        MainWindow->addToolBar(Qt::ToolBarArea::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName("statusBar");
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuCourse->menuAction());
        menuBar->addAction(menuSchedule->menuAction());
        menuFile->addAction(actionImportCourse);
        menuFile->addAction(actionExportSchedule);
        menuFile->addAction(actionExit);
        menuCourse->addAction(actionAddCourse);
        menuCourse->addAction(actionEditCourse);
        menuCourse->addAction(actionDeleteCourse);
        menuSchedule->addAction(actionGenerateSchedule);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(2);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "\346\231\272\350\203\275\351\200\211\350\257\276\347\263\273\347\273\237", nullptr));
        actionImportCourse->setText(QCoreApplication::translate("MainWindow", "\345\257\274\345\205\245\350\257\276\347\250\213\346\225\260\346\215\256", nullptr));
        actionExportSchedule->setText(QCoreApplication::translate("MainWindow", "\345\257\274\345\207\272\351\200\211\350\257\276\346\226\271\346\241\210", nullptr));
        actionExit->setText(QCoreApplication::translate("MainWindow", "\351\200\200\345\207\272", nullptr));
        actionAddCourse->setText(QCoreApplication::translate("MainWindow", "\346\267\273\345\212\240\350\257\276\347\250\213", nullptr));
        actionEditCourse->setText(QCoreApplication::translate("MainWindow", "\347\274\226\350\276\221\350\257\276\347\250\213", nullptr));
        actionDeleteCourse->setText(QCoreApplication::translate("MainWindow", "\345\210\240\351\231\244\350\257\276\347\250\213", nullptr));
        actionGenerateSchedule->setText(QCoreApplication::translate("MainWindow", "\347\224\237\346\210\220\351\200\211\350\257\276\346\226\271\346\241\210", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(courseTab), QCoreApplication::translate("MainWindow", "\345\205\250\351\203\250\350\257\276\347\250\213", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(scheduleTab), QCoreApplication::translate("MainWindow", "\351\200\211\350\257\276\346\226\271\346\241\210", nullptr));
        creditGroupBox->setTitle(QCoreApplication::translate("MainWindow", "\345\255\246\345\210\206\350\256\276\347\275\256", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" color:#00006f;\">\346\200\273\345\255\246\345\210\206\344\270\213\351\231\220(\344\270\244\345\200\215\345\200\274):</span></p></body></html>", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(settingsTab), QCoreApplication::translate("MainWindow", "\347\263\273\347\273\237\350\256\276\347\275\256", nullptr));
        menuFile->setTitle(QCoreApplication::translate("MainWindow", "\346\226\207\344\273\266", nullptr));
        menuCourse->setTitle(QCoreApplication::translate("MainWindow", "\350\257\276\347\250\213", nullptr));
        menuSchedule->setTitle(QCoreApplication::translate("MainWindow", "\351\200\211\350\257\276", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
