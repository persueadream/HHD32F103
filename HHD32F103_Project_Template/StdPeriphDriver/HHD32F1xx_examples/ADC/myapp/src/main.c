/*******************************************************************************
*	Application: Demo code for ADC using in HHD32F0xx
*	Edition:		Version:1.0
*	Company: 		
*	Time: 			September 2015
*******************************************************************************/
#include "hhd32f1xx.h"
#include "hhd_sys.h"
#include "hhd_adc.h"


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

  /* -------------- System initialization ---------------------------------*/	
	SystemInit();
	SystemCoreClockUpdate();
	/* -------------- Initial ADC -------------------------------------------*/
	/* Power up ADC analog module -------------------------------------------*/
	/* set ADC to trigger at software event start ---------------------------*/
	/* set Channel 1 as convertion channel ----------------------------------*/
	/* -------------- Config ADC1 Channel 1 IO ------------------------------*/
	OpenADC1_IN1;
	
	
	/* -------------- Initialise ADC1,and set Sample speed ------------------*/
	ADC_Init(ADC1,500000);
	
	
	/* ------ Set ADC trigger/Burst mode,this example,we set software trigger -
  // ----------------------------------------------------------------------*/
	//ADC_SetTrigger(ADC1,ADC_START_BY_SOFTWAER,0);


	/* -------------- Each ADC has 1-16 analog channel, 
	we set channel 1 to sample buffer DR0,
  you can also set channel 15 to DR5,and so on.                     	-----*/
  	ADC_SetTrigger(ADC1,ADC_START_BY_SOFTWAER,0);
	ADC_SetupChannels(ADC1,DR0EN,CHN1_DR0,TRIGGERMODE);


  #ifdef ADC_INT_ENABLE	
	ADC_EnableConversionInt(ADC1,1);
	NVIC_EnableIRQ(ADC1_2_IRQn);
  #endif
	/* ---------- Issue a software trigger to capture ADC analog signal to 
	// ADC 12bit data register ----------------------------------------------*/

	/* ---------- Delay 100us after ADC power-on ----------------------------*/
	delay1us(0xffff);

	while (1) 
	{
		ADC1_IssueSoftTrigger;
		
		/* use delay or Interrupt mode to read back ADC 12bit data  -----------*/
		delay1us(0xff);

		/* ---------- Get ADC data from DR0 of ADC ----------------------------*/
		temp = ADC_GetConversionData(ADC1,ADC_DR0); 		
  }		
}

void delay1us(uint32_t time)
{
			while(time--);
}
