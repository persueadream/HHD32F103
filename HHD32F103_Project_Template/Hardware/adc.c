
#include "adc.h"
#include <string.h>
#include <stdio.h>
#include "system.h"
/*ADC 通道总数*/
#define ADC_CHANNEL_NUM  4
/*ADC 每个通道采样次数*/
#define ADC_SAMPLE_COUNT 50

#define T25ADC            0xBA3 //25℃ ADC的采样值
#define ADCREF   (double)(3.27) //ADC 参考电压
#define ADCSTEP  (double)(0.008*4096/ADCREF) //1℃ 0.008V

#define ADC_TEST  4
//#define ADC_TEMP    7



uint32_t dValue = 0;
 uint32_t Result[5] = {0};
void ADC_Test(void);
void ADC_Configuration(void);
void ADC_TempSensorConfiguration(void);
uint16_t ADC_TempSensor(void);
uint32_t GetADCVoltage(HHD32F_ADC_TypeDef *ADC, uint8_t dr);

/**----------------------------------------------------------------------------
** @Function:		   ADC_Configuration
**
** @Descriptions:	   	
**
** @parameters:			
**                  
**                  
**                  
** @Returned: none
** 
** @Author:  MCU Application Team
**
** @Date: 28-June-2017
**
-------------------------------------------------------------------------------*/
void ADC_Configuration(void)
{
	/* -------------- Initial ADC -------------------------------------------*/
	/* Power up ADC analog module -------------------------------------------*/
	/* set ADC to trigger at software event start ---------------------------*/
	/* set Channel 0 as convertion channel ----------------------------------*/
 	ENABLEADC1CLK;
 	ENABLEADC2CLK;
// 	//ENABLEADC3CLK;
// 	
//   /*UART1 Configuration*/
//   UART1_IOCFG();
//   UART_Open(UART1,115200,UART_NO_PARITY,UART_RX_HALF_FULL);
//  DEBUG("\r\n----------------ADC Test---------------\r\n");
	/* -------------- Config ADC1 Channel 0 IO ------------------------------*/
	//OpenADC1_IN0;
	/* -------------- Config ADC2 Channel 0 IO ------------------------------*/
	//OpenADC2_IN0;
	/* -------------- Config ADC3 Channel 0 IO ------------------------------*/
	/*
	MON_VCC2V:   ADC1_IN1;
	MON_VCC1V65: ADC1_IN2;
	MON_VCC1V2:  ADC1_IN3;
	MON_MGT1V0:  ADC1_IN4;
	MON_CPS1V0:  ADC1_IN11;
	MON_CPS1V2:  ADC1_IN12;
	MON_VCC1V8:  ADC1_IN13;
	MON_VCC1V5:  ADC1_IN14;
	*/

 	OpenADC2_IN1;
// 	OpenADC2_IN2;
// 	OpenADC2_IN3;
// 	OpenADC2_IN4;
// 	OpenADC2_IN5;
// 	OpenADC2_IN6;
// 	OpenADC2_IN7;
// 	OpenADC2_IN8;
// 	OpenADC2_IN9;
 	OpenADC2_IN10;
// 	OpenADC2_IN11;
 	OpenADC2_IN12;
 	OpenADC2_IN13;
 	OpenADC2_IN14;
// 	OpenADC2_IN15;
// 	OpenADC2_IN16;


// 	OpenADC1_IN1; //PA0 MON12
// 	OpenADC1_IN2;
// 	OpenADC1_IN3;
// 	OpenADC1_IN4;
// 	OpenADC1_IN5;
// 	OpenADC1_IN6;
// 	OpenADC1_IN7;
// 	OpenADC1_IN8;
//	OpenADC1_IN9;
//	OpenADC1_IN10; //PB1 VCC_3.3
//	OpenADC1_IN11; 
//	OpenADC1_IN12; //PC1 VCC_2.5
//	OpenADC1_IN13; //PC2 VCCAUX_1.8
//	OpenADC1_IN14; //pC3 CURRENT_12
//	OpenADC1_IN15; 
	OpenADC1_IN16;
	
 
	/* -------------- Initialise ADC1,ADC2 and set Sample speed ------------------*/
	ADC_Init(ADC1,10000); //1MHz Sample speed
 	ADC_Init(ADC2,10000);
	
	
	/* -------------- Each ADC has 0-7channel, set channel 1 to sample -----*/
//   ADC_SetupChannels(ADC1,CHN1_DR0 | CHN2_DR1 | CHN3_DR2 | CHN4_DR3 | CHN5_DR4 | \
// 												 CHN6_DR5 | CHN7_DR6 | CHN8_DR7,BURSTMODE);
		/* -------------- Each ADC has 8-15channel, set channel 1 to sample -----*/
//   ADC_SetupChannels(ADC1,CHN9_DR0 | CHN10_DR1 | CHN11_DR2 | CHN12_DR3 | CHN13_DR4 | \
// 												 CHN14_DR5 | CHN15_DR6 | CHN16_DR7,BURSTMODE);

  	/* -------------- Each ADC has 0-7channel, set channel 1 to sample -----*/
//   ADC_SetupChannels(ADC2,CHN1_DR0 | CHN2_DR1 | CHN3_DR2 | CHN4_DR3 | CHN5_DR4 | \
// 												 CHN6_DR5 | CHN7_DR6 | CHN8_DR7,BURSTMODE);
		/* -------------- Each ADC has 8-15channel, set channel 1 to sample -----*/
// ADC_SetupChannels(ADC1, (DR0EN | DR1EN | DR2EN | DR3EN | DR4EN | DR5EN | DR6EN | DR7EN),(CHN1_DR0 | CHN2_DR1 | CHN3_DR2 | CHN4_DR3 | CHN5_DR4 | \
// 												 CHN6_DR5 | CHN7_DR6 | CHN8_DR7),BURSTMODE);
//	  ADC_SetupChannels(ADC1, (DR0EN | DR1EN | DR2EN | DR3EN | DR4EN | DR5EN | DR6EN | DR7EN),
//		                        (CHN9_DR0 | CHN10_DR1 | CHN11_DR2 | CHN12_DR3 | CHN13_DR4 | \
//											        CHN14_DR5 | CHN15_DR6 | CHN16_DR7),BURSTMODE);
	  ADC_SetupChannels(ADC1, (DR7EN),
		                        ( CHN16_DR7 ),TRIGGERMODE);
		ADC_SetupChannels(ADC2, (DR0EN | DR1EN | DR2EN | DR3EN | DR4EN),
		                        (CHN1_DR0 | CHN10_DR1 | CHN12_DR2 | CHN13_DR3 | CHN14_DR4),TRIGGERMODE);
  //  ADC_SetupChannels(ADC1,DR0EN,CHN16_DR0,BURSTMODE);

	//ADC_SetupChannels(ADC1,CHN2_DR1,BURSTMODE);
	//ADC_SetupChannels(ADC1,CHN3_DR2,BURSTMODE);
	//ADC_SetupChannels(ADC1,CHN4_DR3,BURSTMODE);
	//ADC_SetupChannels(ADC1,CHN11_DR4,BURSTMODE);
	//ADC_SetupChannels(ADC1,CHN12_DR5,BURSTMODE);
	//ADC_SetupChannels(ADC1,CHN13_DR6,BURSTMODE);
	//ADC_SetupChannels(ADC1,CHN14_DR7,BURSTMODE);

	/* ---------- Delay 100us after ADC power-on ----------------------------*/
	sdelay_us(0xffff);
}

