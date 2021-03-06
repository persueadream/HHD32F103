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
void IOInit();
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
	SystemInit();
	

  /* --------- GPIOA Periph clock enable --------------*/
  ENABLEGPIOACLK;
	
	IOInit();
	
  /* --------- Configure PA0 as output pushpull mode --*/	
	GPIO_ConfigPinsAsOutput(GPIOA,PIN2);

	
  while(1)
	{
		/* -------- Set GPIO bit to 1 ---------------------*/
		GPIO_SetPin(GPIOA,PIN2);
		
		/* -------- Delay time ----------------------------*/
		dly1us(2000000);
		
		/* -------- Clear GPIO bit to 0 -------------------*/
    GPIO_ResetPin(GPIOA,PIN2);		
		
		/* -------- Delay time ----------------------------*/
		dly1us(2000000);	
	}
}

void dly1us(int dlytime) 
{
 while(dlytime--);
}

void IOInit()
{
		IOCON->PA0.bit.FUNC = 0;
		IOCON->PA0.bit.PUE  = 0;
		IOCON->PA0.bit.PDE  = 1;
}
	
