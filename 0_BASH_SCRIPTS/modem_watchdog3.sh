#!/bin/bash
MODEM_DEVICE=/dev/ttyUSB2
TESTING_IP=8.8.8.8
STOP=false
INTERVAL_PING=10s
NUMBER_BAD_PINGS=60
BAD_PINGS=0
MAX_NUMBER_RESTARTS=3
NUMBER_RESTART=0
INTERVAL_WAIT_AFTER_NUMBER_RESTARTS=60m

function IsHostAvaliable {
        ping -c 1 -q $TESTING_IP > /dev/null
        echo $?
    }

function ResetModem {
        echo "Resetting modem...$NUMBER_RESTART"
        echo -e 'AT+QPOWD\r\n' > $MODEM_DEVICE
        echo "sleep 2 min after restart modem"
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
                BAD_PINGS=0
                NUMBER_RESTART=0
        else
                echo "$TESTING_IP is not avaliable!"
        BAD_PINGS=$(($BAD_PINGS+1))
        echo "bad pings - $BAD_PINGS of $NUMBER_BAD_PINGS"

                if [[ "$BAD_PINGS" -eq "$NUMBER_BAD_PINGS" ]];then
                        BAD_PINGS=0
                        NUMBER_RESTART=$(($NUMBER_RESTART+1))
                        ResetModem
                fi
                if [[ "$NUMBER_RESTART" -eq "$MAX_NUMBER_RESTARTS" ]];then
                    NUMBER_RESTART=0
                    echo "sleep $INTERVAL_WAIT_AFTER_NUMBER_RESTARTS after max attempts modem restarting"
                    sleep $INTERVAL_WAIT_AFTER_NUMBER_RESTARTS
                fi
        fi
        sleep $INTERVAL_PING
done