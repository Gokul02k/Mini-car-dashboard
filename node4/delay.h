
void delay_s(int s)
{
	T0PR=15000000-1;
	T0TCR= 0X01;
	while(T0TC<s);
	T0TCR=0X03;
	T0TCR=0X00;
}

void delay_ms(int ms)
{
	T0PR=15000-1;
	T0TCR= 0X01;
	while(T0TC<ms);
	T0TCR=0X03;
	T0TCR=0X00;
}
