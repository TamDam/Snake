#-------------------------------------------------
#
# Project created by QtCreator 2020-09-11T12:21:10
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Snake_Proyecto
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    inicio.cpp \
    dnuevojuego.cpp \
    cuerpo.cpp \
    ayuda.cpp \
    dcontrolraton.cpp \
    fruta.cpp \
    puntuacion.cpp

HEADERS += \
        mainwindow.h \
    inicio.h \
    dnuevojuego.h \
    cuerpo.h \
    ayuda.h \
    dcontrolraton.h \
    fruta.h \
    puntuacion.h

FORMS += \
    inicio.ui \
    dnuevojuego.ui \
    ayuda.ui \
    dcontrolraton.ui \
    puntuacion.ui
