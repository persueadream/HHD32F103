/**
* Copyright(C) 2018, 
* ALL rights reserved.
*
* @file    hal.c
* @author   MCU Application Team
* @version V0.1   MDK version:4.70.0.0
* @date    9-June-2015
* @brief   This file use for the hard abstract layer.
*
*/
#include "hal.h"


/**----------------------------------------------------------------------------
** @Function:		   IRC_TRIM_Print
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
** @Date: 2017-07-14
**
-------------------------------------------------------------------------------*/
void IRC_TRIM_Print(void)
{
	uint32_t temp = 0;
	temp = (*SYSCON).IRCCTRL.all;
	DEBUG("The IRC TRIM is: 0X%x\r\n", temp);
}

/**----------------------------------------------------------------------------
** @Function:		   DeviceInit
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
** @Date: 2017-07-14
**
-------------------------------------------------------------------------------*/
void DeviceInit(void)
{
	/* ----------- System initialization -------------------------------------*/
	//InClockConfigration();
	ExtClockConfigration();
	SYS_SystemInitial();	
	SYS_SetAHBClkDivider(1);//36MHz
	//SysTick_Init();
	//SystemCoreClockUpdate();
	
//	GPIO_Configuration();
//	IO_EXTI_Configuration();
//	ClkOutputConfig();
	USART_Configuration();
	ADC_Configuration();
//	I2C_Configuration();
//	ADC_TempSensorConfiguration();
	//SPI_Configuration();
   //CAN_Configuration();
//	 Timer_Configuration();
//	 PWM_Configuration();
//	 delay_init();
//	 TimerCnt = TIM_5S; //启动5S定时
	 NVIC_Init();
  // NVIC_EnableIRQ(UART1_IRQn);
	#ifdef _DEBUG
		DEBUG("\r\n-------------------Debug Mode---------------\r\n");
	#else
	  printf("\r\n-------------------Relase Mode---------------\r\n");
	#endif
	
}

/**----------------------------------------------------------------------------
** @Function:		   NVIC_Init
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
** @Date: 2017-07-14
**
-------------------------------------------------------------------------------*/
void NVIC_Init(void)
{
	NVIC_SetPriority(EXTI3_IRQn, 0);
	NVIC_SetPriority(EXTI4_IRQn, 1);
	NVIC_SetPriority(UART2_IRQn, 2);
	NVIC_SetPriority(TIM2_IRQn, 3);
	
}


