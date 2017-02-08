// orient lu
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef unsigned char uint8;
typedef unsigned int uint32;
typedef char int8;
typedef int int32;

#define debug_print

struct hfm_node {
	char val;
	int32 freq;

	struct hfm_node *left, *right;
	struct hfm_node *list;
};

struct hfm_code {
	uint8 code;
	uint8 len;
};

static uint32 freq_table[256];
static struct hfm_code hfm_code_table[256];

static void list_insert(struct hfm_node *list, struct hfm_node *new);
static struct hfm_node *list_pop(struct hfm_node *list);

static void cal_char_freq_table(char *array, uint32 len)
{
	memset(freq_table, 0, sizeof(freq_table));
	while (len--) {
		++freq_table[*array++];
	}

#ifdef debug_print
	uint32 i;
	printf("\nBuild frequency table :\nchar:frequency\n");
	for (i = 0; i < 256; ++i) {
		if (freq_table[i] > 0) {
			printf("%c : %d\n", (char)i, freq_table[i]);
		}
	}
	printf("----------\n");
#endif
}

static struct hfm_node *new_hfm_node(char val, char freq)
{
	struct hfm_node *rnt = (struct hfm_node*) malloc(sizeof(struct hfm_node));
	if (rnt != NULL) {
		rnt->val = val;
		rnt->freq = freq;
		rnt->left = NULL;
		rnt->right = NULL;
		rnt->list = NULL;
	}
	return rnt;
}

static int8 build_char_freq_list(struct hfm_node *list)
{
	uint32 i = 0;
	for (; i < 256; ++i) {
		if (freq_table[i] > 0) {
			struct hfm_node *new = new_hfm_node((char)i, freq_table[i]);
			if (new != NULL) {
				list_insert(list, new);
			} else {
				printf("New ffm_node failue!!\n");
				return -1;
			}
		}
	}

#ifdef debug_print
	struct hfm_node *next = list->list;
	printf("Frequency list\nHead -->");
	while (next != NULL) {
		printf("(%c, %d)-->", next->val, next->freq);
		next = next->list;
	}
	printf("NULL\n");
#endif

	return 0;
}

static struct hfm_node *build_char_freq_tree(struct hfm_node *list)
{
	struct hfm_node *new = NULL;
	struct hfm_node *left, *right;

	while (1) {
		left = list_pop(list);
		if (left == NULL) {
			return NULL;
		}

		right = list_pop(list);
		if (right == NULL) {
			// root
			return left;
		}

		new = new_hfm_node(0, left->freq + right->freq);
		new->left = left;
		new->right = right;
		list_insert(list, new);
	}
}

static void free_hfm_tree(struct hfm_node *root)
{
	if (root == NULL) return;

	if (root->left != NULL)
	free_hfm_tree(root->left);

	if (root->right != NULL)
	free_hfm_tree(root->right);

	free(root);
}

static uint8 hfm_code = 0;
static uint8 hfm_deep = 0;
static void _build_hfm_code_table(struct hfm_node *root)
{
	++hfm_deep;

	if (root->left == NULL && root->right == NULL) {
		hfm_code_table[root->val].code = hfm_code;
		hfm_code_table[root->val].len = hfm_deep - 1;
	} else {
		hfm_code = (hfm_code << 1);

		if (root->left != NULL) {
			_build_hfm_code_table(root->left);
		}
		if (root->right != NULL) {
			hfm_code |= 1;
			_build_hfm_code_table(root->right);
		}
		hfm_code = (hfm_code >> 1);
	}

	--hfm_deep;
}

static void build_hfm_code_table(struct hfm_node *root)
{
	hfm_code = 0;
	hfm_deep = 0;
	memset(hfm_code_table, 0, sizeof(hfm_code_table));

	if (root != NULL) _build_hfm_code_table(root);

	#ifdef debug_print
	uint32 i;
	printf("\nBuild code table :\nchar:code:len\n");
	for (i = 0; i < 256; ++i) {
		if (hfm_code_table[i].len > 0) {
			printf("%c :  %02x  %d\n", (char)i, hfm_code_table[i].code, hfm_code_table[i].len);
		}
	}
	printf("----------\n");
	#endif

}

int main(int argc, char *argv[])
{
	char array[] = "adssdajdsakssnnnnssafasdfsafjkkfalsdjfkljskjfakashdsjfakajdfkajsk";

	cal_char_freq_table(array, sizeof(array) - 1);

	struct hfm_node list_head = {.list = NULL};
	build_char_freq_list(&list_head);

	struct hfm_node *hfm_tree = build_char_freq_tree(&list_head);
	if (hfm_tree != NULL) build_hfm_code_table(hfm_tree);

	free_hfm_tree(hfm_tree);
	return 0;
}

// sort by freq, smaller first
static void list_insert(struct hfm_node *list, struct hfm_node *new)
{
	struct hfm_node *prev = list;
	for (; (prev->list != NULL) && (prev->list->freq< new->freq); prev = prev->list);

	new->list = prev->list;
	prev->list = new;
}

// pop node from head
static struct hfm_node *list_pop(struct hfm_node *list)
{
	struct hfm_node *rnt = list->list;
	if (rnt != NULL) {
		list->list = rnt->list;
		rnt->list = NULL;
	}
	return rnt;
}

