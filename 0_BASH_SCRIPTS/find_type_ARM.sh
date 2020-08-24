#!/bin/bash

find (){
lscpu | grep 2208.0000
}

if (find="CPU max MHz:         2208.0000" )
then echo "Khadas"
fi



