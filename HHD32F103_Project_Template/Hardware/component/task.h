/*
* Copyright(C) 2017, 
* ALL rights reserved.
*
* @file    task.h
* @author   MCU Application Team
* @version V0.1
* @date    9-June-2015
* @brief   This file use for the I2C initial configure.
*
*/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __TASK_H
#define __TASK_H


#ifdef __cplusplus
	extern "C" {
#endif
		
/* Includes ------------------------------------------------------------------*/
#include "hhd32f1xx.h"
//#include "hhd_iic.h"	
#include <stdint.h>		
		
typedef struct{
	uint8_t Ih[24];
	uint8_t Uk;
	uint8_t Uf;
	uint8_t Uc;
	uint8_t Ug1;
	uint8_t Ug2;
}ADC_RESULT_TypeDef;



typedef struct{
	uint8_t StartCode[2];
  uint8_t DataLength[2];
  uint8_t SourceAddr[2];
  uint8_t DestAddr[2];
  uint8_t CmdNum[2];	
	uint8_t CmdCode[2];
	uint8_t Version[2];
	uint8_t  Property;
	uint8_t  SerialNum;
	uint8_t PackTotalNum[2];
	uint8_t PackCurrentNum[2];
	uint8_t Mask[2]; //暂定10个字节 Data[0]:MASK_L, Data[0]:MASK_H
	uint8_t CheckCode[2];
	uint8_t StopCode[2];
}ReciveFrameInfo_TypeDef;

typedef struct{
	uint8_t StartCode[2];
  uint8_t DataLength[2];
  uint8_t SourceAddr[2];
  uint8_t DestAddr[2];
  uint8_t CmdNum[2];	
	uint8_t CmdCode[2];
	uint8_t Version[2];
	uint8_t  Property;
	uint8_t  SerialNum;
	uint8_t PackTotalNum[2];
	uint8_t PackCurrentNum[2];
	//uint8_t Status; //暂定10个字节 Data[0]:MASK_L, Data[0]:MASK_H
	uint8_t HVPS_State;
	uint8_t TWT_State[4];
	uint8_t Mask_State[2];
	//uint8_t HardMask_State[2]; //新增加
	uint8_t Uf;
	uint8_t Uk;
	uint8_t Uc;
	uint8_t Ug[2];
	uint8_t Ih[24];
	uint8_t CheckCode[2];
	uint8_t StopCode[2];
}SendFrameInfo_TypeDef;

typedef struct{
	uint8_t StartCode[2];
  uint8_t DataLength[2];
  uint8_t SourceAddr[2];
  uint8_t DestAddr[2];
  uint8_t CmdNum[2];	
	uint8_t CmdCode[2];
	uint8_t Version[2];
	uint8_t  Property;
	uint8_t  SerialNum;
	uint8_t PackTotalNum[2];
	uint8_t PackCurrentNum[2];
	uint8_t IhWakeResult;
	//uint8_t Status; //暂定10个字节 Data[0]:MASK_L, Data[0]:MASK_H
//	uint8_t HVPS_State;
//	uint8_t TWT_State[4];
//	uint8_t Mask_State[2];
//	//uint8_t HardMask_State[2]; //新增加
//	uint8_t Uf;
//	uint8_t Uk;
//	uint8_t Uc;
//	uint8_t Ug[2];
//	uint8_t Ih[24];
	uint8_t CheckCode[2];
	uint8_t StopCode[2];
}WakeFrameInfo_TypeDef; //唤醒

/*命令响应帧*/
typedef struct{
	uint8_t StartCode[2];
  uint8_t DataLength[2];
  uint8_t SourceAddr[2];
  uint8_t DestAddr[2];
  uint8_t CmdNum[2];	
	uint8_t CmdCode[2];
	uint8_t Version[2];
	uint8_t  Property;
	uint8_t  SerialNum;
	uint8_t PackTotalNum[2];
	uint8_t PackCurrentNum[2];
	uint8_t WorkResult[2]; //执行情况
	//uint8_t Status; //暂定10个字节 Data[0]:MASK_L, Data[0]:MASK_H
//	uint8_t HVPS_State;
//	uint8_t TWT_State[4];
//	uint8_t Mask_State[2];
//	//uint8_t HardMask_State[2]; //新增加
//	uint8_t Uf;
//	uint8_t Uk;
//	uint8_t Uc;
//	uint8_t Ug[2];
//	uint8_t Ih[24];
	uint8_t CheckCode[2];
	uint8_t StopCode[2];
}ResponseFrameInfo_TypeDef;

/* Task_Exported_Functions */		
// extern void I2C_Configuration(void);
// extern void I2C_Test(void);
extern void UartOneReciveDataProcess(uint8_t data);
extern void TaskInit(void);
extern void TaskProcess(void);

#ifdef __cplusplus
}
#endif 

#endif /*__TASK_H*/

/******************* (C) COPYRIGHT 2017  *****END OF FILE****/
