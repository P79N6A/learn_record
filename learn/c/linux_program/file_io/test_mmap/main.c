/*
 * 测试ｍｍａｐ函数的使用
 */

#include <stdlib.h>
#include <stdio.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>

int main(void)
{
	int *p;
	int fd = open("hello", O_RDWR);
	if (fd < 0)
	{
		perror("open hello\n");
		exit(1);
	}

	p = mmap(NULL, 6, PROT_WRITE, MAP_SHARED, fd, 0);

	if (p == MAP_FAILED)
	{
		perror("mmap\n");
		exit(1);
	}
	close(fd);

	/* 把fd关掉并不影响该文件已建立的映射，仍然可以对文件进行读写  */
	p[0] = 0x30313233;
	munmap(p, 6);
	return 0;
}
