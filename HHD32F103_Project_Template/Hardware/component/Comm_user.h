/**
* Copyright(C) 2015, 
* ALL rights reserved.
*
* @file    Comm_user.h
* @author   MCU Application Team
* @version V0.1
* @date    1-August-2015
* @brief   comm funcation
*          
*/

#ifndef __COMM_USER_H__
#define __COMM_USER_H__

#include "stm32f10x.h"

/*数据包校验*/
extern u8 DataCheck_user(u8 *uData, u8 len);
/*获取数据校验值*/
extern u8 GetDataCheckVaule_user(u8 *uData, u8 len);
/*串口1接收数据处理*/
extern void UsartOneRecvDataProcess(void);
/*串口2接收数据处理*/
extern void UsartTwoRecvDataProcess(void);
/*变频模块下行数据处理*/
extern void DownDataProcess_FreConversion(uint8_t *pData, uint8_t len);
/*点频源模块下行数据处理*/
extern void DownDataProcess_PointFreSource(uint8_t *pData, uint8_t len);
/*宽带校正源模块下行数据处理*/
extern void DownDataProcess_BroadbandCorrectingSource(uint8_t *pData, uint8_t len);
/*频综模块下行数据处理*/
extern void DownDataProcess_FrequencySynthesizer(uint8_t *pData, uint8_t len);
/*CAN接收数据处理*/
extern void CANRecvDataProcess(void);
/*CAN通信模块选择*/
extern void CanModuleSelect(uint8_t *pData, uint8_t len);
/*同步时序开/关*/
extern void SynchroSequenceSwitch(uint8_t *pData, uint8_t len);
/*变频模块下行自检*/
extern void FreConversionCheck(void);
#endif










/******************* (C) COPYRIGHT 2015  *****END OF FILE****/




