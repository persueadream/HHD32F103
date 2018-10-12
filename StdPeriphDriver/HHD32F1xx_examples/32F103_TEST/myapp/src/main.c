/******************************************************************************
*	Application: Demo code for UART using in HHD32F1xx
*	Edition:		Version:1.0
*	Company: 		
*	Time: 			June 2017
******************************************************************************/
#include "hhd32f1xx.h"
#include "hhd_sys.h"
#include "hhd_uart.h"
#include "hhd_gpio.h"
#include "hhd_adc.h"
#include "hhd_spi.h"
#include "hhd_iic.h"
#include "delay.h"
#include "sys.h"

#include<string.h>
#include<stdio.h>



#define ALL_PIN  0x0000FFFF
#define EIGHT_BIT   7
#define LED     PDout(1)

//#define GPIO_IN_TEST  0
//#define GPIO_OUT_TEST 1
//#define UART_TEST 2
//#define IO_EXTI   3 
#define ADC_TEST  4
//#define SPI_TEST    5
//#define I2C_TEST    6
//#define ADC_TEMP    7

#ifdef __GNUC__
  /* With GCC/RAISONANCE, small printf (option LD Linker->Libraries->Small printf
     set to 'Yes') calls __io_putchar() */
  #define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
  #define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */



void UART1_IOCFG(void);
void UART2_IOCFG(void);
void UART3_IOCFG(void);
void ADC_Configuration(void);
static void SPI_IOCONFIG(void);
void SPI_Configuration(void);
void I2C_Configuration(void);
static void IIC_IOCONFIG(void);

void delay(int i);
void GPIO_Test(void);
void UART_Test(void);
void IO_EXTI_Test(void);
void ADC_Test(void);
void SPI_Test(void);
void I2C_Test(void);
void GetExtiPin(unsigned int extistate);
uint32_t GetADCVoltage(HHD32F_ADC_TypeDef *ADC, uint8_t dr);




uint16_t Value_GPIOA, Value_GPIOB, Value_GPIOC, Value_GPIOD; 
uint32_t dValue = 0;

IIC_CtrlBlk_TypeDef I2C1Ctrl;
IIC_CtrlBlk_TypeDef I2C2Ctrl;
void delay(int i)
{
	int j = i;
	for(; j>0; j--)
	{;}
}
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
		int i;

	/* ----------- System initialization -------------------------------------*/
	SYS_SystemInitial();		
	//SystemCoreClockUpdate();
  ADC_Configuration();
 //	SPI_Configuration();
 //	 I2C_Configuration();
	/* G32F1xx has up to 5 UARTs in different part-number IC -----------------*/
	// Each Uart supports parity check mode.
	// 
	/* ---------- Set UART1 TX/RX GPIO config  -------------------------------*/
//  UART1_IOCFG();
	//delay_init();
	//SysTick_Init();
	/* --------- GPIOA Periph clock enable --------------*/
 // ENABLEGPIOCCLK;
	//	ENABLEGPIOBCLK;
//	ENABLEGPIOCCLK;
//	ENABLEGPIODCLK;
//	ENABLEGPIOECLK;
//	ENABLEGPIOFCLK;
//	ENABLEGPIOGCLK;
	//GPIO_ConfigPinsAsOutput(GPIOC, ALL_PIN);
	//  GPIO_ConfigPinsAsOutput(GPIOB,ALL_PIN);
//	GPIO_ConfigPinsAsOutput(GPIOC,ALL_PIN);
//	GPIO_ConfigPinsAsOutput(GPIOD,ALL_PIN);
//	GPIO_ConfigPinsAsOutput(GPIOE,ALL_PIN);
//	GPIO_ConfigPinsAsOutput(GPIOF,ALL_PIN);
//	GPIO_ConfigPinsAsOutput(GPIOG,ALL_PIN);
	
  /* ---------- Set Uart1 Baudrate to 115200, no parity check ------------- */
  //UART_Open(UART1,115200,UART_NO_PARITY,UART_RX_NOT_EMPTY);
	
	
	/* ---------- Print sting ------------------------------------------------*/
//	UART_PutString(UART1,"\tDemo system for UART!\n");
	
	

	/* ---------- Close Uart1 ------------------------------------------------*/
//	UART_Close(UART1);

 // LED = 0;
