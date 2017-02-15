#!/bin/bash

function rnd() {
        if [ -z "$RANDOM" ] ; then
                SEED=`tr -cd 0-9 < /dev/urandom | head -c 8`
        else
                SEED=$RANDOM
        fi

        RND_NUM=`echo $SEED $1 $2 | awk '{srand($1);printf"%d",rand()*10000%(($3-$2)+$2)}'`
        echo $RND_NUM, 
}

count=0
while [ $count -lt $1 ] ; do 
        rnd $2 $3 
        count=`expr $count + 1`
done
