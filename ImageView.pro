#-------------------------------------------------
#
# Project created by QtCreator 2017-03-02T21:43:41
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ImageView
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    mypixmapitem.cpp \
    imageprocessor.cpp \
    loginformation.cpp \
    bilateraldialog.cpp \
    linearrgbdialog.cpp \
    lineargraydialog.cpp \
    gaussrgbdialog.cpp \
    gaussgraydialog.cpp \
    medianrgbdialog.cpp \
    mediangraydialog.cpp \
    expandrgbdialog.cpp \
    expandgraydialog.cpp \
    corrosionrgbdialog.cpp \
    corrosiongraydialog.cpp \
    affine.cpp \
    fft.cpp \
    hpdialog.cpp \
    lpdialog.cpp

HEADERS  += mainwindow.h \
    mypixmapitem.h \
    imageprocessor.h \
    loginformation.h \
    bilateraldialog.h \
    linearrgbdialog.h \
    lineargraydialog.h \
    gaussrgbdialog.h \
    gaussgraydialog.h \
    medianrgbdialog.h \
    mediangraydialog.h \
    expandrgbdialog.h \
    expandgraydialog.h \
    corrosionrgbdialog.h \
    corrosiongraydialog.h \
    fft.h \
    matrixtemplate.h \
    affine.h \
    hpdialog.h \
    lpdialog.h

FORMS    += mainwindow.ui \
    loginformation.ui \
    bilateraldialog.ui \
    linearrgbdialog.ui \
    lineargraydialog.ui \
    gaussrgbdialog.ui \
    gaussgraydialog.ui \
    medianrgbdialog.ui \
    mediangraydialog.ui \
    expandrgbdialog.ui \
    expandgraydialog.ui \
    corrosionrgbdialog.ui \
    corrosiongraydialog.ui \
    affine.ui \
    hpdialog.ui \
    lpdialog.ui
