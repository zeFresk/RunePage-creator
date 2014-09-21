#-------------------------------------------------
#
# Project created by QtCreator 2014-09-20T17:39:07
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Test_Designer
TEMPLATE = app


SOURCES += main.cpp\
        fenetre.cpp \
    rune.cpp \
    runepage.cpp \
    fileManagement.cpp

HEADERS  += fenetre.h \
    rune.h \
    runepage.h \
    fileManagement.h

FORMS    += fenetre.ui

QMAKE_CXXFLAGS = -std=c++11 \
    -Wall \
    -Wextra \
