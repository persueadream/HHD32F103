/**
* Copyright(C) 2017, 
* ALL rights reserved.
*
* @file    8255.c
* @author   MCU Application Team
* @version V0.1   MDK version:4.70.0.0
* @date    9-June-2015
* @brief   This file use for the I2C initial configure.
*
*/

/* Includes ------------------------------------------------------------------*/
#include "8255.h"
#include <stdio.h>
#include "system_user.h"
#include "hhd_gpio.h"
#include "hhd_sys.h"

/* Defines ------------------------------------------------------------------*/
//RD
#define _RD_L_8255  GPIO_ResetPin(GPIOC,PIN6)
#define _RD_H_8255  GPIO_SetPin(GPIOC,PIN6)
//WR
#define _WR_L_8255  GPIO_ResetPin(GPIOC,PIN5)
#define _WR_H_8255  GPIO_SetPin(GPIOC,PIN5)
//CS2
#define _CS2_L_8255  GPIO_ResetPin(GPIOC,PIN4)
#define _CS2_H_8255  GPIO_SetPin(GPIOC,PIN4)
//CS1
#define _CS1_L_8255  GPIO_ResetPin(GPIOC,PIN3)
#define _CS1_H_8255  GPIO_SetPin(GPIOC,PIN3)
//CS0
#define _CS0_L_8255  GPIO_ResetPin(GPIOC,PIN2)
#define _CS0_H_8255  GPIO_SetPin(GPIOC,PIN2)

#define CS1          (0x00 << 2)
#define CS2          (0x01 << 2)
#define CS3          (0x02 << 2)
#define CS4          (0X03 << 2)
#define CS5          (0x04 << 2)
#define CS6          (0x05 << 2)
#define CS7          (0x06 << 2)
#define D4_ADDR       CS1

#define D5_ADDR       CS2
#define D7_ADDR       CS3


//#define _LE_H  (_LE = 1)
//#define _WR_L  (_WR = 0)
//#define _WR_H  (_WR = 1)
//#define _RD_L  (_RD = 0)
//#define _RD_H  (_RD = 1)
//#define _CS_L  (_CS = 0)
//#define _CS_H  (_CS = 1)

/*--------------------------Function declare-------------------------*/
void WriteData8255(uint8_t addr, uint8_t dat);
uint8_t ReadData8255(uint8_t addr);




/**----------------------------------------------------------------------------
** @Function:		   Delay
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
static void Delay(uint32_t x)
{
 	uint32_t i;
	while(x--)
	{
	 	for(i=0;i<120;i++);
	}
}

/**----------------------------------------------------------------------------
** @Function:		   WriteData8255
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
void WriteData8255(uint8_t addr, uint8_t dat)
{
// 		_CS_H;
// 	  _WR_H;
// 	  _RD_H;
// 	  _LE_H;
// 	  Delay(10);
// 	  _CS_L;
// 	  P0 = addr;
// 	  Delay(10);
// 	  _LE_L;
// 	  P3 = dat;
// 	  Delay(10);
// 	  _WR_L;
// 	  Delay(10);
// 	  _WR_H;
// 	  Delay(10);
// 	  _CS = 1;
	   _RD_H_8255;
	   _WR_H_8255;
	   GPIOC->OUT.all |= addr;
	   GPIO_ConfigPinsAsOutput(GPIOA, 0x00ff); //PA0~PA7
	   GPIOA->OUT.all |= dat; //写入数据
	   Delay(10);
	   _WR_L_8255;
		 Delay(10);
		 _WR_H_8255;
	   
	   
}

/**----------------------------------------------------------------------------
** @Function:		   ReadData8255
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
uint8_t ReadData8255(uint8_t addr)
{
	  uint8_t rval = 0;
//	  _CS_H;
//		_WR_H;
//		_RD_H;
//	
//		_LE_H;
//		Delay(10);
//		_CS_L;
//		P0 = addr;
//		Delay(10);
//		_LE_L;
//		_RD_L;      //启动读信号 
//		P3 = 0xff;  //在置位后才能去读
//		rval = P3;  
//		Delay(10);
//		_RD_H;
//		Delay(10);
//		_CS_H;
	  _RD_H_8255;
	  _WR_H_8255; //RD:1 WR:1 =>54LS138 G2:1 ,Y0-Y7(CS1-CS8):1
	
	  _RD_L_8255;
		Delay(10);
	  GPIOC->OUT.all |= addr;
		GPIO_ConfigPinsAsInput(GPIOA, 0x00ff); //PA0~PA7
		rval = (GPIOA->PIN.all & 0x00ff); //读取数据
		Delay(10);
		_RD_H_8255;
		
	  return rval;
}




/******************* (C) COPYRIGHT 2015  *****END OF FILE****/

