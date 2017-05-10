#-------------------------------------------------
#
# Project created by QtCreator 2010-12-29T16:13:33
#
#-------------------------------------------------

QT       += core gui widgets

TARGET = Smart

TEMPLATE = app

HEADERS += Smart.h \
    GlobDef.h \
    FinishTrack.h \
    Semaphore.h \
    Speedometer.h \
    ErrorIndicator.h \
    TextLabel.h \
    InputLine.h \
    SettingsWidget.h \
    RaceServiceInfo.h \
    ChamferedWidget.h \
    TimeWidget.h \
    Delimeter.h \
    StartWidget.h

SOURCES += main.cpp\
    Smart.cpp \
    FinishTrack.cpp \
    Semaphore.cpp \
    Speedometer.cpp \
    ErrorIndicator.cpp \
    TextLabel.cpp \
    InputLine.cpp \
    SettingsWidget.cpp \
    GlobDef.cpp \
    RaceServiceInfo.cpp \
    ChamferedWidget.cpp \
    TimeWidget.cpp \
    Delimeter.cpp \
    StartWidget.cpp

RESOURCES += \
    SmartTyping.qrc

TRANSLATIONS    = ru.ts

DISTFILES += \
    ru.ts
