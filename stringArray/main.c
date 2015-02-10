/*
 * 字符串全排列
 * lcd 
 */

 #include <stdio.h>
 #include <stdlib.h>
 #include <assert.h>
 #include <string.h>

/*
 * 交换两个char
*/
void swap_char(char *a, char *b)
{
/*	*a=(*a)^(*b);
	*b=(*a)^(*b);
	*a=(*a)^(*b); 使用这种方式交换出错，？？？
*/	char kk = *a;
	*a = *b;
	*b = kk;
}

 /*
  * 打印字符串全排列
  * 递归实现recursion
  * 字符串指针str， 字符串长度m，当前递归级0-（m-1）
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
		swap_char((str+n), (str+i)); 	//交换
		string_array_re(str, m, n+1);
		swap_char((str+n), (str+i)); 	//交换回来
	}
 }


/*
 * 字符串排列
 * 接口
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
