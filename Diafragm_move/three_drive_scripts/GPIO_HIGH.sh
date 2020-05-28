#!/bin/bash
#cd /sys/class/gpio
echo 1 > /sys/class/gpio/gpio"$1"/value

