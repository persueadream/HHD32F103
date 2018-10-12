/*******************************************************************************
*	Application: Demo code for DAC using in G32F0xx
*	Edition:		Version:1.0
*	Company: 		
*	Time: 			September 2015
*******************************************************************************/
#include "hhd32f1xx.h"
#include "hhd_sys.h"
#include "hhd_dac.h"


uint16_t temp;
void delay1us(uint32_t time);
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

	uint32_t i;
  /* -------------- System initialization ---------------------------------*/	
	SystemInit();
	
	/* -------------- Initial DAC -------------------------------------------*/
	/* Power up DAC analog module -------------------------------------------*/
	ENABLEDACCLK;
	
	
	/* -------------- Config DAC2 OUTput to PA8 -----------------------------*/
	OpenDAC2_OUT;
	
	
	/* -------------- Initialise DAC2,and set Sample speed ------------------*/
	DAC_Init(DAC2,1000000,SINGLEMODE);
	
	/* ---------- Delay 100us after DAC power-on ----------------------------*/
	delay1us(0xffff);


	for(i=0;i<1024;i=i+100) 
	{
		while(Get_DACBufferState(DAC2)==BUFFER_is_not_EMPTY);
		
		DAC_SendData(DAC2,i);
		delay1us(5);
		/* use delay or Interrupt mode to wait for data being transmitted -----*/
		
  }	

}

void delay1us(uint32_t time)
{
			while(time--);
}
