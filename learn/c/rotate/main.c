//20150309
//luchaodong

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

/**
 * 旋转字符串
*/
void leftShiftOne(char *str, int len)
{
	char temp = *str; //保留第一个
	int i;
	
	len = len - 1;
	for (i = 0; i < len; ++i)
		str[i] = str[i+1];
	
	str[len] = temp;
}

void leftShiftM_1(char *str, int len, int n)
{
	while(n--)
		leftShiftOne(str, len);
}



int main()
{
	char mystr[] = "abcdef";

	printf("B : %s\n", mystr);

	leftShiftM_1(mystr, strlen(mystr), 2);

	printf("A : %s\n", mystr);

	return 0;
}