/**----------------------------------------------------------------------------
** @Function:		   InClockConfigration
**
** @Descriptions:	  时钟配置，采用内部晶体40MHz,输出72MHz。
**
** @parameters:			
**                  
**                  
**                  
** @Returned: none
** 
** @Author:  MCU Application Team
**
** @Date: 2017-07-14
**
-------------------------------------------------------------------------------*/
void InClockConfigration(void)
{
	uint8_t i;
	uint32_t temp = 0;
(*SYSCON).IRCCTRL.all = 0x1C;
#define CLOCK_SETUP       1
#define MAINCLK_SETUP     1
#define SYSOSC_SETUP	    1
#define CLOCK_SETUP       1                         /* Clock Setup              */
#define SYSPLL_SETUP      1
#if (MAINCLK_SETUP)                               /* System Clock Setup       */


#if (SYSOSC_SETUP)                                /* System Oscillator Setup  */
  /* bit 0 default is crystal bypass, 
  bit1 0=0~2.5Mhz crystal input, 1=2.5~16Mhz crystal input. */

  /* main system OSC run is cleared, bit 5 in PDRUNCFG register */
  HHD_SYSCON->PDRUNCFG     &= ~(1 << 8);          /* Power-up System Osc      */
  HHD_SYSCON->SYSOSCCTRL    = 0x0002;
  //HHD_SYSCON->SYSOSCCTRL    = SYSPLLCLKSEL_Val;
    /* Wait 200us for OSC to be stablized, no status indication, dummy wait. */
  for (i = 0; i < 200; i++) __NOP();
#endif  // #if (SYSOSC_SETUP)



#if (SYSPLL_SETUP)
  HHD_SYSCON->SYSPLLCLKUEN  = 0x01;               /* Update Clock Source      */
  HHD_SYSCON->SYSPLLCLKSEL  = 0x00;               /* Select PLL Input    1:extern  osc   0: inner osc  */
 //  HHD_SYSCON->SYSPLLCLKSEL  = 0x01;               /* Select PLL Input    1:extern  osc   0: inner osc  */
  HHD_SYSCON->SYSPLLCLKUEN  = 0x00;               /* Toggle Update Register   */

//  while (!(HHD_SYSCON->SYSPLLCLKUEN & 0x01));   /* Wait Until Updated       */

/* System PLL Setup         */
  HHD_SYSCON->SYSPLLCTRL    = 0x00004149;         //72MHz, Inner 40MHz OSC  M=9 N=5 D=1  Fout = Fin * M/N/D.
	//HHD_SYSCON->SYSPLLCTRL    = 0x00004146;         //72MHz, Ext 12MHz OSC  M=6 N=1 D=1  Fout = Fin * M/N/D.
	//HHD_SYSCON->SYSPLLCTRL    = 0x00004049;         //72MHz, Ext 8MHz OSC  M=6 N=1 D=1  Fout = Fin * M/N/D.
  HHD_SYSCON->PDRUNCFG     &= ~(1 << 7);          /* Power-up SYSPLL          */
	for (i = 0; i < 200; i++) __NOP();
//  while (!(HHD_SYSCON->SYSPLLSTAT & 0x01));	   /* Wait Until PLL Locked    */

#endif // #if (SYSPLL_SETUP)




  HHD_FMC->RDCYCCFG				 = 0x3;
  HHD_SYSCON->MAINCLKUEN    = 0x01;               /* Enable MCLK Source change*/
  HHD_SYSCON->MAINCLKSEL    = 0x0002;             /* Select PLL Clock Output  */
  HHD_SYSCON->MAINCLKUEN    = 0x00;               /*Disable MCLK Source change*/

  HHD_SYSCON->SYSAHBCLKDIV  = 0x0001;
  HHD_SYSCON->UARTCLKDIV    = 0x0001;
//  while (!(HHD_SYSCON->MAINCLKUEN & 0x01));     /* Wait Until Updated       */
  temp = HHD_SYSCON->SYSPLLCTRL;
  MainClock = 40000000UL * (temp & 0x03F) / ((temp >> 6) & 0x03F) ;   //(__SYS_PLLCLKIN * (SYSPLLCTRL_Val & 0x01F)/((SYSPLLCTRL_Val >> 6) & 0x03F))
	//DEBUG("The MainClock is:\d\r\n", MainClock)
#endif  // #if (MAINCLK_SETUP)

}

