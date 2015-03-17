//20150317
//lcd

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

//数组子数组最大值
int maxSunbarray(int a[], size_t size)
{
	int sum = 0;
	int max = a[0];  //最大值！！
	int cur = 0;

	assert(a != NULL && size >= 0);

	while (cur < size)
	{
		sum += a[cur++];
		if (sum > max)
			max = sum;
		else if (sum < 0)  // <0 的段拉低，抛弃
			sum = 0;
	}
	return max;
}

//----------------------------------------------------------------------------------
//二叉树定义
typedef struct treeNode
{
	int m_data;
	struct treeNode *m_left;
	struct treeNode *m_right;
}TreeNode;

//打印路径， 树， 树到叶节点 --和为某一个值的路径
void printPaths(TreeNode *root, int sum)
{
	int path[100];  //比树的深度大即可
	helper(root, sum, path, 0);
}

void printPath(int path[], int top)
{
	int i;
	for (i=0; i<top; ++i)
		printf("%d ", path[i]);
}

//前序遍历，递归
void helper(TreeNode *root, int sum, int path[], int top)
{
	path[top++] = root->m_data;
	sum -= root->m_data;
	if (root->m_left == NULL && root->m_right == NULL) //到达叶节点
	{
		if (sum == 0) //符合条件
			printpath(path, top);
	}	
	else
	{
		if (root->m_left  != NULL) helper(root->m_left, sum, path, top);
		if (root->m_right != NULL) helper(root->m_right, sum, path, top);
	}
	
	//退出当前节点 恢复
	--top; 
	sum += root->m_data;  
}


//---------------------------------------------------------------------------------------




int main(void)
{
	
	int ar[] = {1, -2, 3, 10, -4, 7, 2, -5};
	//子数组最大值
	int redata = maxSunbarray(ar, 8);
	printf("%d\n", redata);



	return 0;
}

