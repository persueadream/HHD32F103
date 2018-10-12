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
// TWT1to16.0  TWT1、TWT2的控制信号  单片机输出TTL低有效
// TWT1to16.1  TWT3、TWT4的控制信号
// TWT1to16.2  TWT5、TWT6的控制信号
// TWT1to16.3  TWT7、TWT8的控制信号
// TWT1to16.4  TWT9、TWT10的控制信号
// TWT1to16.5  TWT11、TWT12的控制信号
// TWT1to16.6  TWT13、TWT14的控制信号
// TWT1to16.7  TWT15、TWT16的控制信号

uint8_t TWT17to24;
// TWT17to24.0  TWT17、TWT18的控制信号 
// TWT17to24.1  TWT19、TWT20的控制信号
// TWT17to24.2  TWT21、TWT22的控制信号
// TWT17to24.3  TWT23、TWT24的控制信号
uint8_t HVPS_CTRL;
// HVPS_CTRL.0   低压控制  未用
// HVPS_CTRL.1   高压控制 单片机输出TTL低有效
// HVPS_CTRL.2   栅极1控制  单片机输出TTL低有效
// HVPS_CTRL.4   软件螺线复位  单片机输出TTL低有效

uint8_t CHOOSE1;
// CHOOSE1.0~ CHOOSE.2  FAD0~FAD2对螺线电流、灯丝、栅极等模拟量检测的8选1开关的控制信号  
// CHOOSE1.3  EN0 (FEN) 对螺线电流模拟量和螺流保护检测、故障信息等的8选1开关的使能控制信号 
// CHOOSE1.4~ CHOOSE.6  SAD0~SAD2对螺线电流模拟量和螺流保护检测的8选1开关的控制信号
// CHOOSE1.7  EN1 对(除了EN2控制之外)螺线电流模拟量和螺流保护检测的8选1开关的使能控制信号

uint8_t HVPS_STATE;

// HVPS_STATE。0  低压指示  1表示亮，0表示灭
// HVPS_STATE。1  延时指示  1表示亮，0表示灭
// HVPS_STATE。2  高压指示  1表示亮，0表示灭
// HVPS_STATE。3  栅极指示  1表示亮，0表示灭
// HVPS_STATE。4  故障指示  1表示亮，0表示灭
// HVPS_STATE。5  软件加高压指示  1表示软件加高压，0表示硬件加高压，默认为0
// HVPS_STATE。6~HVPS_STATE。7  未用置0

uint8_t TWT1_STATE;
// TWT1_STATE。0~TWT1_STATE。5 分别表示TWT1~TWT6工作状态，1表示故障，0表示正常
// TWT1_STATE。6~TWT1_STATE。7 未用置0
uint8_t TWT2_STATE;
//TWT2_STATE。0~TWT2_STATE。5 分别表示TWT1~TWT6工作状态，1表示故障，0表示正常
//TWT2_STATE。6~TWT2_STATE。7 未用置0
uint8_t TWT3_STATE;
//TWT3_STATE。0~TWT3_STATE。5 分别表示TWT1~TWT6工作状态，1表示故障，0表示正常
//TWT3_STATE。6~TWT3_STATE。7 未用置0
uint8_t TWT4_STATE;
//TWT4_STATE。0~TWT4_STATE。5 分别表示TWT1~TWT6工作状态，1表示故障，0表示正常
//TWT4_STATE。6~TWT4_STATE。7 未用置0
uint8_t MASK1_STATE;
//MASK1_STATE.0 表示对TWT1和TWT2的屏蔽操作，1表示屏蔽，0表示未屏蔽
//...
//MASK1_STATE.7 表示对TWT15和TWT16的屏蔽操作，1表示屏蔽，0表示未屏蔽
uint8_t MASK2_STATE;
// MASK2_STATE.0 表示对TWT17和TWT18的屏蔽操作，1表示屏蔽，0表示未屏蔽
// MASK2_STATE.1 表示对TWT19和TWT20的屏蔽操作，1表示屏蔽，0表示未屏蔽
// 本课题未用置0

