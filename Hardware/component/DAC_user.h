/**
* Copyright(C) 2015, 
* ALL rights reserved.
*
* @file    DAC_user.h
* @author   MCU Application Team
* @version V0.1
* @date    1-August-2015
* @brief   
*          
*/

#ifndef __DAC_USER_H__
#define __DAC_USER_H__

#ifdef __cplusplus
 extern "C" {
#endif 

#include "stm32f10x.h"
#include "stdio.h"
	 
/* Private define ------------------------------------------------------------*/
#define DAC_1        1
#define DAC_2        2



/*--------------------------Function declare-------------------------*/
extern void DAC_Configuration(void);
extern void DAC_SetVoltage(uint8_t adc, uint16_t vol);	 
#ifdef __cplusplus
}
#endif

#endif /*__U_CHANNEL_H__*/


/******************* (C) COPYRIGHT 2015  *****END OF FILE****/





