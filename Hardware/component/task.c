/*
* Copyright(C) 2017,HiWafer
* ALL rights reserved.
*
* @file    task.c
* @author  MCU Application Team
* @version V0.1
* @date    9-June-2015
* @brief   
*
*/

/* Includes ------------------------------------------------------------------*/
#include "task.h"
#include <string.h>
#include <stdio.h>
#include "system_user.h"
#include "8255.h"
#include "hhd_uart.h"
#include "hhd_gpio.h"
#include "Timer_user.h"

/*--------------------------Private define-------------------------*/
#define ON                  0x55
#define OFF                 0x66

/*--------------------------Private variable-------------------------*/
ADC_RESULT_TypeDef ADC_Result;
SendFrameInfo_TypeDef SendFrameInfo;
WakeFrameInfo_TypeDef WakeFrameInfo;


uint8_t Frame_ReciveBuffer[26];
uint8_t Frame_ResponseBuffer[26];


ReciveFrameInfo_TypeDef *ReciveFrameInfo = (ReciveFrameInfo_TypeDef *)Frame_ReciveBuffer;
ResponseFrameInfo_TypeDef *ResponseFrameInfo = (ResponseFrameInfo_TypeDef *)Frame_ResponseBuffer;
uint8_t Frame_SendBuffer[60];
uint8_t InWake_SendBuffer[25];
uint8_t *pSend = (uint8_t *)&Frame_SendBuffer;
uint8_t *pInWakeSend = (uint8_t *)&InWake_SendBuffer;

uint8_t ReciveIndex;
uint8_t SendIndex;

uint8_t TWT1to16;
// TWT1to16.0  TWT1��TWT2�Ŀ����ź�  ��Ƭ�����TTL����Ч
// TWT1to16.1  TWT3��TWT4�Ŀ����ź�
// TWT1to16.2  TWT5��TWT6�Ŀ����ź�
// TWT1to16.3  TWT7��TWT8�Ŀ����ź�
// TWT1to16.4  TWT9��TWT10�Ŀ����ź�
// TWT1to16.5  TWT11��TWT12�Ŀ����ź�
// TWT1to16.6  TWT13��TWT14�Ŀ����ź�
// TWT1to16.7  TWT15��TWT16�Ŀ����ź�

uint8_t TWT17to24;
// TWT17to24.0  TWT17��TWT18�Ŀ����ź� 
// TWT17to24.1  TWT19��TWT20�Ŀ����ź�
// TWT17to24.2  TWT21��TWT22�Ŀ����ź�
// TWT17to24.3  TWT23��TWT24�Ŀ����ź�
uint8_t HVPS_CTRL;
// HVPS_CTRL.0   ��ѹ����  δ��
// HVPS_CTRL.1   ��ѹ���� ��Ƭ�����TTL����Ч
// HVPS_CTRL.2   դ��1����  ��Ƭ�����TTL����Ч
// HVPS_CTRL.4   ������߸�λ  ��Ƭ�����TTL����Ч

uint8_t CHOOSE1;
// CHOOSE1.0~ CHOOSE.2  FAD0~FAD2�����ߵ�������˿��դ����ģ��������8ѡ1���صĿ����ź�  
// CHOOSE1.3  EN0 (FEN) �����ߵ���ģ����������������⡢������Ϣ�ȵ�8ѡ1���ص�ʹ�ܿ����ź� 
// CHOOSE1.4~ CHOOSE.6  SAD0~SAD2�����ߵ���ģ������������������8ѡ1���صĿ����ź�
// CHOOSE1.7  EN1 ��(����EN2����֮��)���ߵ���ģ������������������8ѡ1���ص�ʹ�ܿ����ź�

uint8_t HVPS_STATE;

// HVPS_STATE��0  ��ѹָʾ  1��ʾ����0��ʾ��
// HVPS_STATE��1  ��ʱָʾ  1��ʾ����0��ʾ��
// HVPS_STATE��2  ��ѹָʾ  1��ʾ����0��ʾ��
// HVPS_STATE��3  դ��ָʾ  1��ʾ����0��ʾ��
// HVPS_STATE��4  ����ָʾ  1��ʾ����0��ʾ��
// HVPS_STATE��5  ����Ӹ�ѹָʾ  1��ʾ����Ӹ�ѹ��0��ʾӲ���Ӹ�ѹ��Ĭ��Ϊ0
// HVPS_STATE��6~HVPS_STATE��7  δ����0

uint8_t TWT1_STATE;
// TWT1_STATE��0~TWT1_STATE��5 �ֱ��ʾTWT1~TWT6����״̬��1��ʾ���ϣ�0��ʾ����
// TWT1_STATE��6~TWT1_STATE��7 δ����0
uint8_t TWT2_STATE;
//TWT2_STATE��0~TWT2_STATE��5 �ֱ��ʾTWT1~TWT6����״̬��1��ʾ���ϣ�0��ʾ����
//TWT2_STATE��6~TWT2_STATE��7 δ����0
uint8_t TWT3_STATE;
//TWT3_STATE��0~TWT3_STATE��5 �ֱ��ʾTWT1~TWT6����״̬��1��ʾ���ϣ�0��ʾ����
//TWT3_STATE��6~TWT3_STATE��7 δ����0
uint8_t TWT4_STATE;
//TWT4_STATE��0~TWT4_STATE��5 �ֱ��ʾTWT1~TWT6����״̬��1��ʾ���ϣ�0��ʾ����
//TWT4_STATE��6~TWT4_STATE��7 δ����0
uint8_t MASK1_STATE;
//MASK1_STATE.0 ��ʾ��TWT1��TWT2�����β�����1��ʾ���Σ�0��ʾδ����
//...
//MASK1_STATE.7 ��ʾ��TWT15��TWT16�����β�����1��ʾ���Σ�0��ʾδ����
uint8_t MASK2_STATE;
// MASK2_STATE.0 ��ʾ��TWT17��TWT18�����β�����1��ʾ���Σ�0��ʾδ����
// MASK2_STATE.1 ��ʾ��TWT19��TWT20�����β�����1��ʾ���Σ�0��ʾδ����
// ������δ����0

uint8_t FLAGA;
uint8_t CHOOSE2; //CHOOSE2.0  EN2
uint8_t RESULT;  //���ѽ����־λ
// RESULT.0   1~6֧�в��ܻ��������0�ɹ���1ʧ��
// RESULT.1   7~12֧�в��ܻ��������0�ɹ���1ʧ��
// RESULT.2   13~18֧�в��ܻ��������0�ɹ���1ʧ��
// RESULT.3   19~24֧�в��ܻ��������0�ɹ���1ʧ��
uint8_t D4_PB;
uint8_t STATE_FLAG; //״̬�仯��־λ��00=״̬δ�仯������״̬�仯����Ҫ�����ϱ�״̬

uint8_t Ih_WAKE; //���ѽ��00=�ɹ���01=ʧ��
uint8_t ADDATA1,ADDATA2;//��1�κ͵ڶ���AD�ɼ�����

uint8_t Ih[24], Uk, Uf, Uc, Ug[2];

