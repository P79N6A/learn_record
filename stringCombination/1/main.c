/*
 *  �ַ�����ϴ�ӡ����
 *  lcd 
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>


typedef unsigned int u32;


/*
 * ʹ��λ��Ǵ�ӡ�ַ������
 * �����ַ���str���˴�Ĭ��С��32���������ظ���
 * ��׼�ַ�����'\0'��β
*/
void print_string_combi(const char *str)
{
	u32 flag = 1; //���
	u32 max_num;
	int len = strlen(str); //���Ԫ�ظ���
	int i;

	assert(str != NULL);
	
	for (i = 0; i < len; i++)  //�������ֵ��ȫ1 --> 2^len
		max_num |= (1<<i);
	
	while (flag <= max_num)
	{
		printf("{");
		for (i = 0; i < len; i++)
		{
			if ( flag & (1<<i) ) //�ж��Ƿ�Ϊ1
				printf("%c", *(str+i));
		}
		printf("}\n");
		flag++;
	}
	printf("Count : %d \n", max_num);	
}



int main(void)
{
	char string[] = "abcdef";
	print_string_combi(string);
	
	return 0;
}


/*---------------------------------------------------------------------*/

