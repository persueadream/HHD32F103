/**
* Copyright(C) 2015, 
* ALL rights reserved.
*
* @file    system_user.h
* @author   MCU Application Team
* @version V0.1
* @date    1-August-2015
* @brief   Peripheral clock and IO configure
*          NVIC Configure
*/

#ifndef __SYSTEM_USER_H__
#define __SYSTEM_USER_H__

#ifdef __cplusplus
 extern "C" {
#endif 

#include"hhd32f1xx.h"
#include "stdio.h"
/* Private define ------------------------------------------------------------*/


	 



/*--------------------------Function declare-------------------------*/
extern void RCC_Configuration(void);
//extern void GPIO_Configuration(void);
extern void NVIC_Configuration(void);
extern void delay_us(u32 count);

#ifdef __cplusplus
}
#endif

#endif /*__SYSTEM_USER_H__*/


/******************* (C) COPYRIGHT 2015  *****END OF FILE****/