/**----------------------------------------------------------------------------
** @Function:		   ExtClockConfigration
**
** @Descriptions:	  时钟配置，采用外部25MHz有源时钟,输出100MHz。
**
** @parameters:			
**                  
**                  
**                  
** @Returned: none
** 
** @Author:  MCU Application Team
**
** @Date: 2017-07-14
**
-------------------------------------------------------------------------------*/
void ExtClockConfigration(void)
{
	uint8_t i;
	uint32_t temp = 0;
	(*SYSCON).IRCCTRL.all = 0x18;
#define CLOCK_SETUP       1
#define MAINCLK_SETUP     1
#define SYSOSC_SETUP	    1
#define CLOCK_SETUP       1                         /* Clock Setup              */
#define SYSPLL_SETUP      1
#if (MAINCLK_SETUP)                               /* System Clock Setup       */


#if (SYSOSC_SETUP)                                /* System Oscillator Setup  */
  /* bit 0 default is crystal bypass, 
  bit1 0=0~2.5Mhz crystal input, 1=2.5~16Mhz crystal input. */

  /* main system OSC run is cleared, bit 5 in PDRUNCFG register */
  HHD_SYSCON->PDRUNCFG     &= ~(1 << 8);          /* Power-up System Osc      */
  HHD_SYSCON->SYSOSCCTRL    = 0x0002;
  //HHD_SYSCON->SYSOSCCTRL    = SYSPLLCLKSEL_Val;
    /* Wait 200us for OSC to be stablized, no status indication, dummy wait. */
  for (i = 0; i < 200; i++) __NOP();
#endif  // #if (SYSOSC_SETUP)



#if (SYSPLL_SETUP)
  HHD_SYSCON->SYSPLLCLKUEN  = 0x01;               /* Update Clock Source      */
  //HHD_SYSCON->SYSPLLCLKSEL  = 0x00;               /* Select PLL Input    1:extern  osc   0: inner osc  */
  HHD_SYSCON->SYSPLLCLKSEL  = 0x01;               /* Select PLL Input    1:extern  osc   0: inner osc  */
  HHD_SYSCON->SYSPLLCLKUEN  = 0x00;               /* Toggle Update Register   */

//  while (!(HHD_SYSCON->SYSPLLCLKUEN & 0x01));   /* Wait Until Updated       */

/* System PLL Setup         */
 // HHD_SYSCON->SYSPLLCTRL    = 0x00004149;         //72MHz, Inner 40MHz OSC  M=9 N=5 D=1  Fout = Fin * M/N/D.
	//HHD_SYSCON->SYSPLLCTRL    = 0x00004146;         //72MHz, Ext 12MHz OSC  M=6 N=1 D=1  Fout = Fin * M/N/D.
  HHD_SYSCON->SYSPLLCTRL    = 0x00004049;         //72MHz, Ext 8MHz OSC   M=6 N=1 D=1  Fout = Fin * M/N/D.
	//HHD_SYSCON->SYSPLLCTRL    = 0x00004043;          //75MHz, Ext 25MHz OSC   M=3 N=1 D=1  Fout = Fin * M/N/D.
  HHD_SYSCON->PDRUNCFG     &= ~(1 << 7);          /* Power-up SYSPLL          */
	for (i = 0; i < 200; i++) __NOP();
//  while (!(HHD_SYSCON->SYSPLLSTAT & 0x01));	   /* Wait Until PLL Locked    */

#endif // #if (SYSPLL_SETUP)




  HHD_FMC->RDCYCCFG				 = 0x3;
  HHD_SYSCON->MAINCLKUEN    = 0x01;               /* Enable MCLK Source change*/
  HHD_SYSCON->MAINCLKSEL    = 0x0002;             /* Select PLL Clock Output  */
  HHD_SYSCON->MAINCLKUEN    = 0x00;               /*Disable MCLK Source change*/

  HHD_SYSCON->SYSAHBCLKDIV  = 0x0001;
  HHD_SYSCON->UARTCLKDIV    = 0x0001;
//  while (!(HHD_SYSCON->MAINCLKUEN & 0x01));     /* Wait Until Updated       */
  temp = HHD_SYSCON->SYSPLLCTRL;
  //MainClock = 40000000UL * (temp & 0x03F) / ((temp >> 6) & 0x03F) ;   //(__SYS_PLLCLKIN * (SYSPLLCTRL_Val & 0x01F)/((SYSPLLCTRL_Val >> 6) & 0x03F))
	//MainClock = 25000000UL * (temp & 0x03F) / ((temp >> 6) & 0x03F) ;
	MainClock = 8000000UL * (temp & 0x03F) / ((temp >> 6) & 0x03F) ;
	//DEBUG("The MainClock is:\d\r\n", MainClock)
#endif  // #if (MAINCLK_SETUP)

}

/**----------------------------------------------------------------------------
** @Function:		   ClkOutputConfig
**
** @Descriptions:	  PA8输出
**
** @parameters:			
**                  
**                  
**                  
** @Returned: none
** 
** @Author:  MCU Application Team
**
** @Date: 2017-07-14
**
-------------------------------------------------------------------------------*/
void ClkOutputConfig(void)
{
	  /* ------- Select Clock out source  ------------- */
	(*SYSCON).MAINCLKUEN.bit.ENA = 1;
	(*SYSCON).MAINCLKSEL.bit.SEL = 2;//主时钟选择：0,内部晶振;1:外部高速晶振；2：PLL输出；3：看门狗。
	(*SYSCON).MAINCLKUEN.bit.ENA = 0;
////	(*SYSCON).IRCCTRL.bit.CTRIM = 0;
////	(*SYSCON).IRCCTRL.bit.RTRIM = 0X06;
////	(*SYSCON).IRCCTRL.bit.SW = 1;
	  (*SYSCON).WDTOSCCTRL.bit.CTRIM = 3; //校准看门狗32KHz时钟输出
	  (*SYSCON).WDTOSCCTRL.bit.RTRIM = 11;  
		ENABLEGPIOACLK;
		SYS_SelectClkOutSrc(MAIN_CLK); //选择PA8输出的时钟源
		/* ------- Set clock out divider ---------------- */
		SYS_SetClkOutDivider(10); //10分频输出
	  SYS_EnableClkOut();
}

/******************* (C) COPYRIGHT 2018  *****END OF FILE****/


