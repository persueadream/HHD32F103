/**
* Copyright(C) 2015, 
* ALL rights reserved.
*
* @file    TIMER_user.c
* @author   MCU Application Team
* @version V0.1
* @date    1-August-2015
* @brief   Timer initialize setting
*          
*/

#include "timer.h"
#include "system.h"
//#include "task.h"

#define TIM_5S        3  //100ms x 5 = 500ms

uint16_t TimerCnt , gTimerFlag;
extern unsigned int pluseTimerCnt;
extern unsigned char pluseTimerCntFlag;
//extern uint8_t FLAGA;
/*----------------------------------------------------------------------------
** Function name:		Timer_Configuration
**
** Descriptions:		timer Initialize
**
** parameters:			
**                  
**                  
**                  
** Returned value:		none
** 
** Author:  MCU Application Team
**
** Date:12-August-2017
**
-------------------------------------------------------------------------------*/
void Timer_Configuration(void)
{
		  /* ----------- Basic Timer 6 Periph clock enable, set TIM5 to run at 1MHz */
  TIM_Init(TIM2,100000UL);
	TIM_Init(TIM3,1000000UL);
	
	/* ------------------- Reset Timer ---------------------------------------*/
	TIM_RESET(TIM2);
	TIM_RESET(TIM3);
	
	/* ---------- Set Timer return to zero when it matches MR value ----------*/
	TIM_ConfigMatch(TIM2,9999,TIM_MATCH_RESET_COUNTER); //1MHz/10000 = 100Hz,10ms
	TIM_ConfigMatch(TIM3,9,TIM_MATCH_RESET_COUNTER); //1MHz/10 = 100KHz,10us
	/* --- Enable TMR0 interrupt to invert PA0 in each int service rountine --*/
	TIM_EnableInt(TIM2);
  NVIC_EnableIRQ(TIM2_IRQn);
	
	/* ---------- Start TMR0 -------------------------------------------------*/
	TIM_START(TIM2);
	
	
}

/*----------------------------------------------------------------------------
** Function name:		TIM2_IRQHandler
**
** Descriptions:		
**
** parameters:			
**                  
**                  
**                  
** Returned value:		none
** 
** Author:  MCU Application Team
**
** Date:12-August-2017
**
-------------------------------------------------------------------------------*/
void TIM2_IRQHandler()
{
//	  TIM_DisableInt(TIM2);
//	  TIM_STOP(TIM2);
	  /* ----- Clear int flag  -----------------------------------------------*/ 
	  TIM_ClearIntFlag(TIM2);
#if 0
		/* ----- Invert GPIO bit when come to each intterrupt ------------------*/
		GPIO_InvertOutPin(GPIOC, PIN7);	//WDI max6822

	  if(TimerCnt != 0)
		{
			TimerCnt--;
			if(TimerCnt == 0)
			{
					gTimerFlag = 1;
				  //FLAGA |= (0x01 << 7); //定时启动数据采集标志位
				  GPIO_InvertOutPin(GPIOB, PIN9);	//LED
				  Delay_10us(3000);
				  GPIO_InvertOutPin(GPIOB, PIN8);	//LED
				  TimerCnt = TIM_5S;
			}
		}
#endif
		
#if 1
		if(pluseTimerCnt != 0)
		{
			pluseTimerCnt--;
			if(pluseTimerCnt == 0)
			{
				pluseTimerCntFlag = 1;
			}
		}
#endif
//	  TIM_EnableInt(TIM2);
//	  TIM_START(TIM2);
	//  TIM_STOP(TIM5);
	
}


/*----------------------------------------------------------------------------
** Function name:		Delay_10us
**
** Descriptions:		use timer count to delay 10us.
**
** parameters:			
**                  
**                  
**                  
** Returned value:		none
** 
** Author:  MCU Application Team
**
** Date:12-August-2017
**
-------------------------------------------------------------------------------*/
void Delay_10us(uint32_t i)
{
	uint32_t temp = i;
	while(temp--)
	{
		TIM_START(TIM3);
    while((TIM3->TC.bit.TC) != (TIM3->MR0.bit.MATCH))	
    {
			;
		}		
	}
	TIM_RESET(TIM3);
	TIM_STOP(TIM3);
}

/******************* (C) COPYRIGHT 2017  *****END OF FILE*****************/

