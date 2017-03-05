/*************************************************************************
	> File Name: varg_test.c
	> Author: orient lu
	> Mail: lcdsdream@126.com
	> Created Time: Thu 23 Feb 2017 04:23:48 PM CST
 ************************************************************************/

#include<stdio.h>
#include<stdarg.h>

void fun1(char *fmt, ...)
{
	va_list ap;
	va_start(ap, fmt);
	while (*fmt) {
		switch (*fmt) {
		case 'd' :
			fprintf(stdout, "%d\n", (int)va_arg(ap, int));
			break;
		case 'c':
			fprintf(stdout, "%c\n", (char)va_arg(ap, int));
			break;
		case 's':
			fprintf(stdout, "%s\n", (char*)va_arg(ap, char *));
			break;
		default :
			fprintf(stderr, "err fmt\n");
			break;
		}
		++fmt;
	}
	va_end(ap);
}

/*
#define _bnd(X, bnd)            (((sizeof (X)) + (bnd)) & (~(bnd)))
#define va_arg(ap, T)           (*(T *)(((ap) += (_bnd (T, _AUPBND))) - (_bnd (T,_ADNBND))))
#define va_end(ap)              (ap = (va_list) NULL)
#define va_start(ap, A)         (void) ((ap) = (((char *) &(A)) + (_bnd (A,_AUPBND))))*/

void fun_pa(int a, char b, int c)
{
	// 4byte
	printf("a : %x\n", (unsigned int)&a);
	printf("b : %x\n", (unsigned int)&b);
	printf("c : %x\n", (unsigned int)&c);
}

int main(void)
{

	fun1("ddcs", 1, 2, 'c', "dsdfs");

	fun_pa(1, 2, 3);

	return 0;
}

