/******************************************************************************
*	Application: Demo code for Timer using in HHD32F1xx
*	Edition:		Version:1.0
*	Company: 		
*	Time: 			September 2017
******************************************************************************/
#include "hhd32f1xx.h"
#include "hhd_sys.h"
#include "hhd_timer.h"
#include "hhd_gpio.h"

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
	SYS_SystemInitial();	
	
	
	/* G32F1xx has 6-14 timers in different part-number IC --------------------*/
	// TIM6,TIM7 are basic timer, which only have one MR and no capture register
	// TIM2-14 are enhenced timer, which have 4 MR & 4 Capture register.
	/*                                                                --------*/
	
  /* ----------- Basic Timer 6 Periph clock enable, set TIM6 to run at 1MHz */
  TIM_Init(TIM6,1000000UL);
	
	
	/* ------------------- Reset Timer ---------------------------------------*/
	TIM_RESET(TIM6);
	
	
	/* ---------- Set Timer return to zero when it matches MR value ----------*/
	TIM_ConfigMatch(TIM6,1000,TIM_MATCH_RESET_COUNTER);
	
	
  /* ---------- Configure PA0 as output pushpull mode ----------------------*/	
	GPIO_ConfigPinsAsOutput(GPIOA,PIN0);

	
	/* --- Enable TMR0 interrupt to invert PA0 in each int service rountine --*/
	TIM_EnableInt(TIM6);
  NVIC_EnableIRQ(TIM6_IRQn);
	
	/* ---------- Start TMR0 -------------------------------------------------*/
	TIM_START(TIM6);
	
	
  while(1);

}

void TIM6_IRQHandler()
{
		/* ----- Invert GPIO bit when come to each intterrupt ------------------*/
		GPIO_InvertOutPin(GPIOA,PIN0);	
	
	  /* ----- Clear int flag  -----------------------------------------------*/ 
	  TIM_ClearIntFlag(TIM6);
	
	//  TIM_STOP(TIM6);
	
}

// void WWDT_IRQHandler()
// {
// 	while(1);
// }	

// void BOD_IRQHandler ()
// {
// 	while(1);
// }	

// void DAC_IRQHandler ()
// {
// 	while(1);
// }	

// void RTC_IRQHandler ()
// {         
// 	while(1);
// }	

// void EXTI0_IRQHandler ()
// {      
// 	while(1);
// }	

// void EXTI1_IRQHandler ()
// {   
// 	while(1);
// }	

// void EXTI2_IRQHandler ()
// {
// 	while(1);
// }	

// void EXTI3_IRQHandler ()
// {
// 	while(1);
// }	

// void EXTI4_IRQHandler ()
// {
// 	while(1);
// }	

// void DMA1_CHANNEL1_IRQHandler ()
// {
// 	while(1);
// }	

// void DMA1_CHANNEL2_IRQHandler ()
// {
// 	while(1);
// }	

// void DMA1_CHANNEL3_IRQHandler ()
// {
// 	while(1);
// }	

// void DMA1_CHANNEL4_IRQHandler ()
// {
// 	while(1);
// }	

// void DMA1_CHANNEL5_IRQHandler ()
// {
// 	while(1);
// }	

// void DMA1_CHANNEL6_IRQHandler ()
// {
// 	while(1);
// }	

// void DMA1_CHANNEL7_IRQHandler ()
// {
// 	while(1);
// }	

// void ADC1_2_IRQHandler ()
// {
// 	while(1);
// }

// void EXTI9_5_IRQHandler ()
// {
// 	while(1);
// }	

// void TIM1FAULT_TIM9_IRQHandler ()
// {   
// 	while(1);
// }	

// void TIM10_IRQHandler ()
// {
// 	while(1);
// }	

// void TIM11_IRQHandler ()
// {
// 	while(1);
// }	

// void TIM1_IRQHandler ()
// {
// 	while(1);
// }	

// void TIM2_IRQHandler ()
// {
// 	while(1);
// }	

// void TIM3_IRQHandler (){
// 	while(1);
// }	

// void TIM4_IRQHandler ()
// {
// 	while(1);
// }	

// void I2C1_IRQHandler ()
// {
// 	while(1);
// }	

// void I2C2_IRQHandler ()
// {
// 	while(1);
// }	

// void SPI1_IRQHandler ()
// {
// 	while(1);
// }	

// void SPI2_IRQHandler ()
// {
// 	while(1);
// }	

// void UART1_IRQHandler ()
// {
// 	while(1);
// }	

// void UART2_IRQHandler ()
// {
// 	while(1);
// }	

// void UART3_IRQHandler ()
// {
// 	while(1);
// }	

// void EXTI15_10_IRQHandler ()
// {
// 	while(1);
// }	

// void USBWAKEUP_IRQHandler ()
// {
// 	while(1);
// }	

// void TIM8FAULT_TIM12_IRQHandler ()
// {  
// 	while(1);
// }	

// void TIM13_IRQHandler ()
// {
// 	while(1);
// }	

// void TIM14_IRQHandler ()
// {
// 	while(1);
// }	

// void TIM8_IRQHandler ()
// {
// 	while(1);
// }	

// void ADC3_IRQHandler ()
// {
// 	while(1);
// }	

// void TIM5_IRQHandler ()
// {
// 	while(1);
// }	

// void SPI3_IRQHandler ()
// {
// 	while(1);
// }	

// void UART4_IRQHandler ()
// {
// 	while(1);
// }	

// void UART5_IRQHandler ()
// {
// 	while(1);
// }	

// void TIM7_IRQHandler ()
// {
// 	while(1);
// }	

// void DMA2_CHANNEL1_IRQHandler ()
// {
// 	while(1);
// }	

// void DMA2_CHANNEL2_IRQHandler ()
// {
// 	while(1);
// }	

// void DMA2_CHANNEL3_IRQHandler ()
// {
// 	while(1);
// }

// void DMA2_CHANNEL4_5_IRQHandler ()
// {
// 	while(1);
// }	

// void CAN_IRQHandler ()
// {
// 	while(1);
// }	

// void USB_IRQHandler ()
// {
// 	while(1);
// }	

// void HardFault_Handler()
// {
// 	while(1);
// }

// void NMI_Handler()
// {
// 	while(1);
// }
