#include<lpc214x.h>


//to read matrix keyboard
#define COL0 (IO1PIN & 1U<<19)
#define COL1 (IO1PIN & 1U<<18)
#define COL2 (IO1PIN & 1U<<17) 
#define COL3 (IO1PIN & 1U<<16)

//to read configuration pins
#define SW2 (IOPIN0 & (1U << 14))
#define SW6 (IOPIN1 & (1U << 20))
#define SW5 (IO1PIN & (1 << 19))

#define LED_ON (IO0CLR = 1U << 31)
#define LED_OFF (IO0SET = 1U << 31)

//to produce software delay, depends on clock cycle
void delay(unsigned int i)
{
	int j,x;
	for(j=0;j<i;j++){
		for(x=0;x<10000;x++);
	}
}

void uart_init(void){
PINSEL0|=0X00000005;
U0LCR=0X83;
	U0DLM=0;
	U0DLL=8;
	U0LCR=0X03;
	U0FCR=0X07;
}

//to set the characters produced from matrix keyboard
unsigned char Lookup_table[4][4]={{'0','1','2','3'},{'4','5','6','7'},{'8','9','A','B'},{'C','D','E','F'}};


unsigned int rowsel=0,colsel=0;

//to display chars in 7-seg display
unsigned char alpha7(unsigned char alphachar)
{
switch(alphachar){
	case '0':return 0xc0;
	case '1':return 0xf9;
	case '2':return 0xa4;
	case '3':return 0xb0;
	case '4':return 0x99;
	case '5':return 0x92;
	case '6':return 0x82;
	case '7':return 0xf8;
	case '8':return 0x80;
	case '9':return 0x90;
	case 'A':return 0x88;
	case 'B':return 0x83;
	case 'C':return 0xc6;
	case 'D':return 0xa1;
	case 'E':return 0x86;
	case 'F':return 0x8e;
	case 'G':return 0xc2;
	case 'H':return 0x89;
	case 'I':return 0xf9;
	case 'J':return 0xe1;
	case 'K':return 0x8a;
	case 'L':return 0xc7;
	case 'M':return 0xea;
	case 'N':return 0xc8;
	case 'O':return 0xc0;
	case 'P':return 0x8c;
	case 'Q':return 0xa4;
	case 'R':return 0xce;
	case 'S':return 0x92;
	case 'T':return 0x87;
	case 'U':return 0xc1;
	case 'V':return 0xd5;
	case 'W':return 0xe2;
	case 'X':return 0x89;
	case 'Y':return 0x91;
	case 'Z':return 0xa4;
	
	case '-': return 0xbf;
	case ' ': return 0xff;
	default : return 0xbf;
	
}
}

void alpha7segdisplay(char *buf, unsigned int k){
	unsigned char temp=0,alpha;
	unsigned char i,j;

		for(i=0;i<k;i++)
		{
		alpha=alpha7(*(buf+i));
		for(j=0;j<8;j++){
			temp=alpha&0x80;
			if(temp==0x80)
				IO0SET|=1<<19;
			else
				IO0CLR|=1<<19;
			
			IO0SET=1<<20;
			delay(10);
			IO0CLR=1<<20;
			alpha=alpha<<1;
		}
		IO0SET = 1<<30;
	delay(100);
	IO0CLR = 1<<30;
		}

}

