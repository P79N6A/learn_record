#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int count = 0;
void swap(char *a, char *b)
{
	*a = *a + *b;
	*b = *a - *b;
	*a = *a - *b;
}

void print_stringarrang(char *pstr, char *pcurrent)
{
	char *ptr = pcurrent + 1;
	
	if ( *ptr == '\0') //×Ö·û´®Î²
	{
		printf("{ %s } %d\n", pstr, ++count);
		return;
	}

	
	print_stringarrang(pstr, pcurrent+1);
	while ( *ptr != '\0')
	{
		swap(pcurrent, ptr);
		print_stringarrang(pstr, pcurrent+1);
		swap(pcurrent, ptr);
		++ptr;
	}
}


int main()
{
	char a[]= "abcdefg";

	printf("%s\n", a);

	print_stringarrang(a, a);
	
	return 0;
}