//	IO_EXTI_Test();
	while(1)
	{
// 	 	for(i=0; i<8; i++)
// 		{
// 			GPIO_SetPin(GPIOC,PIN0<<i);
// 			delay_ms(200);
// 			GPIO_ResetPin(GPIOC,PIN0<<i);	
// 			delay_ms(200);	
// 			
// 	}
		
		//delay_ms(200);	
//   	GPIO_SetPin(GPIOC,ALL_PIN);
// 		delay_us(1000000);
// 		GPIO_ResetPin(GPIOC,ALL_PIN);	
// 		delay_us(1000000);	
//   	GPIO_SetPin(GPIOC,0xff);
//  		UART_PutString(UART1,"\tDemo system for UART!\n");
		 // GPIO_Test();
		//  UART_Test();
		 ADC_Test();
    // SPI_Test();
		//I2C_Test();
		delay(2000000);	
		delay(2000000);	
		/* -------- Set GPIO bit to 1 ---------------------*/
//		GPIO_SetPin(GPIOA,ALL_PIN);
//		GPIO_SetPin(GPIOB,0x0000FEFF);
//		GPIO_SetPin(GPIOC,ALL_PIN);
//		GPIO_SetPin(GPIOD,ALL_PIN);
//		GPIO_SetPin(GPIOE,ALL_PIN);
//		GPIO_SetPin(GPIOF,ALL_PIN);
//		GPIO_SetPin(GPIOG,ALL_PIN);
		/* -------- Delay time ----------------------------*/
//		dly1us(2000000);
		
		/* -------- Clear GPIO bit to 0 -------------------*/
//    GPIO_ResetPin(GPIOA,ALL_PIN);		
//		GPIO_ResetPin(GPIOB,0x0000FEFF);	
//		GPIO_ResetPin(GPIOC,ALL_PIN);	
//		GPIO_ResetPin(GPIOD,ALL_PIN);	
//		GPIO_ResetPin(GPIOE,ALL_PIN);	
//		GPIO_ResetPin(GPIOF,ALL_PIN);	
//		GPIO_ResetPin(GPIOG,ALL_PIN);	

		/* -------- Delay time ----------------------------*/
//		dly1us(2000000);	
  }
	
//  return 0;

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

/**----------------------------------------------------------------------------
** @Function:		   UART2_IOCFG
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
void UART2_IOCFG(void)
{
	/* you can config UART2 RX from PA3 or PD6,
	and you can config UART2 TX to PA2 or PD5 --------------------------------*/
	#if 1
	IOCON->PA2.bit.FUNC  = UART2_TX_to_PA2;
	IOCON->PA2.bit.PUE   = 1;
	IOCON->PA3.bit.FUNC  = UART2_RX_from_PA3;
	IOCON->PA3.bit.PUE   = 1;	
  #else
	IOCON->PD5.bit.FUNC  = UART2_TX_to_PD5;
	IOCON->PD5.bit.PUE   = 1;
	IOCON->PD6.bit.FUNC  = UART2_RX_from_PD6;
	IOCON->PD6.bit.PUE   = 1;	
	#endif
}

/**----------------------------------------------------------------------------
** @Function:		   UART3_IOCFG
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
void UART3_IOCFG(void)
{
	/* you can config UART3 RX from PB11 or PD9,
	and you can config UART3 TX to PB10 or PD8 --------------------------------*/
	#if 1
	IOCON->PB10.bit.FUNC = UART3_TX_to_PB10;
	IOCON->PB10.bit.PUE  = 1;
	IOCON->PB11.bit.FUNC = UART3_RX_from_PB11;
	IOCON->PB11.bit.PUE  = 1;	
  #else
	IOCON->PD8.bit.FUNC  = UART3_TX_to_PD8;
	IOCON->PD8.bit.PUE   = 1;
	IOCON->PD9.bit.FUNC  = UART3_RX_from_PD9;
	IOCON->PD9.bit.PUE   = 1;	
	#endif
}

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
// 	ENABLEADC2CLK;
	//ENABLEADC3CLK;
	
  /*UART1 Configuration*/
  UART1_IOCFG();
  UART_Open(UART1,115200,UART_NO_PARITY,UART_RX_HALF_FULL);
  printf("\r\n----------------ADC Test---------------\r\n");
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

// 	OpenADC2_IN1;
// 	OpenADC2_IN2;
// 	OpenADC2_IN3;
// 	OpenADC2_IN4;
// 	OpenADC2_IN5;
// 	OpenADC2_IN6;
// 	OpenADC2_IN7;
// 	OpenADC2_IN8;
// 	OpenADC2_IN9;
// 	OpenADC2_IN10;
// 	OpenADC2_IN11;
// 	OpenADC2_IN12;
// 	OpenADC2_IN13;
// 	OpenADC2_IN14;
// 	OpenADC2_IN15;
// 	OpenADC2_IN16;


	OpenADC1_IN1;
	OpenADC1_IN2;
	OpenADC1_IN3;
	OpenADC1_IN4;
	OpenADC1_IN5;
	OpenADC1_IN6;
	OpenADC1_IN7;
	OpenADC1_IN8;
// 	OpenADC1_IN9;
// 	OpenADC1_IN10;
// 	OpenADC1_IN11;
// 	OpenADC1_IN12;
// 	OpenADC1_IN13;
// 	OpenADC1_IN14;
// 	OpenADC1_IN15;
// 	OpenADC1_IN16;
	
 
	/* -------------- Initialise ADC1,ADC2 and set Sample speed ------------------*/
	ADC_Init(ADC1,100000);
// 	ADC_Init(ADC2,100000);
	
	
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
ADC_SetupChannels(ADC1, (DR0EN | DR1EN | DR2EN | DR3EN | DR4EN | DR5EN | DR6EN | DR7EN),(CHN1_DR0 | CHN2_DR1 | CHN3_DR2 | CHN4_DR3 | CHN5_DR4 | \
												 CHN6_DR5 | CHN7_DR6 | CHN8_DR7),BURSTMODE);
