#!/bin/bash
cd /sys/class/gpio
count=0
while [ 1 ]
do
echo 0 > gpio36/value
echo 1 > gpio35/value
echo 1 > gpio33/value
echo 0 > gpio32/value
sleep 0.01
echo 0 > gpio36/value
echo 0 > gpio35/value
echo 0 > gpio33/value
echo 0 > gpio32/value
sleep 0.005
let "count++"
if [ $count -eq $1 ]
then
break
fi
echo 0 > gpio36/value
echo 1 > gpio35/value
echo 0 > gpio33/value
echo 1 > gpio32/value
sleep 0.01
echo 0 > gpio36/value
echo 0 > gpio35/value
echo 0 > gpio33/value
echo 0 > gpio32/value
sleep 0.005
let "count++"
if [ $count -eq $1 ]
then
break
fi

echo 1 > gpio36/value
echo 0 > gpio35/value
echo 0 > gpio33/value
echo 1 > gpio32/value
sleep 0.01
echo 0 > gpio36/value
echo 0 > gpio35/value
echo 0 > gpio33/value
echo 0 > gpio32/value
sleep 0.005
let "count++"
if [ $count -eq $1 ]
then
break
fi

echo 1 > gpio36/value
echo 0 > gpio35/value
echo 1 > gpio33/value
echo 0 > gpio32/value
sleep 0.01
echo 0 > gpio36/value
echo 0 > gpio35/value
echo 0 > gpio33/value
echo 0 > gpio32/value
sleep 0.005
let "count++"
if [ $count -eq $1 ]
then
break
fi

done
