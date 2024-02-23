#include"header.h"
#define en 1<<0
#define a1 1<<17
#define a2 1<<18

int main ()
{
	CAN2_MSG m1;
	IODIR0=en|a1|a2;
	IOSET0=en|a2|a1;
	can2_init();                                                                                                                                                                                                                                                                                                                                                                           
	while(1)
	{
		can2_rx(&m1);
		if(m1.id==3)
		{
			char i=0;
			IOSET0=a2|a1;
			while(i++<5)
			{
				IOCLR0=a1;		// turn right ...
				delay_s(3);
				IOSET0=a1;		// stop...
				delay_s(2);
				IOCLR0=a2;		// turn left ... 
				delay_s(3);		
				IOSET0=a2;		 // stop...
				delay_s(2);
			}
		}
	}
}
