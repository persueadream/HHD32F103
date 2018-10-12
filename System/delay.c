#include "delay.h"
#include "system.h"
#define SysTick_CLKSource_HCLK_Div8    ((uint32_t)0xFFFFFFFB)
#define SysTick_CLKSource_HCLK         ((uint32_t)0x00000004)

#if 0
static uint8_t  fac_us=0;							//us延时倍乘数			   
static uint16_t fac_ms=0;							//ms延时倍乘数,在ucos下,代表每个节拍的ms数
	
	
			   
//初始化延迟函数
//SYSTICK的时钟固定为HCLK时钟的1/8
//SYSCLK:系统时钟
void delay_init(void)
{
  SysTick->CTRL &=0xFFFFFFFB;//选择外部时钟  HCLK/8
/*
9.1.1 系统嘀嗒(SysTick)校准值寄存器
系统嘀嗒校准值固定为9000，当系统嘀嗒时钟设定为9MHz(HCLK/8的最大值)，产生1ms时间基准。	
*/	
	fac_us=SystemCoreClock/8000000;				//为系统时钟的1/8  
	fac_ms=(uint16_t)fac_us*1000;					//非OS下,代表每个ms需要的systick时钟数   
	
	//SysTick_Config(SystemCoreClock/8000000);
}								    

//延时nus
//nus为要延时的us数.		    								   
void delay_us(uint32_t nus)
{		
	uint32_t temp;	    	 
	SysTick->LOAD=nus*fac_us ; 				//时间加载	  		 
	SysTick->VAL=0x00;        				//清空计数器
	SysTick->CTRL= 0x01;      				//开始倒数 	 
 	do
 	{
 		temp=SysTick->CTRL;
 	}while((temp&0x01)&&!(temp&(0x10000)));	//等待时间到达   
	while(SysTick->CTRL != 0X10001);
	SysTick->CTRL=0x00;      	 			//关闭计数器
	SysTick->VAL =0X00;       				//清空计数器	 
}
//延时nms
//注意nms的范围
//SysTick->LOAD为24位寄存器,所以,最大延时为:
//nms<=0xffffff*8*1000/SYSCLK
//SYSCLK单位为Hz,nms单位为ms
//对72M条件下,nms<=1864 
void delay_ms(uint16_t nms)
{	 		  	  
	uint32_t temp;		   
	SysTick->LOAD=(uint32_t)nms*fac_ms;			//时间加载(SysTick->LOAD为24bit)
	SysTick->VAL =0x00;           			//清空计数器
	SysTick->CTRL=0x01 ;          			//开始倒数  
	do
	{
		temp=SysTick->CTRL;

	}while((temp&0x01)&&!(temp&(1<<16)));	//等待时间到达   
	SysTick->CTRL=0x00;      	 			//关闭计数器
	SysTick->VAL =0X00;       				//清空计数器	  	    
} 

#endif

#if 1
/*-------------------------------------------------------------------------------
文件名称：SysTick.c
文件描述：SysTick 系统滴答时钟1us中断函数库,中断时间可自由配置，
          常用的有 1us 10us 1ms 中断。        
备    注：程序默认使用72M时钟，无分频 
---------------------------------------------------------------------------------*/
//#include "delay.h"

static __IO uint32_t TimingDelay;

/*-------------------------------------------------------------------------------
程序名称：SysTick_Init
程序描述：启动系统滴答定时器 SysTick
输入参数：无
返回参数：无
备    注：使用此功能之前需要调用此函数，初始化寄存器等参数
---------------------------------------------------------------------------------*/
void SysTick_Init(void)
{
	 // SystemFrequency / 1000     1ms中断一次
	 // SystemFrequency / 100000	 10us中断一次
	 // SystemFrequency / 1000000  1us中断一次
	 //t1=1/72M  t2 = 72*(t1) = 1 us
	if (SysTick_Config(SystemCoreClock / 1000))	// 1us ST3.5.0库版本
	{ 
		//SysTick->CTRL &= SysTick_CLKSource_HCLK_Div8;
		/* Capture error */ 
		while (1);
	}

}


/*-------------------------------------------------------------------------------
程序名称：Delay_us 
程序描述：延时nTime us  (max 233016us)
输入参数：nTime
返回参数：无
备    注：无
---------------------------------------------------------------------------------*/
void delay_us(__IO uint32_t nTime)
{ 
	TimingDelay = nTime;	
  
	//while(TimingDelay != 0);
	while(TimingDelay > 0);
}

/*-------------------------------------------------------------------------------
程序名称：Delay_us
程序描述：延时nTime us   (max 233ms)
输入参数：nTime 
返回参数：无
备    注：无
---------------------------------------------------------------------------------*/
void delay_ms(__IO uint32_t nTime)
{ 
	TimingDelay = nTime;	
  //DEBUG("delay_ms\r\n");
	//while(TimingDelay != 0);
	while(TimingDelay > 0);
}

/*-------------------------------------------------------------------------------
程序名称：TimingDelay_Decrement
程序描述：数字递减直到0  
输入参数：无
返回参数：无
备    注：需要在中断函数SysTick_Handler()中调用
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

