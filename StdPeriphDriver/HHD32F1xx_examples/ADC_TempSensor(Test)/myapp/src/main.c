/*******************************************************************************
*	Application: Demo code for Temp sensor using ADC1 Channel-16
*	Edition:		Version:1.0
*	Company: 		
*	Time: 			September 2015
*******************************************************************************/
#include "hhd32f1xx.h"
#include "hhd_sys.h"
#include "hhd_adc.h"
#include "hhd_uart.h"
#include "hhd_gpio.h"
#include<string.h>
#include<stdio.h>

#define T25ADC            0xBA3 //25℃ ADC的采样值
#define ADCREF   (double)(3.34) //ADC 参考电压
#define ADCSTEP  (double)(0.008*4096/ADCREF) //1℃ 0.008V

#ifdef __GNUC__
  /* With GCC/RAISONANCE, small printf (option LD Linker->Libraries->Small printf
     set to 'Yes') calls __io_putchar() */
  #define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
  #define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */


uint32_t temp;
//uint16_t led = 0x200;
uint16_t led = 0x01;
//uint16_t led = 0x04;
void delay1us(uint32_t time);
void UART1_IOCFG(void);

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
	//SystemCoreClockUpdate();
	/* --------- GPIOA Periph clock enable --------------*/
  ENABLEGPIOBCLK;
	ENABLEGPIOCCLK;
	ENABLEGPIODCLK;
	GPIO_ConfigPinsAsOutput(GPIOB, PIN9);
	GPIO_ConfigPinsAsOutput(GPIOC, PIN0);
	GPIO_ConfigPinsAsOutput(GPIOD, PIN2);
	  /*UART1 Configuration*/
  UART1_IOCFG();
  UART_Open(UART1,115200,UART_NO_PARITY,UART_RX_HALF_FULL);
  printf("\r\n----------------ADC Test---------------\r\n");
	
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
  ADC_SetupChannels(ADC1,DR1EN,CHN16_DR1,BURSTMODE);

  #ifdef ADC_INT_ENABLE	
	ADC_EnableConversionInt(ADC1,1);
	NVIC_EnableIRQ(ADC1_2_IRQn);
  #endif


	/* ---------- Delay 100us after ADC power-on ----------------------------*/
	delay1us(0xffff);
	while(1)
	{
		double vol = 0.0;
	  double temperature = 0.0;
		temp = 0;
		/* ---------- Sample 500ms ADC data -------------------------------------*/
		for (i=0;i<1024;i=i+1) 
		{
					
			/* use delay or Interrupt mode to read back temp sensor data  ---------*/
			delay1us(5000);

			/* ---------- Get ADC data from DR0 of ADC ----------------------------*/
			temp += ADC_GetConversionData(ADC1,ADC_DR1); 		
		}		
		temp = temp>>10;
		if(temp > T25ADC)
		{
			temperature = 25.0 - ((double)(temp) - (double)(T25ADC)) / ADCSTEP;
		}
		else
		{
			temperature = 25.0 + ((double)(T25ADC) - (double)(temp)) / ADCSTEP;
		}
		printf("The temperature  is: %.1f ℃\r\n", temperature);
		printf("The temp value is: 0x%x\r\n", temp);
		temp = temp * 333 / 4095;
		vol = (double)(temp) / 100.0;
		printf("The ADC12_IN16 capture voltage is: %.3f V \r\n",vol);
		led = ~led;
		//GPIO_WritePort(GPIOB, led);
		GPIO_WritePort(GPIOC, led);
		

 }

	
	  return 0;
}

void delay1us(uint32_t time)
{
			while(time--);
}
/**
  * @brief  Retargets the C library printf function to the USART.
  * @param  None
  * @retval None
  */
PUTCHAR_PROTOTYPE
{
  /* Place your implementation of fputc here */
  /* e.g. write a character to the USART */
 // USART_SendData(USART1, (uint8_t) ch); /*发送一个字符函数*/ 
	UART_ByteWrite(UART1, (uint8_t) ch);

  /* Loop until the end of transmission */
	while((UART_GetStatus(UART1) & UART_TX_EMPTY) == 1 )
	{}
  //while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET)/*等待发送完成*/
  //{
  
 // }
  return ch;
}

/**----------------------------------------------------------------------------
** @Function:		   UART1_IOCFG
**
** @Descriptions:	 UART GPIO Configuration  	
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
void UART1_IOCFG(void)
{
	/* you can config UART1 RX from PB7,
	and you can config UART1 TX to PB6 --------------------------------*/
	#if 0
	IOCON->PB6.bit.FUNC  = UART1_TX_to_PB6;
	IOCON->PB6.bit.PUE   = 1;
	IOCON->PB7.bit.FUNC  = UART1_RX_from_PB7;
	IOCON->PB7.bit.PUE   = 1;	
	
 #else
	IOCON->PA9.bit.FUNC  = UART1_TX_to_PA9;
	IOCON->PA9.bit.PUE   = 1;
	IOCON->PA10.bit.FUNC = UART1_RX_from_PA10;
	IOCON->PA10.bit.PUE  = 1;	
	#endif
}



