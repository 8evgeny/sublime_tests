#!/bin/bash
cd /sys/class/gpio
echo 0 > gpio"$1"/value

