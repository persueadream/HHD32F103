/*
* Copyright(C) 2015, 
* ALL rights reserved.
*
* @file    8255.h
* @author   MCU Application Team
* @version V0.1
* @date    9-June-2015
* @brief   This file use for the 8255 configuration.
*
*/



/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __8255_H
#define __8255_H


#ifdef __cplusplus
	extern "C" {
#endif
		
/* Includes ------------------------------------------------------------------*/
#include "hhd32f1xx.h"
#include "hhd_iic.h"	
#include <stdint.h>		
/* Defines ------------------------------------------------------------------*/		
#define ADDR_CMD              0x03
#define ADDR_A_PORT           0x00
#define ADDR_B_PORT           0x01
#define ADDR_C_PORT           0x02

#define C_PORT_LOW_IN_CMD     (0x01<<0)
#define C_PORT_LOW_OUT_CMD    (~(0x01<<0))
#define B_PORT_IN_CMD         (0x01<<1)
#define B_PORT_OUT_CMD        (~(0x01<<1))
#define C_PORT_UP_IN_CMD      (0x01<<3)
#define C_PORT_UP_OUT_CMD     (~(0x01<<3))
#define A_PORT_IN_CMD         (0x01<<4)
#define A_PORT_OUT_CMD        (~(0x01<<4))

#define D4_A_ADDR             0x00
#define D4_B_ADDR             0x01
#define D4_C_ADDR             0x02
#define D4_K_ADDR             0x03
#define D5_A_ADDR             0x04
#define D5_B_ADDR             0x05
#define D5_C_ADDR             0x06
#define D5_K_ADDR             0x07
#define D7_A_ADDR             0x0C //Ó¦¸ÃÎª0x08
#define D7_B_ADDR             0x0D
#define D7_C_ADDR             0x0E
#define D7_K_ADDR             0x0F

/* 8255_Exported_Functions */		
extern void WriteData8255(uint8_t addr, uint8_t dat);
extern uint8_t ReadData8255(uint8_t addr);

		
		
#ifdef __cplusplus
}
#endif 

#endif /*__8255_H*/

/******************* (C) COPYRIGHT 2015  *****END OF FILE****/

