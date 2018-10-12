/** www.armjishu.com
  ******************************************************************************
  * @file    CAN/LoopBack/hhd32f10x_it.c 
  * @author  MCD Application Team
  * @version V3.3.0
  * @date    04/16/2010
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and 
  *          peripherals interrupt service routine.
  ******************************************************************************
  * @copy
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT,  SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2010 </center></h2>
  */ 

/* Includes ------------------------------------------------------------------*/
#include "hhd32f10x_it.h"
#include "stdio.h"
#include "string.h"
#include "hhd_spi.h"
//#include "hhd32_eval.h"
#include <stdio.h>
//#include "HMC820.h"
#include "uart.h"
#include "system.h"

/** @addtogroup HHD32F10x_StdPeriph_Examples
  * @{
  */

/** @addtogroup USART_DEBUG
  * @{
  */ 
	


/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/
#define LED                      GPIO_Pin_2          //PD2
#define YES                      0X99
#define NO                       0X00
#define BUFFERSIZE               50
#define UP_CMD_CAN               (uint16_t)0x04      //CAN上报数据命令   
#define UP_CMD_KDJZ              (uint16_t)0x03      //宽带校正源上报数据命令
/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
//CanRxMsg RxMessage;
//CanRxMsg g_CanRxMessage[10];
//CanRxMsg g_SubCanRxMessage[10];
extern void LED_Display(uint8_t Ledstatus);
uint8_t uSynchro = 0;

/*串口2接收数据超时定时器*/
extern uint32_t g_UsartTwoTimer;
/*串口2接收数据完成与否标志，0-未完成，1-完成*/
extern uint8_t g_UsartTwoReceiveFlag;
/*串口2接收数据缓存*/
extern uint8_t g_UsartTwoReceiveBuffer[BUFFERSIZE];
extern uint8_t g_UsartTwoReceiveData[BUFFERSIZE];
/*串口2接收数据计数器*/
uint32_t g_ReceiveCounterTwo = 0;


/*串口1接收数据超时定时器*/
extern uint32_t g_UsartOneTimer ;
/*串口1接收数据完成与否标郑,0-未完成，1-完成*/
extern uint8_t g_UsartOneReceiveFlag;
/*串口1接收数据缓存*/
extern uint8_t g_UsartOneReceiveBuffer[BUFFERSIZE];
extern uint8_t g_UsartOneReceiveData[BUFFERSIZE];
/*串口1接收数据计数器*/
uint32_t g_ReceiveCounterOne = 0;


/*CAN接收数据完成与否标志*/
extern uint8_t g_CanRecvFlag;
/*CAN接收数据超时定时器*/
uint32_t g_CANTimer;
/*CAN接收数据计数器*/
uint32_t g_CANRcvCounter = 0;
uint32_t g_SubCANRcvCounter = 0;

/*同步定时器100ms*/
//extern uint8_t gSynTimer;

//extern CanTxMsg TxMessage;

uint32_t gCAN_RcvCnt = 0;

/*U/V/C PSK计时器*/
uint8_t gPSKTimer_U = 0;
uint8_t gPSKTimer_V = 0;
uint8_t gPSKTimer_C = 0;
uint8_t gPSKSwitch_U = 0;
uint8_t gPSKSwitch_V = 0;
uint8_t gPSKSwitch_C = 0;
uint8_t gFlag_U = 0, gFlag_V = 0, gFlag_C = 0;
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M3 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
	DEBUG("HardFualt_Handler\r\n");
  while (1)
  {
  }
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
//void SysTick_Handler(void)
//{
//}

/******************************************************************************/
/*            STM32F10x Peripherals Interrupt Handlers                        */
/******************************************************************************/







/**
  * @brief  This function handles USART1 global interrupt request.
  * @param  None
  * @retval None
  */
#if 0
void USART1_IRQHandler(void)
{
	uint8_t temp;
  if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
  {
//    /* Read one byte from the receive data register */
      temp = USART_ReceiveData(USART1);
			frame_get(temp);
//			if(g_ReceiveCounterOne < BUFFERSIZE)
//			{
//				g_UsartOneReceiveBuffer[g_ReceiveCounterOne++] = temp;
//			}
//			/*开启20ms超时定时器*/
//			g_UsartOneTimer = 2;
			//USART_SendData(USART1, temp);
			while(USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);
				
  }

//  if(USART_GetITStatus(USART2, USART_IT_TXE) != RESET)
//  {   
//    /* Write one byte to the transmit data register */
//    USART_SendData(USART2, TxBuffer2[TxCounter2++]);

//    if(TxCounter2 == NbrOfDataToTransfer2)
//    {
//      /* Disable the USART2 Transmit interrupt */
//      USART_ITConfig(USART2, USART_IT_TXE, DISABLE);
//    }
//		  USART_SendData(USART2, temp);
//  }
}
#endif
/**
  * @brief  This function handles USART1 global interrupt request.
  * @param  None
  * @retval None
  */
