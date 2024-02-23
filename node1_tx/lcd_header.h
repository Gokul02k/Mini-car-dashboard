#include <LPC21XX.h>
#define LCD_D 0X00f00000
#define RS 1<<17
#define RW 1<<18
#define E 1<<19

void LCD_init(void);
void LCD_COMMAND(unsigned char);
void LCD_DATA(unsigned char);
void Disp_int(int);
void Disp_float(float);
void Disp_str(char *);
void Rotate(char*);

void LCD_init(void)
{
	IODIR1 |= LCD_D|RS|E|RW;
	IOCLR1|=RW;
	LCD_COMMAND(0x01);
	LCD_COMMAND(0x02);
	LCD_COMMAND(0x0C);
	LCD_COMMAND(0x28);
	LCD_COMMAND(0x80);
}

void LCD_COMMAND(unsigned char cmd)
{
	IOCLR1|=LCD_D;
	IOSET1|=((cmd&0xf0)<<16);
	IOCLR1|=RS;
	IOSET1|=E;
	delay_ms(2);
	IOCLR1|=E;
	
	IOCLR1|=LCD_D;
	IOSET1|=((cmd&0x0f)<<20);
	IOCLR1|=RS;
	IOSET1|=E;
	delay_ms(2);
	IOCLR1|=E;
}

void LCD_DATA(unsigned char a)
{
	IOCLR1|=LCD_D;
	IOSET1|=((a&0xf0)<<16);
	IOSET1|=RS;
	IOSET1|=E;
	delay_ms(2);
	IOCLR1|=E;
	
	IOCLR1|=LCD_D;
	IOSET1|=((a&0x0f)<<20);
	IOSET1|=RS;
	IOSET1|=E;
	delay_ms(2);
	IOCLR1|=E;
}

void Disp_int(int n)
{
	signed char i;
	unsigned char arr[10];
	if(n==0) 
		LCD_DATA('0');
	else
	{
		if (n<0)
		{
			LCD_DATA('-');
			n=-n;
		}
		
		for(i=0;n;n/=10)
			arr[i++]=n%10;
		for(--i;i>=0;i--)
			LCD_DATA(arr[i]+48);
	}
}

void Disp_float(float n)
{
	int temp;
	temp=n;
	Disp_int(temp);
	LCD_DATA('.');
	temp=(n-temp)*1000;
	Disp_int(temp);
}

void Disp_str(char *p)
{
	while(*p)
		LCD_DATA(*p++);
}
