#!/bin/bash
g++ -Wall -o move move.cpp pulse.cpp -lwiringPi -lwiringPiDev -lpthread -lrt -lm -lcrypt
#make diaphragm_move
