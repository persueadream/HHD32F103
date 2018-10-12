/*******************************************************************************
*	Application: Demo code for GPIO using in HHD32F0xx
*	Edition:		Version:1.0
*	Company: 		
*	Time: 			September 2015
*******************************************************************************/
#include "hhd32f1xx.h"
#include "hhd_sys.h"
#include "hhd_gpio.h"



void dly1us(int dlytime);
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

	/* --------- System initialization ------------------*/
	SYS_SystemInitial();	
	
  /* --------- GPIOA Periph clock enable --------------*/
  ENABLEGPIOCCLK;

	
  /* --------- Configure PA0 as output pushpull mode --*/	
	GPIO_ConfigPinsAsOutput(GPIOC,PIN0);

	
  while(1)
	{
		/* -------- Set GPIO bit to 1 ---------------------*/
		GPIO_SetPin(GPIOC,PIN0);
		
		/* -------- Delay time ----------------------------*/
		dly1us(2000000);
		
		/* -------- Clear GPIO bit to 0 -------------------*/
    GPIO_ResetPin(GPIOC,PIN0);		
		
		/* -------- Delay time ----------------------------*/
		dly1us(2000000);	
	}
}

void dly1us(int dlytime) 
{
 while(dlytime--);
}
