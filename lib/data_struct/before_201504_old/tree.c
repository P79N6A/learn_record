/*
 * AD 二叉树
 * luchaodong 20150314
 */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>


//二叉树
typedef struct node *ptr_tree;
typedef struct node
{
	int data;
	ptr_tree left_child;
	ptr_tree right_child;
}node_tree;

//中序遍历
void inorder(ptr_tree ptr)
{
	if (ptr == NULL)
		return;
	
	inorder(ptr->left_child);
	printf("%d ", ptr->data);
	inorder(ptr->right_child);
}

//前序遍历
void prorder(ptr_tree ptr)
{
	if (ptr == NULL)
		return;
	
	printf("%d ", ptr->data);
	prorder(ptr->left_child);
	prorder(ptr->right_child);
}

//后序遍历
void postorder(ptr_tree ptr)
{
	if (ptr == NULL)
		return 0;
	
	postorder(ptr->left_child);
	postorder(ptr->right_child);
	printf("%d ", ptr->data);
}

/*

//迭代实现树的遍历
//需要栈
void iter_inorder(ptr_tree ptr)
{
	//left_child 全部入栈
	//到叶 返回
	Stack *stack;   
	stack_init(stack);

	while (1)
	{
		for(; ptr != NULL; ptr = ptr->left_child)
			push(stack, ptr); 

		ptr = pop(stack);
		if (ptr == NULL) break; //栈空，截止
		
		printf("%d ", ptr->data);
		ptr = ptr->right_child;
	}

}

*/

//程序遍历
void level_order(ptr_tree ptr)
{


}

//二叉树复制
ptr_tree tree_copy(ptr_tree ptr)
{
	ptr_tree ptr_new = NULL;


	return ptr_new;
}

//二叉树比较
int tree_isequal(ptr_tree ptr1, ptr_tree ptr2)
{


	return -1;
}

























int main()
{

	return 0;
}
