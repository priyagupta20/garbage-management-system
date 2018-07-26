#include<reg51.h>
sbit led=P3^3;
sbit buzzer=P2^1;
sbit RS=P2^0;
sbit EN=P2^2;
sbit ECHO=P3^4;
sbit trig=P0^5;
unsigned int i,j,range,height;

void cmdlcd(unsigned char cmd);
void datalcd(unsigned char dat);
void delay(unsigned int ms);
unsigned int ultrasonic(void);

void main()
{while(1)
	{led=1; buzzer=1;
		cmdlcd(0x38); delay(5);
    cmdlcd(0x0E); delay(5);
    cmdlcd(0x01); delay(5);
    cmdlcd(0x80); delay(5);
    range=ultrasonic();
    height=10;
    if(range>=0.75*height)
    {buzzer=0; 
		 datalcd('R');
     datalcd('E');	
     datalcd('Q');
     datalcd('U');
     datalcd('I');	
     datalcd('R');	
     datalcd('E');
     datalcd('S');
     datalcd(' ');
		 datalcd('C');
		 datalcd('L');
		 datalcd('E');
		 datalcd('A');
		 datalcd('N');
		 datalcd('I');
		 datalcd('N');
		 datalcd('G');}
		else if(range>=0.5*height)
		        {led=0;
						 datalcd('A');
						 datalcd('C');
						 datalcd('C');
						 datalcd('E');
						 datalcd('P');
						 datalcd('T');
						 datalcd('A');
						 datalcd('B');
						 datalcd('L');
						 datalcd('E');}
					else 
					  {datalcd('C');
					   datalcd('L');
					   datalcd('E');
					   datalcd('A');
					   datalcd('N');}
	 }
}

void cmdlcd(unsigned char cmd)
{ P1=cmd; RS=0;  EN=1;
	for(i=0;i<100;i++);
	EN=0; }

void datalcd(char dat)
{ P1=dat; RS=1;  EN=1;
	for(i=0;i<100;i++);
0	EN=0; }



unsigned int ultrasonic(void)
{ unsigned int target_range=0,timer_val;
	P3|=0x04;		//P3.2 as INPUT
		TMOD=0x01;
		TH0=0xFF;TL0=0xF5;
		trig=1;
		TR0=1;
		while(!TF0);
		TR0=0;
		TF0=0;
		TMOD=0x09;		//timer0 in 16 bit mode with gate enable
		TH0=0x00; TL0=0x00;
		TR0=1;		//timer0 run enabled
		trig=0;
		while(!INT0);
		while (INT0);
		TR0=0;
		timer_val=TH0<<8|TL0;
		if(timer_val<35000)
			target_range=timer_val*0.01860775;
		else
			target_range=0; // indicates that there is no obstacle in front of the sensor
		return(target_range);
}

void delay(unsigned int ms)
{ for(i=0;i<ms;i++)
	 for(j=0;j<1000;j++);
}