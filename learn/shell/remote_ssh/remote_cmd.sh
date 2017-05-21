#!/bin/bash


if [ ! -f "host.list" ]; then
	echo "host.list no exit"
	exit -1
fi

# 去除空行
sed -i '/^[:space:]*$/d' host.list

while read LINE
do
	eval $(echo $LINE | awk '{printf("IP=%s USER=%s PASSWD=%s",$1, $2, $3)}')
	expect <<-END
		set timeout 1200
		spawn ssh -p 36000 -l $USER $IP 
		expect {
			"yes/no"  {send "yes\r"; exp_continue}
			"password:" {send $PASSWD\r";}
		}
		sleep 1
		send "cd ~/work/\r"
		sleep 1
		send "touch aa\r"
		sleep 1
		send "exit\n"
		expect eof
		exit
	END
done < host.list
