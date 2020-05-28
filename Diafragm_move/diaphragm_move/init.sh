#!/bin/bash
gpio readall
cd /sys/class/gpio
echo 50 > export
echo out > gpio50/direction
echo 54 > export
echo out > gpio54/direction
echo 55 > export
echo out > gpio55/direction
echo 56 > export
echo out > gpio56/direction

