/**
* Copyright(C) 2015, 
* ALL rights reserved.
*
* @file    TIMER_user.h
* @author   MCU Application Team
* @version V0.1
* @date    1-August-2015
* @brief   Timer initialize setting
*          
*/

#ifndef __TIMER_USER_H__
#define __TIMER_USER_H__

#ifdef __cpulsplus
	extern "C"¡¡£û
#endif
	
	
#include "hhd32f1xx.h"

extern void Timer_Configuration(void);
// extern void TIM3_PWM_Init_user(u16 arr, u16 psc);
extern void Delay_10us(uint32_t i);
	
#ifdef __cplusplus
}
#endif


#endif /*end of __TIMER_USER_H__*/

/******************* (C) COPYRIGHT 2015  *****END OF FILE****/

