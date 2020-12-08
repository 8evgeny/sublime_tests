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