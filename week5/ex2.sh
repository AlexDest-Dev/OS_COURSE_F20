#!/bin/bash
#The race condition appears from starting of writing in file.
#So, file with
finishnumber=40
while true;
do
    
    if ln ex2.txt ex2.txt.lock
    then
        number=$(cat ex2.txt | tail -n 1)
        if [ "$number" -eq "$finishnumber" ] 
        then 
            break 
        fi
        sleep 1
    else 
        number=$(cat ex2.txt | tail -n 1)
        if [ "$number" -eq "$finishnumber" ] 
        then 
            break 
        fi
        expr $number + 1 >> ex2.txt
        rm ex2.txt.lock
    fi
done
rm ex2.txt.lock