// 	  ADC_SetupChannels(ADC2, (DR0EN | DR1EN | DR2EN | DR3EN | DR4EN | DR5EN | DR6EN | DR7EN),(CHN9_DR0 | CHN10_DR1 | CHN11_DR2 | CHN12_DR3 | CHN13_DR4 | \
// 											 CHN14_DR5 | CHN15_DR6 | CHN16_DR7),BURSTMODE);
  //  ADC_SetupChannels(ADC1,DR0EN,CHN16_DR0,BURSTMODE);

	//ADC_SetupChannels(ADC1,CHN2_DR1,BURSTMODE);
	//ADC_SetupChannels(ADC1,CHN3_DR2,BURSTMODE);
	//ADC_SetupChannels(ADC1,CHN4_DR3,BURSTMODE);
	//ADC_SetupChannels(ADC1,CHN11_DR4,BURSTMODE);
	//ADC_SetupChannels(ADC1,CHN12_DR5,BURSTMODE);
	//ADC_SetupChannels(ADC1,CHN13_DR6,BURSTMODE);
	//ADC_SetupChannels(ADC1,CHN14_DR7,BURSTMODE);

	/* ---------- Delay 100us after ADC power-on ----------------------------*/
	delay(0xffff);
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
		ADC1_IssueSoftTrigger;
		/* use delay or Interrupt mode to read back ADC 12bit data  -----------*/
		delay(0xff);

		/* ---------- Get ADC data from DR0 of ADC ----------------------------*/
		//temp = ADC_GetConversionData(ADC1,ADC_DR0); 		
		//dValue = (temp * 330 / 4095);
		printf("\r\n-----------------------------------------------\r\n");
		/*ADC12_IN0*/
		dValue = GetADCVoltage(ADC1, ADC_DR0);
	  temp = (double)(dValue) / 100.0;
	  printf("The ADC12_IN0 capture voltage is: %.3f V \r\n",temp);
	  delay(2000000);
	  delay(2000000);
	  
	  /*ADC12_IN1*/
		dValue = GetADCVoltage(ADC1, ADC_DR1);
	  
	  temp = (double)(dValue) / 100.0;
	  printf("The ADC12_IN1 capture voltage is: %.3f V \r\n",temp);
	  delay(2000000);
		delay(2000000);
		
		/*ADC12_IN2*/
		dValue = GetADCVoltage(ADC1, ADC_DR2);
	  
	  temp = (double)(dValue) / 100.0;
	  printf("The ADC12_IN2 capture voltage is: %.3f V \r\n",temp);
	  delay(2000000);
		delay(2000000);
		
		/*ADC12_IN3*/
		dValue = GetADCVoltage(ADC1, ADC_DR3);
	  
	  temp = (double)(dValue) / 100.0;
	  printf("The ADC12_IN3 capture voltage is: %.3f V \r\n",temp);
	  delay(2000000);
		delay(2000000);
		
		/*ADC12_IN4*/
		dValue = GetADCVoltage(ADC1, ADC_DR4);
	  
	  temp = (double)(dValue) / 100.0;
	  printf("The ADC12_IN4 capture voltage is: %.3f V \r\n",temp);
	  delay(2000000);
		delay(2000000);
		
		/*ADC12_IN5*/
		dValue = GetADCVoltage(ADC1, ADC_DR5);
	  
	  temp = (double)(dValue) / 100.0;
	  printf("The ADC12_IN5 capture voltage is: %.3f V \r\n",temp);
	  delay(2000000);
		delay(2000000);
		
		/*ADC12_IN6*/
		dValue = GetADCVoltage(ADC1, ADC_DR6);
	  
	  temp = (double)(dValue) / 100.0;
	  printf("The ADC12_IN6 capture voltage is: %.3f V \r\n",temp);
	  delay(2000000);
		delay(2000000);
		
		/*ADC12_IN7*/
		dValue = GetADCVoltage(ADC1, ADC_DR7);
	  
	  temp = (double)(dValue) / 100.0;
	  printf("The ADC12_IN7 capture voltage is: %.3f V \r\n",temp);
	  delay(2000000);
		delay(2000000);
		printf("\r\n-----------------------------------------------\r\n");
		

   

		#endif /*end of ADC_TEST*/
		
		#ifdef ADC_TEMP
		  int i = 0;
			uint32_t temp = 0;
			double vol = 0;
			/* ---------- Sample 500ms ADC data -------------------------------------*/
			for (i=0;i<4;i=i+1) 
			{
						
				/* use delay or Interrupt mode to read back temp sensor data  ---------*/
				delay(2000);

				/* ---------- Get ADC data from DR0 of ADC ----------------------------*/
				temp += ADC_GetConversionData(ADC1,ADC_DR0); 		
			}		
			 
			temp = temp>>2;
			temp = temp * 333 / 4095;
			vol = (double)(temp) / 100.0;
			 printf("The ADC12_IN16 capture voltage is: %.3f V \r\n",vol);
			
		#endif
		
		return;
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
	  temp = temp * 333 / 4095;
	  return temp;
}

