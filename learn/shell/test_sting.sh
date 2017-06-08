#!/bin/bash
# by orientlu

string_Z=abcABC123ABCabc

# length
echo "sting_Z's length :" $string_Z
echo ${#string_Z}
echo `expr length $string_Z`
echo `expr "$string_Z" : '.*'`

# sub string
# {string: start: length}
echo ${string_Z:0}
echo ${string_Z:1}
echo ${string_Z:2}
echo ${string_Z:7:3}

# 括号或者空格
echo ${string_Z: -2}
echo ${string_Z:(-2)}

# 删除匹配子串
# 从前向后
echo ${string_Z#a*C} # 最短
echo ${string_Z##a*C} # 最长
# 从后向前, 注意子串整体看
echo ${string_Z%C*c} # 最短
echo ${string_Z%%C*c} # 最长
photo_name="myphoto.jpg"
echo ${photo_name%.*}

# replace
echo ${string_Z/abc/xyz}
echo ${string_Z//abc/xyz}
echo ${string_Z/#abc/xyz}
echo ${string_Z/%abc/xyz}


