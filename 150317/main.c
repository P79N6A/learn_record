//20150317
//lcd

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

//�������������ֵ
int maxSunbarray(int a[], size_t size)
{
	int sum = 0;
	int max = a[0];  //���ֵ����
	int cur = 0;

	assert(a != NULL && size >= 0);

	while (cur < size)
	{
		sum += a[cur++];
		if (sum > max)
			max = sum;
		else if (sum < 0)  // <0 �Ķ����ͣ�����
			sum = 0;
	}
	return max;
}

//----------------------------------------------------------------------------------
//����������
typedef struct treeNode
{
	int m_data;
	struct treeNode *m_left;
	struct treeNode *m_right;
}TreeNode;

//��ӡ·���� ���� ����Ҷ�ڵ� --��Ϊĳһ��ֵ��·��
void printPaths(TreeNode *root, int sum)
{
	int path[100];  //��������ȴ󼴿�
	helper(root, sum, path, 0);
}

void printPath(int path[], int top)
{
	int i;
	for (i=0; i<top; ++i)
		printf("%d ", path[i]);
}

//ǰ��������ݹ�
void helper(TreeNode *root, int sum, int path[], int top)
{
	path[top++] = root->m_data;
	sum -= root->m_data;
	if (root->m_left == NULL && root->m_right == NULL) //����Ҷ�ڵ�
	{
		if (sum == 0) //��������
			printpath(path, top);
	}	
	else
	{
		if (root->m_left  != NULL) helper(root->m_left, sum, path, top);
		if (root->m_right != NULL) helper(root->m_right, sum, path, top);
	}
	
	//�˳���ǰ�ڵ� �ָ�
	--top; 
	sum += root->m_data;  
}


//---------------------------------------------------------------------------------------




int main(void)
{
	
	int ar[] = {1, -2, 3, 10, -4, 7, 2, -5};
	//���������ֵ
	int redata = maxSunbarray(ar, 8);
	printf("%d\n", redata);



	return 0;
}

