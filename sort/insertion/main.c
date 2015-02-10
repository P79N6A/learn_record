/*
 * /sort/insertion/main.c
 * ��������ʵ��
 * 20150210 lcd 
 */

#include <stdio.h>
#include <stdlib.h>

/**
 * insertion_sort   
 * @array 	����ָ��
 * @len 	���鳤��
 *
 * ������������в�������(����)
 * lcd 20150210
*/
void insertion_sort(int *array, int len)
{
	int i, j, key;

	for (i = 1; i < len; i++)
	{
		for (j = 0; j < len; j++)
			printf("%d\t", array[j]);
		printf("\n");

		key = array[i];
		j = i - 1;
		while ((j >= 0) && ( array[j] > key))
		{
			/* ����ƶ� */
			array[j+1] = array[j]; 
			j--;
		}
		array[j+1] = key;
	}

	for (i = 0; i < len; i++)
		printf("%d\t", array[i]);
	printf("\n");
}


/**
 * main
 */
int main(void)
{
	int array[] = {4, 3, 6, 1, 5, 2, 7};
	insertion_sort(array, 7);
	return 0;
}
