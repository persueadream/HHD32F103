
#include "DMA_user.h"


/*ADC ͨ������*/
#define ADC_CHANNEL_NUM  4
/*ADC ÿ��ͨ����������*/
#define ADC_SAMPLE_COUNT 50

__IO uint16_t ADCConvertedValue;

/*���ڴ��ADת�����*/
uint16_t AD_Value[ADC_SAMPLE_COUNT][ADC_CHANNEL_NUM];
/*���������ƽ��ֵ��Ľ��*/
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
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);		 //ʹ��DMAʱ��
  
  /* DMA1 channel1 configuration ----------------------------------------------*/
  DMA_DeInit(DMA1_Channel1);		  //����DMA1�ĵ�һͨ��
  DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&ADC1->DR;		  //DMA��Ӧ���������ַ
  DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)&AD_Value;   //�ڴ�洢����ַ
  DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;	//DMA��ת��ģʽΪSRCģʽ����������Ƶ��ڴ�
  DMA_InitStructure.DMA_BufferSize = ADC_CHANNEL_NUM * ADC_SAMPLE_COUNT;		   //DMA�����С��1��
  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;	//����һ�����ݺ��豸��ַ��ֹ����
  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;	//Ŀ���ڴ��ַ����
  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;  //�����������ݿ��Ϊ16λ
  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;  //DMA�������ݳߴ磬HalfWord����Ϊ16λ
  DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;   //ת��ģʽ��ѭ������ģʽ��
  DMA_InitStructure.DMA_Priority = DMA_Priority_High;	//DMA���ȼ���
  DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;		  //M2Mģʽ���ã����ڴ浽�ڴ�Ĵ���
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
