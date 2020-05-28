TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt


SOURCES += \
        diaphragm.cpp pulse.cpp
HEADERS += \
        diaphragm.h
LIBS += -L/lib -lwiringPi -lwiringPiDev -lpthread -lrt -lm -lcrypt
