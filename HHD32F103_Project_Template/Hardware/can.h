/**
* Copyright(C) 2018, 
* ALL rights reserved.
*
* @file    can.h
* @author   MCU Application Team
* @version V0.1   MDK version:4.70.0.0
* @date    9-Mary-2018
* @brief   This file use for the hard abstract layer.
*/

#ifndef __CAN_H__
#define __CAN_H__

#ifdef __cplusplus
extern "C" {
#endif
/* Includes ------------------------------------------------------------------*/
#include "hhd32f1xx.h"


	
extern void CAN_Configuration(void);		
extern void CAN_ReciveTest(void);
extern void CAN_TransmitTest(void);

	
#ifdef __cplusplus
}
#endif	/**/








#endif /*__CAN_H__*/