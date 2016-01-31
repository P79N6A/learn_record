/*************************************************************************
	> File Name: t.c
	> Author: luchaodong
	> Mail: luchaodong@meizu.com
	> Created Time: 2016年01月08日 星期五 14时19分36秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>

typedef unsigned char UINT8;


typedef struct {
	UINT8 dis_id;
	UINT8 type;
	UINT8 r17_id;

	UINT8 task_id		:4; //l
	UINT8 group_id		:4; //h

	UINT8 mesh_id;
	UINT8 mesh_op;
	UINT8 slot_hour1;
	UINT8 slot_minute1;
	UINT8 slot_hour2;
	UINT8 slot_minute2;
	UINT8 week_repeat;

	UINT8 r17_state		:1;
	UINT8 slot_flag		:2;
	UINT8 task_state	:2;
	UINT8			:3;
} packet;



int main(void)
{
	int size = sizeof(packet);
	UINT8 data[] = {0xFB, 0X01, 0X17, 0XAB, 0X14, 0X01,
			0X10, 0X01, 0X12, 0X21, 0X0F, 0X13};
	packet *P = (packet*)data;
	printf("size %d\n", size);
	printf("Dis_id		 : 0x%2X, write 0xFB\n", P->dis_id);
	printf("Type		 : 0x%2X, write 0x01\n", P->type);
	printf("R17_id		 : 0x%2X, write 0x17\n", P->r17_id);
	printf("Group_id	 : 0x%2X, write 0x0A\n", P->group_id);
	printf("Task_id		 : 0x%2X, write 0x0B\n", P->task_id);
	printf("Mesh_id		 : 0x%2X, write 0x14\n", P->mesh_id);
	printf("Mesh_op		 : 0x%2X, write 0x01\n", P->mesh_op);
	printf("Slot h1		 : 0x%2X, write 0x10\n", P->slot_hour1);
	printf("Slot m1		 : 0x%2X, write 0x01\n", P->slot_minute1);
	printf("Slot h2		 : 0x%2X, write 0x12\n", P->slot_hour2);
	printf("Slot m2		 : 0x%2X, write 0x21\n", P->slot_minute2);
	printf("Slot w		 : 0x%2X, write 00xF\n", P->week_repeat);
	printf("Task_flag	 : 0x%2X, write 0x02\n", P->task_state);
	printf("Slot_flag	 : 0x%2X, write 0x01\n", P->slot_flag);
	printf("R17_state	 : 0x%2X, write 0x01\n", P->r17_state);
	return 0;
}
