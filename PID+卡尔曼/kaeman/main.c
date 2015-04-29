
#include "kalman.h"

#include "stdio.h"

#include "stdlib.h"

void main(void)
{


	KalmanCountData k;
	//定义一个卡尔曼运算结构体
	Kalman_Filter_Init(&k);
	//讲运算变量初始化
	int m,n;        

   	for(int a = 0;a<80;a++)
	//测试80次
	{

		//m,n为1到100的随机数
		m = 1+ rand() %100;

		n = 1+ rand() %100;

                //卡尔曼滤波，传递2个测量值以及运算结构体
	
	Kalman_Filter((float)m,(float)n,&k);

		//打印结果
		printf("%d and %d is %f - %f\r\n",m,n,k.Angle_Final,k.K_0);
	
	}




}