#if 0
void USART2_IRQHandler(void)
{
	uint8_t temp;
  if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)
  {
    /* Read one byte from the receive data register */
//			temp = USART_ReceiveData(USART2);
//		  if(g_ReceiveCounterTwo < BUFFERSIZE)
//			{
//				g_UsartTwoReceiveBuffer[g_ReceiveCounterTwo++] = temp;
//			}
//			/*开启20ms超时定时器*/
//			g_UsartTwoTimer = 2;
	//	  USART_SendData(USART2, temp);
		
  }
  
//  if(USART_GetITStatus(USART2, USART_IT_TXE) != RESET)
//  {   
//    /* Write one byte to the transmit data register */
//    USART_SendData(USART2, TxBuffer2[TxCounter2++]);

//    if(TxCounter2 == NbrOfDataToTransfer2)
//    {
//      /* Disable the USART2 Transmit interrupt */
//      USART_ITConfig(USART2, USART_IT_TXE, DISABLE);
//    }
//		  USART_SendData(USART2, temp);
//  }
}
#endif

/**
  * @brief  This function handles SPI1 global interrupt request.
  * @param  None
  * @retval None
  */
#if 0
void SPI1_IRQHandler(void)
{
	 uint8_t temp = 0;
	 //SPI_SLAVE_Buffer_Rx[RxIdx++] = SPI_I2S_ReceiveData(SPI1);
	 temp	= SPI_I2S_ReceiveData(SPI1);
	 //SetFrequecy_HMC820(temp);	
	// g_temp = temp;
	// U_SetChannel(g_temp);
}
#endif

/**
  * @brief  This function handles SPI2 global interrupt request.
  * @param  None
  * @retval None
  */
#if 0
void SPI2_IRQHandler(void)
{
	uint8_t temp = 0;
	  /* Store SPI_SLAVE received data */
  //SPI_SLAVE_Buffer_Rx[RxIdx++] = SPI_I2S_ReceiveData(SPI2);
	temp	= SPI_I2S_ReceiveData(SPI2);
	//V_SetChannel(temp);

}
#endif


/**
  * @brief  This function handles TIM4 Handler.
  * @param  None
  * @retval None
  */
#if 0
void TIM4_IRQHandler(void)
{
	//TIM_Cmd(TIM3, DISABLE);
	if(TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET)
	{
			TIM_ClearITPendingBit(TIM4, TIM_IT_Update);
#if 0
			if(uSynchro == 0)
			{
				GPIO_SetBits(GPIOD, LED);
			  uSynchro = 1;
			}
			else
			{
				GPIO_ResetBits(GPIOE, LED);
				uSynchro = 0;
				//TIM_ITConfig(TIM4, TIM_IT_Update, DISABLE);
				TIM_Cmd(TIM4, DISABLE);
			//	gSynTimer = 10;
			}
#endif

	}
	//TIM_Cmd(TIM3, ENABLE);


}
#endif

/**
  * @brief  This function handles TIM3 Handler.
  * @param  None
  * @retval None
  */
#if 0
void TIM3_IRQHandler(void)
{
	TIM_Cmd(TIM3, DISABLE);
	if(TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)
	{
			TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
	
			if(gFlag_C == 0)
			{
				GPIO_SetBits(GPIOA, C_BIT_PSK);
				gFlag_C = 1;
			}
			else
			{
				GPIO_ResetBits(GPIOA, C_BIT_PSK);
				gFlag_C = 0;
			}

#if 0
			/**/
			if(gPSKTimer_U != 0)
      {
				gPSKTimer_U--;
				if(gPSKTimer_U == 0)
				{
					//TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);
					TIM_Cmd(TIM4, ENABLE);
				}
			
			}			
#endif
			
#if 0
			if(uSynchro == 0)
			{
				GPIO_ResetBits(GPIOD, GPIO_Pin_2);
			  uSynchro = ~uSynchro;
			}
			else
			{
				GPIO_SetBits(GPIOD, GPIO_Pin_2);
				uSynchro = ~uSynchro;
			}
#endif


	}
	TIM_Cmd(TIM3, ENABLE);

}
#endif


#if 0
void TIM4_IRQHandler(void)
{
		if(TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET)
		{
			TIM_ClearITPendingBit(TIM4, TIM_IT_Update);
			if(led == 0)
			{
				GPIO_SetBits(GPIOE, GPIO_Pin_8);
			  led = ~led;
			}
			else
			{
				GPIO_ResetBits(GPIOE, GPIO_Pin_8);
				led = ~led;
			}		
			//USART_Send_user(USART2, SendBuffer, BUFFER_LEN);
			//USART_Send_user(USART2, g_DigtalPowerInfoArray, INFO_LEN);
		}
}
#endif

/******************************************************************************/
/*                 hhd32F10x Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_hhd32f10x_xx.s).                                            */
/******************************************************************************/

/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/

/**
  * @}
  */ 

/**
  * @}
  */ 

/******************* (C) COPYRIGHT 2010 STMicroelectronics *****END OF FILE****/
