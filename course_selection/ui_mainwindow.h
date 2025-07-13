/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
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
    QHBoxLayout *searchLayout;
    QLineEdit *lineEdit_searchId;
    QLineEdit *lineEdit_searchTeacher;
    QLineEdit *lineEdit_searchName;
    QPushButton *pushButton_search;
    QLabel *label_noResults;
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
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1024, 768);
        MainWindow->setStyleSheet(QString::fromUtf8("QMainWindow { background-color:rgba(255, 255, 255, 0.72); }"));
        actionImportCourse = new QAction(MainWindow);
        actionImportCourse->setObjectName(QString::fromUtf8("actionImportCourse"));
        actionExportSchedule = new QAction(MainWindow);
        actionExportSchedule->setObjectName(QString::fromUtf8("actionExportSchedule"));
        actionExit = new QAction(MainWindow);
        actionExit->setObjectName(QString::fromUtf8("actionExit"));
        actionAddCourse = new QAction(MainWindow);
        actionAddCourse->setObjectName(QString::fromUtf8("actionAddCourse"));
        actionEditCourse = new QAction(MainWindow);
        actionEditCourse->setObjectName(QString::fromUtf8("actionEditCourse"));
        actionDeleteCourse = new QAction(MainWindow);
        actionDeleteCourse->setObjectName(QString::fromUtf8("actionDeleteCourse"));
        actionGenerateSchedule = new QAction(MainWindow);
        actionGenerateSchedule->setObjectName(QString::fromUtf8("actionGenerateSchedule"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        centralWidget->setStyleSheet(QString::fromUtf8("background-color:rgba(255, 255, 255, 0.59);"));
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setStyleSheet(QString::fromUtf8("QTabBar::tab { background-color: #87abdd; color: black; padding: 8px; min-width: 80px; } QTabBar::tab:selected { background-color: #504cc4; color: black; }"));
        courseTab = new QWidget();
        courseTab->setObjectName(QString::fromUtf8("courseTab"));
        verticalLayout_2 = new QVBoxLayout(courseTab);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        searchLayout = new QHBoxLayout();
        searchLayout->setSpacing(6);
        searchLayout->setObjectName(QString::fromUtf8("searchLayout"));
        lineEdit_searchId = new QLineEdit(courseTab);
        lineEdit_searchId->setObjectName(QString::fromUtf8("lineEdit_searchId"));
        lineEdit_searchId->setMinimumHeight(30);
        lineEdit_searchId->setStyleSheet(QString::fromUtf8("background-color: #ade6c5; color: black;"));

        searchLayout->addWidget(lineEdit_searchId);

        lineEdit_searchTeacher = new QLineEdit(courseTab);
        lineEdit_searchTeacher->setObjectName(QString::fromUtf8("lineEdit_searchTeacher"));
        lineEdit_searchTeacher->setMinimumHeight(30);
        lineEdit_searchTeacher->setStyleSheet(QString::fromUtf8("background-color: #ade6c5; color: black;"));

        searchLayout->addWidget(lineEdit_searchTeacher);

        lineEdit_searchName = new QLineEdit(courseTab);
        lineEdit_searchName->setObjectName(QString::fromUtf8("lineEdit_searchName"));
        lineEdit_searchName->setMinimumHeight(30);
        lineEdit_searchName->setStyleSheet(QString::fromUtf8("background-color: #ade6c5; color: black;"));

        searchLayout->addWidget(lineEdit_searchName);

        pushButton_search = new QPushButton(courseTab);
        pushButton_search->setObjectName(QString::fromUtf8("pushButton_search"));
        pushButton_search->setMinimumHeight(30);
        pushButton_search->setStyleSheet(QString::fromUtf8("background-color: #ade6c5; color: black;"));

        searchLayout->addWidget(pushButton_search);


        verticalLayout_2->addLayout(searchLayout);

        label_noResults = new QLabel(courseTab);
        label_noResults->setObjectName(QString::fromUtf8("label_noResults"));
        QFont font;
        font.setPointSize(16);
        font.setBold(true);
        font.setWeight(75);
        label_noResults->setFont(font);
        label_noResults->setStyleSheet(QString::fromUtf8("color: black;"));
        label_noResults->setAlignment(Qt::AlignCenter);
        label_noResults->setVisible(false);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label_noResults->sizePolicy().hasHeightForWidth());
        label_noResults->setSizePolicy(sizePolicy);

        verticalLayout_2->addWidget(label_noResults);

        courseTableWidget = new QTableWidget(courseTab);
        if (courseTableWidget->columnCount() < 8)
            courseTableWidget->setColumnCount(8);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        courseTableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        courseTableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        courseTableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        courseTableWidget->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        courseTableWidget->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        courseTableWidget->setHorizontalHeaderItem(5, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        courseTableWidget->setHorizontalHeaderItem(6, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        courseTableWidget->setHorizontalHeaderItem(7, __qtablewidgetitem7);
        courseTableWidget->setObjectName(QString::fromUtf8("courseTableWidget"));
        courseTableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
        courseTableWidget->setColumnCount(8);
        courseTableWidget->setStyleSheet(QString::fromUtf8("QTableWidget { color: black; font-weight: 500; }\n"
"QTableWidget::item { background-color:rgb(153, 181, 222); color: black; }\n"
"QTableWidget::item:alternate { background-color:rgb(179, 198, 222); color: black; }\n"
"QHeaderView::section { background-color: #f0f0f0; color: black; padding: 4px; border: 1px solid #dddddd; }"));
        courseTableWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        courseTableWidget->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);
        courseTableWidget->setWordWrap(true);
        courseTableWidget->setAlternatingRowColors(true);

        verticalLayout_2->addWidget(courseTableWidget);

        tabWidget->addTab(courseTab, QString());
        scheduleTab = new QWidget();
        scheduleTab->setObjectName(QString::fromUtf8("scheduleTab"));
        verticalLayout_3 = new QVBoxLayout(scheduleTab);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        scheduleTableWidget = new QTableWidget(scheduleTab);
        if (scheduleTableWidget->columnCount() < 7)
            scheduleTableWidget->setColumnCount(7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        scheduleTableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem8);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        scheduleTableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem9);
        QTableWidgetItem *__qtablewidgetitem10 = new QTableWidgetItem();
        scheduleTableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem10);
        QTableWidgetItem *__qtablewidgetitem11 = new QTableWidgetItem();
        scheduleTableWidget->setHorizontalHeaderItem(3, __qtablewidgetitem11);
        QTableWidgetItem *__qtablewidgetitem12 = new QTableWidgetItem();
        scheduleTableWidget->setHorizontalHeaderItem(4, __qtablewidgetitem12);
        QTableWidgetItem *__qtablewidgetitem13 = new QTableWidgetItem();
        scheduleTableWidget->setHorizontalHeaderItem(5, __qtablewidgetitem13);
        QTableWidgetItem *__qtablewidgetitem14 = new QTableWidgetItem();
        scheduleTableWidget->setHorizontalHeaderItem(6, __qtablewidgetitem14);
        if (scheduleTableWidget->rowCount() < 14)
            scheduleTableWidget->setRowCount(14);
        QTableWidgetItem *__qtablewidgetitem15 = new QTableWidgetItem();
        scheduleTableWidget->setVerticalHeaderItem(0, __qtablewidgetitem15);
        QTableWidgetItem *__qtablewidgetitem16 = new QTableWidgetItem();
        scheduleTableWidget->setVerticalHeaderItem(1, __qtablewidgetitem16);
        QTableWidgetItem *__qtablewidgetitem17 = new QTableWidgetItem();
        scheduleTableWidget->setVerticalHeaderItem(2, __qtablewidgetitem17);
        QTableWidgetItem *__qtablewidgetitem18 = new QTableWidgetItem();
        scheduleTableWidget->setVerticalHeaderItem(3, __qtablewidgetitem18);
        QTableWidgetItem *__qtablewidgetitem19 = new QTableWidgetItem();
        scheduleTableWidget->setVerticalHeaderItem(4, __qtablewidgetitem19);
        QTableWidgetItem *__qtablewidgetitem20 = new QTableWidgetItem();
        scheduleTableWidget->setVerticalHeaderItem(5, __qtablewidgetitem20);
        QTableWidgetItem *__qtablewidgetitem21 = new QTableWidgetItem();
        scheduleTableWidget->setVerticalHeaderItem(6, __qtablewidgetitem21);
        QTableWidgetItem *__qtablewidgetitem22 = new QTableWidgetItem();
        scheduleTableWidget->setVerticalHeaderItem(7, __qtablewidgetitem22);
        QTableWidgetItem *__qtablewidgetitem23 = new QTableWidgetItem();
        scheduleTableWidget->setVerticalHeaderItem(8, __qtablewidgetitem23);
        QTableWidgetItem *__qtablewidgetitem24 = new QTableWidgetItem();
        scheduleTableWidget->setVerticalHeaderItem(9, __qtablewidgetitem24);
        QTableWidgetItem *__qtablewidgetitem25 = new QTableWidgetItem();
        scheduleTableWidget->setVerticalHeaderItem(10, __qtablewidgetitem25);
        QTableWidgetItem *__qtablewidgetitem26 = new QTableWidgetItem();
        scheduleTableWidget->setVerticalHeaderItem(11, __qtablewidgetitem26);
        QTableWidgetItem *__qtablewidgetitem27 = new QTableWidgetItem();
        scheduleTableWidget->setVerticalHeaderItem(12, __qtablewidgetitem27);
        QTableWidgetItem *__qtablewidgetitem28 = new QTableWidgetItem();
        scheduleTableWidget->setVerticalHeaderItem(13, __qtablewidgetitem28);
        scheduleTableWidget->setObjectName(QString::fromUtf8("scheduleTableWidget"));
        scheduleTableWidget->setRowCount(14);
        scheduleTableWidget->setColumnCount(7);
        scheduleTableWidget->setStyleSheet(QString::fromUtf8("QHeaderView::section { background-color: #ade6c5; padding: 4px; border: 1px solid #dddddd; color: black; } \n"
"QTableWidget { background-color: white; alternate-background-color: #f5f5f5; color: black; }"));
        scheduleTableWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        scheduleTableWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);

        verticalLayout_3->addWidget(scheduleTableWidget);

        tabWidget->addTab(scheduleTab, QString());
        settingsTab = new QWidget();
        settingsTab->setObjectName(QString::fromUtf8("settingsTab"));
        verticalLayout_4 = new QVBoxLayout(settingsTab);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        creditGroupBox = new QGroupBox(settingsTab);
        creditGroupBox->setObjectName(QString::fromUtf8("creditGroupBox"));
        creditGroupBox->setStyleSheet(QString::fromUtf8("QGroupBox { color: black; font-weight: bold; border: 1px solid #ade6c5; border-radius: 4px; margin-top: 1ex; padding-top: 0.5ex; } QGroupBox::title { subcontrol-origin: margin; left: 10px; padding: 0 3px 0 3px; }"));
        formLayout = new QFormLayout(creditGroupBox);
        formLayout->setSpacing(6);
        formLayout->setContentsMargins(11, 11, 11, 11);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        label = new QLabel(creditGroupBox);
        label->setObjectName(QString::fromUtf8("label"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label);

        creditSpinBox = new QSpinBox(creditGroupBox);
        creditSpinBox->setObjectName(QString::fromUtf8("creditSpinBox"));
        creditSpinBox->setMinimum(100);
        creditSpinBox->setMaximum(300);
        creditSpinBox->setValue(100);
        creditSpinBox->setStyleSheet(QString::fromUtf8("color: black;"));

        formLayout->setWidget(0, QFormLayout::FieldRole, creditSpinBox);


        verticalLayout_4->addWidget(creditGroupBox);

        tabWidget->addTab(settingsTab, QString());

        verticalLayout->addWidget(tabWidget);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1024, 21));
        menuBar->setStyleSheet(QString::fromUtf8("background-color: #438b73; color: black;"));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        menuCourse = new QMenu(menuBar);
        menuCourse->setObjectName(QString::fromUtf8("menuCourse"));
        menuSchedule = new QMenu(menuBar);
        menuSchedule->setObjectName(QString::fromUtf8("menuSchedule"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        mainToolBar->setStyleSheet(QString::fromUtf8("QToolButton { background-color: #6acbac; color: black; border: none; padding: 6px 12px; border-radius: 4px; margin: 2px; } QToolButton:hover { background-color: #438b73; color: black; }"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuCourse->menuAction());
        menuBar->addAction(menuSchedule->menuAction());
        menuFile->addAction(actionImportCourse);
        menuFile->addAction(actionExportSchedule);
        menuFile->addAction(actionExit);
        menuCourse->addAction(actionAddCourse);
        menuSchedule->addAction(actionGenerateSchedule);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(0);


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
        lineEdit_searchId->setPlaceholderText(QCoreApplication::translate("MainWindow", "\350\257\276\347\250\213ID", nullptr));
        lineEdit_searchTeacher->setPlaceholderText(QCoreApplication::translate("MainWindow", "\346\225\231\345\270\210", nullptr));
        lineEdit_searchName->setPlaceholderText(QCoreApplication::translate("MainWindow", "\350\257\276\347\250\213\345\220\215", nullptr));
        pushButton_search->setText(QCoreApplication::translate("MainWindow", "\346\237\245\350\257\242", nullptr));
        label_noResults->setText(QCoreApplication::translate("MainWindow", "\346\227\240\345\214\271\351\205\215\347\273\223\346\236\234", nullptr));
        QTableWidgetItem *___qtablewidgetitem = courseTableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("MainWindow", "\345\274\200\350\257\276\345\255\246\346\234\237", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = courseTableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("MainWindow", "\350\257\276\347\250\213ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = courseTableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("MainWindow", "\350\257\276\347\250\213\345\220\215\347\247\260", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = courseTableWidget->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("MainWindow", "\350\257\276\347\250\213\347\261\273\345\210\253", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = courseTableWidget->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("MainWindow", "\346\225\231\345\270\210", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = courseTableWidget->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("MainWindow", "\344\270\212\350\257\276\346\227\266\351\227\264", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = courseTableWidget->horizontalHeaderItem(6);
        ___qtablewidgetitem6->setText(QCoreApplication::translate("MainWindow", "\345\255\246\345\210\206(\344\270\244\345\200\215)", nullptr));
        QTableWidgetItem *___qtablewidgetitem7 = courseTableWidget->horizontalHeaderItem(7);
        ___qtablewidgetitem7->setText(QCoreApplication::translate("MainWindow", "\345\211\215\347\275\256\350\257\276\347\250\213", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(courseTab), QCoreApplication::translate("MainWindow", "\345\205\250\351\203\250\350\257\276\347\250\213", nullptr));
        QTableWidgetItem *___qtablewidgetitem8 = scheduleTableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem8->setText(QCoreApplication::translate("MainWindow", "\345\221\250\344\270\200", nullptr));
        QTableWidgetItem *___qtablewidgetitem9 = scheduleTableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem9->setText(QCoreApplication::translate("MainWindow", "\345\221\250\344\272\214", nullptr));
        QTableWidgetItem *___qtablewidgetitem10 = scheduleTableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem10->setText(QCoreApplication::translate("MainWindow", "\345\221\250\344\270\211", nullptr));
        QTableWidgetItem *___qtablewidgetitem11 = scheduleTableWidget->horizontalHeaderItem(3);
        ___qtablewidgetitem11->setText(QCoreApplication::translate("MainWindow", "\345\221\250\345\233\233", nullptr));
        QTableWidgetItem *___qtablewidgetitem12 = scheduleTableWidget->horizontalHeaderItem(4);
        ___qtablewidgetitem12->setText(QCoreApplication::translate("MainWindow", "\345\221\250\344\272\224", nullptr));
        QTableWidgetItem *___qtablewidgetitem13 = scheduleTableWidget->horizontalHeaderItem(5);
        ___qtablewidgetitem13->setText(QCoreApplication::translate("MainWindow", "\345\221\250\345\205\255", nullptr));
        QTableWidgetItem *___qtablewidgetitem14 = scheduleTableWidget->horizontalHeaderItem(6);
        ___qtablewidgetitem14->setText(QCoreApplication::translate("MainWindow", "\345\221\250\346\227\245", nullptr));
        QTableWidgetItem *___qtablewidgetitem15 = scheduleTableWidget->verticalHeaderItem(0);
        ___qtablewidgetitem15->setText(QCoreApplication::translate("MainWindow", "1", nullptr));
        QTableWidgetItem *___qtablewidgetitem16 = scheduleTableWidget->verticalHeaderItem(1);
        ___qtablewidgetitem16->setText(QCoreApplication::translate("MainWindow", "2", nullptr));
        QTableWidgetItem *___qtablewidgetitem17 = scheduleTableWidget->verticalHeaderItem(2);
        ___qtablewidgetitem17->setText(QCoreApplication::translate("MainWindow", "3", nullptr));
        QTableWidgetItem *___qtablewidgetitem18 = scheduleTableWidget->verticalHeaderItem(3);
        ___qtablewidgetitem18->setText(QCoreApplication::translate("MainWindow", "4", nullptr));
        QTableWidgetItem *___qtablewidgetitem19 = scheduleTableWidget->verticalHeaderItem(4);
        ___qtablewidgetitem19->setText(QCoreApplication::translate("MainWindow", "5", nullptr));
        QTableWidgetItem *___qtablewidgetitem20 = scheduleTableWidget->verticalHeaderItem(5);
        ___qtablewidgetitem20->setText(QCoreApplication::translate("MainWindow", "6", nullptr));
        QTableWidgetItem *___qtablewidgetitem21 = scheduleTableWidget->verticalHeaderItem(6);
        ___qtablewidgetitem21->setText(QCoreApplication::translate("MainWindow", "7", nullptr));
        QTableWidgetItem *___qtablewidgetitem22 = scheduleTableWidget->verticalHeaderItem(7);
        ___qtablewidgetitem22->setText(QCoreApplication::translate("MainWindow", "8", nullptr));
        QTableWidgetItem *___qtablewidgetitem23 = scheduleTableWidget->verticalHeaderItem(8);
        ___qtablewidgetitem23->setText(QCoreApplication::translate("MainWindow", "9", nullptr));
        QTableWidgetItem *___qtablewidgetitem24 = scheduleTableWidget->verticalHeaderItem(9);
        ___qtablewidgetitem24->setText(QCoreApplication::translate("MainWindow", "10", nullptr));
        QTableWidgetItem *___qtablewidgetitem25 = scheduleTableWidget->verticalHeaderItem(10);
        ___qtablewidgetitem25->setText(QCoreApplication::translate("MainWindow", "11", nullptr));
        QTableWidgetItem *___qtablewidgetitem26 = scheduleTableWidget->verticalHeaderItem(11);
        ___qtablewidgetitem26->setText(QCoreApplication::translate("MainWindow", "12", nullptr));
        QTableWidgetItem *___qtablewidgetitem27 = scheduleTableWidget->verticalHeaderItem(12);
        ___qtablewidgetitem27->setText(QCoreApplication::translate("MainWindow", "13", nullptr));
        QTableWidgetItem *___qtablewidgetitem28 = scheduleTableWidget->verticalHeaderItem(13);
        ___qtablewidgetitem28->setText(QCoreApplication::translate("MainWindow", "14", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(scheduleTab), QCoreApplication::translate("MainWindow", "\351\200\211\350\257\276\346\226\271\346\241\210", nullptr));
        creditGroupBox->setTitle(QCoreApplication::translate("MainWindow", "\345\255\246\345\210\206\350\256\276\347\275\256", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" color:#000000;\">\346\200\273\345\255\246\345\210\206\344\270\213\351\231\220(\344\270\244\345\200\215\345\200\274):</span></p></body></html>", nullptr));
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
