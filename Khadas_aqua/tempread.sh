#!/bin/bash
# 
if [ -n "$1" -a "$1" = "-h" ]; then
	echo "USAGE: $0 [-h]"
	echo "read all 1wire temperature sensors form /sys/bus/w1/devices/"
	exit 0
fi
sensdir=/sys/bus/w1/devices
for s in $sensdir/*-*/w1_slave; do
	if [ ! -r $s ]; then
		echo "ERROR: can not read sensor $s"
	else
		#  we are looking for a line with t= 
		# 41 00 4b 46 ff ff 07 10 38 t=32312
		awk '/t=/{sub(/^.+t=/, "");c=$0/1000;print c}' $s
	fi
done
