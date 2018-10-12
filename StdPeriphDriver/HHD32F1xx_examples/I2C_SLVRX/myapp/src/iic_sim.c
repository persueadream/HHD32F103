#include "hhd32f1xx.h"
#define SDA_H  HHD_GPIOB->SET = (1<<7)
#define SDA_L  HHD_GPIOB->CLR = (1<<7)
#define SCL_H  HHD_GPIOB->SET = (1<<6)
#define SCL_L  HHD_GPIOB->CLR = (1<<6)

#define SDA_RD  HHD_GPIOB->DIR &= ~(1<<7);
#define SDA_WR  HHD_GPIOB->DIR |= (1<<7);
#define RDSDA   (HHD_GPIOB->PIN&(1<<7))

void delay_us(int i)
{
	int ust;
	while(i--)
	{
		ust=40;
		while(ust--);
	}
}

void IicStart()  
{  
  
    SDA_H;  
    SCL_H;  
    delay_us(5);  
    SDA_L;  
    delay_us(5);  
    SCL_L;             
    delay_us(2);  
    SDA_H;  
    delay_us(2);  
}  
  
void IicStop()  
{  
    SDA_L;  
    SCL_L;  
    delay_us(2);  
  
    SCL_H;  
    delay_us(2);  
    SDA_H;         
    delay_us(2);  
//    SCL_L;               
      
//    delay_us(2);    
}  
void IicAck() 
{  
    SCL_L;  
    SDA_L;  
    delay_us(5);  
  
    SCL_H;  
    delay_us(5);
    SCL_L;  
  
    delay_us(2);  
    SDA_H;  
    delay_us(2);  
}  
  
void IicNack() 
{  
    SCL_L;  
    SDA_H;  
    delay_us(5);  
  
    SCL_H;  
    delay_us(5); 
    SCL_L;  
  
    delay_us(2);  
    SDA_H;  
    delay_us(2);  
}  
char IicWaiteAck()  
{     
	char ack;
    SCL_L;  
//    SDA_H;  
		SDA_RD;
    delay_us(2);  
  
    SCL_H;  
    delay_us(2);
    if(RDSDA)  
      ack=1;  
    else  
      ack=0;   
    SCL_L;  
    delay_us(2); 
	SDA_WR;
    delay_us(2);  
	return ack;
}  
void IicSendByte(uint8_t temp)  
{  
    uint8_t i;  
  
    for(i=0;i<8;i++)  
    {  
        SCL_L;  
        delay_us(3);  
        if(temp&0x80)     
            SDA_H;  
        else  
            SDA_L;
        delay_us(2);  
        SCL_H;  
        delay_us(5);  
        SCL_L;  
        temp<<=1;  
    }  
      
    delay_us(2);  
    SDA_H;  
    delay_us(2);  
          
}  
  
uint8_t IicReceiveByte()  
{  
    uint8_t i,temp=0;  
  
    delay_us(2);  
    SDA_H;          
    delay_us(2);             
  
    SDA_RD;
    for(i=0;i<8;i++)  
    {  
        temp<<=1;  
        SCL_L;  
        delay_us(5);  
        SCL_H;  
        delay_us(2);  

        if(RDSDA)  
            temp=temp|0x01;  
        else  
            temp=temp&0xFE;   
    }  
    SDA_WR;
  
    SCL_L;  
    delay_us(2);  
    return temp;      
}  

