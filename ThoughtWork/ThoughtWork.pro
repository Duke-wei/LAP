TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    utiltool.cpp \
    courtfactory.cpp \
    courtproduct.cpp \
    governor.cpp \
    cost.cpp \
    record.cpp \
    message.cpp

HEADERS += \
    utiltool.h \
    courtfactory.h \
    courtproduct.h \
    governor.h \
    cost.h \
    record.h \
    message.h