/**----------------------------------------------------------------------------
** @Function:		   GetADCVoltage
**
** @Descriptions:	 获取ADC采集的电压值，乘以100.   	
**
** @parameters:			
**                  
**                  
**                  
** @Returned: none
** 
** @Author:  MCU Application Team
**
** @Date: 30-June-2017
**
-------------------------------------------------------------------------------*/
uint32_t GetADCVoltage(HHD32F_ADC_TypeDef *ADC, uint8_t dr)
{
	  uint32_t temp = 0;
		temp = ADC_GetConversionData(ADC, dr);
	  temp = temp * 327 / 4095;
	  return temp;
}

/**----------------------------------------------------------------------------
** @Function:		   ADC_Test
**
** @Descriptions:		
**
** @parameters:			
**                  
**                  
**                  
** @Returned: none
** 
** @Author:  MCU Application Team
**
** @Date: 30-June-2017
**
-------------------------------------------------------------------------------*/
void ADC_Test(void)
{
		#ifdef ADC_TEST
	 
	  double temp = 0.0;
    /*start smaple*/
		ADC2_IssueSoftTrigger;
		/* use delay or Interrupt mode to read back ADC 12bit data  -----------*/
		sdelay_us(0xff);

		/* ---------- Get ADC data from DR0 of ADC ----------------------------*/
		//temp = ADC_GetConversionData(ADC1,ADC_DR0); 		
		//dValue = (temp * 330 / 4095);
		DEBUG("\r\n----------------------ADC Test-------------------------\r\n");
	  /*MON12:2V: ADC12_IN1*/
		dValue = GetADCVoltage(ADC2, ADC_DR0);
		//Result[0] = ADC_GetConversionData(ADC2, ADC_DR0);
	  temp = (double)(dValue) / 100.0;
	 // DEBUG("The ADC12_IN0 capture voltage is: %.3f V \r\n",temp);
	  DEBUG("The MON12:2V:    ADC12_IN1  capture voltage is: %.3f V \r\n",temp);
	  sdelay_us(2000000);
	  //sdelay_us(2000000);
	  
	  /*VCC3.3: ADC12_IN10*/
		dValue = GetADCVoltage(ADC2, ADC_DR1);
		//Result[1] = ADC_GetConversionData(ADC2, ADC_DR1);
	  
	  temp = (double)(dValue) / 100.0;
	  DEBUG("The VCC3.3:    ADC12_IN10 capture voltage is: %.3f V \r\n",temp);
	  sdelay_us(2000000);
		//sdelay_us(2000000);
		
		/*VCC2.5: ADC12_IN12*/
		dValue = GetADCVoltage(ADC2, ADC_DR2);
	  //Result[2] = ADC_GetConversionData(ADC2, ADC_DR2);
	  temp = (double)(dValue) / 100.0;
	  DEBUG("The VCC2.5:    ADC12_IN12  capture voltage is: %.3f V \r\n",temp);
	  sdelay_us(2000000);
		//sdelay_us(2000000);
		
		/*VCCAUX1.8: ADC12_IN13*/
		dValue = GetADCVoltage(ADC2, ADC_DR3);
	  //Result[3] = ADC_GetConversionData(ADC2, ADC_DR3);
	  temp = (double)(dValue) / 100.0;
	  DEBUG("The VCCAUX1.8: ADC12_IN13  capture voltage is: %.3f V \r\n",temp);
	  sdelay_us(2000000);
		//sdelay_us(2000000);
		
		/*Current: ADC12_IN14*/
		dValue = GetADCVoltage(ADC2, ADC_DR4);
	  //Result[4] = ADC_GetConversionData(ADC2, ADC_DR4);
	  temp = (double)(dValue) / 100.0;
	  DEBUG("The Current:   ADC12_IN14  capture voltage is: %.3f V \r\n",temp);
	  sdelay_us(2000000);
		//sdelay_us(2000000);
//		
//		/*ADC12_IN5*/
//		dValue = GetADCVoltage(ADC1, ADC_DR5);
//	  
//	  temp = (double)(dValue) / 100.0;
//	  DEBUG("The ADC12_IN5 capture voltage is: %.3f V \r\n",temp);
//	  delay_us(2000000);
//		delay_us(2000000);
//		
//		/*ADC12_IN6*/
//		dValue = GetADCVoltage(ADC1, ADC_DR6);
//	  
//	  temp = (double)(dValue) / 100.0;
//	  DEBUG("The ADC12_IN6 capture voltage is: %.3f V \r\n",temp);
//	  delay_us(2000000);
//		delay_us(2000000);
//		
//		/*ADC12_IN7*/
//		dValue = GetADCVoltage(ADC1, ADC_DR7);
//	  
//	  temp = (double)(dValue) / 100.0;
//	  DEBUG("The ADC12_IN7 capture voltage is: %.3f V \r\n",temp);
//	  delay_us(2000000);
//		delay_us(2000000);
//		DEBUG("\r\n-----------------------------------------------\r\n");
		

   

		#endif /*end of ADC_TEST*/
		
		#ifdef ADC_TEMP
		  int i = 0;
			uint32_t temp = 0;
			double vol = 0;
			/* ---------- Sample 500ms ADC data -------------------------------------*/
			for (i=0;i<4;i=i+1) 
			{
						
				/* use delay or Interrupt mode to read back temp sensor data  ---------*/
				delay_us(2000);

				/* ---------- Get ADC data from DR0 of ADC ----------------------------*/
				temp += ADC_GetConversionData(ADC1,ADC_DR0); 		
			}		
			 
			temp = temp>>2;
			temp = temp * 333 / 4095;
			vol = (double)(temp) / 100.0;
			 DEBUG("The ADC12_IN16 capture voltage is: %.3f V \r\n",vol);
			
		#endif
		
		return;
}


