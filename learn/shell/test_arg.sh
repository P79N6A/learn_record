#!/bin/bash
# by orientlu

if [ -z $1 ]; then
    echo "need arg"
fi
echo $#
echo $@

your_id=${USER}-on-${HOSTNAME}
echo $your_id
echo "Old \$PATH = $PATH"

echo -----------------------------------------------
## use default var
echo ${para-"para0_nodeclare_setme"}
echo ${para:-"para0_noset_setme"}
para1=
echo ${para1-"para1_nodeclare_setme"}
echo ${para1:-"para1_declare_butnoset_setme"}
para2=para2_has_declare_and_set
echo ${para2-"para2_nodeclare_setme"}
echo ${para2:-"para2_declare_bttnoset_setme"}
echo -----------------------------------------------

declare -r var1=11 # same : readonly var1=11
#var1=22 --> error

f1()
{
    f1_var1="var1"
    declare f1_var2="var2"
}
f2()
{
    f1
    echo $f1_var1
    echo "f1_var1 is local varlue"
    echo $f1_var2
}
f2

a=letter_z
letter_z=z
echo "a = $a"
eval a=\$$a
#> eval 替换后执行命令，"a=$letter_z" -> a=z
echo $a


exit 0
