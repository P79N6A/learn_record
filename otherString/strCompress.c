/*
 字符串压缩， 去掉多余空格
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/*
 * 字符串压缩
 * "I like    you    haha!" --> "I like you haha!"
 */
char *strCompress(char *strSrc)
{
	char *ptrA = strSrc;
	char *ptrB = NULL;
	int count = 0;

	assert(strSrc != NULL);

	if (*ptrA != ' ')    //行首没有空格
		while (*ptrA != '\0')    //跳过前面不需要压缩部分
		{
			if (*ptrA++ == ' ')
				++count;
			else
				count = 0;
			if (*ptrA == ' ' && count == 1)  //continuous ' '
				break;
		}

	else
		count = 1;

	if (count != 0) 
	{
		ptrB = ptrA + 1;
							
		while(*ptrB != '\0')	//压缩	
		{
			while (*ptrB == ' ' && *ptrB != '\0')
				++ptrB;

			while (*ptrB != ' ' && (*ptrA++ = *ptrB) != '\0')
				ptrB++;
			*ptrA++ = ' ';
		}

	}
	return strSrc;
}



int main()
{
	char str[] = "   I like  you     haha";

	printf("B : %s\n", str);
	printf("A : %s\n", strCompress(str) );
	return 0;

}	