uint8_t COUNTER_500MS,WRPOINT,ADDATA,COUNTER,
			  HVPS_OLD, TWT1_OLD, TWT2_OLD, TWT3_OLD, 
				TWT4_OLD, MASK1_OLD, MASK2_OLD;
// WRPOINT: ������������ָ��
uint16_t TimerCnt = 0, gTimerFlag = 0;


/*--------------------------Function declare-------------------------*/
extern void UartOneReciveDataProcess(uint8_t data);
extern void TaskInit(void);
extern void TaskProcess(void);

static void VariableInit(void);
static void D8255_Init(void);
static void DataCheck(uint8_t data);
static void TimingAcquisition(void);
static void WakeResultProcess(void);
static void StatusReporting(void);
static void WorkStateSend(void);
static uint8_t ADC_Conversion(void);
static void InWakeResult(void);
static void CommandCheck(void);
static void CommandResponse(void);
static void ResetIh(void);
static void unResetIh(void);
static void SetMask(void);
static void MaskTwtControl(uint8_t cmd);
static void HvControl(uint8_t cmd);
static void GControl(uint8_t cmd);
static void MaskTwtControl(uint8_t cmd);
static void WakeOver(void);




/**----------------------------------------------------------------------------
** @Function:		   TaskInit
**
** @Descriptions:		
**
** @parameters:			
**                  
**                  
**                  
** @Returned: none
** 
** @Author:  MCU Application Team
**
** @Date: 30-June-2017
**
-------------------------------------------------------------------------------*/
void TaskInit(void)
{
	VariableInit();
	D8255_Init();
}
/**----------------------------------------------------------------------------
** @Function:		   VariableInit
**
** @Descriptions:	   	
**
** @parameters:			
**                  
**                  
**                  
** @Returned: none
** 
** @Author:  MCU Application Team
**
** @Date: 2017-07-14
**
-------------------------------------------------------------------------------*/
static void VariableInit(void)
{
	  uint8_t i =0;
	  FLAGA = 0x80;
	  TWT1to16 = 0x00;
	  TWT17to24 = 0x00;
	  HVPS_CTRL = 0xEF;
	  HVPS_STATE = 0x00;
	  TWT1_STATE = 0x00;
	  TWT2_STATE = 0x00;
	  TWT3_STATE = 0x00;
	  TWT4_STATE = 0x00;
	  MASK1_STATE = 0x00;
	  MASK2_STATE = 0x00;
	  HVPS_OLD = 0x00;
	  TWT1_OLD = 0x00;
	  TWT2_OLD = 0x00;
	  TWT3_OLD = 0x00;
	  TWT4_OLD = 0x00;
	  MASK1_OLD = 0x00;
	  MASK2_OLD = 0x00;
	  for( ; i<24; i++)
	  {
			ADC_Result.Ih[i] = 0x00;
		}
	  ADC_Result.Uk = 0x00;
		ADC_Result.Uf = 0x00;
		ADC_Result.Uc = 0x00;
		ADC_Result.Ug1 = 0x00;
		ADC_Result.Ug2 = 0x00;
		
		STATE_FLAG = 0x00; //Ϊ0״̬û�б仯
		RESULT = 0x00;
		Ih_WAKE = 0x00;
		TimerCnt = 0;
		gTimerFlag = 0;
		delay_us(500);

}


/**----------------------------------------------------------------------------
** @Function:		   D8255_Init
**
** @Descriptions:		
**
** @parameters:			
**                  
**                  
**                  
** @Returned: none
** 
** @Author:  MCU Application Team
**
** @Date: 30-June-2017
**
-------------------------------------------------------------------------------*/
static void D8255_Init(void)
{
	WriteData8255(D4_K_ADDR, 0x90); //����D4/8255�Ŀ��ƼĴ�����ַ,���ù�����ʽΪ0��AΪ���룬B��CΪ�����
  WriteData8255(D5_K_ADDR, 0x80); //����D5/8255�Ŀ��ƼĴ�����ַ,���ù�����ʽΪ0��A��B��CΪ�����
	WriteData8255(D7_K_ADDR, 0x80); //����D7/8255�Ŀ��ƼĴ�����ַ,���ù�����ʽΪ0��A��B��CΪ�����
	/*8255����˿ڳ�ʼ��*/
	WriteData8255(D4_B_ADDR, 0x77);
	WriteData8255(D4_C_ADDR, 0x00);
	WriteData8255(D5_A_ADDR, 0xFF);
	WriteData8255(D5_B_ADDR, 0xFF);
	WriteData8255(D5_C_ADDR, 0x0F);
	WriteData8255(D7_A_ADDR, 0xFF);
	WriteData8255(D7_C_ADDR, 0x00);
	ResetIh();
	delay_us(20000);
	unResetIh(); //��ֹ����
	
}




/**----------------------------------------------------------------------------
** @Function:		   UartOneReciveDataProcess
**
** @Descriptions:	 UART1 Recive data process
**
** @parameters:			
**                  
**                  
**                  
** @Returned: none
** 
** @Author:  MCU Application Team
**
** @Date: 30-June-2017
**
-------------------------------------------------------------------------------*/
void UartOneReciveDataProcess(uint8_t data)
{
		uint8_t temp = data;
	  if((FLAGA&0x01) == 0x01) //������ͷ��1λ����֤��ȷ
		{
			if((FLAGA&0x02) == 0x02)//������ͷ��2λ����֤��ȷ
			{
				 if(temp != 0x7E) //��ʼ��������
         {
						FLAGA |= 0x10; //��λ��ͷ�Ѽ��־
					  FLAGA &= 0xf0; //��λ7E7E�Ѽ��־λ���������β����֮ǰ�ֳ�����ͷ�����´洢���
					  ReciveIndex = 2;//��֡���ȿ�ʼ�洢����
					  //CommandTailCheck(temp);
				 }
				else//�ּ�⵽��Ч����ͷ,�����ж��Ƿ���ͷ�Ѽ죬�Ѽ���ֽڵ���һ�����ݣ������ж���һ���ֽڡ�
				{
						//CommandTailCheck(temp);
				}
			}//end of FLAG.1 = 0x02
			else//start of FLAG.1 != 0x02
			{
				if(temp != 0x7E)//����������0x7e 0x7e,���ǿ�������
				{
					FLAGA  &= 0xF0; //��λ�Ѽ��־λ
					//CommandTailCheck(temp);
				}
				else //��ʾ��2λ�ѱ�У����ȷ
				{
					FLAGA = 0x02;
				  //CommandTailCheck(temp);
				}
			}//end of FLAG.1 != 0x02
		}//end of FLAG.0 = 0x01
		else//start of FLAG.0 != 0x01
		{
			if(temp != 0x7E)
			{
				//CommandTailCheck(temp);
			}
			else
			{
				FLAGA |= 0x01;
				//CommandTailCheck(temp);
			}
		}
	  DataCheck(temp);
}

