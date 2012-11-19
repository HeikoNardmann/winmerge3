TEMPLATE = app
CONFIG += console

SOURCES += \
    main.cpp \
    ../common.cpp

HEADERS += \
    ../common.h

INCLUDEPATH += ../

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../ext/libxdiff/release/ -llibxdiff
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../ext/libxdiff/debug/ -llibxdiff
else:symbian: LIBS += -llibxdiff
else:unix: LIBS += -L$$PWD/../../ext/libxdiff/ -llibxdiff

INCLUDEPATH += $$PWD/../../ext/libxdiff/xdiff
DEPENDPATH += $$PWD/../../ext/libxdiff/xdiff

win32:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../ext/libxdiff/release/libxdiff.lib
else:win32:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../ext/libxdiff/debug/libxdiff.lib
else:unix:!symbian: PRE_TARGETDEPS += $$PWD/../../ext/libxdiff/liblibxdiff.a
