void uart_init(unsigned int );
void uart_tx(unsigned char );
unsigned char uart_rx(void);
void uart_tx_str(char *);
void uart_tx_int(int );
void uart_tx_hex(int );

void uart_init(unsigned int baud)
{
	PINSEL0|=0x5;
	U0LCR=0x83;
	switch(baud){	
		case 115200:U0DLL=32;	break;//PCLK=60MHz
		case 9600 :U0DLL=97; break;
		case 921600:U0DLL=4;	break;
		default:	U0DLL=32	;	
	}
	U0LCR=0x03;
}

void uart_tx(unsigned char data)
{
	U0THR=data;
	while((U0LSR&(1<<5))==0);
}

unsigned char uart_rx(void)
{
	while((U0LSR&0x1)==0);
	return U0RBR;
}


void uart_tx_str(char *ptr)
{
	while(*ptr!=0){
		U0THR=*ptr;
		while((U0LSR&(1<<5))==0);
		ptr++;
	}
}

 #include <stdio.h>
void uart_tx_int(int num)
{
	char buf[10];
	sprintf(buf,"%d",num);
	uart_tx_str(buf);
}


void uart_tx_hex(int num)
{
	char buf[10];
	sprintf(buf,"%X",num);
	uart_tx_str(buf);
}

//void uart0_tx_float(float num){		
//	int i=0;
//	i=num;
//	uart0_tx_integer(i);
//	i=(num-i)*10;
//	uart0_tx('.');
//	uart0_tx_integer(i);
//}


