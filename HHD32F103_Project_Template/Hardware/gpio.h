/*
* Copyright(C) 2015, 
* ALL rights reserved.
*
* @file    GPIO_user.h
* @author   MCU Application Team
* @version V0.1
* @date    9-June-2015
* @brief   This file use for the I2C initial configure.
*
*/



/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __GPIO_USER_H
#define __GPIO_USER_H


#ifdef __cplusplus
	extern "C" {
#endif
		
/* Includes ------------------------------------------------------------------*/
#include "hhd32f1xx.h"
#include "hhd_gpio.h"	
#include "hhd_sys.h"
#include <stdint.h>		
/* GPIO_Exported_Functions */		

extern void GPIO_Test(void);
extern void IO_EXTI_Configuration(void);
extern void GPIO_Configuration(void);
extern void IO_ExtTest(void);		
extern void GetPusleFrameInfo(void);
extern void PusleFrameInfoProcess(void);
extern void LED_Test(void);
#ifdef __cplusplus
}
#endif 

#endif /*__GPIO_USER_H*/

/******************* (C) COPYRIGHT 2015  *****END OF FILE****/

