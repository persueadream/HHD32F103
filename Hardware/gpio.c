/**
* Copyright(C) 2015, 
* ALL rights reserved.
*
* @file    GPIO_user.c
* @author   MCU Application Team
* @version V0.1
* @date    9-June-2015
* @brief   This file use for the I2C initial configure.
*
*/

/* Includes ------------------------------------------------------------------*/
#include "gpio.h"
#include <stdio.h>
#include "system.h"
#include "delay.h"
#include "timer.h"
#include <string.h>
//#define GPIO_OUT_TEST
//#define GPIO_IN_TEST
#define ALL_PIN  0x0000FFFF

uint16_t Value_GPIOA, Value_GPIOB, Value_GPIOC, Value_GPIOD; 
uint8_t  PreValue;

/*手摇脉冲发生器*/
#define S_IDLE        0
#define S_A_NO1       1
#define S_B_NO2       2
#define S_B_NO1       3
#define S_A_NO2       4
#define S_RIGHT       9
#define S_OK          10
#define FORWARD       11   
#define REVERSE       12  

typedef struct Frame_Info_sm
{
  unsigned char stat;
  unsigned int  idx;
	unsigned char dirction;
	unsigned char aVal;
	unsigned char bVal;
//  unsigned char buf[MAX_BUF_LEN_R];
} PulseFrameInfo_Typedef;
PulseFrameInfo_Typedef PulseFrameInfo = {S_IDLE, 0, 0, 0, 0};

unsigned int pluseTimerCnt = 0;
unsigned char pluseTimerCntFlag = 0;

void GPIO_Test(void);
void IO_EXTI_Test(void);
void GetExtiPin(unsigned int extistate);
void GPIO_Configuration(void);
void GetPusleFrameInfo(void);

/**----------------------------------------------------------------------------
** @Function:		   GPIO_Configuration
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
void GPIO_Configuration(void)
{
			/* --------- GPIOA Periph clock enable --------------*/
		ENABLEGPIOACLK;
		ENABLEGPIOBCLK;
		ENABLEGPIOCCLK;
	  //ENABLEGPIODCLK;
		GPIO_ConfigPinsAsOutput(GPIOB, PIN8|PIN9);
	  GPIO_SetPin(GPIOB, PIN8|PIN9);
	#ifdef GPIO_OUT_TEST
	  /*
	   SST_HOLDN: PA8
		 MCU_IRQO:  PA10 
	   PROG_B:    PA11
	  */
		GPIO_ConfigPinsAsOutput(GPIOA, PIN8|PIN10|PIN11);
//	  IOCON->PA8.bit.FUNC  = 0x05;
////	(*SYSCON).CLKOUTUEN.bit.ENA = 0;
////	  (*SYSCON).CLKOUTCLKSEL.all = 0x01;
////	  (*SYSCON).CLKOUTUEN.bit.ENA = 1;
////	  (*SYSCON).CLKOUTDIV.all = 0x01;
//	  SYS_SelectClkOutSrc(MAIN_CLK);
//		/* ------- Set clock out divider ---------------- */
//	 SYS_SetClkOutDivider(1);
//	 SYS_EnableClkOut();
	 //while(1);
	  /*
	    控制二极管的状态指示灯: PC4:
	    POWER_ON:  PC12  
	   */
		GPIO_ConfigPinsAsOutput(GPIOC,PIN4|PIN12);