/**----------------------------------------------------------------------------
** @Function:		   GPIO_Test
**
** @Descriptions:	 GPIO test	
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
void GPIO_Test()
{
	  Value_GPIOA = 0;
	  Value_GPIOB = 0;
	  Value_GPIOC = 0;
	  Value_GPIOD = 0;
		/* --------- GPIOA Periph clock enable --------------*/
		ENABLEGPIOACLK;
		ENABLEGPIOBCLK;
		ENABLEGPIOCCLK;
	  ENABLEGPIODCLK;
	//	ENABLEGPIOECLK;
	//	ENABLEGPIOFCLK;
	//	ENABLEGPIOGCLK;
	while(1)
	{
		#ifdef GPIO_OUT_TEST
		GPIO_ConfigPinsAsOutput(GPIOA, ALL_PIN);
	  GPIO_ConfigPinsAsOutput(GPIOB,ALL_PIN);
		GPIO_ConfigPinsAsOutput(GPIOC,ALL_PIN);
		GPIO_ConfigPinsAsOutput(GPIOD,ALL_PIN);
	//	GPIO_ConfigPinsAsOutput(GPIOE,ALL_PIN);
	//	GPIO_ConfigPinsAsOutput(GPIOF,ALL_PIN);
	//	GPIO_ConfigPinsAsOutput(GPIOG,ALL_PIN);
	
	  Value_GPIOA = GPIO_ReadPort(GPIOA);
		GPIO_ResetPin(GPIOA,ALL_PIN);
		Value_GPIOA = GPIO_ReadPort(GPIOA);
		delay_us(2000000);
		GPIO_SetPin(GPIOA,ALL_PIN);	
		Value_GPIOA = GPIO_ReadPort(GPIOA);
		delay_us(2000000);	
		/*GPIOB*/
		Value_GPIOB = GPIO_ReadPort(GPIOB);
		GPIO_ResetPin(GPIOB,ALL_PIN);
		Value_GPIOB = GPIO_ReadPort(GPIOB);
		delay_us(2000000);
		GPIO_SetPin(GPIOB,ALL_PIN);	
		Value_GPIOB = GPIO_ReadPort(GPIOB);
		delay_us(2000000);
		/*GPIOC*/
		Value_GPIOC = GPIO_ReadPort(GPIOC);
		GPIO_ResetPin(GPIOC,ALL_PIN);
		Value_GPIOC = GPIO_ReadPort(GPIOC);
		delay_us(2000000);
		GPIO_SetPin(GPIOC,ALL_PIN);	
		Value_GPIOC = GPIO_ReadPort(GPIOC);
		delay_us(2000000);
		
		/*GPIOD*/
		Value_GPIOD = GPIO_GetPortState(GPIOD);
		GPIO_ResetPin(GPIOD,ALL_PIN);
		Value_GPIOD = GPIO_GetPortState(GPIOD);
		delay_us(2000000);
		GPIO_SetPin(GPIOD,ALL_PIN);	
		Value_GPIOD = GPIO_GetPortState(GPIOD);
		delay_us(2000000);
#endif

#ifdef GPIO_IN_TEST
		GPIO_ConfigPinsAsInput(GPIOA, ALL_PIN);
	  GPIO_ConfigPinsAsInput(GPIOB,ALL_PIN);
		GPIO_ConfigPinsAsInput(GPIOC,ALL_PIN);
		GPIO_ConfigPinsAsInput(GPIOD,ALL_PIN);
	//	GPIO_ConfigPinsAsOutput(GPIOE,ALL_PIN);
	//	GPIO_ConfigPinsAsOutput(GPIOF,ALL_PIN);
	//	GPIO_ConfigPinsAsOutput(GPIOG,ALL_PIN);
	
	  Value_GPIOA = GPIO_ReadPort(GPIOA);
		delay_us(2000000);

		/*GPIOB*/
		Value_GPIOB = GPIO_ReadPort(GPIOB);
	  delay_us(2000000);
		/*GPIOC*/
		Value_GPIOC = GPIO_ReadPort(GPIOC);
    delay_us(2000000);
		
		/*GPIOD*/
		Value_GPIOD = GPIO_GetPortState(GPIOD);
		delay_us(2000000);

#endif
	
	}

}

/**----------------------------------------------------------------------------
** @Function:		   IO_EXTI_Test
**
** @Descriptions:	 GPIO external interrupt test
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
void IO_EXTI_Test()
{
			/* --------- GPIOA Periph clock enable --------------*/
		ENABLEGPIOACLK;
		ENABLEGPIOBCLK;
		ENABLEGPIOCCLK;
	  ENABLEGPIODCLK;
	  /*UART1 Configuration*/
		UART1_IOCFG();
	  UART_Open(UART1,115200,UART_NO_PARITY,UART_RX_HALF_FULL);
	   printf("\r\n----------------IO_EXTI Test---------------\r\n");
// 	  /*GPIOA外部中断配置*/
// 	  GPIO_ConfigPinsAsInput(GPIOA, 0x1DFF);     //配置PA8为中断输入
// 	  GPIO_EnableInt(GPIOA, 0x1DFF, FALL_EDGE); //上升沿中断
	   
// 	  /*GPIOB外部中断配置 whout PB3,PB4   */
// 	  GPIO_ConfigPinsAsInput(GPIOB, 0xFFE7);     //配置PA8为中断输入
// 	  GPIO_EnableInt(GPIOB, 0xFFE7, RISE_EDGE); //上升沿中断
	
