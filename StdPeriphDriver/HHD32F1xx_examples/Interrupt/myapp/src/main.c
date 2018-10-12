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
	
	
  /* ----------- Basic Timer 6 Periph clock enable, set TIM6 to run at 1MHz */
  TIM_Init(TIM6,1000000UL);
	
	
	/* ------------------- Reset Timer ---------------------------------------*/
	TIM_RESET(TIM6);
	
	
	/* ---------- Set Timer return to zero when it matches MR value ----------*/
	TIM_ConfigMatch(TIM6,1000,TIM_MATCH_RESET_COUNTER);
	
	
  /* ---------- Configure PA0 as output pushpull mode ----------------------*/	
	GPIO_ConfigPinsAsOutput(GPIOA,PIN0);

	
	/* --- Enable TIMx interrupt to invert PA0 in each int service rountine --*/
	TIM_EnableInt(TIM6);



	/* --- Call ARM system function NVIC_EnableIRQ() to enable IRQ          --*/
	/* --- Call ARM system function NVIC_DisableIRQ() to disable IRQ        --*/
	//NVIC_EnableIRQ(TIM1_IRQn);
	//NVIC_EnableIRQ(TIM2_IRQn);
	//NVIC_EnableIRQ(TIM3_IRQn);
	//NVIC_EnableIRQ(TIM4_IRQn);
	//NVIC_EnableIRQ(TIM5_IRQn);
  NVIC_EnableIRQ(TIM6_IRQn);
	//NVIC_EnableIRQ(TIM7_IRQn);
	//NVIC_EnableIRQ(TIM8_IRQn);
	//NVIC_EnableIRQ(TIM9_IRQn);
	//NVIC_EnableIRQ(TIM10_IRQn);
	//NVIC_EnableIRQ(TIM11_IRQn);
	//NVIC_EnableIRQ(TIM12_IRQn);
	//NVIC_EnableIRQ(TIM13_IRQn);
	//NVIC_EnableIRQ(TIM14_IRQn);
	//NVIC_EnableIRQ(TIM15_IRQn);
	//NVIC_EnableIRQ(UART2_IRQn);
	
	/* ---------- Start TIM6 -------------------------------------------------*/
	TIM_START(TIM6);
	
	
  while(1);

}


//---- Window Watch Dog IRQ -------
void WWDT_IRQHandler()
{
	NVIC_DisableIRQ(WWDT_IRQn);
	while(1);
}	

//---- Window Brown Out IRQ -------
void BOD_IRQHandler ()
{
	NVIC_DisableIRQ(BOD_IRQn);
	while(1);
}	

//---- DAC1&2 IRQ -----------------
void DAC_IRQHandler ()
{
	NVIC_DisableIRQ(DAC_IRQn);
	while(1);
}	

//---- xxxxx ----------------------
void RTC_IRQHandler ()
{       
	NVIC_DisableIRQ(RTC_IRQn);
	while(1);
}	

//---- xxxxx ----------------------
void EXTI0_IRQHandler ()
{    
	NVIC_DisableIRQ(EXTI0_IRQn);
	while(1);
}	

//---- xxxxx ----------------------
void EXTI1_IRQHandler ()
{ 
	NVIC_DisableIRQ(EXTI1_IRQn);
	while(1);
}	

//---- xxxxx ----------------------
void EXTI2_IRQHandler ()
{
	NVIC_DisableIRQ(EXTI2_IRQn);
	while(1);
}	

//---- xxxxx ----------------------
void EXTI3_IRQHandler ()
{
	NVIC_DisableIRQ(EXTI3_IRQn);
	while(1);
}	

//---- xxxxx ----------------------
void EXTI4_IRQHandler ()
{
	NVIC_DisableIRQ(EXTI4_IRQn);
	while(1);
}	

//---- xxxxx ----------------------
void DMA1_CHANNEL1_IRQHandler ()
{
	NVIC_DisableIRQ(DMA1_CHANNEL1_IRQn);
	while(1);
}	

//---- xxxxx ----------------------
void DMA1_CHANNEL2_IRQHandler ()
{
	NVIC_DisableIRQ(DMA1_CHANNEL2_IRQn);
	while(1);
}	

//---- xxxxx ----------------------
void DMA1_CHANNEL3_IRQHandler ()
{
	NVIC_DisableIRQ(DMA1_CHANNEL3_IRQn);
	while(1);
}	

//---- xxxxx ----------------------
void DMA1_CHANNEL4_IRQHandler ()
{
	NVIC_DisableIRQ(DMA1_CHANNEL4_IRQn);
	while(1);
}	

//---- xxxxx ----------------------
void DMA1_CHANNEL5_IRQHandler ()
{
	NVIC_DisableIRQ(DMA1_CHANNEL5_IRQn);
	while(1);
}	

//---- xxxxx ----------------------
void DMA1_CHANNEL6_IRQHandler ()
{
	NVIC_DisableIRQ(DMA1_CHANNEL6_IRQn);
	while(1);
}	

//---- xxxxx ----------------------
void DMA1_CHANNEL7_IRQHandler ()
{
	NVIC_DisableIRQ(DMA1_CHANNEL7_IRQn);
	while(1);
}	

//---- xxxxx ----------------------
void ADC1_2_IRQHandler ()
{
	NVIC_DisableIRQ(ADC1_2_IRQn);
	while(1);
}

//---- xxxxx ----------------------
void EXTI9_5_IRQHandler ()
{
	NVIC_DisableIRQ(EXTI9_5_IRQn);
	while(1);
}	

//---- xxxxx ----------------------
void TIM1FAULT_TIM9_IRQHandler ()
{   
	NVIC_DisableIRQ(TIM1FAULT_TIM9_IRQn);
	while(1);
}	

