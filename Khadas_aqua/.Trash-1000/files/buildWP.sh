#!/bin/bash

g++ -o wiringpi wiringpi.cpp -lwiringPi -lpthread -lrt -lm -lcrypt
