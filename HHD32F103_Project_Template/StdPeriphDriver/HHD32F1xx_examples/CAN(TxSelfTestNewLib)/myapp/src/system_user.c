/**
* Copyright(C) 2015, 
* ALL rights reserved.
*
* @file    system_user.c
* @author   MCU Application Team
* @version V0.1
* @date    1-August-2015
* @brief   Peripheral clock and IO configure
*          NVIC Configure
*/


#include "system_user.h"

/*--------------------------------∫Í∂®“Â----------------------------*/

/*USART*/
#define USART2_GPIO_CLK          RCC_APB2Periph_GPIOA  //
#define USART1_GPIO_CLK          RCC_APB2Periph_GPIOA  //
#define USART2_CLK               RCC_APB1Periph_USART2 //
#define USART1_CLK               RCC_APB2Periph_USART1 //
#define USART1_RxPin             GPIO_Pin_10 //PA10
#define USART1_TxPin             GPIO_Pin_9  //PA9
#define USART2_RxPin             GPIO_Pin_3  //PA3
#define USART2_TxPin             GPIO_Pin_2  //PA2

/*CAN*/
#define CAN1_GPIO_CLK            RCC_APB2Periph_GPIOA
#define CAN2_GPIO_CLK            RCC_APB2Periph_GPIOB
#define CAN1_CLK                 RCC_APB1Periph_CAN1
#define CAN2_CLK                 RCC_APB1Periph_CAN2
#define CAN1_RxPin               GPIO_Pin_11 //PA11
#define CAN1_TxPin               GPIO_Pin_12 //PA12
#define CAN2_RxPin               GPIO_Pin_12 //PB12
#define CAN2_TxPin               GPIO_Pin_13 //PB13




/*----------------------------------------------------------------------------
** Function name:		RCC_Configuration
**
** Descriptions:		Clock Configure
**
** parameters:			
**                  
**                  
**                  
** Returned value:		none
** 
** Author:  MCU Application Team
**
** Date:9-June-2015
**
-------------------------------------------------------------------------------*/
void RCC_Configuration(void)
{   
	
	
}


/*----------------------------------------------------------------------------
** Function name:		GPIO_Configuration
**
** Descriptions:		GPIO Configure
**
** parameters:			
**                  
**                  
**                  
** Returned value:		none
** 
** Author:  MCU Application Team
**
** Date:9-June-2015
**
-------------------------------------------------------------------------------*/
// void GPIO_Configuration(void)
// {

// 												
// 												
// }

/*----------------------------------------------------------------------------
** Function name:		NVIC_Configuration
**
** Descriptions:		NVIC Configure
**
** parameters:			
**                  
**                  
**                  
** Returned value:		none
** 
** Author:  MCU Application Team
**
** Date:9-June-2015
**
-------------------------------------------------------------------------------*/
void NVIC_Configuration(void)
{

}


/*----------------------------------------------------------------------------
** Function name:		Delay
**
** Descriptions:		Delay function
**
** parameters:			count is u32 type
**                  
**                  
**                  
** Returned value:		none
** 
** Author:  MCU Application Team
**
** Date:9-June-2015
**
-------------------------------------------------------------------------------*/
void delay_us(u32 count)
{
	u32 i = 0;
	for(; i<count; i++)
	{
		;
	}
}



/******************* (C) COPYRIGHT 2015  *****END OF FILE****/

