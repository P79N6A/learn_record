/*************************************************************************
	> File Name: mmapText.c
	> Author: luchaodong
	> Mail: luchaodong@meizu.com
	> Created Time: Fri 26 Feb 2016 02:44:36 PM HKT
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/mman.h>
#include<sys/file.h>
#include<errno.h>
#include<unistd.h>

char *path_1 = "./1.db";
char *path_2 = "./2.db";

struct data_struct {
	int magic;
	char name[20];
	char say[20];
	char adrr[20];
};

struct data_struct_old {
	int magic;
	char name[20];
	char adrr[20];
};

struct data_struct *data_db;


#define MAGIC   0X00110011
#define MAGIC_1 0X00110010

int main()
{
	char cmd[128];
	sprintf(cmd, "cp %s %s", path_1, path_2);
	system(cmd);

	int p2_fd = open(path_2, O_CREAT|O_RDWR, 00664);
	if (p2_fd < 0) {
		printf("Failed to open or create p2.db : %s\n",
		strerror(errno));
		return 1;
	}

	if (ftruncate(p2_fd, sizeof(*data_db)) == -1) {
		printf("failed to turn file length\n");
		return 1;
	}

	data_db = mmap(NULL, sizeof(*data_db), PROT_READ | PROT_WRITE,
			MAP_SHARED, p2_fd, 0);
	if (data_db == MAP_FAILED) {
		printf("Map failed\n");
		return 1;
	}

	close(p2_fd);

	if (data_db->magic != MAGIC) {
		printf("Init....%x\n", data_db->magic);

		if (data_db->magic == MAGIC_1) {
			printf("Old version db , transfer to new version\n");
			struct data_struct_old *data_db_old;

			int p1_fd = open(path_1, O_RDWR, 00664);
			if (p1_fd < 0) {
				printf("Failed to open or create p1.db : %s\n",
				strerror(errno));
				return 1;
			}

			if (ftruncate(p1_fd, sizeof(*data_db_old)) == -1) {
				printf("failed to turn file length 22\n");
				return 1;
			}

			data_db_old = mmap(NULL, sizeof(*data_db_old), PROT_READ | PROT_WRITE,
					MAP_SHARED, p1_fd, 0);
			if (data_db_old == MAP_FAILED) {
				printf("Map failed\n");
				return 1;
			}

			close(p1_fd);
			memset(data_db, 0, sizeof(*data_db));
			memcpy(data_db->name, data_db_old->name, sizeof(data_db->name));
			memcpy(data_db->adrr, data_db_old->adrr, sizeof(data_db->adrr));
			sprintf(data_db->say,  "hello\n");
			printf ("Cp old  : %s", data_db_old->name);
			printf ("CP old  : %s", data_db_old->adrr);
			data_db->magic = MAGIC;

		} else {
			printf("Init new one\n");
			memset(data_db, 0, sizeof(*data_db));
			sprintf(data_db->name, "luchaodong\n");
			sprintf(data_db->say,  "hello\n");
			sprintf(data_db->adrr, "shenzhen\n");
			data_db->magic = MAGIC;
		}
	}
	printf("%s", data_db->name);
	printf("%s", data_db->say);
	printf("%s", data_db->adrr);

	msync(data_db, sizeof(*data_db), MS_SYNC);
	sprintf(cmd, "cp %s %s", path_2, path_1);
	system(cmd);

	return 0;
}
