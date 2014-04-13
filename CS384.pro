#-------------------------------------------------
#
# Project created by QtCreator 2014-04-12T13:59:48
#
#-------------------------------------------------

QT       += core gui
QT       += concurrent

CONFIG += c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CS384
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    person.cpp \
    algorithmrunner.cpp

HEADERS  += widget.h \
    person.h \
    algorithmrunner.h

FORMS    += widget.ui
