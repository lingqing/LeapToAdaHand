#-------------------------------------------------
#
# Project created by QtCreator 2016-05-28T15:45:40
#
#-------------------------------------------------

QT       += core gui
QT      += serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = adaLeap
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    leapmotionfinger.cpp \
    userserialport.cpp \
    userfilter.cpp

HEADERS  += mainwindow.h \
    leapmotionfinger.h \
    userserialport.h \
    typedefine.h \
    userfilter.h

FORMS    += mainwindow.ui

INCLUDEPATH += D:\Develop\LeapSDK\include
LIBS += -LD:\Develop\LeapSDK\lib\x86 \
-lLeap
