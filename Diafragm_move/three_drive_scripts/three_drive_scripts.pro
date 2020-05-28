TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt


SOURCES += \
        uln2003.cpp pulse.cpp
HEADERS += \
        uln2003.h
#LIBS += -L/lib -lwiringPi -lwiringPiDev -lpthread -lrt -lm -lcrypt
