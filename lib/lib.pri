# This file is included by the gui/gui.pro file

HEADERS += $$PWD/dircompare.h \
           $$PWD/libxdiff_tools.h \
           $$PWD/resultitem.h \
    ../lib/difference.h \
    ../lib/differenceblock.h \
    ../lib/differenceline.h \
    ../lib/differencefilepair.h \
    ../lib/comparison.h \
    ../lib/xdiffmmfile.h

SOURCES += $$PWD/dircompare.cpp \
           $$PWD/libxdiff_tools.cpp \
    ../lib/difference.cpp \
    ../lib/differenceblock.cpp \
    ../lib/differenceline.cpp \
    ../lib/differencefilepair.cpp \
    ../lib/xdiffmmfile.cpp
