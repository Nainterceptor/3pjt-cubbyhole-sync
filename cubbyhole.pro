#-------------------------------------------------
#
# Project created by QtCreator 2014-02-03T14:22:11
#
#-------------------------------------------------

QT       += core gui\
         network xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = cubbyhole
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    iconbarre.cpp \
    synchro.cpp

HEADERS  += mainwindow.h \
    iconbarre.h \
    synchro.h

FORMS    += mainwindow.ui
