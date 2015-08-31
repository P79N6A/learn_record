#!/bin/bash
# 批量烧录  输入烧写设备数， <10
# lcd

str_1="sudo ./make r15-BCM920737TAG_Q32 download UART=/dev/ttyUSB"
str_2="BT_DEVICE_ADDRESS=20737A1CEE0"
#sudo ./make r15-BCM920737TAG_Q32 download UART=/dev/ttyUSB0 BT_DEVICE_ADDRESS=20737A1CEE00

var=0 
while ((${var}<$1)); do
    echo $str_1${var} ${str_2}${var}
    sudo ./make r14-BCM920737TAG_Q32 download UART=/dev/ttyUSB${var} BT_DEVICE_ADDRESS=20737A1CEE0${var}
    var=$((var+1))
done

