/*
 * AD ������
 * luchaodong 20150314
 */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>


//������
typedef struct node *ptr_tree;
typedef struct node
{
	int data;
	ptr_tree left_child;
	ptr_tree right_child;
}node_tree;

//�������
void inorder(ptr_tree ptr)
{
	if (ptr == NULL)
		return;
	
	inorder(ptr->left_child);
	printf("%d ", ptr->data);
	inorder(ptr->right_child);
}

//ǰ�����
void prorder(ptr_tree ptr)
{
	if (ptr == NULL)
		return;
	
	printf("%d ", ptr->data);
	prorder(ptr->left_child);
	prorder(ptr->right_child);
}

//�������
void postorder(ptr_tree ptr)
{
	if (ptr == NULL)
		return 0;
	
	postorder(ptr->left_child);
	postorder(ptr->right_child);
	printf("%d ", ptr->data);
}

/*

//����ʵ�����ı���
//��Ҫջ
void iter_inorder(ptr_tree ptr)
{
	//left_child ȫ����ջ
	//��Ҷ ����
	Stack *stack;   
	stack_init(stack);

	while (1)
	{
		for(; ptr != NULL; ptr = ptr->left_child)
			push(stack, ptr); 

		ptr = pop(stack);
		if (ptr == NULL) break; //ջ�գ���ֹ
		
		printf("%d ", ptr->data);
		ptr = ptr->right_child;
	}

}

*/

//�������
void level_order(ptr_tree ptr)
{


}

//����������
ptr_tree tree_copy(ptr_tree ptr)
{
	ptr_tree ptr_new = NULL;


	return ptr_new;
}

//�������Ƚ�
int tree_isequal(ptr_tree ptr1, ptr_tree ptr2)
{


	return -1;
}

























int main()
{

	return 0;
}