uint8_t FLAGA;
uint8_t CHOOSE2; //CHOOSE2.0  EN2
uint8_t RESULT;  //唤醒结果标志位
// RESULT.0   1~6支行波管唤醒情况，0成功，1失败
// RESULT.1   7~12支行波管唤醒情况，0成功，1失败
// RESULT.2   13~18支行波管唤醒情况，0成功，1失败
// RESULT.3   19~24支行波管唤醒情况，0成功，1失败
uint8_t D4_PB;
uint8_t STATE_FLAG; //状态变化标志位，00=状态未变化，其他状态变化，需要主动上报状态

uint8_t Ih_WAKE; //唤醒结果00=成功，01=失败
uint8_t ADDATA1,ADDATA2;//第1次和第二次AD采集数据

uint8_t Ih[24], Uk, Uf, Uc, Ug[2];

uint8_t COUNTER_500MS,WRPOINT,ADDATA,COUNTER,
			  HVPS_OLD, TWT1_OLD, TWT2_OLD, TWT3_OLD, 
				TWT4_OLD, MASK1_OLD, MASK2_OLD;
// WRPOINT: 接收命令数据指针
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
		
		STATE_FLAG = 0x00; //为0状态没有变化
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
	WriteData8255(D4_K_ADDR, 0x90); //设置D4/8255的控制寄存器地址,设置工作方式为0，A为输入，B和C为输出。
  WriteData8255(D5_K_ADDR, 0x80); //设置D5/8255的控制寄存器地址,设置工作方式为0，A、B和C为输出。
	WriteData8255(D7_K_ADDR, 0x80); //设置D7/8255的控制寄存器地址,设置工作方式为0，A、B和C为输出。
	/*8255输出端口初始化*/
	WriteData8255(D4_B_ADDR, 0x77);
	WriteData8255(D4_C_ADDR, 0x00);
	WriteData8255(D5_A_ADDR, 0xFF);
	WriteData8255(D5_B_ADDR, 0xFF);
	WriteData8255(D5_C_ADDR, 0x0F);
	WriteData8255(D7_A_ADDR, 0xFF);
	WriteData8255(D7_C_ADDR, 0x00);
	ResetIh();
	delay_us(20000);
	unResetIh(); //禁止唤醒
	
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
	  if((FLAGA&0x01) == 0x01) //命令字头第1位被验证正确
		{
			if((FLAGA&0x02) == 0x02)//命令字头第2位被验证正确
			{
				 if(temp != 0x7E) //开始接收数据
         {
						FLAGA |= 0x10; //置位字头已检标志
					  FLAGA &= 0xf0; //复位7E7E已检标志位（如果在字尾出现之前又出现字头则重新存储命令）
					  ReciveIndex = 2;//从帧长度开始存储数据
					  //CommandTailCheck(temp);
				 }
				else//又检测到有效的字头,继续判断是否字头已检，已检该字节当着一般数据，否则判断下一个字节。
				{
						//CommandTailCheck(temp);
				}
			}//end of FLAG.1 = 0x02
			else//start of FLAG.1 != 0x02
			{
				if(temp != 0x7E)//不是连续的0x7e 0x7e,则是可用数据
				{
					FLAGA  &= 0xF0; //复位已检标志位
					//CommandTailCheck(temp);
				}
				else //表示第2位已被校验正确
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
	  if((FLAGA&0x10) == 0x10)//命令字头已检
		{
			if(temp != 0x0A) // 表明是数据，开始存储
			{
				Frame_ReciveBuffer[ReciveIndex++] = temp;
				if(ReciveIndex >= (26-2)) //存储命令超出范围(26个字节)
				{
					ReciveIndex = 2; //接收索引复位
				  FLAGA = 0x00;    //清除所有标志位
				}
			}
			else //终止码高位 temp = 0x0A。终止码0x0a0d，低位在前高位在后，故0x0a是最后一个接收字节。
			{
				ReciveIndex--;
				val = Frame_ReciveBuffer[ReciveIndex]; 
				if(val != 0x0D)//判断0x0A前一字节是否是0x0D
				{
					ReciveIndex++; //不是0x0D,那么0x0A为普通数据，恢复接收索引接收数据
					Frame_ReciveBuffer[ReciveIndex++] = temp;
					if(ReciveIndex >= 26) //存储命令超出范围(26个字节)
					{
							ReciveIndex = 2; //接收索引复位，起始代码2字节不存储
							FLAGA = 0x00;    //清除所有标志位
					} 					
				}
				else //若0x0a前一字节为0x0D,表示接收完了一帧完整的数据。
				{
					FLAGA |= 0x20; //命令有效，置位标志位FLAGA.5，接收完一帧数据。
				}
			}
		}

}
/**----------------------------------------------------------------------------
** @Function:		   TaskProcess
**
** @Descriptions:	 任务处理
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
** @Descriptions:	 检测状态是否变化，变化则上报。  	
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
	if(HVPS_OLD == temp) //没变化
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
	if(temp != 0x00) //状态变化
	{
			WorkStateSend(); //主动上报状态
	}
	else
	{
		;
	}
	
}

/**----------------------------------------------------------------------------
** @Function:		   WorkStatusSend
**
** @Descriptions:	 工作状态回送
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
	SendFrameInfo.SourceAddr[0] = ReciveFrameInfo->DestAddr[0]; //接收帧的目的地址变为了发送的源地址
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
	SendFrameInfo.StopCode[0] = 0x0D;  //报文尾
	SendFrameInfo.StopCode[1] = 0x0A;
	
	UART_Send(UART1, pSend, 60); // 上报数据
	
	
	
}

/**----------------------------------------------------------------------------
** @Function:		   CommandCheck
**
** @Descriptions:	 检查下发指令，确定控制内容。
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
	  if((temp&0x20) == 0x20) //FLAGA.5,判断串口有无数据
		{
			FLAGA &= ~0x20; //清除串口有数据标志
			switch(ReciveFrameInfo->CmdCode[0])
			{
				case 0x04: //工作状态查询
				{
					CommandResponse(); //命令响应
					WorkStateSend(); //工作状态回送
					break;
				}
				case 0x07: //开高压
				{
					CommandResponse(); //命令响应
				//HVON:
					HvControl(ON);
					break;
				}
				case 0x08: //开栅极指令
				{
					CommandResponse(); //命令响应
				//GON:
					GControl(ON);
					break;
				}
				case 0x09: //关栅极指令
				{
					CommandResponse(); //命令响应
				//GOFF:
					GControl(OFF);
					break;
				}
				case 0x10: //关高压指令
				{
					CommandResponse(); //命令响应
				//HVOFF:
					HvControl(OFF);
					break;
				}
				case 0x11: //螺线复位指令
				{
					CommandResponse(); //命令响应
				//RESET_Ih:
					ResetIh();
					break;
				}
				case 0x12: //行波管屏蔽指令
				{
					CommandResponse(); //命令响应
				//MASKTWT:
					MaskTwtControl(OFF); //OFF:屏蔽 ON 唤醒
					break;
				}
				case 0x13: //螺线唤醒指令
				{
					CommandResponse(); //命令响应
				//WAKE_TWT:
					MaskTwtControl(ON);
					//
					break;
				}
				case 0x14: //螺线唤醒结束命令
				{
					CommandResponse(); //命令响应
					GControl(OFF);     //关栅极电压
					Delay_10us(5000);//50ms
					//HVOFF:
					HvControl(OFF);   // 关高压
					HVPS_STATE &= ~0x20; //HVPS_STATE.5 //清除软件加高压标志
					FLAGA |= 0x40; //唤醒结束标志
					WakeOver(); //唤醒结束
					
					break;
				}
				case 0x15: //禁止螺线复位指令
				{
					CommandResponse(); //命令响应
					unResetIh(); //
					break;
				}
				default: break;
				
			}
		}
}


/*+----------------------------------------------------------------------------
                              指令执行子程序
+-----------------------------------------------------------------------------*/

/**----------------------------------------------------------------------------
** @Function:		   HvControl
**
** @Descriptions:	 高压控制
**
** @parameters:		cmd:ON 开，OFF 关
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
	
	if(cmd == ON)//开
	{   
		  temp = HVPS_CTRL & 0xFD; //HVPS_CTRL.1 高压控制，低电平有效
			WriteData8255(D5_C_ADDR, temp);
		  HVPS_STATE |= 0x20; //HVPS_STATE.5 软件加高压标志位
		  HVPS_CTRL = temp;
	}
	else //关
	{
		temp = HVPS_CTRL | 0x02; //HVPS_CTRL.1 高压控制，低电平有效
		WriteData8255(D5_C_ADDR, temp);
		HVPS_STATE &= ~0x20; //HVPS_STATE.5 清除软件加高压标志位
		HVPS_CTRL = temp;
	}
}

/**----------------------------------------------------------------------------
** @Function:		   GControl
**
** @Descriptions:	 栅极控制
**
** @parameters:		cmd:ON 开，OFF 关
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
** @Descriptions:	 TWT 屏蔽控制
**
** @parameters:		cmd: ON 唤醒，OFF 屏蔽
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
	SetMask(); //颠倒TWT控制顺序
	if(cmd == OFF) //屏蔽
	{
		temp = ~TWT1to16; //1关/0开
		WriteData8255(D5_A_ADDR, temp);
		temp = ~TWT17to24;
		WriteData8255(D5_B_ADDR, temp);
		MASK1_STATE = ReciveFrameInfo->Mask[0]; //TWT屏蔽状态
		MASK2_STATE = ReciveFrameInfo->Mask[1];
	}
	else //唤醒
	{
		temp = TWT1to16;
		WriteData8255(D5_A_ADDR, temp);
		temp = TWT17to24;
		WriteData8255(D5_B_ADDR, temp);
		
		temp = ~(ReciveFrameInfo->Mask[0]);
		MASK1_STATE = temp;   //1唤醒，0不唤醒
		temp = ~(ReciveFrameInfo->Mask[1]);
		MASK2_STATE = temp;
	}

}

/**----------------------------------------------------------------------------
** @Function:		   WakeOver
**
** @Descriptions:	 唤醒结束
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
	WriteData8255(D5_A_ADDR, temp); //1:唤醒，0：不唤醒
	WriteData8255(D5_B_ADDR, temp);
	MASK1_STATE = 0x00; //TWT屏蔽状态，都未屏蔽
	MASK2_STATE = 0X00;
}


/**----------------------------------------------------------------------------
** @Function:		   ResetIh
**
** @Descriptions:	  螺线复位 	
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
** @Descriptions:	   	禁止螺线复位
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
** @Descriptions:	 颠倒TWT控制顺序，TWT13/14~23/24顺序反了
**
** @parameters:		cmd:ON 开，OFF 关
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
	if((temp&0x08) == 0x08) //判断TWT23/24是否为高，并置位TWT13/14相应的位
	{
		TWT1to16 |= 0x40;  //对应TWT14/13
	}
	else
	{
		TWT1to16 &= ~0x40; //TWT1to16.6
	}
	if((temp&0x04) == 0x04) //判断TWT22/21是否为高，并置位TWT16/15相应的位
	{
		TWT1to16 |= 0x80;   //对应TWT16/15
	}
	else
	{
		TWT1to16 &= ~0x80;
	}
	if((temp&0x02) == 0x02)//判断TWT20/19是否为高，并置位TWT18/17相应的位
	{
		TWT17to24 |= 0x01;   //对应TWT18/17
	}
	else
	{
		TWT17to24 &= ~0x01;
 	}
	if((temp&0x01) == 0x01)//判断TWT18/17是否为高，并置位TWT20/19相应的位
	{
		TWT17to24 |= 0x02;   //对应TWT20/19
	}
	else
	{
		TWT17to24 &= ~0x02;
	}
	temp = ReciveFrameInfo->Mask[0]; //MASK_L
	if((temp&0x80) == 0x80 ) //判断TWT16/15是否为高，并置位TWT22/21相应的位
	{
		TWT17to24 |= 0x04;   //对应TWT22/21
	}
	else
	{
		TWT17to24 &= ~0x04;
	}
	if((temp&0x40) == 0x40)//判断TWT14/13是否为高，并置位TWT24/23相应的位
	{
		TWT17to24 |= 0x08;   //对应TWT24/23
	}
	else
	{
		TWT17to24 &= ~0x08;
	}
}



/**----------------------------------------------------------------------------
** @Function:		   TimingAcquisition
**
** @Descriptions:	 5s定时数据采集 	
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
    if((temp&0x80) == 0x80)//FLAGA.7 表示定时5S定时时间到标志，定时采集数据
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
					D4_PB += 0x10; //增加偏移量
					
				}
			//In9_16JC:
			  D4_PB = 0x89;
			  for(i=8 ; i<16; i++)
				{
					Delay_10us(5);//50us
					WriteData8255(D4_B_ADDR, ~D4_PB);  //D4_PB = 0x89 ,~D4_PB = 0x76
					WriteData8255(D4_C_ADDR, 0x10);
					ADC_Result.Ih[i] = ADC_Conversion();
					D4_PB += 0x10; //增加偏移量
					
				}
			//In17_24JC:
			  D4_PB = 0x8A;
			  for(i=16 ; i<24; i++)
				{
					Delay_10us(5);//50us
					WriteData8255(D4_B_ADDR, ~D4_PB);  //D4_PB = 0x8A ,~D4_PB = 0x75,PB口输出10001000对应EN1、SAD2、SAD1、SAD0、EN0、FAD2、FAD1、FAD0
					WriteData8255(D4_C_ADDR, 0x10);    //PC口输出对应EN0、FAD2、FAD1、FAD0
					ADC_Result.Ih[i] = ADC_Conversion();
					D4_PB += 0x10; //增加偏移量
				}
			//TWTFAULT:
				WriteData8255(D7_A_ADDR, 0xFF); //EN2有效
			  WriteData8255(D4_B_ADDR, 0x77);
			  Delay_10us(20);//200us
	      temp = ReadData8255(D4_A_ADDR); //读取状态
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
	      temp = ReadData8255(D4_A_ADDR); //读取状态
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
	      temp = ReadData8255(D4_A_ADDR); //读取状态
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
	      temp = ReadData8255(D4_A_ADDR); //读取状态
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
	      temp = ReadData8255(D4_A_ADDR); //读取状态
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
	      temp = ReadData8255(D4_A_ADDR); //读取状态
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
	      temp = ReadData8255(D4_A_ADDR); //读取状态
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
	      temp = ReadData8255(D4_A_ADDR); //读取状态
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
				WriteData8255(D7_A_ADDR, 0x01); //PA口输出00000001对应EN2 
	      temp = ReadData8255(D4_A_ADDR); //读取状态
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
	      temp = ReadData8255(D4_A_ADDR); //读取状态
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
	      temp = ReadData8255(D4_A_ADDR); //读取状态
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
	      temp = ReadData8255(D4_A_ADDR); //读取状态
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
	      temp = ReadData8255(D4_A_ADDR); //读取状态
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
	      temp = ReadData8255(D4_A_ADDR); //读取状态
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
	      temp = ReadData8255(D4_A_ADDR); //读取状态
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
	      temp = ReadData8255(D4_A_ADDR); //读取状态
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
	      temp = ReadData8255(D4_A_ADDR); //读取状态
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
	      temp = ReadData8255(D4_A_ADDR); //读取状态
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
	      temp = ReadData8255(D4_A_ADDR); //读取状态
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
	      temp = ReadData8255(D4_A_ADDR); //读取状态
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
	      temp = ReadData8255(D4_A_ADDR); //读取状态
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
	      temp = ReadData8255(D4_A_ADDR); //读取状态
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
	      temp = ReadData8255(D4_A_ADDR); //读取状态
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
	      temp = ReadData8255(D4_A_ADDR); //读取状态
				if((temp&0x02) == 0x02)
				{
					TWT1_STATE |= 0x20; //TWT1_STATE.5
				}
				else
				{
					TWT1_STATE &= ~0x20;
				}
				/*高压电源工作状态检测*/
			//DY://低压指示
				WriteData8255(D4_B_ADDR, 0xF7);
				Delay_10us(5);//50us
				temp = ReadData8255(D4_A_ADDR); //读取状态
				if((temp&0x08) != 0x08) //ACC.3
				{
						HVPS_STATE |= 0x01; 
				}
				else
				{
						HVPS_STATE &= ~0x01; 
				}
			//GY://高压指示
				WriteData8255(D4_B_ADDR, 0xF6);
				Delay_10us(5);//50us
				temp = ReadData8255(D4_A_ADDR); //读取状态
				if((temp&0x08) != 0x08) //ACC.3
				{
						HVPS_STATE |= 0x04; 
				}
				else
				{
						HVPS_STATE &= ~0x04; 
				}
			//FS://发射指示
				WriteData8255(D4_B_ADDR, 0xF5);
				Delay_10us(5);//50us
				temp = ReadData8255(D4_A_ADDR); //读取状态
				if((temp&0x08) != 0x08) //ACC.3
				{
						HVPS_STATE |= 0x08; 
				}
				else
				{
						HVPS_STATE &= ~0x08; 
				}
			//READY://延时到
				WriteData8255(D4_B_ADDR, 0xF4);
				Delay_10us(5);//50us
				temp = ReadData8255(D4_A_ADDR); //读取状态
				if((temp&0x08) == 0x08) //ACC.3
				{
						HVPS_STATE |= 0x02; 
				}
				else
				{
						HVPS_STATE &= ~0x02; 
				}
			//PRO://故障
				WriteData8255(D4_B_ADDR, 0xF3);
				Delay_10us(5);//50us
				temp = ReadData8255(D4_A_ADDR); //读取状态
				if((temp&0x08) == 0x08) //ACC.3
				{
						HVPS_STATE |= 0x10; //HVPS_STATE.4
					  //GOFF//关栅极电压
					 //关高压，清软件控制标志位
					temp = HVPS_CTRL | 0x02;
					WriteData8255(D5_C_ADDR, temp);
					HVPS_STATE &= ~0x20; //清除软件加高压标志位HVPS_STATE.5
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
** @Descriptions:	 ADC转换
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
	  for(; i<3; i++) //AD采集3次
	  {
			GPIO_ResetPin(GPIOC, PIN14); //启动AD转换
			
			GPIO_ConfigPinsAsInput(GPIOC, PIN8); //配置为输入
			while(GPIO_GetPinState(GPIOC, PIN8)); //等待转换结束状态
			
			GPIO_SetPin(GPIOC, PIN14); //置位后开始读取数据
			GPIOC->OUT.all |= 0x1F;   //配置AD574地址
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
** @Descriptions:	 唤醒结果判断	
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
					Ih_WAKE = 0x01; //唤醒失败。
				}
				else
				{
					Ih_WAKE = 0x00; //唤醒成功
					
				}
			InWakeResult(); //螺线唤醒结果回送子程序
			FLAGA &= ~0x40;//清除唤醒结束标志位，等待下一次唤醒结束指令
		}
}

/**----------------------------------------------------------------------------
** @Function:		   InWakeResult
**
** @Descriptions:	 螺线唤醒结果回送子程序	
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
	WakeFrameInfo.DataLength[0] = 0x19; //26个字节
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
	UART_Send(UART1, pInWakeSend, 25); // 上报唤醒结果
	
}


/**----------------------------------------------------------------------------
** @Function:		   CommandResponse
**
** @Descriptions:	 命令响应
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
	UART_Send(UART1, pInWakeSend, 26); // 命令响应发送
	
}

/******************* (C) COPYRIGHT 2017  *****END OF FILE****/
























