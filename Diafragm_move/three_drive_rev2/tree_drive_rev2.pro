TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt


SOURCES += \
        move.cpp pulse.cpp
HEADERS += \
        move.h
LIBS += -L/lib -lwiringPi -lwiringPiDev -lpthread -lrt -lm -lcrypt
