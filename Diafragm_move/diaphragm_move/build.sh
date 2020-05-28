#!/bin/bash
g++ -Wall -o move diaphragm.cpp pulse.cpp -lwiringPi -lwiringPiDev -lpthread -lrt -lm -lcrypt
#make diaphragm_move
