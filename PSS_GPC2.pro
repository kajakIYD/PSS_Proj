#-------------------------------------------------
#
# Project created by QtCreator 2018-04-18T19:19:12
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = PSS_GPC2
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

#INCLUDEPATH += E:/Armadillo/armadillo-8.500.0/include \
  #              E:/Eigen/eigen-eigen-5a0156e40feb



SOURCES += \
        main.cpp \
        mainwindow.cpp \
    qcustomplot-source/qcustomplot.cpp \
    arx.cpp \
    siso.cpp \
    subject.cpp \
    p.cpp \
    config.cpp \
    Xgenerator.cpp \
    regulator.cpp \
    configregulatorparameters.cpp \
    Xsignal.cpp \
    plotdelegate.cpp \
    regulationloop.cpp \
    pid.cpp \
    identify.cpp \
    gpc.cpp \
    zpp.cpp

HEADERS += \
        mainwindow.h \
    qcustomplot-source/qcustomplot.h \
    plotdelegate.h \
    observer.h \
    siso.h \
    subject.h \
    arx.h \
    p.h \
    Xgenerator.h \
    config.h \
    regulator.h \
    configregulatorparameters.h \
    Xsignal.h \
    regulationloop.h \
    pid.h \
    identify.h \
    gpc.h \
    zpp.h

FORMS += \
        mainwindow.ui

DISTFILES += \
    GPC_Logo.png

RESOURCES += \
    resources.qrc
