QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = course_selection
TEMPLATE = app
CONFIG += c++17

SOURCES += main.cpp \
    mainwindow.cpp \
    courseparser.cpp \
    scheduleexporter.cpp \
    coursealgorithm.cpp \
    coursedialog.cpp \
    classtimedialog.cpp

HEADERS += mainwindow.h \
    courseparser.h \
    scheduleexporter.h \
    coursealgorithm.h \
    coursedialog.h \
    classtimedialog.h

FORMS += mainwindow.ui \
    coursedialog.ui \
    classtimedialog.ui

# 部署规则（可选）
unix:!android {
    target.path = $$[QT_INSTALL_BINS]/$${TARGET}
    INSTALLS += target
}

# 调试/发布配置（可选）
CONFIG += debug_and_release
CONFIG(debug, debug|release) {
    DEFINES += DEBUG_MODE
} else {
    DEFINES += RELEASE_MODE
}