// 	  IOCON->PC12.bit.PUE = 0;
// 	  IOCON->PC12.bit.OD = 1;
    GPIO_SetPin(GPIOC,PIN12); //默认开启电源
	
	  /*LED*/
		GPIO_ConfigPinsAsOutput(GPIOB,PIN9);
	
	#endif
	
	#ifdef GPIO_IN_TEST
	  /*
	  MCU_IRQI:  PA9
		PG_MGTAUX: PA12
	  */
		GPIO_ConfigPinsAsInput(GPIOA, PIN9|PIN12);
	
		
	  /*GA0~GA4,GAP :PC5~PC10
	    MASKALBE_RESET: PC13, BUSSEDIO: PC14 openvpx标准信号，暂不处理。
			SYS_CON_N:   PC11
	   */
		GPIO_ConfigPinsAsInput(GPIOC,PIN5|PIN6|PIN7|PIN8|PIN9|PIN10|PIN11|PIN13|PIN14);
		
		
		 /*EXIT_IO configuration*/
		 GPIO_EnableInt(GPIOA, PIN9, RISE_EDGE); //配置MCU_IRQI管脚为上升沿中断
		 NVIC_EnableIRQ(EXTI9_5_IRQn); //开启中断
	#endif

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
void GPIO_Test(void)
{
	  Value_GPIOA = 0;
	  Value_GPIOB = 0;
	  Value_GPIOC = 0;
	  Value_GPIOD = 0;


#ifdef GPIO_OUT_TEST

	
	  Value_GPIOA = GPIO_ReadPort(GPIOA);
		GPIO_ResetPin(GPIOA, PIN8|PIN10|PIN11);
		Value_GPIOA = GPIO_ReadPort(GPIOA);
	  if((Value_GPIOA & 0x0D00) == 0x0000)
		{
			DEBUG("The GPIOA Pin Reset Success. \r\n");
		}
		else
		{
			DEBUG("The GPIOA Pin Reset fail. \r\n");
		}
		delay_us(2000000);
		GPIO_SetPin(GPIOA,PIN8|PIN10|PIN11);	
		Value_GPIOA = GPIO_ReadPort(GPIOA);
	  if((Value_GPIOA & 0x0D00) == 0x0D00)
		{
			DEBUG("The GPIOA Pin Set Success. \r\n");
		}
		else
		{
			DEBUG("The GPIOA Pin Set fail. \r\n");
		}
		delay_us(2000000);	
	
//		/*GPIOB*/
//		Value_GPIOB = GPIO_ReadPort(GPIOB);
//		GPIO_ResetPin(GPIOB,ALL_PIN);
//		Value_GPIOB = GPIO_ReadPort(GPIOB);
//		delay_us(2000000);
//		GPIO_SetPin(GPIOB,ALL_PIN);	
//		Value_GPIOB = GPIO_ReadPort(GPIOB);
//		delay_us(2000000);
		/*GPIOC*/
		Value_GPIOC = GPIO_ReadPort(GPIOC);
		GPIO_ResetPin(GPIOC, PIN4|PIN12);
		//GPIO_ResetPin(GPIOC, PIN12);
		Value_GPIOC = GPIO_ReadPort(GPIOC);
		if((Value_GPIOC & 0x1010) == 0x0000)
		{
			DEBUG("The GPIOC Pin Reset Success. \r\n");
		}
		else
		{                          
			DEBUG("The GPIOC Pin Reset fail. \r\n");
		}
		delay_us(2000000);
		//	GPIO_SetPin(GPIOC, 0XFFFF);	
		GPIO_SetPin(GPIOC, PIN4|PIN12);	
		Value_GPIOC = GPIO_ReadPort(GPIOC);
		if((Value_GPIOC & 0x1010) == 0x1010)
		{
			DEBUG("The GPIOC Pin Set Success. \r\n");
		}
		else
		{                          
			DEBUG("The GPIOC Pin Set fail. \r\n");
		}
		delay_us(2000000);
//		delay_us(2000000);
		
//		/*GPIOD*/
//		Value_GPIOD = GPIO_GetPortState(GPIOD);
//		GPIO_ResetPin(GPIOD,ALL_PIN);
//		Value_GPIOD = GPIO_GetPortState(GPIOD);
//		delay_us(2000000);
//		GPIO_SetPin(GPIOD,ALL_PIN);	
//		Value_GPIOD = GPIO_GetPortState(GPIOD);
//		delay_us(2000000);
#endif

#ifdef GPIO_IN_TEST

	  /*Read GPIOA port state */
	  Value_GPIOA = GPIO_ReadPort(GPIOA);
		delay_us(2000000);

		/*GPIOB*/
	//	Value_GPIOB = GPIO_ReadPort(GPIOB);
	//  delay_us(2000000);
		/*GPIOC*/
		Value_GPIOC = GPIO_ReadPort(GPIOC);
    delay_us(2000000);
		
		/*GPIOD*/
		//Value_GPIOD = GPIO_GetPortState(GPIOD);
		//delay_us(2000000);

#endif

	
	
}

