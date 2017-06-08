#!/bin/bash
# by orientlu


# 测试是否正确切换到目
cd ~/work/nohhhh || {
    echo "Cannot change to nohhhh" >&2
}


path=`pwd`
cd ~ || {
    echo "Cannot change to ~"
}

if [ `pwd` != $path ]; then
    echo "path: `pwd`"
fi

exit 0
