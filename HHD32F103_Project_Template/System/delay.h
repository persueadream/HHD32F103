#ifndef __DELAY_H
#define __DELAY_H 			   
#include "hhd32f1xx.h"  

void delay_init(void);
void delay_ms(__IO uint32_t nTime);
void delay_us(__IO uint32_t nus);
void SysTick_Init(void);
#endif





