//---- xxxxx ----------------------
void TIM10_IRQHandler ()
{
	NVIC_DisableIRQ(TIM10_IRQn);
	while(1);
}	

//---- xxxxx ----------------------
void TIM11_IRQHandler ()
{
	NVIC_DisableIRQ(TIM11_IRQn);
	while(1);
}	

//---- xxxxx ----------------------
void TIM1_IRQHandler ()
{
	NVIC_DisableIRQ(TIM1_IRQn);
	while(1);
}	

//---- xxxxx ----------------------
void TIM2_IRQHandler ()
{
	NVIC_DisableIRQ(TIM2_IRQn);
	while(1);
}	

//---- xxxxx ----------------------
void TIM3_IRQHandler ()
{
	NVIC_DisableIRQ(TIM3_IRQn);
	while(1);
}	

//---- xxxxx ----------------------
void TIM4_IRQHandler ()
{
	NVIC_DisableIRQ(TIM4_IRQn);
	while(1);
}	

//---- xxxxx ----------------------
void I2C1_IRQHandler ()
{
	NVIC_DisableIRQ(I2C1_IRQn);
	while(1);
}	

//---- xxxxx ----------------------
void I2C2_IRQHandler ()
{
	NVIC_DisableIRQ(I2C2_IRQn);
	while(1);
}	

//---- xxxxx ----------------------
void SPI1_IRQHandler ()
{
	NVIC_DisableIRQ(SPI1_IRQn);
	while(1);
}	

//---- xxxxx ----------------------
void SPI2_IRQHandler ()
{
	NVIC_DisableIRQ(SPI2_IRQn);
	while(1);
}	

//---- xxxxx ----------------------
void UART1_IRQHandler ()
{
	NVIC_DisableIRQ(UART1_IRQn);
	while(1);
}	

//---- xxxxx ----------------------
void UART2_IRQHandler ()
{
	NVIC_DisableIRQ(UART2_IRQn);
	while(1);
}	

//---- xxxxx ----------------------
void UART3_IRQHandler ()
{
	NVIC_DisableIRQ(UART3_IRQn);
	while(1);
}	

//---- xxxxx ----------------------
void EXTI15_10_IRQHandler ()
{
	NVIC_DisableIRQ(EXTI15_10_IRQn);
	while(1);
}	

//---- xxxxx ----------------------
void USBWAKEUP_IRQHandler ()
{
	NVIC_DisableIRQ(USBWAKEUP_IRQn);
	while(1);
}	

//---- xxxxx ----------------------
void TIM8FAULT_TIM12_IRQHandler ()
{ 
	NVIC_DisableIRQ(TIM8FAULT_TIM12_IRQn);
	while(1);
}	

//---- xxxxx ----------------------
void TIM13_IRQHandler ()
{
	NVIC_DisableIRQ(TIM13_IRQn);
	while(1);
}	

//---- xxxxx ----------------------
void TIM14_IRQHandler ()
{
	NVIC_DisableIRQ(TIM14_IRQn);
	while(1);
}	

//---- xxxxx ----------------------
void TIM8_IRQHandler ()
{
	NVIC_DisableIRQ(TIM8_IRQn);
	while(1);
}	

//---- xxxxx ----------------------
void ADC3_IRQHandler ()
{
	NVIC_DisableIRQ(ADC3_IRQn);
	while(1);
}	

//---- xxxxx ----------------------
void TIM5_IRQHandler ()
{
	NVIC_DisableIRQ(TIM5_IRQn);
	while(1);
}	

//---- xxxxx ----------------------
void SPI3_IRQHandler ()
{
	NVIC_DisableIRQ(SPI3_IRQn);
	while(1);
}	

//---- xxxxx ----------------------
void UART4_IRQHandler ()
{
	NVIC_DisableIRQ(UART4_IRQn);
	while(1);
}	

//---- xxxxx ----------------------
void UART5_IRQHandler ()
{
	NVIC_DisableIRQ(UART5_IRQn);
	while(1);
}	

//---- xxxxx ----------------------
void TIM6_IRQHandler()
{
	NVIC_DisableIRQ(TIM6_IRQn);
	while(1);
}

//---- xxxxx ----------------------
void TIM7_IRQHandler ()
{
	NVIC_DisableIRQ(TIM7_IRQn);
	while(1);
}	

//---- xxxxx ----------------------
void DMA2_CHANNEL1_IRQHandler ()
{
	NVIC_DisableIRQ(DMA2_CHANNEL1_IRQn);
	while(1);
}	

//---- xxxxx ----------------------
void DMA2_CHANNEL2_IRQHandler ()
{
	NVIC_DisableIRQ(DMA2_CHANNEL2_IRQn);
	while(1);
}	

//---- xxxxx ----------------------
void DMA2_CHANNEL3_IRQHandler ()
{
	NVIC_DisableIRQ(DMA2_CHANNEL3_IRQn);
	while(1);
}

//---- xxxxx ----------------------
void DMA2_CHANNEL4_5_IRQHandler ()
{
	NVIC_DisableIRQ(DMA2_CHANNEL4_5_IRQn);
	while(1);
}	

//---- xxxxx ----------------------
void CAN_IRQHandler ()
{
	NVIC_DisableIRQ(CAN_IRQn);
	while(1);
}	

//---- xxxxx ----------------------
void USB_IRQHandler ()
{
	NVIC_DisableIRQ(USB_IRQn);
	while(1);
}	

//---- xxxxx ----------------------
void HardFault_Handler()
{
	while(1);
}

//---- xxxxx ----------------------
void NMI_Handler()
{
	while(1);
}
