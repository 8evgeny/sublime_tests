#!/bin/bash
gpio readall
cd /sys/class/gpio
#echo 145 > export
#echo out > gpio145/direction
#echo 144 > export
#echo out > gpio144/direction
echo 149 > export
echo out > gpio149/direction
gpio readall
while [ 1 ]
do
echo 0 > gpio149/value
sleep 0.5
echo 1 > gpio149/value
sleep 0.5
done
