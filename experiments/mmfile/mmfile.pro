#-------------------------------------------------
#
# Project created by QtCreator 2012-11-18T15:43:23
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = mmfile
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

INCLUDEPATH += ../

SOURCES += main.cpp \
    ../common.cpp

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../ext/libxdiff/release/ -llibxdiff
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../ext/libxdiff/debug/ -llibxdiff
else:symbian: LIBS += -llibxdiff
else:unix: LIBS += -L$$PWD/../../ext/libxdiff/ -llibxdiff

INCLUDEPATH += $$PWD/../../ext/libxdiff/xdiff
DEPENDPATH += $$PWD/../../ext/libxdiff/xdiff

win32:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../ext/libxdiff/release/libxdiff.lib
else:win32:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../ext/libxdiff/debug/libxdiff.lib
else:unix:!symbian: PRE_TARGETDEPS += $$PWD/../../ext/libxdiff/liblibxdiff.a

HEADERS += \
    ../common.h