/*
void IICSendData(uint8_t addr, uint32_t data)
{
	uint8_t i,j;
	uint8_t *p;
	p=(uint8_t*)&data;
  IicStart();  
  IicSendByte(0xA0);     
  IicWaiteAck();
  IicSendByte(addr);  
  IicWaiteAck();
	for(i=0;i<4;i++)  
	{  
		IicSendByte(*(p+i));    
		IicWaiteAck();  
	}
  IicStop();  
  delay_us(4);  
}
*/
void IICSendData(uint8_t addr, uint32_t data)
{
	uint8_t i;
	uint32_t waitlimit;
	uint8_t *p;
	p=(uint8_t*)&data;
//	for(i=0;i<4;i++)
	{
		IicStart();  
		IicSendByte(0xA0);     
		IicWaiteAck();
		IicSendByte(addr++);  
		IicWaiteAck();

		IicSendByte(*(p+0));    
		IicWaiteAck();  

		IicSendByte(*(p+1));    
		IicWaiteAck();  

		IicSendByte(*(p+2));    
		IicWaiteAck();  

		IicSendByte(*(p+3));    
		IicWaiteAck();  
		IicStop();  
#if 0
		waitlimit=1000;
  	while(waitlimit--)    //acknology polling
	  {
      IicStart();  
      IicSendByte(0xA0);     
    	if(0==IicWaiteAck())
	    {
        IicStop();  
    		break;
	    }
      IicStop();  
			delay_us(10);
	  }
#endif
     delay_us(10);
	
  }

	delay_us(10);
}
/*
void IICReceiveData(uint8_t addr, uint32_t *data)
{
	uint8_t i,*p;
	p=(uint8_t*)data;
  IicStart();  
  IicSendByte(0xA0);      
  if(0==IicWaiteAck())
		delay_us(1);
  IicSendByte(addr);  
  IicWaiteAck();  

  IicStart();    
  IicSendByte(0xA1); 
	
  for(i=0;i<4;i++)       
  {  
     IicAck();  
    *(p+i)=IicReceiveByte();  
  }  
  IicNack();  
  IicStop();  
}
*/

void IICReceiveData(uint8_t addr, uint32_t *data)
{
#if 0
  uint8_t *p;
  p=(uint8_t*)data;
  IicStart();  
  IicSendByte(0xA0);      
  IicWaiteAck();
  IicSendByte(addr);  
  IicWaiteAck();  
  IicStart();    
  IicSendByte(0xA1); 
  IicWaiteAck();  
  *p++=IicReceiveByte();  
  IicAck();  
  *p++=IicReceiveByte();  
  IicAck();  
  *p++=IicReceiveByte();  
  IicAck();  
  *p++=IicReceiveByte();  
  IicNack();  
  IicStop();  

#else   //this program can work
	uint8_t *p;
	p=(uint8_t*)data;
  IicStart();  
  IicSendByte(0xA0);      
  IicWaiteAck();
  IicSendByte(addr);  
  IicWaiteAck();  
  IicStart();    
  IicSendByte(0xA1); 
  IicWaiteAck();  
  *p++=IicReceiveByte();  
  IicNack();  
  IicStop();  

  IicStart();  
  IicSendByte(0xA0);      
  IicWaiteAck();
  IicSendByte(addr+1);  
  IicWaiteAck();  
  IicStart();    
  IicSendByte(0xA1); 
  IicWaiteAck();  
  *p++=IicReceiveByte();  
  IicNack();  
  IicStop();  

  IicStart();  
  IicSendByte(0xA0);      
  IicWaiteAck();
  IicSendByte(addr+2);  
  IicWaiteAck();  
  IicStart();    
  IicSendByte(0xA1); 
  IicWaiteAck();  
  *p++=IicReceiveByte();  
  IicNack();  
  IicStop();  

  IicStart();  
  IicSendByte(0xA0);      
  IicWaiteAck();
  IicSendByte(addr+3);  
  IicWaiteAck();  
  IicStart();    
  IicSendByte(0xA1); 
  IicWaiteAck();  
  *p++=IicReceiveByte();  
  IicNack();  
  IicStop();  
#endif
}

void IicTest()
{
	unsigned int data;
//		IICReceiveData(4,&data);
//	IICSendData(4,0x1234567);
//	IICReceiveData(4,&data);
//	IICReceiveData(16,&data);
//	(*(unsigned int*)0x20000000)=data;
	IICSendData(0,0xffffffff);
	IICSendData(4,0xffffffff);
	IICReceiveData(4,&data);
	IICReceiveData(0,&data);
	
}
