#!/bin/sh
# chmod +x /alager/scripts/watchdog_lte.sh
# echo "* * * * * /alager/scripts/watchdog_lte.sh" | crontab -
n=0
while [ 1 ]; do
  #ping with timeout 10 seconds
  ping -c 1 -W 10 -w 10 8.8.8.8
  ret=$?
  echo ping result $ret
  if [ $ret -eq 0 ]; then
    echo ping ok
    exit 0
  else
    echo ping fail
    n=$((n+1))
    # when wan-dhcp fail,
    # net is unreachable and ping return without any delay
    # using sleep 1 avoid fail count overflow too fast
    sleep 1
  fi
  echo fail counter $n
  if [ $n -gt 180 ]; then
    # in case of wan-dhcp fail total time to reboot is 3 min (180 seconds)
    # in case of ping-timeout total time to reboot is 30 min (1800 seconds)
    echo 'reboot ec25'
  fi
done

modem_watchdog.sh
#!/usr/bin/env bash
if [[ $# -ne 2 ]]; then
        echo "Usage: $0 <modem_device> <testing_ip>"
        exit 1
fi
# /dev/ttyUSB4
MODEM_DEVICE=$1
# 10.177.83.1
TESTING_IP=$2
STOP=false
CHECK_INTERVAL=5m

function IsHostAvaliable {
        ping -c 3 -q $TESTING_IP > /dev/null
        echo $?
}

function ResetModem {
        echo 'Resetting modem...'
        echo -e 'AT+CFUN=0\r\n' > $MODEM_DEVICE
        sleep 30s
        echo -e 'AT+CFUN=1\r\n' > $MODEM_DEVICE
        sleep 2m
        echo 'Resetting modem...Done'
}

function StopScript {
        STOP=true
}

trap "StopScript" INT

stty -F $MODEM_DEVICE 9600

while [[ $STOP != 'true' ]]; do
        if [[ `IsHostAvaliable` -eq 0 ]]; then
                echo "$TESTING_IP is awaliable"
        else
                echo "$TESTING_IP is not avaliable!"
                ResetModem
        fi
        sleep $CHECK_INTERVAL
done