#ifndef __ADC_H__
#define __ADC_H__

#ifdef __cplusplus
extern "C" {
#endif
	
#include "hhd32f1xx.h"
	
typedef enum
{
	MON_VCC9V = 0,
	MON_VCC6V5,
	MON_VCC12V,
	MON_VCC5V,
	MON_CURRENT,
	MON_TEMP
}	ADC_RegularNum;

#define INTER_AD_NUM	(MON_TEMP+1)

void ADC1_Init(void);
void ADC_GETVOL_POLL(void);
uint16_t Adc1_GetValue(uint8_t index);

#ifdef __cplusplus
}
#endif

#endif
