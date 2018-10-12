/**
* Copyright(C) 2018, 
* ALL rights reserved.
*
* @file    flash.h
* @author   MCU Application Team
* @version V0.1   MDK version:4.70.0.0
* @date    10-October-2018
* @brief   This file use for the hard abstract layer.
*/

#ifndef __FLASH_H__
#define __FLASH_H__

#ifdef __cplusplus
	extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "hhd32f1xx.h"

#define FLASH_BASE_ADDR        0X00000000		
#define FLASH_MAX_ADDR         (128*1024)	 //128KB
#define FLASH_SIZE             128 //128KB
#define FLASH_SECTOR_SIZE            0X200       //512B
		
		
extern void FlashTest(void);
extern void HHD_FLASH_Read(u32 ReadAddr,u32 *pBuffer,u16 NumToRead);		
extern void HHD_FLASH_Write(u32 WriteAddr,u32 *pBuffer,u32 NumToWrite);			
		
#ifdef __cplusplus
	}
#endif /*__cplusplus*/


#endif /*__FLASH_H__*/



/******************* (C) COPYRIGHT 2018  *****END OF FILE****/