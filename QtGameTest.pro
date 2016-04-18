#-------------------------------------------------
#
# Project created by QtCreator 2016-02-20T20:36:36
#
#-------------------------------------------------

QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GameOfRectangles
TEMPLATE = app


SOURCES += main.cpp \
    bullet.cpp \
    enemy.cpp \
    game.cpp \
    player.cpp \
    gamescene.cpp \
    mainwindow.cpp \
    statusbar.cpp \
    gamecontainer.cpp \
    topscoresdialog.cpp \
    yellowenemy.cpp \
    redenemy.cpp \
    darkinvader.cpp \
    alienspaceship.cpp \
    bonus.cpp

HEADERS  += \
    bullet.h \
    enemy.h \
    game.h \
    player.h \
    sprite.h \
    gamescene.h \
    mainwindow.h \
    statusbar.h \
    gamecontainer.h \
    topscoresdialog.h \
    yellowenemy.h \
    redenemy.h \
    darkinvader.h \
    alienspaceship.h \
    bonus.h

RESOURCES += \
    res.qrc

DISTFILES +=