//to red keyboard input
unsigned char Keyboard(){
  
	
	do{
	while(1){
	rowsel=0;IO0SET=0X000F0000;IO0CLR=1<<16;
	if(COL0==0){colsel=0;break;}
	if(COL1==0){colsel=1;break;}
	if(COL2==0){colsel=2;break;}
	if(COL3==0){colsel=3;break;}
	
	rowsel=1;IO0SET=0X000F0000;IO0CLR=1<<17;
	if(COL0==0){colsel=0;break;}
	if(COL1==0){colsel=1;break;}
	if(COL2==0){colsel=2;break;}
	if(COL3==0){colsel=3;break;}
	
	rowsel=2;IO0SET=0X000F0000;IO0CLR=1<<18;
	if(COL0==0){colsel=0;break;}
	if(COL1==0){colsel=1;break;}
	if(COL2==0){colsel=2;break;}
	if(COL3==0){colsel=3;break;}
	
	rowsel=3;IO0SET=0X000F0000;IO0CLR=1<<19;
	if(COL0==0){colsel=0;break;}
	if(COL1==0){colsel=1;break;}
	if(COL2==0){colsel=2;break;}
	if(COL3==0){colsel=3;break;}
	};
	delay(50);
	while(COL0==0||COL1==0||COL2==0||COL3==0){
		LED_OFF;
		
	}
	alpha7segdisplay(" ", 1);
	delay(50);
	IO0CLR=0X00FF0000;
	return Lookup_table[rowsel][colsel];
	}
	while(1);
	

}
//to control stepper motor for door operation
void DoorRotate(unsigned int c, unsigned int dir){
	

	if(dir==1){
	do{
	IO0CLR=0X000F0000;IO0SET=0X00010000;delay(10);if(--c==0)break;
	IO0CLR=0X000F0000;IO0SET=0X00020000;delay(10);if(--c==0)break;
	IO0CLR=0X000F0000;IO0SET=0X00040000;delay(10);if(--c==0)break;
	IO0CLR=0X000F0000;IO0SET=0X00080000;delay(10);if(--c==0)break;
	}while(1);
	IO0CLR=0X00FF0000;
	}


	if(dir==0){
	do{
	IO0CLR=0X000F0000;IO0SET=0X00080000;delay(10);if(--c==0)break;
	IO0CLR=0X000F0000;IO0SET=0X00040000;delay(10);if(--c==0)break;
	IO0CLR=0X000F0000;IO0SET=0X00020000;delay(10);if(--c==0)break;
	IO0CLR=0X000F0000;IO0SET=0X00010000;delay(10);if(--c==0)break;
	}while(1);
	IO0CLR=0X00FF0000;
	}


}
//to read proximity sensor
int readSensor(int sen_no)
{
	int result=0;
	IO1CLR=1<<24;
	switch(sen_no)
	{
		case 1:result=IO1PIN&(1<<22);
		break;
		case 2: result=IO1PIN&(1<<23);
		break;
		default : result=0;
	};
	IO1SET=1<<24;
	return result;
}

//void beep(unsigned int val)
//{
//	
//	PINSEL1 |= 0x00080000;	
//	DACR = ((1<<16) | (val << 6));
//	
//	delay(500);
//	DACR = ((1<<16) | (1023 << 6));
//	delay(5);
//	
//}

	

int main()
{ 

IO0DIR|=1U<<19|1U<<20|1U<<30;
IO0DIR|=(0X00FF0000) | (1U<<31) | (1U<<25);
	int result;
	IO1DIR|=1<<24;
	//beep(50);
IOSET0 = 1U<<25;
	
unsigned int i;
 char letter, password[4];
unsigned char pass[5] = {'1', '2', '3', '4'};

int auth = 0;
int flag=0;
while(1){
	while(!auth){
if(!SW2)
 {

 if(!flag){
  alpha7segdisplay("  PASSCODE", 10);
  for(i=0; i<4; i++)
  {
  
   letter = '-';
   while(1)
   {
   letter = Keyboard();
   
   if(letter != '-')
   {break;}
   }
   password[i] = letter;
   
   
  }
	
	alpha7segdisplay(&password[0], 4);
  flag=1;
  for(i=0; i<4; i++)
  {
    if(password[i] !=  pass[i])
 flag = 0;	
  }
  
  if(flag == 0)
  {
		auth=0;
  alpha7segdisplay("FALSE", 9);
  
  }
	else{
		auth =1;
	alpha7segdisplay("SUCCESS", 7);
	
		
	}
  }

  
 }
 
}
int auth2=1;
int x;
int Beeper = 1;
while(auth2){
		result=readSensor(1);
	if(!SW6){
		auth =0;
		auth2=0;
		flag =1;
	}
	
	if(!SW5 && Beeper == 1)
	{alpha7segdisplay("BEEP-OFF",8);
	 Beeper = 0;
		delay(1000);
	}
	if(!SW5 && Beeper == 0)
	{alpha7segdisplay(" BEEP-ON ",9);
	 Beeper = 1;
	}
		
	
	
		if(result)
			
		{
		
			
			DoorRotate(50,1);
			alpha7segdisplay(" OPEN",5);
			if(Beeper)IOCLR0 = 1U<<25;
			delay(1000);
			
			if(Beeper) IOSET0 = 1U<<25;
			DoorRotate(50,0);
		
	}
		
		else{
		
			
			alpha7segdisplay(" CLOSE",6);
			
			
			
		}
}



}
 
 

}
