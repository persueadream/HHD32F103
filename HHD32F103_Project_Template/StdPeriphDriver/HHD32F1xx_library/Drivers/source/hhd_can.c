/*****************************************************************************
 *   hhd_can.C:  Sourse file for  MCU CAN application
 *
 *   Copyright(C) 2015,  Technology
 *   All rights reserved.
 *
 *   History
 *   2015.08.14  ver 1.00
 *
******************************************************************************/
#include "hhd_can.h"
#include "hhd_sys.h"


/*****************************************************************************
Function Name	CAN_SetMode
Function Definition	void CAN_SetMode(uint32_t mod)
Function Description	Set CAN mode
Input Parameters	
Condition	#include sys.h
Function called	-

Last Change Date: 2015/12/12			
*****************************************************************************/
void CAN_SetMode(uint32_t mode)
{


	CAN->MOD.all = mode;

	return;
}

/*****************************************************************************
Function Name	CAN_GetStatus
Function Definition	int CAN_GetStatus()
Function Description	Get CAN SR status register
Input Parameters	
Condition	#include sys.h
Function called	-

Last Change Date: 2015/12/12			
*****************************************************************************/
int CAN_GetStatus(void)
{
	
	return (CAN->SR.all);
}


/*****************************************************************************
Function Name	CAN_ClearStatus
Function Definition	int CAN_ClearStatus()
Function Description	Clear CAN SR status register
Input Parameters	
Condition	#include sys.h
Function called	-

Last Change Date: 2015/12/12			
*****************************************************************************/
void CAN_ClearStatus(uint32_t clrbit)
{

	CAN->SR.all &= ~clrbit;
	return ;
}


/*****************************************************************************
Function Name	CAN_SetCMD
Function Definition	int CAN_SetCMD()
Function Description	Set CAN command register
Input Parameters	
Condition	#include sys.h
Function called	-

Last Change Date: 2015/12/12			
*****************************************************************************/
void CAN_SetCMD(uint32_t cmddata)
{
 CAN->CMR.all |= cmddata;
	return;
}

/*****************************************************************************
Function Name	CAN_ClrCMD
Function Definition	int CAN_ClrCMD()
Function Description	CAN command register
Input Parameters	
Condition	#include sys.h
Function called	-

Last Change Date: 2015/12/12			
*****************************************************************************/
void CAN_ClrCMD(uint32_t cmddata)
{
	CAN->CMR.all &= ~cmddata;
	return;
}

/*****************************************************************************
Function Name	CAN_EnableInt
Function Definition	void CAN_EnableInt(uint32_t intbit)
Function Description	Setup CAN interrupt
Input Parameters	
Condition	#include sys.h
Function called	-

Last Change Date: 2015/12/12			
*****************************************************************************/
void CAN_EnableInt(uint32_t intbit)
{

	CAN->IER.all |= intbit ; ///int enable
	NVIC_EnableIRQ(CAN_IRQn);
	return;
}

/*****************************************************************************
Function Name	CAN_DisableInt
Function Definition	void CAN_DisableInt(uint32_t intbit)
Condition	#include sys.h
Function called	-

Last Chang Date: 2015/12/12			
*****************************************************************************/
void CAN_DisableInt(uint32_t intbit)
{
	CAN->IER.all  &= ~intbit ; ///int disable
	NVIC_DisableIRQ(CAN_IRQn);
	return;
}

