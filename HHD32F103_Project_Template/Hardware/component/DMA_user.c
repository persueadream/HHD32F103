
#include "DMA_user.h"


/*ADC 通道总数*/
#define ADC_CHANNEL_NUM  4
/*ADC 每个通道采样次数*/
#define ADC_SAMPLE_COUNT 50

__IO uint16_t ADCConvertedValue;

/*用于存放AD转换结果*/
uint16_t AD_Value[ADC_SAMPLE_COUNT][ADC_CHANNEL_NUM];
/*用来存放求平均值后的结果*/
uint16_t After_filter[ADC_CHANNEL_NUM];

/*----------------------------------------------------------------------------
** Function name:		DMAInit_user
**
** Descriptions:		DMA Configer Initial
**
** parameters:			
**                  
**                  
**                  
** Returned value:		none
** 
** Author: CETC47 MCU Application Team
**
** Date:9-June-2015
**
-------------------------------------------------------------------------------*/
void DMAInit_user(void)
{
	DMA_InitTypeDef DMA_InitStructure;
	
	  /* Enable DMA1 clock */
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);		 //使能DMA时钟
  
  /* DMA1 channel1 configuration ----------------------------------------------*/
  DMA_DeInit(DMA1_Channel1);		  //开启DMA1的第一通道
  DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&ADC1->DR;		  //DMA对应的外设基地址
  DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)&AD_Value;   //内存存储基地址
  DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;	//DMA的转换模式为SRC模式，由外设搬移到内存
  DMA_InitStructure.DMA_BufferSize = ADC_CHANNEL_NUM * ADC_SAMPLE_COUNT;		   //DMA缓存大小，1个
  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;	//接收一次数据后，设备地址禁止后移
  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;	//目标内存地址后移
  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;  //定义外设数据宽度为16位
  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;  //DMA搬移数据尺寸，HalfWord就是为16位
  DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;   //转换模式，循环缓存模式。
  DMA_InitStructure.DMA_Priority = DMA_Priority_High;	//DMA优先级高
  DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;		  //M2M模式禁用，非内存到内存的传输
  DMA_Init(DMA1_Channel1, &DMA_InitStructure); 
	
  /* Enable DMA1 channel1 */
  DMA_Cmd(DMA1_Channel1, ENABLE);
	
}

/*----------------------------------------------------------------------------
** Function name:		filter
**
** Descriptions:		ADC data average
**
** parameters:			
**                  
**                  
**                  
** Returned value:		none
** 
** Author: CETC47 MCU Application Team
**
** Date:9-June-2015
**
-------------------------------------------------------------------------------*/
void filter(void)
{
	int sum = 0, i = 0;
	uint8_t count;
	for(i=0; i<ADC_CHANNEL_NUM; i++)
	{
		for(count=0; count<ADC_SAMPLE_COUNT; count++)
		{
			sum += AD_Value[count][i];
		}
		After_filter[i] = sum / ADC_SAMPLE_COUNT;
		sum = 0;
	}
}

/*----------------------------------------------------------------------------
** Function name:		filter
**
** Descriptions:		ADC data average
**
** parameters:			
**                  
**                  
**                  
** Returned value:		none
** 
** Author: CETC47 MCU Application Team
**
** Date:9-June-2015
**
-------------------------------------------------------------------------------*/
uint16_t GetVolt(u16 advalue)
{
	return(u16)(advalue * 3279 / 4096);
}
