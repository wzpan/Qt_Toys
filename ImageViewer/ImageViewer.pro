#-------------------------------------------------
#
# Project created by QtCreator 2014-01-07T13:31:23
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = excutable
TEMPLATE = app

SOURCES += main.cpp\
        mainwindow.cpp \
    MorphoDialog.cpp \
    MorphoProcessor.cpp \
    SaltProcessor.cpp \
    SaltDialog.cpp

HEADERS  += mainwindow.h \
    ImageProcessor.h \
    MorphoDialog.h \
    MorphoProcessor.h \
    SaltProcessor.h \
    SaltDialog.h

FORMS    += mainwindow.ui \
    MorphoDialog.ui \
    SaltDialog.ui

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
