/*½»»»*/

#include <stdio.h>
#include <stdlib.h>

void swap_1(char *a, char *b)
{
	char kk = *a;
	*a = *b;
	*b = kk;
}


void swap_2(char *a, char *b)
{
	*a = (*a) ^ (*b);
	*b = (*a) ^ (*b);
	*a = (*a) ^ (*b);
}


int main(void)
{
	char a = 'c';
	char b = 'd';

	printf("%c %c\n", a, b);
	swap_1(&a, &b);
	printf("%c %c\n", a, b);

	swap_2(&a, &b);
	printf("%c %c\n", a, b);

	return 0;
}