/**----------------------------------------------------------------------------
** @Function:		   DataCheck
**
** @Descriptions:	 
**
** @parameters:			
**                  
**                  
**                  
** @Returned: none
** 
** @Author:  MCU Application Team
**
** @Date: 17-8-2017
**
-------------------------------------------------------------------------------*/
static void DataCheck(uint8_t data)
{
		uint8_t temp = data;
	  uint8_t val = 0;
	  if((FLAGA&0x10) == 0x10)//������ͷ�Ѽ�
		{
			if(temp != 0x0A) // ���������ݣ���ʼ�洢
			{
				Frame_ReciveBuffer[ReciveIndex++] = temp;
				if(ReciveIndex >= (26-2)) //�洢�������Χ(26���ֽ�)
				{
					ReciveIndex = 2; //����������λ
				  FLAGA = 0x00;    //������б�־λ
				}
			}
			else //��ֹ���λ temp = 0x0A����ֹ��0x0a0d����λ��ǰ��λ�ں󣬹�0x0a�����һ�������ֽڡ�
			{
				ReciveIndex--;
				val = Frame_ReciveBuffer[ReciveIndex]; 
				if(val != 0x0D)//�ж�0x0Aǰһ�ֽ��Ƿ���0x0D
				{
					ReciveIndex++; //����0x0D,��ô0x0AΪ��ͨ���ݣ��ָ�����������������
					Frame_ReciveBuffer[ReciveIndex++] = temp;
					if(ReciveIndex >= 26) //�洢�������Χ(26���ֽ�)
					{
							ReciveIndex = 2; //����������λ����ʼ����2�ֽڲ��洢
							FLAGA = 0x00;    //������б�־λ
					} 					
				}
				else //��0x0aǰһ�ֽ�Ϊ0x0D,��ʾ��������һ֡���������ݡ�
				{
					FLAGA |= 0x20; //������Ч����λ��־λFLAGA.5��������һ֡���ݡ�
				}
			}
		}

}
/**----------------------------------------------------------------------------
** @Function:		   TaskProcess
**
** @Descriptions:	 ������
**
** @parameters:			
**                  
**                  
**                  
** @Returned: none
** 
** @Author:  MCU Application Team
**
** @Date: 2017-08-15
**
-------------------------------------------------------------------------------*/
void TaskProcess(void)
{
	StatusReporting();
	TimingAcquisition();
	WakeResultProcess();
	CommandCheck();
}

/**----------------------------------------------------------------------------
** @Function:		   StatusReporting
**
** @Descriptions:	 ���״̬�Ƿ�仯���仯���ϱ���  	
**
** @parameters:			
**                  
**                  
**                  
** @Returned: none
** 
** @Author:  MCU Application Team
**
** @Date: 2017-07-14
**
-------------------------------------------------------------------------------*/
static void StatusReporting(void)
{
	uint8_t temp =0;
	//LOOP:
	temp = HVPS_STATE;
	if(HVPS_OLD == temp) //û�仯
	{
		STATE_FLAG &= ~(0x01); //STATE_FLAG.0
	}
	else
	{
		STATE_FLAG |= 0x01;
		 HVPS_OLD = HVPS_STATE;
	}
	//NEXT1:
	temp = TWT1_STATE;
	if(TWT1_OLD == temp)
	{
		STATE_FLAG &= ~(0x02);//STATE_FLAG.1
	}
	else
	{
		STATE_FLAG |= 0x02;
		TWT1_OLD = TWT1_STATE;
	}
	//NEXT2:
	temp = TWT2_STATE;
	if(TWT2_OLD == temp)
	{
		STATE_FLAG &= ~(0x04);//STATE_FLAG.2
	}
	else
	{
		STATE_FLAG |= 0x04;
		TWT2_OLD = TWT2_STATE;
	}
	//NEXT3:
	temp = TWT3_STATE;
	if(TWT3_OLD == temp)
	{
		STATE_FLAG &= ~(0x08);//STATE_FLAG.3
	}
	else
	{
		STATE_FLAG |= 0x08;
		TWT3_OLD = TWT3_STATE;
	}
	//NEXT4:
	temp = TWT4_STATE;
	if(TWT4_OLD == temp)
	{
		STATE_FLAG &= ~(0x10);//STATE_FLAG.4
	}
	else
	{
		STATE_FLAG |= 0x10;
		TWT4_OLD = TWT4_STATE;
	}
	//NEXT5:
	temp = MASK1_STATE;
	if(MASK1_OLD == temp)
	{
		STATE_FLAG &= ~(0x20); //STATE_FLAG.5
	}
	else
	{
		STATE_FLAG |= 0x20;
		MASK1_OLD = MASK1_STATE;
	}
	//NEXT6:
	temp = MASK2_STATE;
	if(MASK2_OLD == temp)
	{
		STATE_FLAG &= ~(0x40); //STATE_FLAG.6
	}
	else
	{
		STATE_FLAG |= 0x40;
		MASK2_OLD = MASK2_STATE;
	}
	//NEXT7:
	temp = STATE_FLAG;
	if(temp != 0x00) //״̬�仯
	{
			WorkStateSend(); //�����ϱ�״̬
	}
	else
	{
		;
	}
	
}

/**----------------------------------------------------------------------------
** @Function:		   WorkStatusSend
**
** @Descriptions:	 ����״̬����
**
** @parameters:			
**                  
**                  
**                  
** @Returned: none
** 
** @Author:  MCU Application Team
**
** @Date: 2017-08-15
**
-------------------------------------------------------------------------------*/
static void WorkStateSend(void)
{
	int i = 0;
	SendFrameInfo.StartCode[0] = 0x7e;
	SendFrameInfo.StartCode[1] = 0x7e;
	SendFrameInfo.DataLength[0] = 0x3C;
	SendFrameInfo.DataLength[1] = 0x00;
	SendFrameInfo.SourceAddr[0] = ReciveFrameInfo->DestAddr[0]; //����֡��Ŀ�ĵ�ַ��Ϊ�˷��͵�Դ��ַ
	SendFrameInfo.SourceAddr[1] = ReciveFrameInfo->DestAddr[1];
	SendFrameInfo.DestAddr[0] = ReciveFrameInfo->SourceAddr[0];
	SendFrameInfo.DestAddr[1] = ReciveFrameInfo->SourceAddr[1];
	SendFrameInfo.CmdNum[0] = ReciveFrameInfo->CmdNum[0];
	SendFrameInfo.CmdNum[1] = ReciveFrameInfo->CmdNum[1];
	SendFrameInfo.CmdCode[0] = 0x84;
	SendFrameInfo.CmdCode[1] = 0x09;
	SendFrameInfo.Version[0] = 0x01;
	SendFrameInfo.Version[1] = 0x00;
	SendFrameInfo.Property = 0x00;
	SendFrameInfo.SerialNum = 0x00;
	SendFrameInfo.PackTotalNum[0] = 0x01;
	SendFrameInfo.PackTotalNum[1] = 0x00;
	SendFrameInfo.PackCurrentNum[0] = 0x01;
	SendFrameInfo.PackCurrentNum[0] = 0x00;
	SendFrameInfo.HVPS_State = HVPS_STATE;
	SendFrameInfo.TWT_State[0] = TWT1_STATE;
	SendFrameInfo.TWT_State[1] = TWT2_STATE;
	SendFrameInfo.TWT_State[2] = TWT3_STATE;
	SendFrameInfo.TWT_State[3] = TWT4_STATE;
	SendFrameInfo.Mask_State[0] = MASK1_STATE;
	SendFrameInfo.Mask_State[1] = MASK2_STATE;
	SendFrameInfo.Uf = ADC_Result.Uf;
	SendFrameInfo.Uk = ADC_Result.Uk;
	SendFrameInfo.Uc = ADC_Result.Uc;
	SendFrameInfo.Ug[0] = ADC_Result.Ug1;
	SendFrameInfo.Ug[1] = ADC_Result.Ug2;
	//memecpy((uint8_t *)(SendFrameInfo.Ih), (uint8_t *)(ADC_Result.Ih), 24);
	for(; i<24; i++)
  {
		SendFrameInfo.Ih[i] = ADC_Result.Ih[i];
	}
	SendFrameInfo.CheckCode[0] = 0x00;
	SendFrameInfo.CheckCode[1] = 0X00;
	SendFrameInfo.StopCode[0] = 0x0D;  //����β
	SendFrameInfo.StopCode[1] = 0x0A;
	
	UART_Send(UART1, pSend, 60); // �ϱ�����
	
	
	
}

