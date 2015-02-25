/*
 *  �ַ�����ϴ�ӡ����
 *  �ݹ�ʵ�֡�
 *��lcd 20150225����У�г���
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

/* ͳ����ϸ�����*/
static int count = 0;

/**
 * ��ӡ�ַ�����ϵݹ麯��
 * @�ݹ黺�����׵�ַ
 * @�ݹ黺�����ײ�
 * @�����ַ�����ǰ�ַ���ַ
*/
void string_combi(char *ptr_buff, char *ptr_current, const char *str)
{
	assert(ptr_buff != NULL);
	assert(ptr_current != NULL);
	assert(str != NULL);
	
	/*�ݹ��������*/
	if (*str == '\0') 
	{
		if (ptr_buff == ptr_current)  //��ȥ�հ����
			return; 

		printf("{");
		while (ptr_buff != ptr_current)
		{
			printf("%c", *ptr_buff++);
		}
		printf("}\n");
		
		count++; 
		return;
	}

	/*������ǰ�ַ�*/
	*ptr_current  = *str;
	string_combi(ptr_buff, (ptr_current+1), (str+1));

	/*��������ǰ�ַ�*/
	string_combi(ptr_buff, ptr_current, (str+1));
}

/*
 * ��ӡ�ַ�����Ͻӿں���
 * �����ַ���str
 * ��׼�ַ�����'\0'��β
*/
void print_string_combi(const char *str)
{
	char   *ptr_buff = NULL; 	//������ָ��
	char   *ptr_current = NULL;  	//��������ǰָ��
	size_t str_len;

	assert(str != NULL);
	
	str_len = strlen(str);  	//��ʼ�ַ�������
	printf("Input string's length : %d\n", str_len);

	ptr_buff = (char*)malloc(str_len * sizeof(char));
	assert(ptr_buff != NULL);
	
	ptr_current = ptr_buff;
	string_combi(ptr_buff, ptr_current, str);
	printf("Total conbi : %d \n", count);
	return;
}

int main(void)
{
	char string[] = "abcdef";
	
	print_string_combi(string);	

	return 0;
}

