#
#




### 库安装
### libevent


### [gflag](https://gflags.github.io/gflags/)

```
## udo apt-get install libgflags-dev
$ git clone https://github.com/gflags/gflags.git
$ cd ./gflags/
$ ls
$ mkdir build && cd ./build
$ ccmake ..
$ cmake ..
$ make
$ sudo make install
```
### glog

```
$ git clone https://github.com/google/glog.git
$ cd ./glog/; mkdir build && cd ./build
$ cmake ..
$ make
$ sudo make install
```
### protobuf

```
$ git clone https://github.com/protocolbuffers/protobuf.git
$ cd ./protobuf/
$ git submodule update --init --recursive
$ cd ./cmake/
$ cmake .
$ make
$ sudo make install
```
