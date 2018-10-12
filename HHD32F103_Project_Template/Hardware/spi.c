/**
* Copyright(C) 2017, HiWafer
* ALL rights reserved.
*
* @file    SPI_user.h
* @author   MCU Application Team
* @version V0.1
* @date    9-June-2015
* @brief   This file use for the SPI initial configure.
*
*/

/* Includes ------------------------------------------------------------------*/
#include "spi.h"
#include "hhd_spi.h"
#include "system.h"
#include<string.h>
#include<stdio.h>

#define EIGHT_BIT   7
#define SPI_TEST    5

/*SPI_Private_TypesDefinitions------------------------------------------------*/
void SPI_Configuration(void);
void SPI_Test(void);
static void SPI_IOCONFIG(void);

/**----------------------------------------------------------------------------
** @Function:		   SPI_Configuration
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
void SPI_Configuration(void)
{
 /*UART1 Configuration*/
 // UART1_IOCFG();
 // UART_Open(UART1,115200,UART_NO_PARITY,UART_RX_HALF_FULL);
  //DEBUG("\r\n----------------SPI Test---------------\r\n");
	/* ----------- SPI1,SPI2 GPIO configuration --------------------- */
	SPI_IOCONFIG();	

	/* ----------- initial SPI--------------------- */
	/*
	SPI_FRAME:  ��׼SPI
	EIGHT_BIT:  8λ���ݴ���
	SPI_MASTER: SPI��ģʽ
	SPI_MODE0:  SCK����ʱΪ�͵�ƽ����һ��ʱ�����䲶�����ݡ�
	*/
	SPI_Open(SPI1,SPI_FRAME, EIGHT_BIT, SPI_MASTER, SPI_MODE0, 2000000);
	/*
	SPI speed 1MHz
	*/
	//SPI_SetClk(SPI1,300000);
	
	/*
	SPI_FRAME:  ��׼SPI
	EIGHT_BIT:  8λ���ݴ���
	SPI_MASTER:  SPI��ģʽ
	SPI_MODE0:  SCK����ʱΪ�͵�ƽ����һ��ʱ�����䲶�����ݡ�
	*/
	SPI_Open(SPI2,SPI_FRAME, EIGHT_BIT, SPI_MASTER, SPI_MODE0, 600000);
	//SPI_SetClk(SPI2,3000000);
	
	SPI_EnableInt(SPI1, SPI_RX_FIFO_NOT_EMPTY);
  /*
	�˴�����SPI_RX_FIFO_NOT_EMPTY�жϷ�ʽ��SPI2�ܹ�����ÿһ֡SPI1���͵����ݡ�	
	SPI_RX_FIFO_FULL��SPI_RX_FIFO_HALF_FULL��ʽ���ж����������
	*/
	SPI_EnableInt(SPI2, SPI_RX_FIFO_NOT_EMPTY);
	SPI_Set_SSEL_High(SPI1);
  //SPI_Set_SSEL_High(SPI2);
	NVIC_EnableIRQ(SPI1_IRQn);
	//NVIC_EnableIRQ(SPI2_IRQn);
}

/**----------------------------------------------------------------------------
** @Function:		   SPI_IOCONFIG
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
static void SPI_IOCONFIG(void)
{
	#if 1			//SPI1, SSEL-> PA4, SCK-> PA5, MISO-> PA6, MOSI-> PA7
	SPI1_SSEL_PA4;
	SPI1_SCK_PA5;	
	SPI1_MISO_PA6;
	SPI1_MOSI_PA7;	
	#endif

	#if 0			//SPI1, SSEL-> PA15, SCK-> PB3, MISO-> PB4, MOSI-> PB5
	SPI1_SSEL_PA15;
	SPI1_SCK_PB3;	
	SPI1_MISO_PB4;
	SPI1_MOSI_PB5;	
	#endif

	#if 1			//SPI2, SSEL-> PB12, SCK-> PB13, MISO-> PB14, MOSI-> PB15
	SPI2_SSEL_PB12;
	SPI2_SCK_PB13;	
	SPI2_MISO_PB14;
	SPI2_MOSI_PB15;	
	#endif

	#if 0			//SPI3, SSEL-> PA15, SCK-> PB3, MISO-> PB4, MOSI-> PB5
	SPI3_SSEL_PA15;
	SPI3_SCK_PB3;	
	SPI3_MISO_PB4;
	SPI3_MOSI_PB5;	
	#endif
	
	
}	

/**----------------------------------------------------------------------------
** @Function:		   SPI_Test
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
void SPI_Test(void)
{

//	int rdata = 0,temp = 0;
//	int i = 0;
	/* ----------- Flush SPI FIFO ----------------------------- */
	SPI_ClearFIFO(SPI1);
