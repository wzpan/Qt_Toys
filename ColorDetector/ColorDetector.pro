#-------------------------------------------------
#
# Project created by QtCreator 2014-02-11T16:30:48
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = colorDetector
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    ColorDetector.cpp

HEADERS  += mainwindow.h \
    ColorDetector.h \
    ColorDetectController.h

FORMS    += mainwindow.ui

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
