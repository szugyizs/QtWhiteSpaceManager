#-------------------------------------------------
#
# Project created by QtCreator 2019-04-01T22:13:35
#
#-------------------------------------------------

QT       += core gui sql quickwidgets location network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QtWhiteSpaceManager
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

CONFIG += c++11

SOURCES += \
    database.cpp \
    device.cpp \
    main.cpp \
    transmitter.cpp \
    user.cpp \
    databasewindow.cpp \
    transmitteradmin.cpp \
    useradmin.cpp \
    helpdialog.cpp
RESOURCES += \
    mapper.qrc
OTHER_FILES +=

HEADERS += \
    database.h \
    device.h \
    transmitter.h \
    user.h \
    databasewindow.h \
    transmitteradmin.h \
    useradmin.h \
    tvwsmodel.h \
    tvwspoint.h \
    helpdialog.h

FORMS += \
    databasewindow.ui \
    transmitteradmin.ui \
    useradmin.ui \
    helpdialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    modeltest.qmodel
