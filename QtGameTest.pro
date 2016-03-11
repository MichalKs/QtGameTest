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
    sprite.cpp \
    gamescene.cpp \
    mainwindow.cpp \
    statusbar.cpp \
    gamecontainer.cpp

HEADERS  += \
    bullet.h \
    enemy.h \
    game.h \
    player.h \
    sprite.h \
    gamescene.h \
    mainwindow.h \
    statusbar.h \
    gamecontainer.h

RESOURCES += \
    res.qrc

DISTFILES +=
