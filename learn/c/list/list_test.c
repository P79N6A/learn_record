/*************************************************************************
	> File Name: list_test.c
	> Author: orient lu
	> Mail: lcdsdream@126.com
	> Created Time: Sun 02 Oct 2016 11:26:09 PM PDT
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>

#include "list.h"

int main(int argc, char *argv[])
{
	printf("********** List Test ***********\n\r");

	list_t list;
	list_init(&list);

	list_item_t item_1 = {.value = 1,};
	list_item_t item_2 = {.value = 2,};
	list_item_t item_2_2 = {.value = 2,};
	list_item_t item_3 = {.value = 3,};
	list_item_t item_4 = {.value = 4,};
	list_item_t item_5 = {.value = 5,};
	list_item_t item_8 = {.value = 8,};

	list_insert(&list, &item_1);
	print_list(&list);

	list_insert(&list, &item_2);
	print_list(&list);

	list_insert(&list, &item_8);
	list_insert(&list, &item_5);
	print_list(&list);

	list_insert(&list, &item_2);
	list_insert(&list, &item_2_2);
	print_list(&list);

	list_insert(&list, &item_3);
	list_insert(&list, &item_4);
	print_list(&list);

	if (list_remove(&list, 10) == NULL) {
		printf ("No this item\n");
	}

	if (list_remove(&list, 2) == NULL) {
		printf ("No this item\n");
	}
	print_list(&list);

	printf ("Reverse list\n");
	list_reverse(&list);
	print_list(&list);

	return 0;
}

