#!/bin/bash

echo "Up" $count "process"
count=10
i=0
while [ $i -lt $count ]
do
        ./lcd_app &
        i=$(($i+1))
done

ps aux | grep "lcd_app" | grep -v "grep"| awk '{print $2}' | sort | head -n $1 |while read line
do
        kill -9 $line
        echo "kill" $line
done

echo "Other process :"
ps aux | grep "lcd_app" | grep -v "grep"
