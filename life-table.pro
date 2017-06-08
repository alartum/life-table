QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = life-table

TEMPLATE = app

OBJECTS_DIR = tmp
MOC_DIR = tmp
RCC_DIR = tmp
UI_DIR  = tmp

DESTDIR = bin


SOURCES += main.cpp\
    fieldeditwidget.cpp \
    fieldmodel.cpp \
    fieldwidget.cpp \
    tile.cpp \
    tilechoicewidget.cpp

HEADERS  += \
    fieldeditwidget.h \
    fieldmodel.h \
    fieldwidget.h \
    tile.h \
    tilechoicewidget.h
