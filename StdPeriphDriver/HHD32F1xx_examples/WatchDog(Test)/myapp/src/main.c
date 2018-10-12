/******************************************************************************
*	Application: Demo code for WatchDog using in 
*	Edition:		Version:1.0
*	Company: 		
*	Time: 			September 2015
******************************************************************************/
#include "hhd32f1xx.h"
#include "hhd_sys.h"
#include "hhd_wdt.h"
#include "hhd_gpio.h"


void delay1us(uint32_t time);

uint16_t led = 0x01;

/*****************************************************************************
* Function name:    Main Function
*
* Descriptions:     Initial device
*
* parameters:       None
* Returned value:   None
* 
*****************************************************************************/
int main(void)
{

	/* ----------- System initialization -------------------------------------*/
	//SystemInit();
	SYS_SystemInitial();		
	
	ENABLEGPIOCCLK;
 
	GPIO_ConfigPinsAsOutput(GPIOC, PIN0);
	
	/*                                                                --------*/
  /* ----------- Initialize WatchDog-------------------------- ------------ */
  WDT_Init();
	
	
	/* ------------------- Set WachDog time out interval ---------------------*/
	WDT_SetIntervalinTick(0x1ff);
	
	/* ------------------- Set WachDog Window size ---------------------------*/
	WDT_SetWindowValue(0x3ff,0x7ff);
	

	/* ---------- Feed  & Enable WatchDog ------------------------------------*/
//	WDT_Feed();
	//WDT_Enable_Timer;


  /* ----------  Enable Window watchdog interrupt.  ------------------------*/
  NVIC_EnableIRQ(WWDT_IRQn);

  while(1)
	{
			WDT_Feed();
		  WDT_Enable_Timer;
		  delay1us(2000000);//设定超过看门狗喂狗时间
		  
  }
  //return 0;

}


void WWDT_IRQHandler()
{
	/*--- Clear Int flag & Disable int of timer ------------------------------ */
	WDT_ClearIntFlag();
	led =~led;
	GPIO_WritePort(GPIOC, led);
//	WDT_Disable_Timer;
	
}

void delay1us(uint32_t time)
{
			while(time--);
}