/**----------------------------------------------------------------------------
** @Function:		   IO_EXTI_Configuration
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
void IO_EXTI_Configuration(void)
{
			/* --------- GPIOA Periph clock enable --------------*/
		ENABLEGPIOACLK;
		ENABLEGPIOBCLK;
		ENABLEGPIOCCLK;
	  ENABLEGPIODCLK;

	   DEBUG("\r\n----------------IO_EXTI Test---------------\r\n");
// 	  /*GPIOA外部中断配置*/
	  /*PA15,PA14,PA13,PA12,PA9有特殊功能*/
	//  GPIO_ConfigPinsAsInput(GPIOA, 0x1DFF);     //配置PA8为中断输入
	//  GPIO_EnableInt(GPIOA, 0x1DFF, FALL_EDGE); //上升沿中断
	   
// 	  /*GPIOB外部中断配置 whout PB3,PB4   */
// 	  GPIO_ConfigPinsAsInput(GPIOB, 0xFFE7);     //配置PA8为中断输入
// 	  GPIO_EnableInt(GPIOB, 0xFFE7, RISE_EDGE); //上升沿中断
	
// 		  /*GPIOC外部中断配置 */
// 	  GPIO_ConfigPinsAsInput(GPIOC, 0xFFFF);     //配置PA8为中断输入
// 	  GPIO_EnableInt(GPIOC, 0xFFFF, FALL_EDGE); //上升沿中断
	  
		  /*GPIOC外部中断配置 */
// 	  GPIO_ConfigPinsAsInput(GPIOD, PIN2);     //配置PA8为中断输入
// 	  GPIO_EnableInt(GPIOD, PIN2, FALL_EDGE); //上升沿中断
	
	
	  GPIO_ConfigPinsAsInput(GPIOB, PIN3|PIN4);     //配置PA8为中断输入
	  GPIO_EnableInt(GPIOB, PIN3|PIN4,RISE_EDGE); //上升沿中断
		
//	  NVIC_EnableIRQ(EXTI0_IRQn);
//	  NVIC_EnableIRQ(EXTI1_IRQn);
//			NVIC_EnableIRQ(EXTI2_IRQn);
			NVIC_EnableIRQ(EXTI3_IRQn);
	    NVIC_EnableIRQ(EXTI4_IRQn);
//	  NVIC_EnableIRQ(EXTI9_5_IRQn);
//	  NVIC_EnableIRQ(EXTI15_10_IRQn);
	
	
	
// 	  GPIO_ConfigPinsAsInput(GPIOA,PIN5|PIN6|PIN7|PIN8);     //配置PA8为中断输入
// 	  GPIO_EnableInt(GPIOA, PIN5|PIN6|PIN7|PIN8, FALL_EDGE); //上升沿中断
// 	  NVIC_EnableIRQ(EXTI9_5_IRQn);
	
	
	  
}