/**----------------------------------------------------------------------------
** @Function:		   ADC_TempSensorConfiguration
**
** @Descriptions:		
**
** @parameters:			
**                  
**                  
**                  
** @Returned: none
** 
** @Author:  MCU Application Team
**
** @Date: 30-June-2017
**
-------------------------------------------------------------------------------*/
void ADC_TempSensorConfiguration(void)
{
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
  ADC_SetupChannels(ADC1, DR7EN, CHN16_DR7, TRIGGERMODE);

  #ifdef ADC_INT_ENABLE	
	ADC_EnableConversionInt(ADC1,1);
	NVIC_EnableIRQ(ADC1_2_IRQn);
  #endif

}

/**----------------------------------------------------------------------------
** @Function:		   ADC_TempSensor
**
** @Descriptions:		
**
** @parameters:			
**                  
**                  
**                  
** @Returned: none
** 
** @Author:  MCU Application Team
**
** @Date: 30-June-2017
**
-------------------------------------------------------------------------------*/
uint16_t ADC_TempSensor(void)
{
		double vol = 0.0;
	  double temperature = 0.0;
		uint32_t temp = 0;
	  uint32_t i = 0;
		/* ---------- Sample 500ms ADC data -------------------------------------*/
		for (i=0;i<32;i=i+1) 
		{
			ADC1_IssueSoftTrigger;		
			/* use delay or Interrupt mode to read back temp sensor data  ---------*/
			sdelay_us(5000);

			/* ---------- Get ADC data from DR0 of ADC ----------------------------*/
			temp += ADC_GetConversionData(ADC1,ADC_DR7); 		
		}		
		temp = temp>>5;
		if(temp > T25ADC)
		{
			temperature = 25.0 - ((double)(temp) - (double)(T25ADC)) / ADCSTEP;
		}
		else
		{
			temperature = 25.0 + ((double)(T25ADC) - (double)(temp)) / ADCSTEP;
		}
		DEBUG("The temperature  is: %.1f ℃ \r\n", temperature);
		//DEBUG("The temp value is: 0x%x\r\n", temp);
		temp = temp * 327/ 4095;
		vol = (double)(temp) / 100.0;
		DEBUG("The ADC12_IN16 capture voltage is: %.3f V \r\n",vol);
		return (uint16_t)(temperature*100);

}


/******************* (C) COPYRIGHT 2015  *****END OF FILE****/


