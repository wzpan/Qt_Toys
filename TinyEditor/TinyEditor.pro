#-------------------------------------------------
#
# Project created by QtCreator 2014-01-05T13:42:40
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = excutable
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
