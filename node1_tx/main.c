#include"header.h"
#define sw1 (IOPIN0&(1<<14))
#define sw2 (IOPIN0&(1<<15))
#define sw3 (IOPIN0&(1<<16))

u8 R[]={0x10,0x18,0x1c,0x1e,0x1c,0x18,0x10,0x00
			,0x01,0x03,0x07,0x0f,0x07,0x03,0x01,0x00};
void CG_write(void)
{
	char i;
	LCD_COMMAND(0X40);
	for(i=0;i<16;i++)		LCD_DATA(R[i]);
}
//#include"msg.h"
int main()
{
	CAN2_MSG m1,m2,m3;
	m1.id=0X01;
	m2.id=0X02;
	m3.id=0X03;
	m1.rtr = m2.rtr= m3.rtr = 0;
	m1.dlc = m2.dlc= m3.dlc = 1;
	m1.byteA=m1.byteB=0;
	m2.byteA=m2.byteB=0;
	m3.byteA=m3.byteB=0;
	can2_init();
	uart_init(115200);
	LCD_init();
	uart_tx_str("node1 ready\r\n");
	LCD_COMMAND(0X01);
	delay_ms(10);
	LCD_COMMAND(0X80);
	delay_ms(10);
	Disp_str("Can nodes ready");
	delay_ms(100);
	while(1)
	{
		if (sw1==0)
		{
			LCD_COMMAND(0X01);
	    delay_ms(10);
			LCD_COMMAND(0X80);
	    delay_ms(10);
			Disp_str("Indicator mode");
	    delay_ms(10);
			uart_tx_str("Indicator mode\r\n");
			while(sw1==0);
			
			
			while(1)
			{
				if (sw1==0)
				{
		    	LCD_COMMAND(0X01);
					uart_tx_str("Out from Indicator mode\r\n");
					break;
				}
				if (sw2==0)
				{
					uart_tx_str("RIGHT LIGHT \r\n");
					CG_write();
					LCD_COMMAND(0XC5);
	        delay_ms(10);
					LCD_DATA(0);
	        delay_ms(10);
					LCD_DATA(0);
	        delay_ms(10);
					m1.byteA=0X1;
					can2_tx(m1);
					uart_tx_str("RIGHT LIGHT is on...\r\n");
					while(sw2==0);
				}
				if (sw3==0)
				{
					uart_tx_str("LEFT LIGHT \r\n");
					LCD_COMMAND(0X01);
					delay_ms(10);
					Disp_str("Indicator mode");
					delay_ms(10);
					LCD_COMMAND(0XC2);
					delay_ms(10);
					LCD_DATA(1);
	        delay_ms(10);
					LCD_DATA(1);
	        delay_ms(10);
					m1.byteA=0X2;
					can2_tx(m1);
					uart_tx_str("LEFT LIGHT is on...\r\n");
					while(sw3==0);
				}
			}
			
			
			while(sw1==0);
		}
		if (sw2==0)
		{
			uart_tx_str("Buzzer\r\n");
			LCD_COMMAND(0X01);
	    delay_ms(10);
			LCD_COMMAND(0X80);
	    delay_ms(10);
			Disp_str("buzzer");
	    delay_ms(100);
			can2_tx(m2);
			uart_tx_str("Buzzer is on...\r\n");
			while(sw2==0);
		}
		if (sw3==0)
		{
			uart_tx_str("MOTOR \r\n");
			LCD_COMMAND(0X01);
	    delay_ms(10);
			LCD_COMMAND(0X80);
	    delay_ms(10);
			Disp_str("Motor running");
	    delay_ms(100);
			can2_tx(m3);
			uart_tx_str("MOTOR is running...\r\n");
			while(sw3==0);
		}
		//delay_s(2);
		//Disp_str("Indicator mode");
		 //delay_ms(100);
	}
}
