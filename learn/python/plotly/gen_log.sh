#!/bin/bash
# by orientlu

count=$1
while [ $count -gt 0 ]
do
    sar -n DEV 1 1 | grep "Average:" | grep "eth0" | awk '{print $4,$5,$6}'
    count=$(($count-1))
done
