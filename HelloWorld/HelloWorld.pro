#-------------------------------------------------
#
# Project created by QtCreator 2014-12-06T21:00:15
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PicPresenter
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    exif.cpp

HEADERS  += mainwindow.h \
    exif.h

FORMS    += mainwindow.ui

DYLD_LIBRARY_PATH = /home/debian/qt-arm/lib
target.files = PicPresenter
target.path = /home/debian
INSTALLS = target

