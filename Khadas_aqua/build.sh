#!/bin/bash

g++ main.cpp -o aqua -lwiringPi -lpthread -lrt -lm -lcrypt -I"/usr/include/aarch64-linux-gnu/qt5/QtCore"
