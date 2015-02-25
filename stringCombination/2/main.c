/*
 *  字符串组合打印程序
 *  递归实现　
 *　lcd 20150225　返校列车上
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

/* 统计组合个数　*/
static int count = 0;

/**
 * 打印字符串组合递归函数
 * @递归缓冲区首地址
 * @递归缓冲区底部
 * @输入字符串当前字符地址
*/
void string_combi(char *ptr_buff, char *ptr_current, const char *str)
{
	assert(ptr_buff != NULL);
	assert(ptr_current != NULL);
	assert(str != NULL);
	
	/*递归结束条件*/
	if (*str == '\0') 
	{
		if (ptr_buff == ptr_current)  //除去空白组合
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

	/*包含当前字符*/
	*ptr_current  = *str;
	string_combi(ptr_buff, (ptr_current+1), (str+1));

	/*不包含当前字符*/
	string_combi(ptr_buff, ptr_current, (str+1));
}

/*
 * 打印字符串组合接口函数
 * 输入字符串str
 * 标准字符串，'\0'结尾
*/
void print_string_combi(const char *str)
{
	char   *ptr_buff = NULL; 	//缓冲区指针
	char   *ptr_current = NULL;  	//缓冲区当前指针
	size_t str_len;

	assert(str != NULL);
	
	str_len = strlen(str);  	//初始字符串长度
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

