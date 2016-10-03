/*************************************************************************
	> File Name: list.h
	> Author: orient lu
	> Mail: lcdsdream@126.com
	> Created Time: Sun 02 Oct 2016 11:25:40 PM PDT
 ************************************************************************/

#ifndef _LIST_H
#define _LIST_H

struct LIST_ITEM {
	struct LIST_ITEM  *p_next;
	int value;		// ascending sort
	void *p_data;
};
typedef struct LIST_ITEM list_item_t;

struct LIST {
	struct LIST_ITEM *p_head;

	struct _mini_item {
		struct LIST_ITEM  *p_next;
	} head;
};
typedef struct LIST list_t;

void list_init(list_t *new_list);
void print_list(list_t *list);
void list_insert(list_t *list, list_item_t *new_item);
list_item_t *list_remove(list_t *list, int value);
void list_reverse(list_t *list);

#endif
