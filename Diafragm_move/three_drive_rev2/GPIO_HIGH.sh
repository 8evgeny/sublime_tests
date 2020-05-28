#!/bin/bash
cd /sys/class/gpio
echo 1 > gpio"$1"/value

