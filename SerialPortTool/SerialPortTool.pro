#-------------------------------------------------
#
# Project created by QtCreator 2019-05-18T21:41:37
#
#-------------------------------------------------

QT       += core gui
QT       += serialport
QT       += printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SerialPortTool
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS
DEFINES += QT_MESSAGELOGCONTEXT

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cpp \
        highlight_keyword/highlight_keyword.cpp \
        qcustomplot/qcustomplot.cpp \
        serialporttool.cpp \
        ymodem/Ymodem.cpp \
        ymodem/YmodemFileReceive.cpp \
        ymodem/YmodemFileTransmit.cpp

HEADERS += \
        highlight_keyword/highlight_keyword.h \
        qcustomplot/qcustomplot.h \
        serialporttool.h \
        ymodem/Ymodem.h \
        ymodem/YmodemFileReceive.h \
        ymodem/YmodemFileTransmit.h \
        crc/CRC.h

FORMS += \
        serialporttool.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RC_FILE = serialport.rc
