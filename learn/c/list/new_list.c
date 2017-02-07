/*************************************************************************
  > File Name: new_list.c
  > Author: orient lu
  > Mail: lcdsdream@126.com
  > Created Time: Tue 07 Feb 2017 11:16:39 AM CST
 ************************************************************************/

#include<stdio.h>
#define incline

struct int_node_old {
	int val;
	struct int_node_old *next;
};

void old_list_insert(struct int_node_old *head, struct int_node_old *new)
{
	new->next = head->next;
	head->next = new;
}

void old_list_insert_tail(struct int_node_old *head, struct int_node_old *new)
{
	struct int_node_old *list = head;
	for (; list->next != NULL; list = list->next);
	list->next = new;
	new->next = NULL;
}

// linux kernel
// cppy from include/linux/list.h
struct list_head {
	struct list_head *next, *prev;
};

struct int_node {
	int val;
	struct list_head list;
};

// init head, point itself
#define LIST_HEAD(name) \
	struct list_head name = {&(name), &(name)};

static inline void __list_add(struct list_head *new,
		struct list_head *prev,
		struct list_head *next)
{
	next->prev = new;
	new->next = next;
	new->prev = prev;
	prev->next = new;
}

static inline void list_add(struct list_head *new, struct list_head *head)
{
	__list_add(new, head, head->next);
}

static inline void list_add_tail(struct list_head *new, struct list_head *head)
{
	__list_add(new, head->prev, head);
}

#define list_for_each(pos, head) \
	for ((pos) = (head)->next; (pos) != (head); (pos) = (pos)->next)

#define list_for_each_prev(pos, head) \
	for ((pos) = (head)->prev; (pos) != (head); (pos) = (pos)->prev)

#define container_of(ptr, type, menber) \
	(type *)((char*)ptr - (char*) &(((type *)0)->menber))

#define list_entry(ptr, type, menber) container_of(ptr, type, menber)

int main(void)
{
	LIST_HEAD(my_list);
	struct int_node a, b, c;

	a.val = 1;
	b.val = 2;
	c.val = 3;

	list_add(&(a.list), &my_list);
	list_add(&(b.list), &my_list);
	list_add_tail(&(c.list), &my_list);

	struct list_head *plist;
	struct int_node *pnode;

	list_for_each(plist, &my_list) {
		pnode = list_entry(plist, struct int_node, list);
		printf("%d ", pnode->val);
	}
	printf("\n");

	list_for_each_prev(plist, &my_list) {
		pnode = list_entry(plist, struct int_node, list);
		printf("%d ", pnode->val);
	}
	printf("\n");

	return 0;
}