// 		  /*GPIOC外部中断配置 */
// 	  GPIO_ConfigPinsAsInput(GPIOC, 0xFFFF);     //配置PA8为中断输入
// 	  GPIO_EnableInt(GPIOC, 0xFFFF, FALL_EDGE); //上升沿中断
	  
		  /*GPIOC外部中断配置 */
	  GPIO_ConfigPinsAsInput(GPIOD, PIN2);     //配置PA8为中断输入
	  GPIO_EnableInt(GPIOD, PIN2, FALL_EDGE); //上升沿中断
	
	
	
	  NVIC_EnableIRQ(EXTI0_IRQn);
	  NVIC_EnableIRQ(EXTI1_IRQn);
	  NVIC_EnableIRQ(EXTI2_IRQn);
	  NVIC_EnableIRQ(EXTI3_IRQn);
	  NVIC_EnableIRQ(EXTI4_IRQn);
	  NVIC_EnableIRQ(EXTI9_5_IRQn);
	  NVIC_EnableIRQ(EXTI15_10_IRQn);
	
	
	
// 	  GPIO_ConfigPinsAsInput(GPIOA,PIN5|PIN6|PIN7|PIN8);     //配置PA8为中断输入
// 	  GPIO_EnableInt(GPIOA, PIN5|PIN6|PIN7|PIN8, FALL_EDGE); //上升沿中断
// 	  NVIC_EnableIRQ(EXTI9_5_IRQn);
	
	
	  
}


/**----------------------------------------------------------------------------
** @Function:		   UART_Test
**
** @Descriptions:	 UART test
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
void UART_Test()
{
	/* ---------- Set UART1 TX/RX GPIO config  -------------------------------*/
  UART1_IOCFG();
	UART2_IOCFG();
	UART3_IOCFG();
	/* ---------- Set Uart1 Baudrate to 115200, no parity check ------------- */
  UART_Open(UART1,115200,UART_NO_PARITY,UART_RX_HALF_FULL);
	UART_Open(UART2,115200,UART_NO_PARITY,UART_RX_NOT_EMPTY);
	UART_Open(UART3,115200,UART_NO_PARITY,UART_RX_NOT_EMPTY);
	
		/*使能接收中断*/
//	UART_EnableInt(UART1, UART_RX_HALF_FULL); RXHLFINT
  UART_EnableInt(UART1, UART_RX_NOT_EMPTY);
	UART_EnableInt(UART2, UART_RX_NOT_EMPTY);
	UART_EnableInt(UART3, UART_RX_NOT_EMPTY);
	NVIC_EnableIRQ(UART1_IRQn);
	NVIC_EnableIRQ(UART2_IRQn);
	NVIC_EnableIRQ(UART3_IRQn);
	/* ---------- Print sting ------------------------------------------------*/
//	UART_PutString(UART1,"\tDemo system for UART!\n");
	while(1)
	{
 				  delay_us(2000000);
		      printf("Hello wangnkui!\r\n");
	}
}



