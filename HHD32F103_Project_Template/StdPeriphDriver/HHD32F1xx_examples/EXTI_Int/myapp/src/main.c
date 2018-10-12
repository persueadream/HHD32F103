/******************************************************************************
*	Application: Demo code for Timer using in HHD32F1xx
*	Edition:		Version:1.0
*	Company: 		
*	Time: 			September 2015
******************************************************************************/
#include "hhd32f1xx.h"
#include "hhd_sys.h"
#include "hhd_timer.h"
#include "hhd_gpio.h"

/*****************************************************************************
* Function name:    Main Function
*
* Descriptions:     Interrupt Example, Enable IRQn, and Disable IRQn once
*                   enter into interrupt service routine.
*
* parameters:       None
* Returned value:   None
* 
*****************************************************************************/
int main(void)
{

	/* ----------- System initialization -------------------------------------*/
	SYS_SystemInitial();	
	
	
	/* --- Call ARM system function NVIC_EnableIRQ() to enable IRQ          --*/
	/* --- Call ARM system function NVIC_DisableIRQ() to disable IRQ        --*/


  /* --------- GPIOA Periph clock enable --------------*/
  ENABLEGPIOACLK;
	
  /* --------- Configure PA9 as in mode ---------------*/	
	GPIO_ConfigPinsAsInput(GPIOA,PIN9);

	/* --------- Configure PA9 as EXTI interrupt source, */
	/* --------- rising edge mode                      --*/	
	GPIO_EnableInt(GPIOA,PIN9,0);
	
  while(1);

}




//---- GPIOx_PIN0 ----------------------
void EXTI0_IRQHandler ()
{    
	NVIC_DisableIRQ(EXTI0_IRQn);
	while(1);
}	

//---- GPIOx_PIN1 ----------------------
void EXTI1_IRQHandler ()
{ 
	NVIC_DisableIRQ(EXTI1_IRQn);
	while(1);
}	

//---- GPIOx_PIN2 ----------------------
void EXTI2_IRQHandler ()
{
	NVIC_DisableIRQ(EXTI2_IRQn);
	while(1);
}	

//---- GPIOx_PIN3 ----------------------
void EXTI3_IRQHandler ()
{
	NVIC_DisableIRQ(EXTI3_IRQn);
	while(1);
}	

//---- GPIOx_PIN4 ----------------------
void EXTI4_IRQHandler ()
{
	NVIC_DisableIRQ(EXTI4_IRQn);
	while(1);
}	



//---- GPIOx_PIN9- GPIOx_PIN5  ----------------------
void EXTI9_5_IRQHandler ()
{
	//NVIC_DisableIRQ(EXTI9_5_IRQn);
	
	//Clear GPIO interrupt flag in flag register, updated @2016/02/16 16:11
	GPIO_ClrIntflag(GPIOA,PIN9);
	while(1);
}	



//---- GPIOx_PIN15 - GPIOx_PIN10 ----------------------
void EXTI15_10_IRQHandler ()
{
	NVIC_DisableIRQ(EXTI15_10_IRQn);
	while(1);
}	

