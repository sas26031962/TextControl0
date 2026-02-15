#-------------------------------------------------
#
# Project created by QtCreator 2026-02-14T09:50:05
#
#-------------------------------------------------

QT       += core gui

CONFIG += c++11 # Добавляем поддержку C++11
CONFIG += c++14 # Добавляем поддержку C++14

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TextControl0
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    classes/cloadfiles.cpp \
    classes/cenvironment.cpp \
    classes/cimportfiles.cpp \
    classes/cinifile.cpp \
    classes/crecord.cpp \
    classes/crecorditem.cpp

HEADERS  += mainwindow.h \
    classes/cloadfiles.h \
    classes/cenvironment.h \
    classes/cimportfiles.h \
    classes/cinifile.h \
    classes/crecord.h \
    classes/crecorditem.h

FORMS    += mainwindow.ui

RESOURCES += \
    resource.qrc