/**----------------------------------------------------------------------------
** @Function:		   UART1_IRQHandler
**
** @Descriptions:	 UART1 interrupt
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
void UART1_IRQHandler()
{
		unsigned char recv = 0;
		uint8_t datalen = 16;
		if(UART1->INTSTATUS.bit.RXNEINT == 1)
		{
			UART_ByteRead(UART1, &recv);
			UART_ByteWrite(UART1, recv);
			while((UART_GetStatus(UART1) & UART_TX_EMPTY) == 1 )
			{;}
		}
}

/**----------------------------------------------------------------------------
** @Function:		   UART2_IRQHandler
**
** @Descriptions:	 UART2 interrupt
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
void UART2_IRQHandler()
{
		unsigned char recv = 0;
		uint8_t datalen = 16;
		if(UART2->INTSTATUS.bit.RXNEINT == 1)
		{
			UART_ByteRead(UART2, &recv);
			UART_ByteWrite(UART2, recv);
			while((UART_GetStatus(UART2) & UART_TX_EMPTY) == 1 )
			{;}
		}
}

/**----------------------------------------------------------------------------
** @Function:		   UART3_IRQHandler
**
** @Descriptions:	 UART3 interrupt
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
void UART3_IRQHandler()
{
		unsigned char recv = 0;
		uint8_t datalen = 16;
		if(UART3->INTSTATUS.bit.RXNEINT == 1)
		{
			UART_ByteRead(UART3, &recv);
			UART_ByteWrite(UART3, recv);
			while((UART_GetStatus(UART3) & UART_TX_EMPTY) == 1 )
			{;}
		}
}


/**----------------------------------------------------------------------------
** @Function:		   EXTI0_IRQHandler
**
** @Descriptions:	 GPIO external interrupt
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
//---- GPIOx_PIN0 ----------------------
void EXTI0_IRQHandler ()
{    
	//NVIC_DisableIRQ(EXTI0_IRQn);
	//while(1);
	unsigned int state = SYSCON->EXTISTAT.all;//外部中断状态寄存器
	//Clear GPIO interrupt flag in flag register, updated @2016/02/16 16:11
	//GPIO_ClrIntflag(GPIOA,PIN0);
	//GPIO_ClrIntflag(GPIOB,PIN0);
	GPIO_ClrIntflag(GPIOC,PIN0);
	printf("\tEXTI0 Interrupt product!\n");
	GetExtiPin(state);
}	

//---- GPIOx_PIN1 ----------------------
void EXTI1_IRQHandler ()
{ 
// 	NVIC_DisableIRQ(EXTI1_IRQn);
// 	while(1);
	unsigned int state = SYSCON->EXTISTAT.all;//外部中断状态寄存器
	//Clear GPIO interrupt flag in flag register, updated @2016/02/16 16:11
// 	GPIO_ClrIntflag(GPIOA,PIN1);
// 	GPIO_ClrIntflag(GPIOB,PIN1);
	GPIO_ClrIntflag(GPIOC,PIN1);
	printf("\tEXTI1 Interrupt product!\n");
	GetExtiPin(state);
}	

//---- GPIOx_PIN2 ----------------------
void EXTI2_IRQHandler ()
{
	//NVIC_DisableIRQ(EXTI2_IRQn);
	//while(1);
	unsigned int state = SYSCON->EXTISTAT.all;//外部中断状态寄存器
	//Clear GPIO interrupt flag in flag register, updated @2016/02/16 16:11
	//GPIO_ClrIntflag(GPIOA,PIN2);
// 	GPIO_ClrIntflag(GPIOB,PIN2);
	//GPIO_ClrIntflag(GPIOC,PIN2);
	GPIO_ClrIntflag(GPIOD,PIN2);
	printf("\tEXTI2 Interrupt product!\n");
	GetExtiPin(state);
}	

//---- GPIOx_PIN3 ----------------------
void EXTI3_IRQHandler ()
{
	//NVIC_DisableIRQ(EXTI3_IRQn);
	//while(1);
	unsigned int state = SYSCON->EXTISTAT.all;//外部中断状态寄存器
	//Clear GPIO interrupt flag in flag register, updated @2016/02/16 16:11
	//GPIO_ClrIntflag(GPIOA,PIN3);
  //GPIO_ClrIntflag(GPIOB,PIN3);
	GPIO_ClrIntflag(GPIOC,PIN3);
	printf("\tEXTI3 Interrupt product!\n");
	GetExtiPin(state);
}	

//---- GPIOx_PIN4 ----------------------
void EXTI4_IRQHandler ()
{
	//NVIC_DisableIRQ(EXTI4_IRQn);
	//while(1);
		unsigned int state = SYSCON->EXTISTAT.all;//外部中断状态寄存器
	//Clear GPIO interrupt flag in flag register, updated @2016/02/16 16:11
	//GPIO_ClrIntflag(GPIOA,PIN4);
	//GPIO_ClrIntflag(GPIOB,PIN4);
	GPIO_ClrIntflag(GPIOC,PIN4);
	printf("\tEXTI4 Interrupt product!\n");
	GetExtiPin(state);
}	



//---- GPIOx_PIN9- GPIOx_PIN5  ----------------------
void EXTI9_5_IRQHandler ()
{
	//NVIC_DisableIRQ(EXTI9_5_IRQn);
	unsigned int state = SYSCON->EXTISTAT.all;//外部中断状态寄存器
	
	//Clear GPIO interrupt flag in flag register, updated @2016/02/16 16:11
	/*whiout PA9,PA13,PA14,PA15*/
	//GPIO_ClrIntflag(GPIOA,0x1DFF);0xFFE7
  //GPIO_ClrIntflag(GPIOB,0xFFE7);
	GPIO_ClrIntflag(GPIOC,0xFFFF);
	printf("\tEXTI9_5 Interrupt product!\n");
	GetExtiPin(state);
//	printf("state:%x\r\n",state);
	//while(1);
}	



//---- GPIOx_PIN15 - GPIOx_PIN10 ----------------------
void EXTI15_10_IRQHandler ()
{
// 	NVIC_DisableIRQ(EXTI15_10_IRQn);
// 	while(1);
		//NVIC_DisableIRQ(EXTI9_5_IRQn);
	unsigned int state = SYSCON->EXTISTAT.all;//外部中断状态寄存器
	
	//Clear GPIO interrupt flag in flag register, updated @2016/02/16 16:11
	//GPIO_ClrIntflag(GPIOA,0x1FFF);
	//GPIO_ClrIntflag(GPIOB,0xFFE7);
	GPIO_ClrIntflag(GPIOC,0xFFFF);
	
	printf("\tEXTI15_10 Interrupt product!\n");
	GetExtiPin(state);
}	