/**----------------------------------------------------------------------------
** @Function:		   CommandCheck
**
** @Descriptions:	 ����·�ָ�ȷ���������ݡ�
**
** @parameters:			
**                  
**                  
**                  
** @Returned: none
** 
** @Author:  MCU Application Team
**
** @Date: 2017-08-15
**
-------------------------------------------------------------------------------*/
static void CommandCheck(void)
{
		uint8_t temp = 0;
	  temp = FLAGA;
	  if((temp&0x20) == 0x20) //FLAGA.5,�жϴ�����������
		{
			FLAGA &= ~0x20; //������������ݱ�־
			switch(ReciveFrameInfo->CmdCode[0])
			{
				case 0x04: //����״̬��ѯ
				{
					CommandResponse(); //������Ӧ
					WorkStateSend(); //����״̬����
					break;
				}
				case 0x07: //����ѹ
				{
					CommandResponse(); //������Ӧ
				//HVON:
					HvControl(ON);
					break;
				}
				case 0x08: //��դ��ָ��
				{
					CommandResponse(); //������Ӧ
				//GON:
					GControl(ON);
					break;
				}
				case 0x09: //��դ��ָ��
				{
					CommandResponse(); //������Ӧ
				//GOFF:
					GControl(OFF);
					break;
				}
				case 0x10: //�ظ�ѹָ��
				{
					CommandResponse(); //������Ӧ
				//HVOFF:
					HvControl(OFF);
					break;
				}
				case 0x11: //���߸�λָ��
				{
					CommandResponse(); //������Ӧ
				//RESET_Ih:
					ResetIh();
					break;
				}
				case 0x12: //�в�������ָ��
				{
					CommandResponse(); //������Ӧ
				//MASKTWT:
					MaskTwtControl(OFF); //OFF:���� ON ����
					break;
				}
				case 0x13: //���߻���ָ��
				{
					CommandResponse(); //������Ӧ
				//WAKE_TWT:
					MaskTwtControl(ON);
					//
					break;
				}
				case 0x14: //���߻��ѽ�������
				{
					CommandResponse(); //������Ӧ
					GControl(OFF);     //��դ����ѹ
					Delay_10us(5000);//50ms
					//HVOFF:
					HvControl(OFF);   // �ظ�ѹ
					HVPS_STATE &= ~0x20; //HVPS_STATE.5 //�������Ӹ�ѹ��־
					FLAGA |= 0x40; //���ѽ�����־
					WakeOver(); //���ѽ���
					
					break;
				}
				case 0x15: //��ֹ���߸�λָ��
				{
					CommandResponse(); //������Ӧ
					unResetIh(); //
					break;
				}
				default: break;
				
			}
		}
}


/*+----------------------------------------------------------------------------
                              ָ��ִ���ӳ���
+-----------------------------------------------------------------------------*/

/**----------------------------------------------------------------------------
** @Function:		   HvControl
**
** @Descriptions:	 ��ѹ����
**
** @parameters:		cmd:ON ����OFF ��
**                  
**                  
**                  
** @Returned: none
** 
** @Author:  MCU Application Team
**
** @Date: 2017-08-15
**
-------------------------------------------------------------------------------*/
static void HvControl(uint8_t cmd)
{
	uint8_t temp = 0;
	
	if(cmd == ON)//��
	{   
		  temp = HVPS_CTRL & 0xFD; //HVPS_CTRL.1 ��ѹ���ƣ��͵�ƽ��Ч
			WriteData8255(D5_C_ADDR, temp);
		  HVPS_STATE |= 0x20; //HVPS_STATE.5 ����Ӹ�ѹ��־λ
		  HVPS_CTRL = temp;
	}
	else //��
	{
		temp = HVPS_CTRL | 0x02; //HVPS_CTRL.1 ��ѹ���ƣ��͵�ƽ��Ч
		WriteData8255(D5_C_ADDR, temp);
		HVPS_STATE &= ~0x20; //HVPS_STATE.5 �������Ӹ�ѹ��־λ
		HVPS_CTRL = temp;
	}
}

/**----------------------------------------------------------------------------
** @Function:		   GControl
**
** @Descriptions:	 դ������
**
** @parameters:		cmd:ON ����OFF ��
**                  
**                  
**                  
** @Returned: none
** 
** @Author:  MCU Application Team
**
** @Date: 2017-08-15
**
-------------------------------------------------------------------------------*/
static void GControl(uint8_t cmd)
{
	uint8_t temp = 0;
	if(cmd == ON)
	{
		temp = HVPS_CTRL & 0xFB;
		WriteData8255(D5_C_ADDR, temp);
		HVPS_CTRL = temp;
	}
	else
	{
		temp = HVPS_CTRL | 0x04;
		WriteData8255(D5_C_ADDR, temp);
		HVPS_CTRL = temp;
	}
}

/**----------------------------------------------------------------------------
** @Function:		   MaskTwtControl
**
** @Descriptions:	 TWT ���ο���
**
** @parameters:		cmd: ON ���ѣ�OFF ����
**                  
**                  
**                  
** @Returned: none
** 
** @Author:  MCU Application Team
**
** @Date: 2017-08-15
**
-------------------------------------------------------------------------------*/
static void MaskTwtControl(uint8_t cmd)
{
	uint8_t temp = 0;
	SetMask(); //�ߵ�TWT����˳��
	if(cmd == OFF) //����
	{
		temp = ~TWT1to16; //1��/0��
		WriteData8255(D5_A_ADDR, temp);
		temp = ~TWT17to24;
		WriteData8255(D5_B_ADDR, temp);
		MASK1_STATE = ReciveFrameInfo->Mask[0]; //TWT����״̬
		MASK2_STATE = ReciveFrameInfo->Mask[1];
	}
	else //����
	{
		temp = TWT1to16;
		WriteData8255(D5_A_ADDR, temp);
		temp = TWT17to24;
		WriteData8255(D5_B_ADDR, temp);
		
		temp = ~(ReciveFrameInfo->Mask[0]);
		MASK1_STATE = temp;   //1���ѣ�0������
		temp = ~(ReciveFrameInfo->Mask[1]);
		MASK2_STATE = temp;
	}

}

