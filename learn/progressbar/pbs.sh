#!/bin/bash

for i in {1..100}
do
        printf "%s%% \r" $i
        sleep 0.01
done

printf "\n"
