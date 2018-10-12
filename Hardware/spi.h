/*
* Copyright(C) 2015, CETC47
* ALL rights reserved.
*
* @file    I2C_user.h
* @author  MCU Application Team
* @version V0.1
* @date    9-June-2015
* @brief   This file use for the SPI initial configure.
*
*/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __SPI_USER_H
#define __SPI_USER_H

#ifdef __cplusplus
	extern "C" {
#endif
	
/* Includes ------------------------------------------------------------------*/
#include "hhd32f1xx.h"

/*宏定义---------------------------------------------------------------------*/
/*SPI1_CS 拉低*/
#define SPI1_CS_L     	GPIO_ResetBits(GPIOA, GPIO_Pin_4); 
/*SPI1_CS 拉高*/		
#define SPI1_CS_H     	GPIO_SetBits(GPIOA, GPIO_Pin_4); 
	
/*SPI2_CS 拉低*/		
#define SPI2_CS_L     	GPIO_ResetBits(GPIOB, GPIO_Pin_12); 
/*SPI2_CS 拉高*/
#define SPI2_CS_H     	GPIO_SetBits(GPIOB, GPIO_Pin_12); 
		
/* SPI_Exported_Functions */	
		
extern void SPI_Configuration(void);
extern void SPI_Test(void);
//extern unsigned char	SPIx_ReadWriteByte(SPI_TypeDef* SPIx, unsigned char WriteData);
		
		
#ifdef __cplusplus
}
#endif 


#endif /*__SPI_USER_H*/

/******************* (C) COPYRIGHT 2017  *****END OF FILE****/

