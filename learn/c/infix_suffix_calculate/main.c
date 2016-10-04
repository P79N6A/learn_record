/*************************************************************************
> File Name: main.c
> Author: orient lu
> Mail: lcdsdream@126.com
> Created Time: Mon 03 Oct 2016 09:47:52 PM PDT
************************************************************************/

#include<stdio.h>

// '0' - '9' '*' '\' '+' '-'
#define STACK_DEEP	2048
static int stack[STACK_DEEP];
static int stack_top = 0;

void stack_push(int value)
{
	if (stack_top < STACK_DEEP) {
		stack[stack_top++] = value;
	} else {

		printf("stack full\n");
	}
}

int stack_pop(void)
{
	if (stack_top > 0) {
		return stack[--stack_top];
	} else {
		return 0;
	}
}


static char suffix[1024];

void infix_to_suffix(char *infix)
{
	int symbol_pop_count = 0;
	int suffix_index = 0;

	// infix -> suffix
	while ((*infix) != 0) {
		while ((*infix) <= '9' && (*infix) >= '0') {
			suffix[suffix_index++] = *infix++;
		}
		if (*infix == '*' || *infix == '/' || *infix == '+' || *infix == '-') {
			++symbol_pop_count;
			stack_push(*infix++);
		}
		if (*infix == ')' && symbol_pop_count) {
			--symbol_pop_count;
			suffix[suffix_index++] = stack_pop();
			infix++;
		}
		if (*infix == '(' || *infix == ' ') {
			infix++;
		}
	}
	while (symbol_pop_count--) {
		suffix[suffix_index++] = stack_pop();
	}

	suffix[suffix_index] = 0;
}

// number < 10
int calculate_suffix(char *suffix)
{
	while (*suffix != 0) {
		while ((*suffix) <= '9' && (*suffix) >= '0') {

			stack_push((*suffix++) - '0'); // char -> int

		}
		if (*suffix == '+') {
			stack_push(stack_pop() + stack_pop());
		}
		if (*suffix == '-') {
			char b = stack_pop();
			char a = stack_pop();
			stack_push(a - b);
		}
		if (*suffix == '*') {
			stack_push(stack_pop() * stack_pop());
		}
		if (*suffix == '/') {
			char b = stack_pop();
			char a = stack_pop();
			stack_push(a / b);
		}
		++suffix;
	}
	return stack_pop();
}


int main(int argc, char* argv[])
{
	char infix[] = "(5 * (((9 + 8) * (4 * 6)) + 7))";
	// suffix : 598+46**7+*
	printf("Infix : [ %s ]\n", infix);

	infix_to_suffix(infix);
	printf("Suffix : [ %s ]\n", suffix);

	int result = calculate_suffix(suffix);
	printf("Result : [ %d ]\n", result);

	return 0;
}

