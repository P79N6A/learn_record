/*************************************************************************
    > File Name: binary_tree.c
    > Author: orient lu
    > Mail: lcdsdream@126.com
    > Created Time: Thu 16 Feb 2017 07:07:19 AM PST
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
// http://blog.csdn.net/luckyxiaoqiang/article/details/7518888/

struct tree_node {
    int value;
    struct tree_node *left;
    struct tree_node *right;
};

char stack_push(struct tree_node *node);
struct tree_node* stack_pop(void);
char queue_push(struct tree_node *node);
struct tree_node* queue_pop(void);

int tree_get_node_num(struct tree_node const *root)
{
    if (root == NULL) return 0;

    return (tree_get_node_num(root->left)
        + tree_get_node_num(root->right)
        + 1);
}

int tree_get_depth(struct tree_node const *root)
{
    if (root == NULL) return 0;
    int left_depth = tree_get_depth(root->left);
    int right_depth = tree_get_depth(root->right);
    return (left_depth > right_depth)?
        (left_depth + 1) : (right_depth + 1);
}

typedef void (*node_visit_fun_t)(struct tree_node* node);
void node_visit(struct tree_node* node)
{
    printf("%d ", node->value);
}

/*
*    1
* 2     5 
*3 4   6  7
* */
void tree_pre_traverse_rec(struct tree_node *root, node_visit_fun_t fun)
{
    if (root == NULL) return;
    fun(root);
    tree_pre_traverse_rec(root->left, fun);
    tree_pre_traverse_rec(root->right, fun);
}

void tree_pre_traverse(struct tree_node *root, node_visit_fun_t fun)
{
    if (root != NULL)
        stack_push(root);

    struct tree_node* node;
    while ((node = stack_pop()) != NULL) {
        fun(node);
        // first in, last out
        if (node->right != NULL) stack_push(node->right);
        if (node->left != NULL) stack_push(node->left);
    }
}

/*
*      4 
*  2       6
*1   3   5   7
* */
void tree_infix_traverse_rec(struct tree_node *root, node_visit_fun_t fun)
{
    if (root == NULL) return;
    tree_pre_traverse_rec(root->left, fun);
    fun(root);
    tree_pre_traverse_rec(root->right, fun);
}


/*
*      7 
*  3      6
*1   2  4   5
* */
void tree_suf_traverse_rec(struct tree_node *root, node_visit_fun_t fun)
{
    if (root == NULL) return;
    tree_pre_traverse_rec(root->left, fun);
    tree_pre_traverse_rec(root->right, fun);
    fun(root);
}

/*
*   1
* 2   3
*4 5 6 7
* */
void tree_layer_traverse(struct tree_node *root, node_visit_fun_t fun)
{
    if (root != NULL)
        queue_push(root);

    struct tree_node *node;
    while ((node = queue_pop()) != NULL) {
        fun(node);
        if (node->left != NULL) queue_push(node->left);
        if (node->right != NULL) queue_push(node->right);
    }
}

void tree_mirror(struct tree_node *root)
{
	if (root == NULL) return;

	tree_mirror(root->left);
	tree_mirror(root->right);

	struct tree_node *temp = root->left;
	root->left = root->right;
	root->right = temp;
}

// get common parent
// recursion
char find_node(struct tree_node *root,  struct tree_node *node)
{
	if (root == NULL || node == NULL) return 0;

	if (root == node) return 1;

	char rnt = find_node(root->left, node);
	if (!rnt) rnt = find_node(root->right, node);
	return rnt;
}

struct tree_node* find_common_rec(struct tree_node *root,
				 struct tree_node *node1,
				 struct tree_node *node2)
{
	if (find_node(root->left, node1)) {
		if (find_node(root->right, node2))
			return root;
		else
			return find_common_rec(root->left, node1, node2);
	} else {
		if (find_node(root->left, node2))
			return root;
		else
			return find_common_rec(root->right, node1, node2);
	}
}


void _find_common_rec2(struct tree_node *root,
		       struct tree_node *node1,
		       struct tree_node *node2,
		       int *flag, struct tree_node **pcom)
{
	assert(flag != NULL && pcom != NULL);

	if (root == NULL || node1 == NULL || node2 == NULL) return;

	if (*pcom == NULL)
		_find_common_rec2(root->left, node1, node2, flag, pcom);
	if (*pcom == NULL)
		_find_common_rec2(root->right, node1, node2, flag, pcom);

	if (flag[0] && flag[1] && *pcom == NULL)
		*pcom = root;

	if (root == node1) flag[0]++;
	if (root == node2) flag[1]++;
}

struct tree_node* find_common_rec2(struct tree_node *root,
				 struct tree_node *node1,
				 struct tree_node *node2)
{
	int flag[2] = {0};
	struct tree_node *com = NULL;
	_find_common_rec2(root, node1, node2, flag, &com);
	return com;
}

// no recursion
struct tree_node* find_common(struct tree_node *root,
			      struct tree_node *node1,
			      struct tree_node *node2)
{
}


// prefix get root, cut infix left / right
struct tree_node* tree_rebuild_pre_infix(int *pre_val, int *infix_val, int len)
{
	if (pre_val == NULL || pre_val == NULL || len <= 0) return NULL;

	int root_val = pre_val[0];
	int i = 0;
	while (i < len) {
		if (infix_val[i] == root_val) break;
		++i;
	}
	if (i == len) return NULL;

	struct tree_node *node = (struct tree_node*)malloc(sizeof(struct tree_node));
	node->value = root_val;
	node->left = tree_rebuild_pre_infix(pre_val + 1, infix_val, i);
	node->right = tree_rebuild_pre_infix(pre_val + 1 + i, infix_val + i + 1,
				     len - 1 - i);
	return node;
}

char tree_struct_compare(struct tree_node* root1, struct tree_node* root2)
{
	if (root1 == NULL && root2 == NULL) return 1;
	else if (root1 == NULL || root2 == NULL) return 0;
	char rnt = tree_struct_compare(root1->left, root2->left);
	if (rnt) tree_struct_compare(root1->right, root2->right);
	return rnt;
}

int tree_get_leaf_num(struct tree_node *root)
{
	if (root == NULL) return 0;
	if (root->left == NULL && root->right == NULL) return 1;

	return (tree_get_node_num(root->left)
		+ tree_get_node_num(root->right));
}

int main(void)
{

    return 0;
}

// stack
#define STACK_DEPTH 512
static struct tree_node* stack_buffer[STACK_DEPTH];
static int stack_top = 0;
char stack_push(struct tree_node *node)
{
    if (stack_top >= STACK_DEPTH) return -1;

    stack_buffer[stack_top++] = node;
    return 0;
}

struct tree_node* stack_pop(void)
{
    if (stack_top <= 0) return NULL;

    return stack_buffer[--stack_top];
}

//queue
#define QUEUE_LEN 512
#define QUEUE_LEN_MARK (QUEUE_LEN - 1)
static struct tree_node* queue_buffer[QUEUE_LEN];
static int queue_push_index = 0;
static int queue_pop_index = 0;
char queue_push(struct tree_node *node)
{
    int index = (queue_push_index + 1) & QUEUE_LEN_MARK;
    if (index == queue_pop_index) return -1;

    queue_buffer[queue_push_index] = node;
    queue_push_index = index;
    return 0;
}

struct tree_node* queue_pop(void)
{
    if (queue_pop_index == queue_push_index) return NULL;
    struct tree_node* rnt = queue_buffer[queue_pop_index];
    queue_pop_index = (queue_pop_index + 1) & QUEUE_LEN_MARK;
    return rnt;
}

