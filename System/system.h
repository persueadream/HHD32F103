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
#include "Debug.h"
/* Private define ------------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/


	 
	
//#define __DEBUG

//#ifdef  __DEBUG
//#define DEBUG(format, ...) DEBUG (format, ##__VA_ARGS__)
////#define DEBUG(format,...) printf("FILE: "__FILE__", LINE: %05d: "format"\n", __LINE__, ##__VA_ARGS__)
////#define DEBUG(...)  DEBUG(__VA_ARGS__)
//#else
//#define DEBUG(format, ...)
//#endif	
	



/*--------------------------Function declare-------------------------*/
extern void RCC_Configuration(void);
//extern void GPIO_Configuration(void);
extern void NVIC_Configuration(void);
extern void sdelay_us(u32 count);
void assert_failed(uint8_t* file, uint32_t line);
#ifdef __cplusplus
}
#endif

#endif /*__SYSTEM_USER_H__*/


/******************* (C) COPYRIGHT 2015  *****END OF FILE****/





