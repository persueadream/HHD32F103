/**
* Copyright(C) 2015, 
* ALL rights reserved.
*
* @file    Comm_user.C
* @author   MCU Application Team
* @version V0.1
* @date    1-August-2015
* @brief   comm funcation
*          
*/

#include "Comm_user.h"
#include "USART_user.h"
#include "system_user.h"
#include <stdio.h>
#include <string.h>

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define YES                    0X99
#define NO                     0X00
#define BUFFER_SIZE            1500//400
#define F_DATA_LEN             13
#define BUFFERSIZE             200
#define UP_DATA_LEN            16
#define DOWN_DATA_LEN          25
#define COMMEN_DATA_LEN        7             
#define USE_CAN1               0X20
#define USE_CAN2               0X30
#define SYNCHRO_ON             0X22
#define SYNCHRO_OFF            0X33
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

//extern uint8_t g_UsartTwoReceiveData[BUFFERSIZE];
//extern uint8_t g_UsartOneReceiveData[BUFFERSIZE];
//extern CanTxMsg TxMessage;//CAN transmit message struct
//extern CanRxMsg g_SubCanRxMessage[10];
/*CAN�������ݼ�����*/
extern uint32_t g_SubCANRcvCounter;
uint8_t g_CanSelect = USE_CAN1;

/*ͬ����ʱ��100ms*/
extern uint8_t gSynTimer;

uint8_t g_id = 0;
/* Private function prototypes -----------------------------------------------*/




/* Private functions ---------------------------------------------------------*/

/*----------------------------------------------------------------------------
** Function name:		Delay_us
**
** Descriptions:	  sample delay funcation	
**
** parameters:			
**                  
**                  
**                  
** Returned value:		none
** 
** Author:  MCU Application Team
**
** Date:1-August-2015
**
-------------------------------------------------------------------------------*/
static void Delay_us(__IO uint32_t nCount)
{
  for (; nCount != 0; nCount--);
}



/*----------------------------------------------------------------------------
** Function name:		DataCheck_user
**
** Descriptions:		����У��
**
** parameters:			
**                  
**                  
**                  
** Returned value:		none
** 
** Author:  MCU Application Team
**
** Date:2015-5-2
**
-------------------------------------------------------------------------------*/
u8 DataCheck_user(u8 *uData, u8 len)
{

	u8 uCheckValue = 0;
	//printf("Length of g_UdpRecvData = %d\n", len);
	/*��ȡ����У��ֵ*/
	uCheckValue = GetDataCheckVaule_user(uData, len);
	if(uCheckValue == uData[len-1])
	{
		return 1;
	}
	else
	{
		return 0;
	}
	
}

/*----------------------------------------------------------------------------
** Function name:		GetDataCheckVaule_user
**
** Descriptions:		�������У��ֵ�������������֮��ȡ��8λ
**
** parameters:			
**                  
**                  
**                  
** Returned value:		none
** 
** Author:  MCU Application Team
**
** Date:2015-5-2
**
-------------------------------------------------------------------------------*/
u8 GetDataCheckVaule_user(u8 *uData, u8 len)
{
		u8 uCheckValue = 0;
		u32 sum = 0;
		u8 i;
	  if(len == 0)
		{
			return 0;
		}
		/*���һλ��У��ֵ�����Լ�1*/
		
		for(i = 0; i<len-1; i++)
		{
			sum += uData[i];
		}
		uCheckValue = sum & 0xff;
		
		return 	uCheckValue;	
}



/*----------------------------------------------------------------------------
** Function name:		DataSetToUpper
**
** Descriptions:		��䷢�͸���λ��������
**
** parameters:			
**                  
**                  
**                  
** Returned value:		none
** 
** Author:  MCU Application Team
**
** Date:2015-5-2
**
-------------------------------------------------------------------------------*/


u8 DataSetToUpper(u8 *uData, u8 len)
{

	return 1;
}











