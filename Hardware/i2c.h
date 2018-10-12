/*
* Copyright(C) 2015, 
* ALL rights reserved.
*
* @file    I2C_user.h
* @author   MCU Application Team
* @version V0.1
* @date    9-June-2015
* @brief   This file use for the I2C initial configure.
*
*/



/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __I2C_USER_H
#define __I2C_USER_H


#ifdef __cplusplus
	extern "C" {
#endif
		
/* Includes ------------------------------------------------------------------*/
#include "hhd32f1xx.h"
#include "hhd_iic.h"	
#include <stdint.h>		
/* I2C_Exported_Functions */		
extern void I2C_Configuration(void);
extern void I2C_Test(void);
		
		
#ifdef __cplusplus
}
#endif 

#endif /*__I2C_USER_H*/

/******************* (C) COPYRIGHT 2017  *****END OF FILE****/

