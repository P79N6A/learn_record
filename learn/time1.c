/*************************************************************************
	> File Name: time1.c
	> Author: luchaodong
	> Mail: luchaodong@meizu.com
	> Created Time: 2016年02月03日 星期三 16时11分25秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int main()
{
	time_t time_raw_foramt;
	time ( &time_raw_foramt );
	printf (" Time is [%d]\n", (int)time_raw_foramt);
	printf (" The local time : %s\n", ctime( &time_raw_foramt ));
	return 0;
}
