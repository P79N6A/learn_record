/*************************************************************************
	> File Name: list.c
	> Author: orient lu
	> Mail: lcdsdream@126.com
	> Created Time: Sun 02 Oct 2016 11:24:47 PM PDT
 ************************************************************************/
#include<stdio.h>
#include "list.h"

void list_init(list_t *new_list)
{
	new_list->head.p_next = NULL;
	new_list->p_head = (list_item_t *) &(new_list->head);
}

void print_list(list_t *list)
{
	list_item_t *interator = list->p_head;

	printf("List print: start");
	while (interator->p_next != NULL) {
		printf(" --> %d", interator->p_next->value);
		interator = interator->p_next;
	}
	printf(" --> end\n\r");
}

void list_insert(list_t *list, list_item_t *new_item)
{
	int new_value = new_item->value;
	list_item_t *interator = list->p_head;

	for (; interator->p_next != NULL && interator->p_next->value <= new_value;
			interator = interator->p_next) {
		// nothing
		// if insert a same value, insert into last
	}

	if (interator == new_item) {
		printf("List warning: Same item\n");
		return;
	}
	new_item->p_next = interator->p_next;
	interator->p_next = new_item;
}

list_item_t *list_remove(list_t *list, int value)
{
	// pop the first item value equal
	list_item_t *rm_item = NULL;
	list_item_t *interator = list->p_head;

	for (; interator->p_next != NULL && interator->p_next->value != value;
			interator = interator->p_next) {
	}

	if (interator->p_next != NULL) {
		rm_item = interator->p_next;
		interator->p_next = rm_item->p_next;
	}
	return rm_item;
}

void list_reverse(list_t *list)
{
	list_item_t *interator = list->p_head->p_next; // first node
	list_item_t *last_end_item = NULL;
	list_item_t *next_item;

	if (interator == NULL) return;

	while (interator->p_next != NULL) {
		next_item = interator->p_next;
		interator->p_next = last_end_item;
		last_end_item = interator;
		interator = next_item;
	}
	interator->p_next = last_end_item;

	// update list head
	list->p_head->p_next = interator;
}

