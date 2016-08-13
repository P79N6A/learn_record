/*
 * �ļ���ɣϲ�������
 * �ο��ص㡡��
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
ssize_t read(int fd, void *buf, size_t count); /* ssize_t �з��ţ����󷵻�-1 */
ssize_t write(int fd, const void *buf, size_t count);

/* �ļ���λ��*/
#include <sys/types.h>
#include <unistd.h>
off_t lseek(int fd, off_t offset, int whence);


/* ���ô��ļ��������á�*/
#include <unistd.h>
#include <fcntl.h>
int fcntl(int fd, int cmd);
int fcntl(int fd, int cmd, long arg);
int fcntl(int fd, int cmd, struct flock *lock);


/* ���������豸��*/
#include <sys/ioctl.h>
int ioctl(int d, int request, ...);


/* mmap���԰Ѵ����ļ���һ����ֱ��ӳ�䵽�ڴ棬
   �����ļ��е�λ��ֱ�Ӿ��ж�Ӧ���ڴ��ַ��
   ���ļ��Ķ�д����ֱ����ָ������
   ������Ҫread/write����
 */
#include <sys/mman.h>
void *mmap(void *addr, size_t len, int prot, int flag, int filedes, off_t off);
int munmap(void *addr, size_t len);



