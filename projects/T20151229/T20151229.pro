TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    idx.cpp

QMAKE_CXXFLAGS += -std=c++11

HEADERS += \
    tensor.hpp \
    term.hpp \
    idx.h