/**----------------------------------------------------------------------------
** @Function:		   GetExtiPin
**
** @Descriptions:	 Get pin number
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
void GetExtiPin(unsigned int extistate)
{
	int i = 15;
	unsigned int temp = extistate;
	for(i = 0; i<=15; i++)
	{
			if(temp == (0x0001<<i))
			{
		    printf("The EXTI Pin is: PIN%d\r\n", i);
			}
	}
}


/**----------------------------------------------------------------------------
** @Function:		   SPI_Configuration
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
void SPI_Configuration(void)
{
	  /*UART1 Configuration*/
  UART1_IOCFG();
  UART_Open(UART1,115200,UART_NO_PARITY,UART_RX_HALF_FULL);
  printf("\r\n----------------SPI Test---------------\r\n");
	/* ----------- SPI1,SPI2 GPIO configuration --------------------- */
	SPI_IOCONFIG();	

	/* ----------- initial SPI--------------------- */
	/*
	SPI_FRAME:  标准SPI
	EIGHT_BIT:  8位数据传输
	SPI_MASTER: SPI主模式
	SPI_MODE0:  SCK空闲时为低电平，第一次时钟跳变捕获数据。
	*/
	SPI_Open(SPI1,SPI_FRAME, EIGHT_BIT, SPI_MASTER, SPI_MODE0);
	/*
	SPI speed 1MHz
	*/
	SPI_SetClk(SPI1,1000000);
	
	SPI_Open(SPI2,SPI_FRAME, EIGHT_BIT, SPI_SLAVE, SPI_MODE0);
	SPI_SetClk(SPI2,1000000);
	
	SPI_EnableInt(SPI1, SPI_RX_FIFO_NOT_EMPTY);
  /*
	此处采用SPI_RX_FIFO_NOT_EMPTY中断方式，SPI2能够接收每一帧SPI1发送的数据。	
	SPI_RX_FIFO_FULL和SPI_RX_FIFO_HALF_FULL方式都有丢包的情况。
	*/
	SPI_EnableInt(SPI2, SPI_RX_FIFO_NOT_EMPTY);
	NVIC_EnableIRQ(SPI1_IRQn);
	NVIC_EnableIRQ(SPI2_IRQn);
}

/**----------------------------------------------------------------------------
** @Function:		   SPI_IOCONFIG
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
static void SPI_IOCONFIG(void)
{
	#if 1			//SPI1, SSEL-> PA4, SCK-> PA5, MISO-> PA6, MOSI-> PA7
	SPI1_SSEL_PA4;
	SPI1_SCK_PA5;	
	SPI1_MISO_PA6;
	SPI1_MOSI_PA7;	
	#endif

	#if 0			//SPI1, SSEL-> PA15, SCK-> PB3, MISO-> PB4, MOSI-> PB5
	SPI1_SSEL_PA15;
	SPI1_SCK_PB3;	
	SPI1_MISO_PB4;
	SPI1_MOSI_PB5;	
	#endif

	#if 1			//SPI2, SSEL-> PB12, SCK-> PB13, MISO-> PB14, MOSI-> PB15
	SPI2_SSEL_PB12;
	SPI2_SCK_PB13;	
	SPI2_MISO_PB14;
	SPI2_MOSI_PB15;	
	#endif

	#if 0			//SPI3, SSEL-> PA15, SCK-> PB3, MISO-> PB4, MOSI-> PB5
	SPI3_SSEL_PA15;
	SPI3_SCK_PB3;	
	SPI3_MISO_PB4;
	SPI3_MOSI_PB5;	
	#endif
	
	
}	

/**----------------------------------------------------------------------------
** @Function:		   SPI_Test
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
void SPI_Test(void)
{
	#ifdef SPI_TEST
	int rdata = 0,temp = 0;
	int i = 0;
	/* ----------- Flush SPI FIFO ----------------------------- */
	SPI_ClearFIFO(SPI1);
//	
//	
//	/* ----------- Send one byte data to TX FIFO -------------- */
//	/* --------- 用跳线把SPI1 的MISO和MOSI连起来 -------------- */
	printf("---------SPI Send data--------\r\n");
	SPI_Set_SSEL_High(SPI1);
	SPI_Reset_SSEL_Low(SPI1);
	SPI_Write_FIFO(SPI1,0x44);
	SPI_Set_SSEL_High(SPI1);
//	
//	
//	//Polling RX FIFO is not empty, if there is more than one byte data,
//	//Then start read FIFO.
// 	POLL_RXFIFO_NOTEMPTY(SPI1);
// //	
// 	rdata = SPI_Read_FIFO(SPI1);
// 	printf("The SPI1 Read data is: %x\r\n", rdata);
//	
//	/* ----------- Flush SPI FIFO ----------------------------- */
	//SPI_ClearFIFO(SPI2);
	
	
	/* ----------- Send one byte data to TX FIFO -------------- */
	/* --------- 用跳线把SPI1 的MISO和MOSI连起来 -------------- */
	//SPI_Write_FIFO(SPI2,0x44);
	
	
	//Polling RX FIFO is not empty, if there is more than one byte data,
	//Then start read FIFO.
// 	POLL_RXFIFO_NOTEMPTY(SPI2);
// 	
// 	rdata = SPI_Read_FIFO(SPI2);
// 	temp = rdata;
// 	printf("The SPI2 Read data is: %x\r\n", rdata);
	#endif /*end of SPI_TEST*/
	return;
}

