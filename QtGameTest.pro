#-------------------------------------------------
#
# Project created by QtCreator 2016-02-20T20:36:36
#
#-------------------------------------------------

QT       += core gui \
            multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GameOfRectangles
TEMPLATE = app


SOURCES += main.cpp \
    bullet.cpp \
    enemy.cpp \
    game.cpp \
    player.cpp \
    score.cpp

HEADERS  += \
    bullet.h \
    enemy.h \
    game.h \
    player.h \
    score.h

RESOURCES += \
    res.qrc
