#!/bin/bash
#cd /sys/class/gpio
echo 0 >/sys/class/gpio/gpio"$1"/value

