QT       += core gui widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = course_selection
TEMPLATE = app

SOURCES += main.cpp \
    mainwindow.cpp \
    courseparser.cpp \
    scheduleexporter.cpp \
    coursealgorithm.cpp \
    coursedialog.cpp \

HEADERS  += mainwindow.h \
    courseparser.h \
    scheduleexporter.h \
    coursealgorithm.h \
    coursedialog.h

FORMS    += mainwindow.ui \
    coursedialog.ui

RESOURCES += 

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