/**----------------------------------------------------------------------------
** @Function:		   IO_ExtTest
**
** @Descriptions:	 IO exti test,将PB9产生的高低电平作为被测IO口的激励信号。
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
void IO_ExtTest(void)
{
	  uint8_t temp = 0 ;
		Delay_10us(100000); //1s
		GPIO_InvertOutPin(GPIOB, PIN9);	//LED
		temp = GPIO_GetPinState(GPIOB, PIN9);
	  if(temp != 0)
		{
			DEBUG("PB9 is change from 0 to 1.\r\n\r\n");
		}
		else
		{
			DEBUG("PB9 is change from 1 to 0.\r\n\r\n");
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
	GPIO_ClrIntflag(GPIOA,PIN0);
	//GPIO_ClrIntflag(GPIOB,PIN0);
	//GPIO_ClrIntflag(GPIOC,PIN0);
	DEBUG("\tEXTI0 Interrupt product!\n");
	GetExtiPin(state);
}	

//---- GPIOx_PIN1 ----------------------
void EXTI1_IRQHandler ()
{ 
// 	NVIC_DisableIRQ(EXTI1_IRQn);
// 	while(1);
	unsigned int state = SYSCON->EXTISTAT.all;//外部中断状态寄存器
	//Clear GPIO interrupt flag in flag register, updated @2016/02/16 16:11
 	GPIO_ClrIntflag(GPIOA,PIN1);
// 	GPIO_ClrIntflag(GPIOB,PIN1);
	//GPIO_ClrIntflag(GPIOC,PIN1);
	DEBUG("\tEXTI1 Interrupt product!\n");
	GetExtiPin(state);
}	

//---- GPIOx_PIN2 ----------------------
void EXTI2_IRQHandler ()
{
	//NVIC_DisableIRQ(EXTI2_IRQn);
	//while(1);
	unsigned int state = SYSCON->EXTISTAT.all;//外部中断状态寄存器
	//Clear GPIO interrupt flag in flag register, updated @2016/02/16 16:11
	GPIO_ClrIntflag(GPIOA,PIN2);
// 	GPIO_ClrIntflag(GPIOB,PIN2);
	//GPIO_ClrIntflag(GPIOC,PIN2);
	//GPIO_ClrIntflag(GPIOD,PIN2);
	DEBUG("\tEXTI2 Interrupt product!\n");
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
  GPIO_ClrIntflag(GPIOB,PIN3);
	//GPIO_ClrIntflag(GPIOC,PIN3);
	//GPIOA->IC.bit.IO3 = 1;
	
	//DEBUG("\tEXTI3 Interrupt product!\n");
	//GetExtiPin(state);
	PulseFrameInfo.aVal = 1;
  GetPusleFrameInfo();
	
}	

//---- GPIOx_PIN4 ----------------------
void EXTI4_IRQHandler ()
{
	//NVIC_DisableIRQ(EXTI4_IRQn);
	//while(1);
	unsigned int state = SYSCON->EXTISTAT.all;//外部中断状态寄存器
	//Clear GPIO interrupt flag in flag register, updated @2016/02/16 16:11
	//GPIO_ClrIntflag(GPIOA,PIN4);
	GPIO_ClrIntflag(GPIOB,PIN4);
	//GPIO_ClrIntflag(GPIOC,PIN4);
	//DEBUG("\tEXTI4 Interrupt product!\n");
	//GetExtiPin(state);
	PulseFrameInfo.bVal = 1;
	GetPusleFrameInfo();
}	

/**----------------------------------------------------------------------------
** @Function:		   GetPusleFrameInfo
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
void GetPusleFrameInfo(void)
{
		switch(PulseFrameInfo.stat)
	 {
		case S_OK:
		case S_IDLE:
		{
			if(PulseFrameInfo.aVal == 1)
			{
				PulseFrameInfo.stat = S_A_NO1;
			}
			if(PulseFrameInfo.bVal == 1)
			{
				PulseFrameInfo.stat = S_B_NO1;
			}
			PulseFrameInfo.aVal = 0;
			PulseFrameInfo.bVal = 0;
			pluseTimerCnt = 20; //开启800ms超时判断
			break;
		}
		case S_A_NO1:
		{
			//PulseFrameInfo.stat = S_B_NO2;
			if(PulseFrameInfo.aVal == 1) //连续两次接收到A脉冲
			{
				PulseFrameInfo.stat = S_IDLE;
				PulseFrameInfo.dirction = 0;
				PulseFrameInfo.idx = 0;
			}
			if(PulseFrameInfo.bVal == 1)//正确接收到B脉冲
			{
				PulseFrameInfo.stat = S_OK;
				PulseFrameInfo.dirction = FORWARD;
				PulseFrameInfo.idx++;
			}
      PulseFrameInfo.aVal = 0;
			PulseFrameInfo.bVal = 0;
			pluseTimerCnt = 20; //开启800ms超时判断。
			break;
		}
//	  case S_B_NO2:
//		{
//			PulseFrameInfo.stat = S_OK;
//			PulseFrameInfo.dirction = FORWARD;
//			PulseFrameInfo.idx++;
//			break;
//		}
		case S_B_NO1:
		{
			//PulseFrameInfo.stat = S_A_NO2;
			if(PulseFrameInfo.bVal == 1) //连续两次接收到B脉冲
			{
				PulseFrameInfo.stat = S_IDLE;
				PulseFrameInfo.dirction = 0;
				PulseFrameInfo.idx = 0;
			}
			if(PulseFrameInfo.aVal == 1)//正确接收到A脉冲
			{
				PulseFrameInfo.stat = S_OK;
				PulseFrameInfo.dirction = REVERSE;
				PulseFrameInfo.idx++;
			}
      PulseFrameInfo.bVal = 0;
			PulseFrameInfo.bVal = 0;
			pluseTimerCnt = 20; //开启800ms超时判断。
		  break;
		}
//		case S_A_NO2:
//		{
//			PulseFrameInfo.stat = S_OK;
//			PulseFrameInfo.dirction = FORWARD;
//			PulseFrameInfo.idx++;
//			break;
//		}
		default:break;
	}
}




void PusleFrameInfoProcess(void)
{
		if(pluseTimerCntFlag == 1)
		{
			pluseTimerCntFlag = 0;
			if(PulseFrameInfo.stat == S_OK)
			{
				if(PulseFrameInfo.dirction == FORWARD)
				{
					DEBUG("FORWARD: %d\r\n", PulseFrameInfo.idx);
				}
				if(PulseFrameInfo.dirction == REVERSE)
				{
					DEBUG("REVERSE: %d\r\n", PulseFrameInfo.idx);
				}
			}
			else
			{
				DEBUG("PusleFrameInfo ERROR \r\n");
			}
			PulseFrameInfo.stat = S_IDLE;
			PulseFrameInfo.aVal = 0;
			PulseFrameInfo.bVal = 0;
			PulseFrameInfo.idx = 0;
			PulseFrameInfo.dirction = 0;
     //       = {S_IDLE, 0, 0, 0, 0};
		}
}

//---- GPIOx_PIN9- GPIOx_PIN5  ----------------------
void EXTI9_5_IRQHandler ()
{
	//NVIC_DisableIRQ(EXTI9_5_IRQn);
	unsigned int state = SYSCON->EXTISTAT.all;//外部中断状态寄存器
	
	//Clear GPIO interrupt flag in flag register, updated @2016/02/16 16:11
	/*whiout PA9,PA13,PA14,PA15*/
	 GPIO_ClrIntflag(GPIOA,0xFFFF);//0xFFE7
	 GPIOA->IC.all |= 0XFFFF;
  //GPIO_ClrIntflag(GPIOB,0xFFE7);
	//GPIO_ClrIntflag(GPIOC,0xFFFF);
	DEBUG("\tEXTI9_5 Interrupt product!\n");
	GetExtiPin(state);
//	DEBUG("state:%x\r\n",state);
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
	
	
	DEBUG("\tEXTI15_10 Interrupt product!\n");
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
		    DEBUG("The EXTI Pin is: PIN%d\r\n", i);
			}
	}
}

/**----------------------------------------------------------------------------
** @Function:		   LED_Test
**
** @Descriptions:	 LED Test
**
** @parameters:			
**                  
**                  
**                  
** @Returned: none
** 
** @Author:  MCU Application Team
**
** @Date: 09-October-2018
**
-------------------------------------------------------------------------------*/
void LED_Test(void)
{
		GPIO_ResetPin(GPIOB, PIN9);
		delay_ms(100);
		delay_ms(100);
		GPIO_SetPin(GPIOB, PIN9);
	  delay_ms(100);
		delay_ms(100);
		delay_ms(100);
		delay_ms(100);

}




/******************* (C) COPYRIGHT 2015  *****END OF FILE****/

