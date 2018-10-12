/*******************************************************************************
*	Application: Demo code for Temp sensor using ADC1 Channel-16
*	Edition:		Version:1.0
*	Company: 		
*	Time: 			September 2015
*******************************************************************************/
#include "hhd32f1xx.h"
#include "hhd_sys.h"
#include "hhd_adc.h"


uint32_t temp;
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
	SystemCoreClockUpdate();
	/* -------------- Initial ADC -------------------------------------------*/
	/* Power up ADC analog module -------------------------------------------*/
	/* set Channel 1 as convertion channel ----------------------------------*/
	/* -------------- Config ADC1 Channel 16 IO -----------------------------*/
	OpenADC1_IN16;
	
	
	/* -------------- Initialise ADC1,and set Sample speed ------------------*/
	/* -------------- Temp sensor is connected to ADC1 channel 16 -----------*/
	ADC_Init(ADC1,100000);
	
	
	
	/* -------------- Each ADC has 1-16 analog channel, 
	we set channel 16 to sample buffer DR0,
  you can also set channel 15 to DR1,and so on.                     	-----*/
  ADC_SetupChannels(ADC1,DR0EN,CHN16_DR0,BURSTMODE);

  #ifdef ADC_INT_ENABLE	
	ADC_EnableConversionInt(ADC1,1);
	NVIC_EnableIRQ(ADC1_2_IRQn);
  #endif


	/* ---------- Delay 100us after ADC power-on ----------------------------*/
	delay1us(0xffff);
	temp = 0;


  /* ---------- Sample 500ms ADC data -------------------------------------*/
	for (i=0;i<1024;i=i+1) 
	{
				
		/* use delay or Interrupt mode to read back temp sensor data  ---------*/
		delay1us(10000);

		/* ---------- Get ADC data from DR0 of ADC ----------------------------*/
		temp += ADC_GetConversionData(ADC1,ADC_DR0); 		
  }		
	 
	  temp = temp>>10;
	
	  return 0;
}

void delay1us(uint32_t time)
{
			while(time--);
}
