#ifndef __DMA_USER_H__
#define __DMA_USER_H__
#include "stm32f10x.h"
/* Private define ------------------------------------------------------------*/
#define DR_ADDRESS                  ((uint32_t)0x4001244C) //ADC1 DR寄存器基地址
/*ADC 通道总数*/
#define ADC_CHANNEL_NUM  4
/*ADC 每个通道采样次数*/
#define ADC_SAMPLE_COUNT 50


/* Private variables ---------------------------------------------------------*/
extern __IO uint16_t ADCConvertedValue;     // ADC为12位模数转换器，只有ADCConvertedValue的低12位有效
extern uint16_t After_filter[ADC_CHANNEL_NUM];
extern void DMAInit_user(void);
extern void filter(void);
extern uint16_t GetVolt(u16 advalue);

#endif


/******************* (C) COPYRIGHT 2015 CETC47 *****END OF FILE****/








