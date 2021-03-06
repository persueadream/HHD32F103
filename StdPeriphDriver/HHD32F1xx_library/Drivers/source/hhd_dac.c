/*****************************************************************************
 *   hhd_dac.c:  Header file for  HHD32F
 *
 *   Copyright(C) 2015,  Technology
 *   All rights reserved.
 *
 *   History
 *   2015.07.21  ver 1.01    Prelimnary version
 *
******************************************************************************/
/* Includes ------------------------------------------------------------------*/

#include "hhd32f1xx.h"
#include "hhd_sys.h"
#include "hhd_dac.h"

extern uint32_t SystemCoreClock;

/*****************************************************************************
Function Name	DAC_Init
Function Definition	void DAC_Init(uint32_t conversionrate)
Function Description	Initial DAC module
Input Parameters	Conversionrate: conversion rate, must less 1000000 (1MHz)
Return Value	No
Condition	No
Function called	-

Last Chang Date: 2015/09/12	
*****************************************************************************/
void DAC_Init(HHD32F_DAC_TypeDef *DAC, uint32_t conversionrate,uint32_t mode)
{
	uint32_t div;

	//Power up DAC
	(*SYSCON).PDRUNCFG.bit.DAC_PD = 0;
	HHD_SYSCON->PDRUNCFG &= ~(1<<4);
	
	//limit convertion rate to 1M/s
	if (conversionrate>1000000)
		conversionrate = 1000000;
	
	//caculate clk divider
	div = SystemCoreClock/conversionrate;

	//set up divider
  (*DAC).CR.bit.DIV   = div;
  (*DAC).CR.bit.DACEN = 1;

	//Set default DAC as BURST mode.
	(*DAC).CR.bit.MODE = mode;

	return;
}
/*****************************************************************************
Function Name	DAC_DeInit
Function Definition	Void DAC_DeInit(viod)
Function Description	De_Initial DAC module. Disable interrupt generated by module and stop any conversion.
Input Parameters	No
Return Value	No
Condition	No
Function called	-

Last Chang Date: 2015/09/12	
*****************************************************************************/
void DAC_DeInit(HHD32F_DAC_TypeDef *DAC)
{
	
	(*DAC).CR.all=0;
	
	//Power down DAC
	(*SYSCON).PDRUNCFG.bit.DAC_PD = 1;
	
  //DISABLEDACCLK;
	
	return;
}

/*****************************************************************************
Function Name	DAC_EnableInt
Function Definition	Void DAC_EnableInt
Function Description	Setup DAC Buffer interrupt
Input Parameters		inttype: combination of interrupt source-
										
Return Value	No
Condition	No
Function called	-

Last Chang Date: 2015/09/12	
*****************************************************************************/
void DAC_EnableInt(HHD32F_DAC_TypeDef *DAC)
{
	(*DAC).CR.bit.INTEN =  1;
	return;
}
/*****************************************************************************
Function Name	DAC_SendData
Function Definition	uint32_t DAC_SendData(uint16_t dr)
Function Description	Send data 
Input Parameters	dr: 
Condition	No
Function called	-

Last Chang Date: 2015/09/12	
*****************************************************************************/
void DAC_SendData(HHD32F_DAC_TypeDef *DAC,uint16_t dr)
{
		(*DAC).BUF.all=dr;
}

/*****************************************************************************
Function Name	DAC_SendData
Function Definition	uint32_t DAC_SendData(uint16_t dr)
Function Description	Send data 
Input Parameters	dr: 
Condition	No
Function called	-

Last Chang Date: 2015/09/12	
*****************************************************************************/
uint32_t Get_DACBufferState(HHD32F_DAC_TypeDef *DAC)
{
	uint32_t state;
	state = (*DAC).CR.bit.BUFSTAT;
	return state;
}


/******************************************************************************
**                            End Of File
******************************************************************************/
