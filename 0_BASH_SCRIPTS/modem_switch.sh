#!/bin/bash
ret=$(ip a |grep "10.64.64.64/32"| wc -l);
if [ $ret -ne 1 ]
   then {
            echo "connection NO!"
            sudo pkill wvdial
            sleep 5
            usb_modeswitch -v 0x12d1 -p 0x14fe -V 0x12d1 -P 0x1506 -M 55534243000000000000000000000011000000000000000000000000000000
            sleep 5
            wvdial
        }
    else
	{
            echo "connection OK!"
	}
fi;




# nano /home/pi/alager/modem_switch.sh
*/1 * * * *  pi /home/pi/alager/modem_switch.sh
