## download zookeeper
http://www-eu.apache.org/dist/zookeeper/stable/

## make zk lib and build your app
```bash
$ cd ./zookeeper-3.4.12/src/c
$ ./configure
$ make; make install
$ ldconfig
$ g++ main.cpp  -DTHREADED -I/usr/local/include/zookeeper/  /usr/local/lib/libzookeeper_mt.so  -o a.out
```



