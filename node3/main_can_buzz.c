#include"header.h"
#define buzz 1<<21

int main()
{
	CAN2_MSG m1; 
	can2_init();                                                                                                                                                                                                                                    
	IODIR0|=buzz;
// 	IOSET0|=buzz;
	while(1)
	{
		can2_rx(&m1);
		if(m1.id==2)
		{
			IOSET0|=buzz;
			delay_s(1);
			IOCLR0=buzz;
			delay_s(1);
			IOSET0|=buzz;
			delay_s(1);
			IOCLR0=buzz;
			delay_s(1);
			IOSET0|=buzz;
			delay_s(2);
			IOCLR0=buzz;
		}
	}
}
