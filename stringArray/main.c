/*
 * �ַ���ȫ����
 * lcd 
 */

 #include <stdio.h>
 #include <stdlib.h>
 #include <assert.h>
 #include <string.h>

/*
 * ��������char
*/
void swap_char(char *a, char *b)
{
/*	*a=(*a)^(*b);
	*b=(*a)^(*b);
	*a=(*a)^(*b); ʹ�����ַ�ʽ��������������
*/	char kk = *a;
	*a = *b;
	*b = kk;
}

 /*
  * ��ӡ�ַ���ȫ����
  * �ݹ�ʵ��recursion
  * �ַ���ָ��str�� �ַ�������m����ǰ�ݹ鼶0-��m-1��
 */
 void string_array_re(char *str, int m, int n)
 {
 	int i;
	assert(str != NULL);
	assert(n < m);

	if (n == m-1) 
	{
		for (i = 0; i < m; i++)
			printf("%c", *(str+i));
		printf("\n");
		return;
	}
	for (i = n; i < m; i++)
	{
		swap_char((str+n), (str+i)); 	//����
		string_array_re(str, m, n+1);
		swap_char((str+n), (str+i)); 	//��������
	}
 }


/*
 * �ַ�������
 * �ӿ�
*/
void string_array(char *str, int m )
{
	string_array_re(str, m, 0);
}


int  main( void )
{
 	char string[] = "abcd";
	
	string_array(string, 4);
	
	return 0;	
 }