/**----------------------------------------------------------------------------
** @Function:		   WakeOver
**
** @Descriptions:	 ���ѽ���
**
** @parameters:		
**                  
**                  
**                  
** @Returned: none
** 
** @Author:  MCU Application Team
**
** @Date: 2017-08-15
**
-------------------------------------------------------------------------------*/
static void WakeOver(void)
{
	uint8_t temp = 0xFF;  
	WriteData8255(D5_A_ADDR, temp); //1:���ѣ�0��������
	WriteData8255(D5_B_ADDR, temp);
	MASK1_STATE = 0x00; //TWT����״̬����δ����
	MASK2_STATE = 0X00;
}


/**----------------------------------------------------------------------------
** @Function:		   ResetIh
**
** @Descriptions:	  ���߸�λ 	
**
** @parameters:			
**                  
**                  
**                  
** @Returned: none
** 
** @Author:  MCU Application Team
**
** @Date: 2017-07-14
**
-------------------------------------------------------------------------------*/
static void ResetIh(void)
{
	 uint8_t temp = 0;
	 temp = HVPS_CTRL;
	 temp |= 0x10;
   WriteData8255(D5_C_ADDR, temp);	
	
}

/**----------------------------------------------------------------------------
** @Function:		   unResetIh
**
** @Descriptions:	   	��ֹ���߸�λ
**
** @parameters:			
**                  
**                  
**                  
** @Returned: none
** 
** @Author:  MCU Application Team
**
** @Date: 2017-08-15
**
-------------------------------------------------------------------------------*/
static void unResetIh(void)
{
	 uint8_t temp = 0;
	 temp = HVPS_CTRL;
	 temp &= 0xef;
   WriteData8255(D5_C_ADDR, temp);	
}
/**----------------------------------------------------------------------------
** @Function:		   SetMask
**
** @Descriptions:	 �ߵ�TWT����˳��TWT13/14~23/24˳����
**
** @parameters:		cmd:ON ����OFF ��
**                  
**                  
**                  
** @Returned: none
** 
** @Author:  MCU Application Team
**
** @Date: 2017-08-15
**
-------------------------------------------------------------------------------*/
static void SetMask(void)
{
	uint8_t temp = 0;
  TWT1to16 = ReciveFrameInfo->Mask[0]; //MASK_L
	temp = ReciveFrameInfo->Mask[1];     //MASK_H
	if((temp&0x08) == 0x08) //�ж�TWT23/24�Ƿ�Ϊ�ߣ�����λTWT13/14��Ӧ��λ
	{
		TWT1to16 |= 0x40;  //��ӦTWT14/13
	}
	else
	{
		TWT1to16 &= ~0x40; //TWT1to16.6
	}
	if((temp&0x04) == 0x04) //�ж�TWT22/21�Ƿ�Ϊ�ߣ�����λTWT16/15��Ӧ��λ
	{
		TWT1to16 |= 0x80;   //��ӦTWT16/15
	}
	else
	{
		TWT1to16 &= ~0x80;
	}
	if((temp&0x02) == 0x02)//�ж�TWT20/19�Ƿ�Ϊ�ߣ�����λTWT18/17��Ӧ��λ
	{
		TWT17to24 |= 0x01;   //��ӦTWT18/17
	}
	else
	{
		TWT17to24 &= ~0x01;
 	}
	if((temp&0x01) == 0x01)//�ж�TWT18/17�Ƿ�Ϊ�ߣ�����λTWT20/19��Ӧ��λ
	{
		TWT17to24 |= 0x02;   //��ӦTWT20/19
	}
	else
	{
		TWT17to24 &= ~0x02;
	}
	temp = ReciveFrameInfo->Mask[0]; //MASK_L
	if((temp&0x80) == 0x80 ) //�ж�TWT16/15�Ƿ�Ϊ�ߣ�����λTWT22/21��Ӧ��λ
	{
		TWT17to24 |= 0x04;   //��ӦTWT22/21
	}
	else
	{
		TWT17to24 &= ~0x04;
	}
	if((temp&0x40) == 0x40)//�ж�TWT14/13�Ƿ�Ϊ�ߣ�����λTWT24/23��Ӧ��λ
	{
		TWT17to24 |= 0x08;   //��ӦTWT24/23
	}
	else
	{
		TWT17to24 &= ~0x08;
	}
}



