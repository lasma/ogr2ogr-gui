#-------------------------------------------------
#
# Project created by QtCreator 2014-07-23T18:44:15
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ogr2ogr-gui
TEMPLATE = app

LIBS += -L/usr/loca/lib -lgdal -lproj

SOURCES += src/main.cpp \
        src/mainwindow.cpp \
        src/ogr2ogr.cpp \
        src/commonutils.cpp \
    src/ogrconfig.cpp

HEADERS  += inc/mainwindow.h \
        inc/ogr2ogr.h \
        inc/commonutils.h \
    inc/ogrconfig.h

FORMS    += ui/mainwindow.ui
