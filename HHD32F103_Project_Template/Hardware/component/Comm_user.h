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

/*���ݰ�У��*/
extern u8 DataCheck_user(u8 *uData, u8 len);
/*��ȡ����У��ֵ*/
extern u8 GetDataCheckVaule_user(u8 *uData, u8 len);
/*����1�������ݴ���*/
extern void UsartOneRecvDataProcess(void);
/*����2�������ݴ���*/
extern void UsartTwoRecvDataProcess(void);
/*��Ƶģ���������ݴ���*/
extern void DownDataProcess_FreConversion(uint8_t *pData, uint8_t len);
/*��ƵԴģ���������ݴ���*/
extern void DownDataProcess_PointFreSource(uint8_t *pData, uint8_t len);
/*���У��Դģ���������ݴ���*/
extern void DownDataProcess_BroadbandCorrectingSource(uint8_t *pData, uint8_t len);
/*Ƶ��ģ���������ݴ���*/
extern void DownDataProcess_FrequencySynthesizer(uint8_t *pData, uint8_t len);
/*CAN�������ݴ���*/
extern void CANRecvDataProcess(void);
/*CANͨ��ģ��ѡ��*/
extern void CanModuleSelect(uint8_t *pData, uint8_t len);
/*ͬ��ʱ��/��*/
extern void SynchroSequenceSwitch(uint8_t *pData, uint8_t len);
/*��Ƶģ�������Լ�*/
extern void FreConversionCheck(void);
#endif










/******************* (C) COPYRIGHT 2015  *****END OF FILE****/




