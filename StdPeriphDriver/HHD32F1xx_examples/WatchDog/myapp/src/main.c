/******************************************************************************
*	Application: Demo code for WatchDog using in HHD32F0xx
*	Edition:		Version:1.0
*	Company: 		
*	Time: 			
******************************************************************************/
#include "hhd32f1xx.h"
#include "hhd_sys.h"
#include "hhd_wdt.h"



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
	
 
	/*                                                                --------*/
  /* ----------- Initialize WatchDog-------------------------- ------------ */
  WDT_Init();
	
	
	/* ------------------- Set WachDog time out interval ---------------------*/
	WDT_SetIntervalinTick(0x1ff);
	
	/* ------------------- Set WachDog Window size ---------------------------*/
	WDT_SetWindowValue(0x3ff,0x7ff);
	

	/* ---------- Feed  & Enable WatchDog ------------------------------------*/
	WDT_Feed();
	WDT_Enable_Timer;


  /* ----------  Enable Window watchdog interrupt.  ------------------------*/
  NVIC_EnableIRQ(WWDT_IRQn);

  while(1);
  //return 0;

}


void WWDT_IRQHandler()
{
	/*--- Clear Int flag & Disable int of timer ------------------------------ */
	WDT_ClearIntFlag();
	WDT_Disable_Timer;
	
}


