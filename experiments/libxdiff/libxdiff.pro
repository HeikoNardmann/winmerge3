TEMPLATE = app
CONFIG += console

INCLUDEPATH += ../../ext/libxdiff/xdiff \
    ../../lib

SOURCES += main.cpp

HEADERS +=


win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../ext/libxdiff/release/ -llibxdiff
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../ext/libxdiff/debug/ -llibxdiff
else:symbian: LIBS += -llibxdiff
else:unix: LIBS += -L$$OUT_PWD/../../ext/libxdiff/ -llibxdiff

INCLUDEPATH += $$PWD/../../ext/libxdiff
DEPENDPATH += $$PWD/../../ext/libxdiff

win32:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../ext/libxdiff/release/libxdiff.lib
else:win32:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../ext/libxdiff/debug/libxdiff.lib
else:unix:!symbian: PRE_TARGETDEPS += $$OUT_PWD/../../ext/libxdiff/liblibxdiff.a
