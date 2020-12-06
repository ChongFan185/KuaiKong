QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Connection/databaseconnection.cpp \
    Connection/fileconnection.cpp \
    Connection/httpconnection.cpp \
    Connection/iconnection.cpp \
    Connection/tcpconnection.cpp \
    Data/basicdata.cpp \
    Data/longradardata.cpp \
    Data/radardata.cpp \
    Data/shortradardata.cpp \
    Data/systemdata.cpp \
    Data/userinformation.cpp \
    Service/Radar/longradarstrategy.cpp \
    Service/Radar/radarprocessstrategy.cpp \
    Service/Radar/radarservice.cpp \
    Service/Radar/shortradarstrategy.cpp \
    Service/Radar/shortradarstrategy_4nosym.cpp \
    Service/SurroundView/surroundviewadaptee.cpp \
    Service/SurroundView/surroundviewservice.cpp \
    Service/SurroundView/tdptarget.cpp \
    Service/basicservice.cpp \
    Simulator/cameradatagenerator.cpp \
    Simulator/datagenerator.cpp \
    Simulator/radardatagenerator.cpp \
    System/systemmonitortask.cpp \
    System/systemroutinetask.cpp \
    System/systemtask.cpp \
    UI/leosurroundviewwidget.cpp \
    UI/longradarwidget.cpp \
    UI/radarwidget.cpp \
    UI/shortradarwidget.cpp \
    UI/surroundviewwidget.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    Connection/databaseconnection.h \
    Connection/fileconnection.h \
    Connection/httpconnection.h \
    Connection/iconnection.h \
    Connection/tcpconnection.h \
    Data/basicdata.h \
    Data/longradardata.h \
    Data/radardata.h \
    Data/shortradardata.h \
    Data/systemdata.h \
    Data/userinformation.h \
    Service/Radar/longradarstrategy.h \
    Service/Radar/radarprocessstrategy.h \
    Service/Radar/radarservice.h \
    Service/Radar/shortradarstrategy.h \
    Service/Radar/shortradarstrategy_4nosym.h \
    Service/SurroundView/surroundviewadaptee.h \
    Service/SurroundView/surroundviewservice.h \
    Service/SurroundView/tdptarget.h \
    Service/basicservice.h \
    Simulator/cameradatagenerator.h \
    Simulator/datagenerator.h \
    Simulator/radardatagenerator.h \
    System/systemmonitortask.h \
    System/systemroutinetask.h \
    System/systemtask.h \
    UI/leosurroundviewwidget.h \
    UI/longradarwidget.h \
    UI/radarwidget.h \
    UI/shortradarwidget.h \
    UI/surroundviewwidget.h \
    mainwindow.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
