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


