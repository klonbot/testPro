#-------------------------------------------------
#
# Project created by QtCreator 2019-08-02T09:20:16
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = testPro
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    database.cpp \
    cache.cpp \
    mainlogics.cpp \
    databaseitem.cpp

HEADERS  += mainwindow.h \
    database.h \
    cache.h \
    mainlogics.h \
    databaseitem.h

FORMS    += mainwindow.ui
