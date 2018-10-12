/**
* Copyright(C) 2018, 
* ALL rights reserved.
*
* @file    pwm.h
* @author   MCU Application Team
* @version V0.1   MDK version:4.70.0.0
* @date    9-Mary-2018
* @brief   This file use for the hard abstract layer.
*/

#ifndef __PWM_H__
#define __PWM_H__

#ifdef __cplusplus
	extern "C" {
#endif
/* Includes ------------------------------------------------------------------*/
#include "hhd32f1xx.h"

		
extern void PWM_Configuration(void);
extern void PWM_Test(void);		
		
#ifdef __cplusplus
	}
#endif	






#endif /* end of __PWM_H__*/
