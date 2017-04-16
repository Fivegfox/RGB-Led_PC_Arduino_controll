#-------------------------------------------------
#
# Project created by QtCreator 2017-01-29T20:55:47
#
#-------------------------------------------------

QT       += core gui
QT += serialport #testlib
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = RGBcontorl
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui

win32 {
        RC_FILE += ico.rc
        OTHER_FILES += ico.rc
}
