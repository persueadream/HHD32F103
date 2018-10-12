#include "delay.h"
#include "system.h"
#define SysTick_CLKSource_HCLK_Div8    ((uint32_t)0xFFFFFFFB)
#define SysTick_CLKSource_HCLK         ((uint32_t)0x00000004)

#if 0
static uint8_t  fac_us=0;							//us��ʱ������			   
static uint16_t fac_ms=0;							//ms��ʱ������,��ucos��,����ÿ�����ĵ�ms��
	
	
			   
//��ʼ���ӳٺ���
//SYSTICK��ʱ�ӹ̶�ΪHCLKʱ�ӵ�1/8
//SYSCLK:ϵͳʱ��
void delay_init(void)
{
  SysTick->CTRL &=0xFFFFFFFB;//ѡ���ⲿʱ��  HCLK/8
/*
9.1.1 ϵͳ���(SysTick)У׼ֵ�Ĵ���
ϵͳ���У׼ֵ�̶�Ϊ9000����ϵͳ���ʱ���趨Ϊ9MHz(HCLK/8�����ֵ)������1msʱ���׼��	
*/	
	fac_us=SystemCoreClock/8000000;				//Ϊϵͳʱ�ӵ�1/8  
	fac_ms=(uint16_t)fac_us*1000;					//��OS��,����ÿ��ms��Ҫ��systickʱ����   
	
	//SysTick_Config(SystemCoreClock/8000000);
}								    

//��ʱnus
//nusΪҪ��ʱ��us��.		    								   
void delay_us(uint32_t nus)
{		
	uint32_t temp;	    	 
	SysTick->LOAD=nus*fac_us ; 				//ʱ�����	  		 
	SysTick->VAL=0x00;        				//��ռ�����
	SysTick->CTRL= 0x01;      				//��ʼ���� 	 
 	do
 	{
 		temp=SysTick->CTRL;
 	}while((temp&0x01)&&!(temp&(0x10000)));	//�ȴ�ʱ�䵽��   
	while(SysTick->CTRL != 0X10001);
	SysTick->CTRL=0x00;      	 			//�رռ�����
	SysTick->VAL =0X00;       				//��ռ�����	 
}
//��ʱnms
//ע��nms�ķ�Χ
//SysTick->LOADΪ24λ�Ĵ���,����,�����ʱΪ:
//nms<=0xffffff*8*1000/SYSCLK
//SYSCLK��λΪHz,nms��λΪms
//��72M������,nms<=1864 
void delay_ms(uint16_t nms)
{	 		  	  
	uint32_t temp;		   
	SysTick->LOAD=(uint32_t)nms*fac_ms;			//ʱ�����(SysTick->LOADΪ24bit)
	SysTick->VAL =0x00;           			//��ռ�����
	SysTick->CTRL=0x01 ;          			//��ʼ����  
	do
	{
		temp=SysTick->CTRL;

	}while((temp&0x01)&&!(temp&(1<<16)));	//�ȴ�ʱ�䵽��   
	SysTick->CTRL=0x00;      	 			//�رռ�����
	SysTick->VAL =0X00;       				//��ռ�����	  	    
} 

#endif

#if 1
/*-------------------------------------------------------------------------------
�ļ����ƣ�SysTick.c
�ļ�������SysTick ϵͳ�δ�ʱ��1us�жϺ�����,�ж�ʱ����������ã�
          ���õ��� 1us 10us 1ms �жϡ�        
��    ע������Ĭ��ʹ��72Mʱ�ӣ��޷�Ƶ 
---------------------------------------------------------------------------------*/
//#include "delay.h"

static __IO uint32_t TimingDelay;

/*-------------------------------------------------------------------------------
�������ƣ�SysTick_Init
��������������ϵͳ�δ�ʱ�� SysTick
�����������
���ز�������
��    ע��ʹ�ô˹���֮ǰ��Ҫ���ô˺�������ʼ���Ĵ����Ȳ���
---------------------------------------------------------------------------------*/
void SysTick_Init(void)
{
	 // SystemFrequency / 1000     1ms�ж�һ��
	 // SystemFrequency / 100000	 10us�ж�һ��
	 // SystemFrequency / 1000000  1us�ж�һ��
	 //t1=1/72M  t2 = 72*(t1) = 1 us
	if (SysTick_Config(SystemCoreClock / 1000))	// 1us ST3.5.0��汾
	{ 
		//SysTick->CTRL &= SysTick_CLKSource_HCLK_Div8;
		/* Capture error */ 
		while (1);
	}

}


/*-------------------------------------------------------------------------------
�������ƣ�Delay_us 
������������ʱnTime us  (max 233016us)
���������nTime
���ز�������
��    ע����
---------------------------------------------------------------------------------*/
void delay_us(__IO uint32_t nTime)
{ 
	TimingDelay = nTime;	
  
	//while(TimingDelay != 0);
	while(TimingDelay > 0);
}

/*-------------------------------------------------------------------------------
�������ƣ�Delay_us
������������ʱnTime us   (max 233ms)
���������nTime 
���ز�������
��    ע����
---------------------------------------------------------------------------------*/
void delay_ms(__IO uint32_t nTime)
{ 
	TimingDelay = nTime;	
  //DEBUG("delay_ms\r\n");
	//while(TimingDelay != 0);
	while(TimingDelay > 0);
}

/*-------------------------------------------------------------------------------
�������ƣ�TimingDelay_Decrement
�������������ֵݼ�ֱ��0  
�����������
���ز�������
��    ע����Ҫ���жϺ���SysTick_Handler()�е���
---------------------------------------------------------------------------------*/
void TimingDelay_Decrement(void)
{
	if (TimingDelay != 0x00)
	{ 
	TimingDelay--;
	}
}



void SysTick_Handler()
{
	TimingDelay_Decrement();
}
#endif
/*----------------------end of--------------------------*/