/**----------------------------------------------------------------------------
** @Function:		   TimingAcquisition
**
** @Descriptions:	 5s��ʱ���ݲɼ� 	
**
** @parameters:			
**                  
**                  
**                  
** @Returned: none
** 
** @Author:  MCU Application Team
**
** @Date: 2017-08-15
**
-------------------------------------------------------------------------------*/
static void TimingAcquisition(void)
{
		uint8_t temp = 0, i = 0;
	  temp = FLAGA;
    if((temp&0x80) == 0x80)//FLAGA.7 ��ʾ��ʱ5S��ʱʱ�䵽��־����ʱ�ɼ�����
    {
			//UK_JC:
		  	WriteData8255(D4_B_ADDR, 0xF5);
			  WriteData8255(D4_C_ADDR, 0x50);
			  Delay_10us(2500);//25ms
	      ADC_Result.Uk = ADC_Conversion();
			  Delay_10us(5);//50us
		  //UC_JC:
				WriteData8255(D4_B_ADDR, 0xF7);
			  WriteData8255(D4_C_ADDR, 0x50);
			  Delay_10us(2500);//25ms
	      ADC_Result.Uc = ADC_Conversion();
			  Delay_10us(5);//50us
			//UF_JC:
				WriteData8255(D4_B_ADDR, 0xF3);
			  WriteData8255(D4_C_ADDR, 0x10);
			  Delay_10us(2500);//25ms
	      ADC_Result.Uf = ADC_Conversion();
			  Delay_10us(5);//50us
			//UG1_JC:
				WriteData8255(D4_B_ADDR, 0xF1);
			  WriteData8255(D4_C_ADDR, 0x10);
			  Delay_10us(2500);//25ms
	      ADC_Result.Ug1 = ADC_Conversion();
			  Delay_10us(5);//50us
			//UG2_JC:
				WriteData8255(D4_B_ADDR, 0xF0);
			  WriteData8255(D4_C_ADDR, 0x10);
			  Delay_10us(2500);//25ms
	      ADC_Result.Ug2 = ADC_Conversion();
			  Delay_10us(5);//50us
			//In1_8JC:
			  D4_PB = 0x88;
			  for(i=0 ; i<8; i++)
				{
					Delay_10us(5);//50us
					WriteData8255(D4_B_ADDR, ~D4_PB);  //D4_PB = 0x88 ,~D4_PB = 0x77
					WriteData8255(D4_C_ADDR, 0x10);
					ADC_Result.Ih[i] = ADC_Conversion();
					D4_PB += 0x10; //����ƫ����
					
				}
			//In9_16JC:
			  D4_PB = 0x89;
			  for(i=8 ; i<16; i++)
				{
					Delay_10us(5);//50us
					WriteData8255(D4_B_ADDR, ~D4_PB);  //D4_PB = 0x89 ,~D4_PB = 0x76
					WriteData8255(D4_C_ADDR, 0x10);
					ADC_Result.Ih[i] = ADC_Conversion();
					D4_PB += 0x10; //����ƫ����
					
				}
			//In17_24JC:
			  D4_PB = 0x8A;
			  for(i=16 ; i<24; i++)
				{
					Delay_10us(5);//50us
					WriteData8255(D4_B_ADDR, ~D4_PB);  //D4_PB = 0x8A ,~D4_PB = 0x75,PB�����10001000��ӦEN1��SAD2��SAD1��SAD0��EN0��FAD2��FAD1��FAD0
					WriteData8255(D4_C_ADDR, 0x10);    //PC�������ӦEN0��FAD2��FAD1��FAD0
					ADC_Result.Ih[i] = ADC_Conversion();
					D4_PB += 0x10; //����ƫ����
				}
			//TWTFAULT:
				WriteData8255(D7_A_ADDR, 0xFF); //EN2��Ч
			  WriteData8255(D4_B_ADDR, 0x77);
			  Delay_10us(20);//200us
	      temp = ReadData8255(D4_A_ADDR); //��ȡ״̬
				if((temp&0x02) == 0x02)
				{
					TWT1_STATE |= 0x04; //TWT1_STATE.2
				}
				else
				{
					TWT1_STATE &= ~0x04;
				}
			//TWT2:
			  WriteData8255(D4_B_ADDR, 0x67);
			  Delay_10us(20);//200us
	      temp = ReadData8255(D4_A_ADDR); //��ȡ״̬
				if((temp&0x02) == 0x02)
				{
					TWT1_STATE |= 0x02; //TWT1_STATE.1
				}
				else
				{
					TWT1_STATE &= ~0x02;
				}
			//TWT3:
			  WriteData8255(D4_B_ADDR, 0x57);
			  Delay_10us(20);//200us
	      temp = ReadData8255(D4_A_ADDR); //��ȡ״̬
				if((temp&0x02) == 0x02)
				{
					TWT2_STATE |= 0x08; //TWT2_STATE.3
				}
				else
				{
					TWT2_STATE &= ~0x08;
				}
			//TWT4:
			  WriteData8255(D4_B_ADDR, 0x47);
			  Delay_10us(20);//200us
	      temp = ReadData8255(D4_A_ADDR); //��ȡ״̬
				if((temp&0x02) == 0x02)
				{
					TWT2_STATE |= 0x10; //TWT2_STATE.4
				}
				else
				{
					TWT2_STATE &= ~0x10;
				}
			//TWT5:
			  WriteData8255(D4_B_ADDR, 0x37);
			  Delay_10us(20);//200us
	      temp = ReadData8255(D4_A_ADDR); //��ȡ״̬
				if((temp&0x02) == 0x02)
				{
					TWT3_STATE |= 0x20; //TWT3_STATE.5
				}
				else
				{
					TWT3_STATE &= ~0x20;
				}
			//TWT6:
			  WriteData8255(D4_B_ADDR, 0x27);
			  Delay_10us(20);//200us
	      temp = ReadData8255(D4_A_ADDR); //��ȡ״̬
				if((temp&0x02) == 0x02)
				{
					TWT1_STATE |= 0x01; //TWT1_STATE.0
				}
				else
				{
					TWT1_STATE &= ~0x01;
				}
			//TWT7:
			  WriteData8255(D4_B_ADDR, 0x17);
			  Delay_10us(20);//200us
	      temp = ReadData8255(D4_A_ADDR); //��ȡ״̬
				if((temp&0x02) == 0x02)
				{
					TWT3_STATE |= 0x10; //TWT3_STATE.4
				}
				else
				{
					TWT3_STATE &= ~0x10;
				}
			//TWT8:
			  WriteData8255(D4_B_ADDR, 0x07);
			  Delay_10us(20);//200us
	      temp = ReadData8255(D4_A_ADDR); //��ȡ״̬
				if((temp&0x02) == 0x02)
				{
					TWT2_STATE |= 0x04; //TWT2_STATE.2
				}
				else
				{
					TWT2_STATE &= ~0x04;
				}
			//TWT9:
			  WriteData8255(D4_B_ADDR, 0x76);
			  Delay_10us(20);//200us
				WriteData8255(D7_A_ADDR, 0x01); //PA�����00000001��ӦEN2 
	      temp = ReadData8255(D4_A_ADDR); //��ȡ״̬
				if((temp&0x02) == 0x02)
				{
					TWT4_STATE |= 0x04; //TWT4_STATE.2
				}
				else
				{
					TWT4_STATE &= ~0x04;
				}
			//TWT10:
			  WriteData8255(D4_B_ADDR, 0x66);
			  Delay_10us(20);//200us
	      temp = ReadData8255(D4_A_ADDR); //��ȡ״̬
				if((temp&0x02) == 0x02)
				{
					TWT3_STATE |= 0x01; //TWT3_STATE.0
				}
				else
				{
					TWT3_STATE &= ~0x01;
				}
			//TWT11:
			  WriteData8255(D4_B_ADDR, 0x56);
			  Delay_10us(20);//200us
	      temp = ReadData8255(D4_A_ADDR); //��ȡ״̬
				if((temp&0x02) == 0x02)
				{
					TWT1_STATE |= 0x10; //TWT1_STATE.4
				}
				else
				{
					TWT1_STATE &= ~0x10;
				}
			//TWT12:
			  WriteData8255(D4_B_ADDR, 0x46);
			  Delay_10us(20);//200us
	      temp = ReadData8255(D4_A_ADDR); //��ȡ״̬
				if((temp&0x02) == 0x02)
				{
					TWT4_STATE |= 0x08; //TWT4_STATE.3
				}
				else
				{
					TWT4_STATE &= ~0x08;
				}
			//TWT13:
			  WriteData8255(D4_B_ADDR, 0x36);
			  Delay_10us(20);//200us
	      temp = ReadData8255(D4_A_ADDR); //��ȡ״̬
				if((temp&0x02) == 0x02)
				{
					TWT1_STATE |= 0x08; //TWT1_STATE.3
				}
				else
				{
					TWT1_STATE &= ~0x08;
				}
			//TWT14:
			  WriteData8255(D4_B_ADDR, 0x26);
			  Delay_10us(20);//200us
	      temp = ReadData8255(D4_A_ADDR); //��ȡ״̬
				if((temp&0x02) == 0x02)
				{
					TWT4_STATE |= 0x01; //TWT4_STATE.0
				}
				else
				{
					TWT4_STATE &= ~0x01;
				}
			//TWT15:
			  WriteData8255(D4_B_ADDR, 0x16);
			  Delay_10us(20);//200us
	      temp = ReadData8255(D4_A_ADDR); //��ȡ״̬
				if((temp&0x02) == 0x02)
				{
					TWT2_STATE |= 0x20; //TWT2_STATE.5
				}
				else
				{
					TWT2_STATE &= ~0x20;
				}
			//TWT16:
			  WriteData8255(D4_B_ADDR, 0x06);
			  Delay_10us(20);//200us
	      temp = ReadData8255(D4_A_ADDR); //��ȡ״̬
				if((temp&0x02) == 0x02)
				{
					TWT4_STATE |= 0x02; //TWT4_STATE.1
				}
				else
				{
					TWT4_STATE &= ~0x02;
				}
			//TWT17:
			  WriteData8255(D4_B_ADDR, 0x75);
			  Delay_10us(20);//200us
	      temp = ReadData8255(D4_A_ADDR); //��ȡ״̬
				if((temp&0x02) == 0x02)
				{
					TWT3_STATE |= 0x08; //TWT3_STATE.3
				}
				else
				{
					TWT3_STATE &= ~0x08;
				}
			//TWT18:
			  WriteData8255(D4_B_ADDR, 0x65);
			  Delay_10us(20);//200us
	      temp = ReadData8255(D4_A_ADDR); //��ȡ״̬
				if((temp&0x02) == 0x02)
				{
					TWT4_STATE |= 0x20; //TWT4_STATE.5
				}
				else
				{
					TWT4_STATE &= ~0x20;
				}
			//TWT19:
			  WriteData8255(D4_B_ADDR, 0x55);
			  Delay_10us(20);//200us
	      temp = ReadData8255(D4_A_ADDR); //��ȡ״̬
				if((temp&0x02) == 0x02)
				{
					TWT4_STATE |= 0x10; //TWT4_STATE.4
				}
				else
				{
					TWT4_STATE &= ~0x10;
				}
			//TWT20:
			  WriteData8255(D4_B_ADDR, 0x45);
			  Delay_10us(20);//200us
	      temp = ReadData8255(D4_A_ADDR); //��ȡ״̬
				if((temp&0x02) == 0x02)
				{
					TWT2_STATE |= 0x02; //TWT2_STATE.1
				}
				else
				{
					TWT2_STATE &= ~0x02;
				}
			//TWT21:
			  WriteData8255(D4_B_ADDR, 0x35);
			  Delay_10us(20);//200us
	      temp = ReadData8255(D4_A_ADDR); //��ȡ״̬
				if((temp&0x02) == 0x02)
				{
					TWT3_STATE |= 0x04; //TWT3_STATE.2
				}
				else
				{
					TWT3_STATE &= ~0x04;
				}
			//TWT22:
			  WriteData8255(D4_B_ADDR, 0x25);
			  Delay_10us(20);//200us
	      temp = ReadData8255(D4_A_ADDR); //��ȡ״̬
				if((temp&0x02) == 0x02)
				{
					TWT3_STATE |= 0x02; //TWT3_STATE.1
				}
				else
				{
					TWT3_STATE &= ~0x02;
				}
			//TWT23:
			  WriteData8255(D4_B_ADDR, 0x15);
			  Delay_10us(20);//200us
	      temp = ReadData8255(D4_A_ADDR); //��ȡ״̬
				if((temp&0x02) == 0x02)
				{
					TWT2_STATE |= 0x01; //TWT2_STATE.0
				}
				else
				{
					TWT2_STATE &= ~0x01;
				}
			//TWT24:
			  WriteData8255(D4_B_ADDR, 0x05);
			  Delay_10us(20);//200us
	      temp = ReadData8255(D4_A_ADDR); //��ȡ״̬
				if((temp&0x02) == 0x02)
				{
					TWT1_STATE |= 0x20; //TWT1_STATE.5
				}
				else
				{
					TWT1_STATE &= ~0x20;
				}
				/*��ѹ��Դ����״̬���*/
			//DY://��ѹָʾ
				WriteData8255(D4_B_ADDR, 0xF7);
				Delay_10us(5);//50us
				temp = ReadData8255(D4_A_ADDR); //��ȡ״̬
				if((temp&0x08) != 0x08) //ACC.3
				{
						HVPS_STATE |= 0x01; 
				}
				else
				{
						HVPS_STATE &= ~0x01; 
				}
			//GY://��ѹָʾ
				WriteData8255(D4_B_ADDR, 0xF6);
				Delay_10us(5);//50us
				temp = ReadData8255(D4_A_ADDR); //��ȡ״̬
				if((temp&0x08) != 0x08) //ACC.3
				{
						HVPS_STATE |= 0x04; 
				}
				else
				{
						HVPS_STATE &= ~0x04; 
				}
			//FS://����ָʾ
				WriteData8255(D4_B_ADDR, 0xF5);
				Delay_10us(5);//50us
				temp = ReadData8255(D4_A_ADDR); //��ȡ״̬
				if((temp&0x08) != 0x08) //ACC.3
				{
						HVPS_STATE |= 0x08; 
				}
				else
				{
						HVPS_STATE &= ~0x08; 
				}
			//READY://��ʱ��
				WriteData8255(D4_B_ADDR, 0xF4);
				Delay_10us(5);//50us
				temp = ReadData8255(D4_A_ADDR); //��ȡ״̬
				if((temp&0x08) == 0x08) //ACC.3
				{
						HVPS_STATE |= 0x02; 
				}
				else
				{
						HVPS_STATE &= ~0x02; 
				}
			//PRO://����
				WriteData8255(D4_B_ADDR, 0xF3);
				Delay_10us(5);//50us
				temp = ReadData8255(D4_A_ADDR); //��ȡ״̬
				if((temp&0x08) == 0x08) //ACC.3
				{
						HVPS_STATE |= 0x10; //HVPS_STATE.4
					  //GOFF//��դ����ѹ
					 //�ظ�ѹ����������Ʊ�־λ
					temp = HVPS_CTRL | 0x02;
					WriteData8255(D5_C_ADDR, temp);
					HVPS_STATE &= ~0x20; //�������Ӹ�ѹ��־λHVPS_STATE.5
				}
				else
				{
						HVPS_STATE &= ~0x10; 
				}
				Delay_10us(5000); //50ms
			
		}			
}

