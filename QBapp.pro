#-------------------------------------------------
#
# Project created by QtCreator 2016-04-27T13:48:23
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = simpleSerial
TEMPLATE = app



SOURCES += main.cpp\
        mainwindow.cpp \


HEADERS  += mainwindow.h \


FORMS    += mainwindow.ui
include(qextserialport/src/qextserialport.pri)