//	
//	
//	/* ----------- Send one byte data to TX FIFO -------------- */
//	/* --------- �����߰�SPI1 ��MISO��MOSI������ -------------- */
	DEBUG("-------------------SPI Test----------------\r\n");
	SPI_Set_SSEL_High(SPI1);
	SPI_Reset_SSEL_Low(SPI1);
	SPI_Write_FIFO(SPI1, 0x7e);
	SPI_Set_SSEL_High(SPI1);
//	
//	
//	//Polling RX FIFO is not empty, if there is more than one byte data,
//	//Then start read FIFO.
// 	POLL_RXFIFO_NOTEMPTY(SPI1);
// //	
// 	rdata = SPI_Read_FIFO(SPI1);
// 	DEBUG("The SPI1 Read data is: %x\r\n", rdata);
//	
//	/* ----------- Flush SPI FIFO ----------------------------- */
	//SPI_ClearFIFO(SPI2);
	
	
	/* ----------- Send one byte data to TX FIFO -------------- */
	/* --------- �����߰�SPI1 ��MISO��MOSI������ -------------- */
	//SPI_Write_FIFO(SPI2,0x44);
	
	
	//Polling RX FIFO is not empty, if there is more than one byte data,
	//Then start read FIFO.
// 	POLL_RXFIFO_NOTEMPTY(SPI2);
// 	
// 	rdata = SPI_Read_FIFO(SPI2);
// 	temp = rdata;
// 	DEBUG("The SPI2 Read data is: %x\r\n", rdata);

	return;
}

/**----------------------------------------------------------------------------
** @Function:		   SPI1_IRQHandler
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
void SPI1_IRQHandler ()
{
	int temp = 0;
	//while(SPI1->SR.bit.RNE==0);
	temp =  SPI_Read_FIFO(SPI1);
	DEBUG("In SPI1 interrupt,the SPI1 Read data is: %x\r\n", temp);
	
	
}	

/**----------------------------------------------------------------------------
** @Function:		   SPI2_IRQHandler
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
void SPI2_IRQHandler ()
{
	int temp = 0;
//	while(SPI2->SR.bit.RNE==0);
	//SPI2->ICR.bit.RTIC = 1;
	temp =  SPI_Read_FIFO(SPI2);
	DEBUG("In SPI2 interrupt,the SPI2 Read data is: %x\r\n", temp);
	SPI_ClearFIFO(SPI2);
	SPI_Write_FIFO(SPI2,0x55);
	
	
}	


/*----------------------------------------------------------------------------
** Function name:		SPIx_ReadWriteByte
**
** Descriptions:		SPI��дһ���ֽ�
**                  SPIx : SPI1, SPI2
** parameters:			
**                  
**                  
**                  
** Returned value:		Read byte
** 
** Author:  MCU Application Team
**
** Date:9-June-2015
**
-------------------------------------------------------------------------------*/
// unsigned char	SPIx_ReadWriteByte(SPI_TypeDef* SPIx, unsigned char WriteData)
// {
// 	/* Loop while DR register in not emplty */
// 	while(SPI_I2S_GetFlagStatus(SPIx,SPI_I2S_FLAG_TXE) == RESET);
// 	
// 	/* Send byte through the SPIx peripheral */
// 	SPI_I2S_SendData(SPIx, WriteData);
// 	
// 	/* Wait to receive a byte */
// 	while(SPI_I2S_GetFlagStatus(SPIx, SPI_I2S_FLAG_RXNE) == RESET);
// 	
// 	/* Return the byte read from the SPI bus */
// 	return SPI_I2S_ReceiveData(SPIx);

// }

/******************* (C) COPYRIGHT 2017  *****END OF FILE****/

