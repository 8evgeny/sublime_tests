#!/bin/bash
gpio readall
cd /sys/class/gpio
echo 32 > export
echo out > gpio32/direction
echo 33 > export
echo out > gpio33/direction
echo 35 > export
echo out > gpio35/direction
echo 36 > export
echo out > gpio36/direction

echo 50 > export
echo out > gpio50/direction
echo 54 > export
echo out > gpio54/direction
echo 55 > export
echo out > gpio55/direction
echo 56 > export
echo out > gpio56/direction

echo 145 > export
echo out > gpio145/direction
echo 144 > export
echo out > gpio144/direction
echo 149 > export
echo out > gpio149/direction

