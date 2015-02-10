/*
 *  字符串组合打印程序
 *  lcd 
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>


typedef unsigned int u32;


/*
 * 使用位标记打印字符串组合
 * 输入字符串str（此处默认小于32，不考虑重复）
 * 标准字符串，'\0'结尾
*/
void print_string_combi(const char *str)
{
	u32 flag = 1; //标记
	u32 max_num;
	int len = strlen(str); //组合元素个数
	int i;

	assert(str != NULL);
	
	for (i = 0; i < len; i++)  //计算最大值，全1 --> 2^len
		max_num |= (1<<i);
	
	while (flag <= max_num)
	{
		printf("{");
		for (i = 0; i < len; i++)
		{
			if ( flag & (1<<i) ) //判断是否为1
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

