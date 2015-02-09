#-------------------------------------------------
#
# Project created by QtCreator 2015-01-19T16:13:08
#
#-------------------------------------------------

QT       += core gui
QT       += multimedia
QT       += multimediawidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Projet
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    myvideosurface.cpp

HEADERS  += mainwindow.h \
    myvideosurface.h

FORMS    += mainwindow.ui

OTHER_FILES += \
    ../../../../../Desktop/chrome_japan.mp4
