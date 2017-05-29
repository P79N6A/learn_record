#!/bin/bash
# by orientlu

if [ !-f "host.list" ]; then
    echo "Cant't find host.list"
    echo "host.list : IP name passwd port"
    exit -1
fi

clear
echo "====================================================="
echo "Host list : "
awk '{printf("(%d) IP : %s\t%s\t%d\n", NR, $1, $2, $4)}' ./host.list
echo ""
echo -n "Number : "
read -r number

eval $(awk -v number="$number" '{if(NR==number){printf("ip=%s name=%s passwd=%s port=%s", $1, $2, $3, $4)}}' ./host.list)
echo "SSH : " $ip

expect ssh.exp $ip $name $passwd $port