/**----------------------------------------------------------------------------
** @Function:		   ADC_Conversion
**
** @Descriptions:	 ADCת��
**
** @parameters:			
**                  
**                  
**                  
** @Returned: none
** 
** @Author:  MCU Application Team
**
** @Date: 2017-08-15
**
-------------------------------------------------------------------------------*/
static uint8_t ADC_Conversion(void)
{
		uint8_t rval = 0, i = 0;
	  uint32_t sum = 0;
	  for(; i<3; i++) //AD�ɼ�3��
	  {
			GPIO_ResetPin(GPIOC, PIN14); //����ADת��
			
			GPIO_ConfigPinsAsInput(GPIOC, PIN8); //����Ϊ����
			while(GPIO_GetPinState(GPIOC, PIN8)); //�ȴ�ת������״̬
			
			GPIO_SetPin(GPIOC, PIN14); //��λ��ʼ��ȡ����
			GPIOC->OUT.all |= 0x1F;   //����AD574��ַ
			GPIO_ConfigPinsAsInput(GPIOA, 0x00ff); //PA0~PA7
			rval = (uint8_t)(GPIOA->PIN.all & 0x00ff);
			sum += rval;
		}
	  rval = (uint8_t)(sum / 3);
	  
	  return rval;
	
}
/**----------------------------------------------------------------------------
** @Function:		   WakeResultProcess
**
** @Descriptions:	 ���ѽ���ж�	
**
** @parameters:			
**                  
**                  
**                  
** @Returned: none
** 
** @Author:  MCU Application Team
**
** @Date: 2017-08-15
**
-------------------------------------------------------------------------------*/
static void WakeResultProcess(void)
{
//	  uint8_t temp = 0;
//	  temp = FLAGA;
	  if((FLAGA&0x40) == 0x40) //FLAGA.6
		{
			//WAKE_RESULT:
				if(TWT1_STATE != 0X00)
				{
					RESULT |= 0x01; //RESULT.0
				}
				else
				{
					RESULT &= ~ 0x01;
				}
			//PRESULT2:
				if(TWT2_STATE != 0X00)
				{
					RESULT |= 0x02;//RESULT.1
				}
				else
				{
					RESULT &= ~0x02;
				}
			//PRESULT3:
				if(TWT3_STATE != 0x00)
				{
					RESULT |= 0x04;//RESULT.2
				}
				else
				{
					RESULT &= ~0x04;
				}
			//PRESULT4:
				if(TWT3_STATE != 0x00)
				{
					RESULT |= 0x08;//RESULT.3
				}
				else
				{
					RESULT &= ~0x08;
				}
				
			//PWAKE:
				if(RESULT != 0x00)
				{
					Ih_WAKE = 0x01; //����ʧ�ܡ�
				}
				else
				{
					Ih_WAKE = 0x00; //���ѳɹ�
					
				}
			InWakeResult(); //���߻��ѽ�������ӳ���
			FLAGA &= ~0x40;//������ѽ�����־λ���ȴ���һ�λ��ѽ���ָ��
		}
}

