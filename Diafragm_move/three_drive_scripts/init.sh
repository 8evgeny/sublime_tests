#!/bin/bash
cd /sys/class/gpio
echo $1 > export
echo out > gpio"$1"/direction

