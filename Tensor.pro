TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    main.cpp \
    src/idx.cpp

QMAKE_CXXFLAGS += -std=c++11

HEADERS += \
    include/tensor.hpp \
    include/term.hpp \
    include/idx.h
