/*************************************************************************
 > File Name: test_file.c
 > Author: orientlu
 > Mail: lcdsdream@126.com
 > Created Time: Mon 05 Nov 2018 04:50:30 PM CST
 ************************************************************************/
//#define _XOPEN_SOURCE 500

#include <fcntl.h>
#include<stdio.h>
#include<unistd.h>
#include <sys/stat.h>
int main()
{
    char buf[256] = "hi this is pwrite";
    char read_buff[256] = "hi this is pread";

    int fd = open("/tmp/lcd.txt", O_RDWR | O_CREAT );
    int ret;
    pid_t pid = fork();
    if (pid < 0) {
        printf("dead\n");
    } else if (pid == 0) {
        snprintf(buf, sizeof(buf), "hi write by child %d", getpid());
        ret  = pwrite(fd, buf, sizeof(buf), 0);
        //ret  = write(fd, buf, sizeof(buf));
    } else {
        snprintf(buf, sizeof(buf), "hi write by daddy %d", getpid());
        ret  = pwrite(fd, buf, sizeof(buf), 300);
        //ret  = write(fd, buf, sizeof(buf));

        sleep(1);
        ret  = pread(fd, read_buff, sizeof(read_buff), 300);
        printf("%s\n", read_buff);
        ret  = pread(fd, read_buff, sizeof(read_buff), 0);
        printf("%s\n", read_buff);
    }


    close(fd);
    return 0;
}
