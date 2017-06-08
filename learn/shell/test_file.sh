#!/bin/bash
# by orientlu

if [ -e lcd.file ];then
    echo "file is here"
fi

if [ -f /root ]; then
    echo "/root is normal file"
else
    echo "/root is no a normale file"
fi

if [ -d /root ]; then
    echo "/root is dir"
else
    echo "/root is no a dir"
fi

if [ -s lcd.file ]; then
    echo "file size is not zero"
    du -h lcd.file
fi

# -r -w -x
if [ -r lcd.file ]; then
    echo "file can read"
fi




