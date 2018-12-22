

# lua 5.3 and cpp/c

## install lua
### 如果需要给 lua 编写 so，（lua require 加载）
修改 lua/src 下的makefile， cppflag 加 -FPIC, 这样后续链接so才不会报错

```bash
curl -R -O http://www.lua.org/ftp/lua-5.3.0.tar.gz
tar vzxf lua-5.3.0.tar.gz
cd ./lua-5.3.0/
#sudo apt-get install libreadline-dev
make linux test
sudo make install
```

## cpp 调用lua
* ./cpp_call_lua.cpp & test.lua
cpp 加载 lua脚本并调用其占定义的函数

## lua 调用cpp
* ./lua_call_cpp.lua & mylualib.*
lua require cpp so
* ./lua_call_cpp.cpp & mylualib.* lua_call_cpp_no_require.lua
cpp 加载lua，lua调用cpp注册的函数

## 问题
### lua require时报错
**only ET_DYN and ET_EXEC can be loaded**
编译命令去掉 -c
g++ -c sourcefile， 只编译，没有链接
