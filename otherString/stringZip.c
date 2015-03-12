//Ñ¹Ëõ×Ö·û´®
#include <stdio.h>
#include <assert.h>

/**
 * ×Ö·û´®Ñ¹Ëõ
 * input aaabbbcdef
 * output a3b3cdef
*/
void stringZip(const char *pInputStr, long lInputLen, char *pOutputStr)
{

	long count = 0;
	char temp;
	
	assert(pInputStr != NULL && pOutputStr != NULL);

	while (lInputLen--)
	{
		temp = *pInputStr++;
		count = 1;

		while (temp == *pInputStr)
		{
			count++;
			++pInputStr;
			lInputLen--;
		}
		
		if (count > 1)
		{
			if (count < 10)
				*pOutputStr++ = count + '0';
			else if (count < 100)
			{
				*pOutputStr++ = count/10 + '0';
				*pOutputStr++ = count%10 + '0';
			}
			else if(count < 1000)
			{
				*pOutputStr++ = count/100 + '0';
				*pOutputStr++ = (count%100)/10  + '0';
				*pOutputStr++ = ((count%100)%10)  + '0';
			}
			else ;
		}	
		*pOutputStr++ = temp;
	}

	*pOutputStr = '\0';

}

int main()
{
	char inStr_1[] = "cccddecc";
	char inStr_2[] = "adef";
	char inStr_3[] = "pppppppppppppppppp";

	char outStr[20];
	
	stringZip(inStr_1, 8, outStr);	
	printf("%s\n%s\n", inStr_1, outStr);
	
	stringZip(inStr_2, 8, outStr);	
	printf("%s\n%s\n", inStr_2, outStr);
	
	stringZip(inStr_3, 18, outStr);	
	printf("%s\n%s\n", inStr_3, outStr);






}
