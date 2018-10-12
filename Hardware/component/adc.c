#include "adc.h"
//#include "func_app.h"
#include "ADC_user.h"
#include "hhd_gpio.h"
#include "system_user.h"
static uint16_t ADC_ConvertedValue[INTER_AD_NUM] = {0x0000};

void ADC1_Init(void)
{
	ENABLEGPIOACLK;
	ENABLEGPIOBCLK;
	ENABLEGPIOCCLK;
	ENABLEADC1CLK;
//	ENABLEAFIOCLK;
	
	//OpenADC1_IN1;		//none
	OpenADC1_IN2;		//9v
	OpenADC1_IN3;		//6.5v
 	OpenADC1_IN4;		//12v
	
	OpenADC1_IN9;		//current
	//OpenADC1_IN10;	//none
	
	OpenADC1_IN11;	//-5v
	//OpenADC1_IN12;	//none
	//OpenADC1_IN13;	//none
	//OpenADC1_IN14;	//none
	
	OpenADC1_IN16;	//temp

	/* -------------- Initialise ADC1,ADC2 and set Sample speed ------------------*/
	ADC_Init(ADC1,100000); //100kHz Sample speed
	ADC_SetTrigger(ADC1,ADC_START_BY_SOFTWAER,1);
	
	ADC_SetupChannels(ADC1,DR0EN | DR1EN | DR2EN | DR3EN | DR4EN | DR5EN,
								CHN2_DR0 | CHN3_DR1 | CHN4_DR2 | CHN9_DR3 | CHN11_DR4 | CHN16_DR5, TRIGGERMODE);
								
	delay_us(100);
}

static uint16_t GetADCVoltage(HHD32F_ADC_TypeDef *ADC, uint8_t dr)
{
	  uint32_t temp = 0;
		temp = ADC_GetConversionData(ADC, dr);
	  temp = (temp * 3.27 / 4096)*100;
	  return temp;
}

int16_t GetADCISensor(HHD32F_ADC_TypeDef *ADC, uint8_t dr)
{
	uint32_t temp = 0;
	int16_t temperature = 0;
	
	temp = ADC_GetConversionData(ADC, dr);
	temperature = (0xBA3-temp)/(0.008*4096/3.27) + 25;
	
	return temperature;
}

void ADC_GETVOL_POLL(void)
{
	static char adc_count = 0;
	double vol = 0;
	
	if (adc_count == 0)
	{
		ADC1_IssueSoftTrigger;
		delay_us(0x0f);
	}
	else if (adc_count == 1)
	{
		ADC_ConvertedValue[MON_VCC9V] = GetADCVoltage(ADC1, ADC_DR0)/*/1.47*9*/;
		vol = ADC_ConvertedValue[MON_VCC9V] / 100.0;
		DEBUG("MON_VCC9V = %.3f\r\n", vol);
	}
	else if (adc_count == 2)
	{
		ADC_ConvertedValue[MON_VCC6V5] = GetADCVoltage(ADC1, ADC_DR1)/*/3.25*6.5*/;
		vol = ADC_ConvertedValue[MON_VCC6V5] / 100.0;
		DEBUG("MON_VCC6V5 = %.3f\r\n", vol);
	}
	else if (adc_count == 3)
	{
		ADC_ConvertedValue[MON_VCC12V] = GetADCVoltage(ADC1, ADC_DR2)/*/1.03*12*/;
		vol = ADC_ConvertedValue[MON_VCC12V] / 100.0;
		DEBUG("MON_VCC12V = %.3f\r\n", vol);
	}
	else if (adc_count == 4)
	{
		ADC_ConvertedValue[MON_VCC5V] = GetADCVoltage(ADC1, ADC_DR4);
		vol = ADC_ConvertedValue[MON_VCC5V] / 100.0;
		DEBUG("MON_VCC5V = %.3f\r\n", vol);
	}
	else if (adc_count == 5)
	{
		ADC_ConvertedValue[MON_CURRENT] = GetADCVoltage(ADC1, ADC_DR3);
		vol = ADC_ConvertedValue[MON_CURRENT] / 100.0;
		DEBUG("MON_CURRENT = %.3f\r\n", vol);
	}
	else if (adc_count == 6)
	{
		ADC_ConvertedValue[MON_TEMP] = GetADCISensor(ADC1, ADC_DR5);
		//ADC_ConvertedValue[MON_TEMP] = ADC_TempSensor();
		vol = ADC_ConvertedValue[MON_TEMP] / 100.0;
		DEBUG("MON_TEMP = %.3f\r\n", vol);
	}
	
	if (adc_count == 6)
	{
		adc_count = 0;
	}
	else
	{
		adc_count++;
	}
}

uint16_t Adc1_GetValue(uint8_t index)
{
    return ADC_ConvertedValue[index];
}
