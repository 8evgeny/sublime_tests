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


#!/bin/bash

# MODEM_DEVICE=$1
MODEM_DEVICE=/dev/ttyUSB2
# TESTING_IP=$2
TESTING_IP=8.8.8.8
STOP=false
CHECK_INTERVAL=1m

function IsHostAvaliable {
        ping -c 3 -q $TESTING_IP > /dev/null
        echo $?
}

function ResetModem {
        echo 'Resetting modem...'
        # echo -e 'AT+CFUN=0\r\n' > $MODEM_DEVICE
        # sleep 30s
        # echo -e 'AT+CFUN=1\r\n' > $MODEM_DEVICE
        # sleep 2m
        echo -e 'AT+QPOWD\r\n' > $MODEM_DEVICE
        sleep 2m
        echo 'Resetting modem...Done'
}

function StopScript {
        STOP=true
}

trap "StopScript" INT

# stty -F $MODEM_DEVICE 9600
echo -e 'AT+IPR=9600\r\n' > $MODEM_DEVICE

while [[ $STOP != 'true' ]]; do
        if [[ `IsHostAvaliable` -eq 0 ]]; then
                echo "$TESTING_IP is awaliable"
        else
                echo "$TESTING_IP is not avaliable!"
                ResetModem
        fi
        sleep $CHECK_INTERVAL
done