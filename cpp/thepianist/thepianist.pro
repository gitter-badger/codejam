#-------------------------------------------------
#
# Project created by QtCreator 2013-11-04T20:24:59
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = thepianist
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    pianoroll.cpp

HEADERS  += mainwindow.h \
    pianoroll.h

FORMS    += mainwindow.ui

RESOURCES += \
    thepianist.qrc
