//RTC Function demo Main Program

#include "hhd32f1xx.h"
#include "hhd_sys.h"
#include "hhd_rtc.h"
#include "hhd_gpio.h"

//Main function entry
int main(void)
{
	//Initial System ----------------------------------------
	SYS_SystemInitial();
	
	//set one pin as led indicator --------------------------
	GPIO_ConfigPinsAsOutput(GPIOC, IO_PIN0);

	//Enable RTC Counter ------------------------------------
	RTC_EnableTimerCounter;
	
	
	//Enable RTC Alarm int ----------------------------------
	RTC_EnableAlarmInt();

	//Set 1sec timeout --------------------------------------
	RTC_SetAlarmInTickLater(1);
	
	// enable RTC interrupt ---------------------------------
	NVIC_EnableIRQ(RTC_IRQn);

	while (1);
}

/*****************************************************************************
** Function name:		RTC_IRQHandler
**
** Descriptions:		RTC timeout int handler
**
** parameters:			None
** Returned value:		None
** 
*****************************************************************************/
void RTC_IRQHandler(void)
{
  GPIO_InvertOutPin(GPIOC,IO_PIN0);
	RTC_ClearIntFlag();
	//Set next 1sec timeout
	RTC_SetAlarmInTickLater(1);

	return;
}
