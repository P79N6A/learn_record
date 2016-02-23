#!/bin/bash

CMD=pgrep
PPROC=time1

while : 
do
        # 注意不是单引号， 是ese下面的点
        if [ -n "`$CMD $PPROC`" ]
        then
                echo "ok"
        else
                echo "no"
        fi
        sleep 20
done

