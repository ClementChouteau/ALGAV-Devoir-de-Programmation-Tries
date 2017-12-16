TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_CXXFLAGS += -std=c++11
QMAKE_CXXFLAGS_RELEASE += -O2
QMAKE_CXXFLAGS_RELEASE += -D NDEBUG

SOURCES += main.cpp

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    TriePatricia.h \
    TrieHybride.h \
    Trie.h \
    Sizeable.h \
    TrieHybride.hpp \
    TriePatricia.hpp \
    Conversions.hpp \
    TrieHybrideUnitTester.h \
    Fusion.h \
    Fusion.hpp \
    Equilibrage.h \
    Equilibrage.hpp \
    TrieStdSet.h \
    TriePerfs.h \
    TrieTest.h \
    TrieTest.hpp

