/*
 * 文件与ＩＯ操作函数
 * 参考地点　：
 * 		http://akaedu.github.io/book/ch28s03.html
 */


#include <sys/types.h>  /* mode_t */
#include <sys/stat.h>
#include <fcntl.h>

int open(const char *pathname, int flags);
int open(const char *pathname, int flags, mode_t mode);


#include <unistd.h>
int close(int fd);


#include <unistd.h>
ssize_t read(int fd, void *buf, size_t count); /* ssize_t 有符号，错误返回-1 */
ssize_t write(int fd, const void *buf, size_t count);

/* 文件定位　*/
#include <sys/types.h>
#include <unistd.h>
off_t lseek(int fd, off_t offset, int whence);


/* 设置打开文件属性设置　*/
#include <unistd.h>
#include <fcntl.h>
int fcntl(int fd, int cmd);
int fcntl(int fd, int cmd, long arg);
int fcntl(int fd, int cmd, struct flock *lock);


/* 控制设置设备　*/
#include <sys/ioctl.h>
int ioctl(int d, int request, ...);


/* mmap可以把磁盘文件的一部分直接映射到内存，
   这样文件中的位置直接就有对应的内存地址，
   对文件的读写可以直接用指针来做
   而不需要read/write函数
 */
#include <sys/mman.h>
void *mmap(void *addr, size_t len, int prot, int flag, int filedes, off_t off);
int munmap(void *addr, size_t len);



