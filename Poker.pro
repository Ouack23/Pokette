#-------------------------------------------------
#
# Project created by QtCreator 2017-05-14T17:33:54
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Poker
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
    pot_odds.cpp \
    card.cpp \
    hand.cpp \
    exception.cpp \
    commoncards.cpp \
    functions.cpp \
    combinaison.cpp \
    gui/choosecardwindow.cpp \
    gui/mainwindow.cpp \
    cards.cpp

HEADERS  += pot_odds.h \
    card.h \
    hand.h \
    exception.h \
    commoncards.h \
    functions.h \
    combinaison.h \
    gui/choosecardwindow.h \
    gui/mainwindow.h \
    cards.h

FORMS    += gui/choosecardwindow.ui \
    gui/mainwindow.ui

CONFIG += c++14

RESOURCES += \
    images/cards/cards.qrc