/*----------------------------------------------------------------------------
** Function name:		UsartTwoRecvDataProcess
**
** Descriptions:		����2�������ݴ���
**
** parameters:			
**                  
**                  
**                  
** Returned value:		none
** 
** Author:  MCU Application Team
**
** Date:2015-5-2
**
-------------------------------------------------------------------------------*/

void UsartTwoRecvDataProcess(void)
{
	#if 0
	uint8_t len = g_UsartTwoReceiveData[2];
	uint8_t temp[DOWN_DATA_LEN];
	memset(temp, 0, len);
	memcpy(temp, g_UsartTwoReceiveData, len);
	memset(g_UsartTwoReceiveData, 0, 50);
	if(1 == DataCheck_user(temp, len))/*У���Ƿ�ɹ�*/
	{
		/*��������*/
		if(temp[1] == 0xbb)
		{
			switch(temp[0])
			{
				/*��Ƶ����ģ��*/
				case 0xff:
				{
					//DownDataProcess_FreConversion(temp, len);
					break;
				}
				/*��ƵԴģ��*/
				case 0xee:
				{
				//	DownDataProcess_PointFreSource(temp, len);
					break;
				}
				/*���У��Դģ��*/
				case 0xdd:
				{
					//DownDataProcess_BroadbandCorrectingSource(temp, len);
					break;
				}
				/*Ƶ��ģ��*/
				case 0xcc:
				{
					//DownDataProcess_FrequencySynthesizer(temp, len);
					break;
				}
				default: break;
			}
		}
		/*ͨ������*/
		if(temp[0] == 0xa1)
		{
			switch(temp[1])
			{
				/*CANѡ��*/
				case 0xb1:
				{
					//CanModuleSelect(temp, len);
					break;
				}
				/*ͬ��ʱ�򿪹�*/
				case 0xb2:
				{
					//SynchroSequenceSwitch(temp, len);
					break;
				}
				default:break;
			}
		}
	}
	#endif
}

/*----------------------------------------------------------------------------
** Function name:		UsartOneRecvDataProcess
**
** Descriptions:		����1�������ݴ���
**
** parameters:			
**                  
**                  
**                  
** Returned value:		none
** 
** Author:  MCU Application Team
**
** Date:2015-5-2
**
-------------------------------------------------------------------------------*/
void UsartOneRecvDataProcess(void)
{
	#if 0
	uint8_t len = g_UsartOneReceiveData[2];
	uint8_t temp[DOWN_DATA_LEN];
	memset(temp, 0, len);
	memcpy(temp, g_UsartOneReceiveData, len);
	memset(g_UsartOneReceiveData, 0, 200);
	if(1 == DataCheck_user(temp, len))/*У���Ƿ�ɹ�*/
	{
		/*��������*/
		if(temp[1] == 0xaa)
		{
			switch(temp[0])
			{
				/*��Ƶ����ģ��*/
				case 0xff:
				{
					//DownDataProcess_FreConversion(temp, len);
					break;
				}
				/*��ƵԴģ��*/
				case 0xee:
				{
				//	DownDataProcess_PointFreSource(temp, len);
					break;
				}
				/*���У��Դģ��*/
				case 0xdd:
				{
					//DownDataProcess_BroadbandCorrectingSource(temp, len);
					break;
				}
				/*Ƶ��ģ��*/
				case 0xcc:
				{
					//DownDataProcess_FrequencySynthesizer(temp, len);
					break;
				}
				default: break;
			}
		}
		/*ͨ������*/
		if(temp[0] == 0xa1)
		{
			switch(temp[1])
			{
				/*CANѡ��*/
				case 0xb1:
				{
					//CanModuleSelect(temp, len);
					break;
				}
				/*ͬ��ʱ�򿪹�*/
				case 0xb2:
				{
					//SynchroSequenceSwitch(temp, len);
					break;
				}
				default:break;
			}
		}
	}
	#endif
}









/******************* (C) COPYRIGHT 2015  *****END OF FILE****/

