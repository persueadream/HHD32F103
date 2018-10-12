/**
* Copyright(C) 2018, 
* ALL rights reserved.
*
* @file    hal.h
* @author   MCU Application Team
* @version V0.1   MDK version:4.70.0.0
* @date    9-June-2015
* @brief   This file use for the hard abstract layer.
*/


#ifndef __HAL_H__
#define __HAL_H__


#ifdef __cplusplus
extern "C" {
#endif

#include "system.h"
#include "delay.h"
#include "stdio.h"
#include "adc.h"
#include "gpio.h"
#include "i2c.h"
#include "spi.h"
#include "timer.h"
#include "uart.h"
#include "can.h"
#include "pwm.h"
#include "flash.h"
	
	
/*--------------------------Private define-------------------------*/

//#define GPIO_IN_TEST  0
//#define GPIO_OUT_TEST 1
//#define UART_TEST 2
//#define IO_EXTI   3 
//#define ADC_TEST  4
//#define SPI_TEST    5
//#define I2C_TEST    6
//#define ADC_TEMP    7	
//#define CAN_TEST    8
	
	

/*--------------------------Function declare-------------------------*/
void NVIC_Init(void);
void DeviceInit(void);
void InClockConfigration(void);
void ExtClockConfigration(void);
void ClkOutputConfig(void);
void IRC_TRIM_Print(void);


#ifdef __cplusplus
}
#endif




#endif /*end of __HAL_H__*/


