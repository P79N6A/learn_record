#!/bin/bash
# by orientlu

if [ $# -lt 1 ]; then
    echo $0 program_name
    exit -1
fi
cmd=$1
user_hz=$(getconf CLK_TCK) #mostly it's 100 on x86/x86_64

while :
do

    ps aux | grep $cmd | grep -v "grep" | grep -v $0 | grep -v "vim" | grep -v "gvim" | awk '{print $2}' | while read line;
    do
        pid=$line

        jiffies=$(cat /proc/$pid/stat | cut -d" " -f22)
        sys_uptime=$(cat /proc/uptime | cut -d" " -f1)
        last_time=$(( ${sys_uptime%.*} - $jiffies/$user_hz  ))

        if [[ $pid == 19545 ]]; then
            continue
        fi

        if [[ $last_time -gt 20 ]];then
            kill -9 $pid
            echo "the process $pid lasts for $last_time seconds."
            echo "kill it"
        fi
    done

done

