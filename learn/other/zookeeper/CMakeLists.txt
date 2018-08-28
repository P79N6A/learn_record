cmake_minimum_required (VERSION 2.8)

project(test_zk)

include_directories (
    /usr/local/include/zookeeper/
)

link_libraries (
    /usr/local/lib/libzookeeper_mt.so
)

ADD_DEFINITIONS (
    -DTHREADED
)

add_executable(test_zk
    main.c
)
