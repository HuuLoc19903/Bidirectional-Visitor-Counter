#include <reg51.h>

sbit but1=P1^0; //entry
sbit but2=P1^1; //exit
sbit rs=P1^2;
sbit rw=P1^3;
sbit en=P1^4;
void lcdcmd(unsigned char);
void lcddat(unsigned char);
void delay();
void lcddisp(unsigned char *s, unsigned char r);
void lcdconv(unsigned char);
void main()
{
      unsigned char x,y;
			int a1=0;
			int a2=0;
      lcdcmd(0x38);
      delay();
      lcdcmd(0x01);
      delay();
      lcdcmd(0x10);
      delay();
      lcdcmd(0x0c);
      delay();
			lcdcmd(0x80);
			delay();
      lcddisp("WELCOME", 7);
      lcdcmd(0xc0);
      delay();	
      lcddisp("VISITOR COUNTER", 15);
      delay();
      while(1)
      {	
	    if(but1==0)
			{
			a1++;
			if (a1==1 && a2==0)
			{
			lcdcmd(0x01);
			delay();
			}
		  lcdcmd(0x80);
		  delay();
		  lcddisp("ENTRY: ", 6);
		  lcdcmd(0x87);
		  delay();
		  x++;
		  lcdconv(x);
	    }
	    if(but2==0)
			{
			a2++;
			if(a2==1 && a1==0)
			{
//		lcdcmd(0x01);
			delay();
			}
		  lcdcmd(0xc0);
		  lcddisp("EXIT: ",5);
		  lcdcmd(0xc6);
		  delay();
		  y++;
			if(y>x)
			{
			lcdcmd(0x01);
//		lcdcmd(0x80);
			lcddisp("ERROR!", 6);
			delay();
			y--;
			continue;
			}
		  lcdconv(y);
		  delay();				
	    }
		}
}
void lcdcmd(unsigned char value)
{
      P2 = value;
      rs = 0;
      rw = 0;
      en = 1;
      delay();
      en = 0;
}
void lcddat(unsigned char dat)
{
      P2 = dat;
      rs = 1;
      rw = 0;
      en = 1;
      delay();
      en = 0;
}
void lcddisp(unsigned char *s, unsigned char r)
{
      unsigned char w;
      for (w=0;w<r;w++)
      {
	    lcddat(s[w]);
	    delay();
      }
}
void lcdconv(unsigned char num)
{
			unsigned char p, n;
      p=num/10;
      n=num%10;
      p=p+0x30;
      n=n+0x30;
      lcddat(p);
      lcddat(n);
}
void delay()
{
      unsigned int k, l;
      for(k=0;k<3000;k++);
      for(l=0;l<100;l++);
}