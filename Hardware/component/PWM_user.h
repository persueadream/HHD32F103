#ifndef __PWM_USER_H__
#define __PWM_USER_H__
#include"stm32f10x.h"

extern void TIM3_PWM_Init_user(u16 arr, u16 psc);
extern void TIM1_PWM_Init_user(void);
extern void TIM8_PWM_Init_user(void);
extern void Set_PWM_Frequecny_Period_user(TIM_TypeDef* TIMx,
          	uint32_t Frequency, uint16_t CompareNo, uint16_t DutyCycle);
#endif

