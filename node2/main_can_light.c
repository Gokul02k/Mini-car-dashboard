#include"header.h"
#define R_Led 1<<19
#define L_Led 1<<17
#define b 1<<21
int main ()
{
	CAN2_MSG m1; 
	can2_init();
	IODIR0|=R_Led|L_Led|b;
	IOSET0|=R_Led|L_Led;
	while(1)
	{
		can2_rx(&m1);
		if (m1.byteA==1)	
		{
			char i=0;
			while(i++<5)
			{
				IOCLR0=R_Led;			
				IOSET0=b;
				delay_s(2);
				IOSET0=R_Led;
				IOCLR0=b;
				delay_s(1);
			}
		}
		if (m1.byteA==2)	
		{
			char i=0;
			while(i++<5)
			{
				IOCLR0=L_Led;			
				IOSET0=b;
				delay_s(2);
				IOSET0=L_Led;
				IOCLR0=b;
				delay_s(1);
			}
		}
	}
}
