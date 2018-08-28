/*************************************************************************
 > File Name: test.c
 > Author: orientlu
 > Mail: lcdsdream@126.com
 > Created Time: Mon 27 Aug 2018 09:05:38 PM CST
 ************************************************************************/

#include <stdio.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "zookeeper.h"
#include "zookeeper_log.h"

void zkConnWatcher(zhandle_t* zh, int type, int state, const char* path, void* watcherCtx)
{
    printf("------------------ start\n");
    printf("Conn wahtcher :\n");
    printf("type:%d ", type);
    printf("state:%d", state);
    printf("path: %s\n", path);
    printf("watcherCtx: %s\n", (char *)watcherCtx);
    printf("------------------ end\n");
}

void zkNodeWatcher(zhandle_t *zh, int type, int state, const char *path,void *watcherCtx)
{
    printf("------------------ start\n");
    printf("Node wahtcher :\n");
    printf("type:%d ", type);
    printf("state:%d", state);
    printf("path: %s\n", path);
    printf("watcherCtx: %s\n", (char *)watcherCtx);
    printf("------------------ end\n");
}

void create(zhandle_t *zkHandle, const char *pPath, const char *pData, const int iDataLen)
{
    char path_buffer[64];
    int bufferlen = sizeof(path_buffer);
    int ret = zoo_create(zkHandle, pPath, pData, iDataLen,
                          &ZOO_OPEN_ACL_UNSAFE, 0,
                          path_buffer, bufferlen);
    if (ret != ZOK) {
        printf("Create node error %d\n", __LINE__);
        exit(EXIT_FAILURE);
    } else {
        printf("Create node : %s\n", path_buffer);
    }
}
void get(zhandle_t* zkHandle, const char *pPath)
{
    char buffer[64];
    int bufferlen = sizeof(buffer);

    int ret = zoo_get(zkHandle, pPath, 0,
                      buffer, &bufferlen, NULL);
    if (ret == ZOK) {
        printf("Get Node [%s] data : %s\n",pPath, buffer);
    } else {
        printf("Get Node [%s] data error %d\n",pPath, ret);
    }
}

void set(zhandle_t* zkHandle, const char *pPath, const char *pData, const int iDataLen, int version)
{
    int ret = zoo_set(zkHandle, pPath, pData, iDataLen, version);
    if (ret == ZOK) {
        printf("Set  Node [%s] data : %s\n",pPath, pData);
    } else {
        printf("Set Node [%s] error %d\n", pPath, ret);
    }
}

void exists(zhandle_t *zkHandle,char *pPath)
{
    int ret = zoo_exists(zkHandle, pPath, 1, NULL);
}

//watch node
void wexists(zhandle_t *zkHandle, char *pPath, char *pMsg)
{
    int ret = zoo_wexists(zkHandle, pPath, zkNodeWatcher, pMsg, NULL);
}

//同步方式获得子节点信息
void getChildren(zhandle_t *zkHandle, char *pPath)
{
    struct String_vector strings;
    struct Stat stat;
    int ret = zoo_wget_children2(zkHandle, pPath,
                                  zkNodeWatcher, "testGetChildren",
                                  &strings,&stat);
    if (ret == ZOK) {
        printf("Get children : \n");
        for (int i = 0; i < strings.count; ++i)
            printf("%s\n",strings.data[i]);
    } else {
        printf("get children error %d\n", ret);
    }
}

void getACL(zhandle_t *zkHandle, char *pPath)
{
    struct ACL_vector acl;
    struct Stat stat;
    int ret = zoo_get_acl(zkHandle, pPath, &acl,&stat);
    if (ret == ZOK) {
        printf("Get ACL of [%s]:", pPath);
        printf("%d\n",acl.count);
        printf("%d\n",acl.data->perms);
        printf("%s\n",acl.data->id.scheme);
        printf("%s\n",acl.data->id.id);
    } else {
        printf("get ACL error %d\n", ret);
    }
}

void delete(zhandle_t *zkHandle,char *pPath)
{
    int ret = zoo_delete(zkHandle, pPath, -1);
    if (ret == ZOK) {
        printf("delete node [%s] success\n", pPath);
    } else {
        printf("delete node [%s] error %d\n", pPath, ret);
    }
}

int main(int argc, const char *argv[])
{
    // random
    const char* host = "127.0.0.1:1997,\
                        127.0.0.1:1998,\
                        127.0.0.1:1999";
    int timeout = 30000;

    //zoo_set_debug_level(ZOO_LOG_LEVEL_DEBUG); // set log level
    zoo_set_debug_level(ZOO_LOG_LEVEL_WARN); // set log level
    zhandle_t* zkHandle = zookeeper_init(host, zkConnWatcher, timeout, 0, "connected zookeeper.", 0);
    if (zkHandle == NULL) {
        fprintf(stderr, "Error when connecting to zookeeper servers...\n");
        exit(EXIT_FAILURE);
    }

    char* pPath = "/orient";
    char pData[] = "thisisData";
    char* pPatha = "/orient/a";
    char* pPathb = "/orient/b";
    char* pPathc = "/orient/b/c";

    delete(zkHandle, pPatha);
    delete(zkHandle, pPathc);
    delete(zkHandle, pPathb);
    delete(zkHandle, pPath);

    wexists(zkHandle, pPath, "when_create");
    create(zkHandle, pPath, pData, sizeof(pData));

    create(zkHandle, pPatha, pData, sizeof(pData));
    create(zkHandle, pPathb, pData, sizeof(pData));
    create(zkHandle, pPathc, pData, sizeof(pData));
    get(zkHandle, pPath);
    getChildren(zkHandle, pPath);

    int version = 0;
    char pData2[] = "thisisData_2";
    char pData3[] = "thisisData_3";
    set(zkHandle, pPath, pData2, sizeof(pData2), version++);
    set(zkHandle, pPath, pData3, sizeof(pData3), version++);
    get(zkHandle, pPath);

    get(zkHandle, pPath);

    getACL(zkHandle, pPath);

    wexists(zkHandle, pPath, "when_delete");
    delete(zkHandle, pPatha);
    delete(zkHandle, pPathc);
    delete(zkHandle, pPathb);
    delete(zkHandle, pPath);

    zookeeper_close(zkHandle);
    return 0;
}

