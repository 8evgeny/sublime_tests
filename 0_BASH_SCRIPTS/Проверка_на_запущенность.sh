#!/bin/bash
	ret=$(ps aux | grep [h]top | wc -l)  
	# если первую букву процесса взять в квадратные скобки, то ‘grep htop’ будет исключаться из списка.
	if [ "$ret" -eq 0 ]
then {
	echo "Running Htop" #output text
        sleep 1  #delay
	htop #command for run program
	exit 1
}
else 
{
	echo "EXIT. Htop already running!"
	exit 1
}
fi;