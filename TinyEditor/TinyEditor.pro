#-------------------------------------------------
#
# Project created by QtCreator 2014-01-05T13:42:40
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TinyEditor
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    finddialog.cpp

HEADERS  += mainwindow.h \
    finddialog.h

FORMS    += mainwindow.ui \
    finddialog.ui

RESOURCES += \
    myResources.qrc

    unix {
    CONFIG += link_pkgconfig
    PKGCONFIG += opencv
    }
    Win32 {
    INCLUDEPATH += C:\OpenCV2.2\include\
    LIBS += -LC:\OpenCV2.2\lib \
    -lopencv_core220 \
    -lopencv_highgui220 \
    -lopencv_imgproc220 \
    -lopencv_features2d220 \
    -lopencv_calib3d220
    }
