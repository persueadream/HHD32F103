#ifndef __DMA_USER_H__
#define __DMA_USER_H__
#include "stm32f10x.h"
/* Private define ------------------------------------------------------------*/
#define DR_ADDRESS                  ((uint32_t)0x4001244C) //ADC1 DR�Ĵ�������ַ
/*ADC ͨ������*/
#define ADC_CHANNEL_NUM  4
/*ADC ÿ��ͨ����������*/
#define ADC_SAMPLE_COUNT 50


/* Private variables ---------------------------------------------------------*/
extern __IO uint16_t ADCConvertedValue;     // ADCΪ12λģ��ת������ֻ��ADCConvertedValue�ĵ�12λ��Ч
extern uint16_t After_filter[ADC_CHANNEL_NUM];
extern void DMAInit_user(void);
extern void filter(void);
extern uint16_t GetVolt(u16 advalue);

#endif


/******************* (C) COPYRIGHT 2015 CETC47 *****END OF FILE****/








