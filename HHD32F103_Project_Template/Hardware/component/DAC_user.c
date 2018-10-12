/**
* Copyright(C) 2015, 
* ALL rights reserved.
*
* @file    DAC_user.c
* @author   MCU Application Team
* @version V0.1
* @date    1-August-2015
* @brief   
*          
*/
/* Includes ------------------------------------------------------------------*/
#include "system_user.h"
#include "DAC_user.h"
/* Defines ------------------------------------------------------------------*/
float gtemp = 0;
/* Private function prototypes -----------------------------------------------*/
void DAC_Configuration(void);
void DAC_SetVoltage(uint8_t adc, uint16_t vol);
/*----------------------------------------------------------------------------
** Function name:		DAC_Configuration
**
** Descriptions:		DAC_Configuration
**
** parameters:			
**                  
**                  
**                  
** Returned value:		none
** 
** Author:  MCU Application Team
**
** Date:9-June-2015
**
-------------------------------------------------------------------------------*/
void DAC_Configuration(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	DAC_InitTypeDef  DAC_InitStructure;

	/* 使能GPIOA、DAC时钟 */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC, ENABLE);

	/* DAC的GPIO配置，模拟输入 */
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_4 | GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	/* 配置DAC 通道1、通道2 */
	DAC_InitStructure.DAC_Trigger = DAC_Trigger_None;						   //不使用触发源
	DAC_InitStructure.DAC_WaveGeneration = DAC_WaveGeneration_None;	//不使用波形发生器
	DAC_InitStructure.DAC_LFSRUnmask_TriangleAmplitude = DAC_LFSRUnmask_Bit0;
	DAC_InitStructure.DAC_OutputBuffer = DAC_OutputBuffer_Disable;	//不使用DAC输出缓冲

	DAC_Init(DAC_Channel_1, &DAC_InitStructure);
	DAC_Init(DAC_Channel_2, &DAC_InitStructure);

	/* 使能通道1 由PA4输出 使能通道2 由PA5输出 */
	DAC_Cmd(DAC_Channel_1, ENABLE);
	DAC_Cmd(DAC_Channel_2, ENABLE);

	/* 使能DAC的DMA请求 */
	//DAC_DMACmd(DAC_Channel_2, ENABLE);
	DAC_SetChannel1Data(DAC_Align_12b_R, 0); //12位右对齐，初始值为0
	DAC_SetChannel2Data(DAC_Align_12b_R, 0); //

}	

/*----------------------------------------------------------------------------
** Function name:		DAC_SetVoltage
**
** Descriptions:		DAC_SetVoltage
**
** parameters:			
**                  
**                  
**                  
** Returned value:		none
** 
** Author:  MCU Application Team
**
** Date:9-June-2015
**
-------------------------------------------------------------------------------*/
void DAC_SetVoltage(uint8_t adc, uint16_t vol)
{
  gtemp = vol;
	gtemp = gtemp / 1000;
	gtemp = gtemp * 4095 / 3.279;
	adc == DAC_1 ? DAC_SetChannel1Data(DAC_Align_12b_R, gtemp) :
								 DAC_SetChannel2Data(DAC_Align_12b_R, gtemp);
}
