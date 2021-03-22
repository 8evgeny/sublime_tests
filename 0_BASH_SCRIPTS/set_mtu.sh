#!/bin/bash
ret=$(ip a |grep "mtu 3700"| wc -l);
if [ $ret -ne 1 ]
   then {
         sudo ip l set eth0 down
         sleep 1
         sudo ip l set eth0 mtu 3700
         sleep 1
         sudo ip l set eth0 up
        }
    else
        {
            echo "MTU OK!"
        }
fi;