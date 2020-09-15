#!/bin/bash
#The race condition appears from starting of writing in file.
#So, file with
rm ex2.txt.lock;
for i in {1..10}
do
    if ln ex2.txt ex2.txt.lock
    then
        last=$(cat ex2.txt | tail -n 1);
        expr $last + 1 >> ex2.txt;
        rm ex2.txt.lock;
    else
        while ! ln ex2.txt ex2.txt.lock
        do  
            temp=0
        done
        last=$(cat ex2.txt | tail -n 1);
        expr $last + 1 >> ex2.txt;
        rm ex2.txt.lock;
    fi
done
rm ex2.txt.lock;
