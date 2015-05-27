#include "kalman.h"

#include "stdio.h"
#include "stdlib.h"
#include "PID_Control.h"

void main(void)

{
	KalmanCountData k;
	PID PIDControlStruct;
	Kalman_Filter_Init(&k);
	PIDInit(50, 1, 0.04, 0.2, &PIDControlStruct);
	int m,n;

	double out;

	for(int a = 0;a<80;a++)
	{
		m = 1+ rand() %100;
		n = 1+ rand() %100;
        	Kalman_Filter((float)m,(float)n,&k);
		out = PIDCalc(k.Angle_Final, &PIDControlStruct);
		printf("%3d and %3d is %6f -pid- %6f\r\n",m,n,k.Angle_Final,out);

	}
}