/**----------------------------------------------------------------------------
** @Function:		   InWakeResult
**
** @Descriptions:	 ���߻��ѽ�������ӳ���	
**
** @parameters:			
**                  
**                  
**                  
** @Returned: none
** 
** @Author:  MCU Application Team
**
** @Date: 2017-08-15
**
-------------------------------------------------------------------------------*/
static void InWakeResult(void)
{
	WakeFrameInfo.StartCode[0] = 0x7e;
	WakeFrameInfo.StartCode[1] = 0x7e;
	WakeFrameInfo.DataLength[0] = 0x19; //26���ֽ�
	WakeFrameInfo.DataLength[1] = 0x00;
	WakeFrameInfo.SourceAddr[0] = ReciveFrameInfo->DestAddr[0];
	WakeFrameInfo.SourceAddr[1] = ReciveFrameInfo->DestAddr[1];
	WakeFrameInfo.DestAddr[0] = ReciveFrameInfo->SourceAddr[0];
	WakeFrameInfo.DestAddr[1] = ReciveFrameInfo->SourceAddr[1];
	WakeFrameInfo.CmdNum[0]  = ReciveFrameInfo->CmdNum[0];
	WakeFrameInfo.CmdNum[1] = ReciveFrameInfo->CmdNum[1];
	WakeFrameInfo.CmdCode[0] = 0x88;
	WakeFrameInfo.CmdCode[1] = 0x09;
	WakeFrameInfo.Version[0] = 0x01;
	WakeFrameInfo.Version[1] = 0x00;
	WakeFrameInfo.Property = 0;
	WakeFrameInfo.SerialNum = 0x00;
	WakeFrameInfo.PackTotalNum[0] = 0x01;
	WakeFrameInfo.PackTotalNum[1] = 0x00;
	WakeFrameInfo.PackCurrentNum[0] = 0x01;
	WakeFrameInfo.PackCurrentNum[1] = 0x00;
	WakeFrameInfo.IhWakeResult = Ih_WAKE;
	WakeFrameInfo.CheckCode[0] = 0x00;
	WakeFrameInfo.CheckCode[1] = 0x00;
	WakeFrameInfo.StopCode[0] = 0x0D;
	WakeFrameInfo.StopCode[1] = 0x0A;
	UART_Send(UART1, pInWakeSend, 25); // �ϱ����ѽ��
	
}


/**----------------------------------------------------------------------------
** @Function:		   CommandResponse
**
** @Descriptions:	 ������Ӧ
**
** @parameters:			
**                  
**                  
**                  
** @Returned: none
** 
** @Author:  MCU Application Team
**
** @Date: 2017-08-15
**
-------------------------------------------------------------------------------*/
static void CommandResponse(void)
{
	ResponseFrameInfo->StartCode[0] = 0x7e;
	ResponseFrameInfo->StartCode[1] = 0x7e;
	ResponseFrameInfo->DataLength[0] = 0x1A;
	ResponseFrameInfo->DataLength[1] = 0x00;
	ResponseFrameInfo->SourceAddr[0] = ReciveFrameInfo->DestAddr[0];
  ResponseFrameInfo->SourceAddr[1] = ReciveFrameInfo->DestAddr[1];	
	ResponseFrameInfo->DestAddr[0] = ReciveFrameInfo->SourceAddr[0];
	ResponseFrameInfo->DestAddr[1] = ReciveFrameInfo->SourceAddr[1];
	ResponseFrameInfo->CmdNum[0] = ReciveFrameInfo->CmdNum[0];
	ResponseFrameInfo->CmdNum[1] = ReciveFrameInfo->CmdNum[1];
	ResponseFrameInfo->CmdCode[0] = 0x81;
	ResponseFrameInfo->CmdCode[1] = 0X09;
	ResponseFrameInfo->Version[0] = 0x01;
	ResponseFrameInfo->Version[1] = 0x00;
	ResponseFrameInfo->Property = 0x00;
	ResponseFrameInfo->SerialNum = 0x00;
	ResponseFrameInfo->PackTotalNum[0] = 0x01;
	ResponseFrameInfo->PackTotalNum[1] = 0x00;
	ResponseFrameInfo->PackCurrentNum[0] = 0x01;
	ResponseFrameInfo->PackCurrentNum[1] = 0x00;
	ResponseFrameInfo->WorkResult[0] = 0x00;
	ResponseFrameInfo->WorkResult[1] = 0x00;
	ResponseFrameInfo->CheckCode[0] = 0x00;
	ResponseFrameInfo->CheckCode[1] = 0x00;
	ResponseFrameInfo->StopCode[0] = 0x0D;
	ResponseFrameInfo->StopCode[1] = 0x0A;
	UART_Send(UART1, pInWakeSend, 26); // ������Ӧ����
	
}

/******************* (C) COPYRIGHT 2017  *****END OF FILE****/
























