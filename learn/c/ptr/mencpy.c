//内存块复制
//20150310

#include <stdio.h>
#include <assert.h>

/*不破坏原来内存块*/
void *mencpy_1(void *dst, const void *src, size_t num)
{
	assert(dst != NULL && src != NULL);

	unsigned char *pdst = (unsigned char *)dst;
	const unsigned char *psrc = (unsigned char *)src;

	assert((psrc < pdst && pdst >= psrc+num));
	assert((pdst < psrc && psrc >= pdst+num));

	while (num--)
		*pdst++ = *psrc++;
	return (void*) dst;
}

/*保证数据复制，允许覆盖源内存块*/
void *mencpy(void *dst, void *src, size_t num)
{
	assert(dst != NULL && src != NULL);
	unsigned char *pdst = (unsigned char *)dst;
	unsigned char *psrc = (unsigned char *)src;

	if (pdst >  psrc && pdst < psrc+num) {
		pdst += num-1;
		psrc += num-1;
		while (num--)
			*pdst-- = *psrc--;
	} else if (pdst != psrc){
		while (num--)
			*pdst++ = *psrc++;
	} else {}
	return (void *)dst;
}

int main()
{
	char a[] = "nihao";
	char b[] = "lucha";

	printf("a : %s b : %s\n", a, b);
	printf("a : %s b : %s\n", a, (char*)mencpy(b, a, 6));
	return 0;
}