/**----------------------------------------------------------------------------
** @Function:		   SPI1_IRQHandler
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
void SPI1_IRQHandler ()
{
	int temp = 0;
	//while(SPI1->SR.bit.RNE==0);
	temp =  SPI_Read_FIFO(SPI1);
	printf("In SPI1 interrupt,the SPI1 Read data is: %x\r\n", temp);
	
}	

/**----------------------------------------------------------------------------
** @Function:		   SPI2_IRQHandler
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
void SPI2_IRQHandler ()
{
	int temp = 0;
//	while(SPI2->SR.bit.RNE==0);
	//SPI2->ICR.bit.RTIC = 1;
	temp =  SPI_Read_FIFO(SPI2);
	printf("In SPI2 interrupt,the SPI2 Read data is: %x\r\n", temp);
	SPI_ClearFIFO(SPI2);
	SPI_Write_FIFO(SPI2,0x55);
	
	
}	


/**----------------------------------------------------------------------------
** @Function:		   I2C_Test
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
void I2C_Test(void)
{
	#ifdef I2C_TEST
	unsigned char temp = 0;
	int i = 0;
	unsigned char arry[7] = {0x11, 0x22, 0x33, 0x44, 0x55, 0x66,0xFF};
  unsigned char ReadArry[8] = {0};
  I2C2Ctrl.WrIndex = 0;
  #if 0
  /*
   I2C1 master  write  data to I2C2 slaver.
  */
  //IIC_CtrlBlk_TypeDef* IICCtrl1 = &IIC2_CtrlBlk;
  printf("\r\n--------IIC_WriteArray starting--------\r\n");
  IIC_WriteArray(I2C1, 0x70, 0xaa, arry, 7);
  printf("\r\n--------IIC_WriteArray  ending--------\r\n");
  //delay_us(100);
	printf("\r\n-------The I2C2 Recive Data Start Printing------\r\n");
  if(I2C2Ctrl.WrIndex != 0)
	{  for( ; i<8; i++)
		{
			printf("The I2C2 Recive No.%d data is:%x\r\n", i, I2C2Ctrl.IICMasterBuffer[i]);
		}
  }
	printf("\r\n-------The I2C2 Recive Data Print ending--------\r\n");
	//IIC_WriteArray(I2C2, 0x70, 0xaa, arry, 7);
  #endif
	//delay_us(100);
	delay(2000000);
	
	#if 1
  /*
   I2C1 master  read data from I2C2 slaver.
  */
//	printf("\r\n--------IIC_ReadArray  starting--------\r\n");
	IIC_ReadArray(I2C1, 0x70, 0xaa, 8, ReadArry);
//	printf("--------IIC_ReadArray  ending--------\r\n");
 	printf("\r\n-------The I2C1 Recive Data Print ending--------\r\n");
	i = 0;
	for( ; i<8; i++)
	{
		printf("The I2C1 Recive No.%d data is:%x\r\n", i, ReadArry[i]);
	}
  printf("\r\n-------The I2C1 Recive Data Print ending--------\r\n");
	#endif

   
//	IIC_WriteByte(I2C1,0x70,0x80,0x55);
//	temp = IIC_ReadByte(I2C2,0x70,0x80);
//	//printf("Temp = %x\r\n", temp);
	//IIC_WriteByte(I2C2,0x70,0x80,3);
	
	#endif /*end of I2C_TEST*/
	return;
}
/**----------------------------------------------------------------------------
** @Function:		   I2C_Configuration
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
void I2C_Configuration(void)
{
	/*UART1 Configuration*/
  UART1_IOCFG();
  UART_Open(UART1,115200,UART_NO_PARITY,UART_RX_HALF_FULL);
  printf("\r\n----------------I2C Test---------------\r\n");
  /* --------- Config I2C1,I2C2 AFIO assignment -------------*/
	IIC_IOCONFIG();
	/* --------- IIC initiallization ---------------------*/
	/*
	1-MASTER;50-50KHz Speed; 0x00 - Slave address in slave mode;
	*/
	IIC_Init(I2C1,1,1,0x70);
	IIC_Init(I2C2,0,1,0x70);
	//IIC_SlaveGetData(I2C2,0,1);
}

/**----------------------------------------------------------------------------
** @Function:		   IIC_IOCONFIG
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
static void IIC_IOCONFIG(void)
{
	#if 1			//IIC1, SCL-> PB6, SDA-> PB7
	IIC1_SCL_PB6;
	IIC1_SDA_PB7;	
	#endif

	#if 0			//IIC1, SCL-> PB8, SDA-> PB8
	IIC1_SCL_PB8;
	IIC1_SDA_PB9;	
	#endif

	#if 1			//IIC2, SCL-> PB10, SDA-> PB11
	IIC2_SCL_PB10;
	IIC2_SDA_PB11;	
	#endif

}	

/**----------------------------------------------------------------------------
** @Function:		   I2C1_IRQHandler
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
void I2C1_IRQHandler(void)
{
	//printf("\r\nI2C1 Interrupt\r\n");
	IIC_IRQHandler(I2C1);
	// IIC1_IRQHandler(I2C1);
}

/**----------------------------------------------------------------------------
** @Function:		   I2C2_IRQHandler
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
void I2C2_IRQHandler(void)
{
	//printf("\r\nI2C2 Interrupt\r\n");
	IIC_IRQHandler(I2C2);
	//IIC2_IRQHandler(I2C2);
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

