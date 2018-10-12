/**
* Copyright(C) 2017, 
* ALL rights reserved.
*
* @file    I2C_user.c
* @author   MCU Application Team
* @version V0.1   MDK version:4.70.0.0
* @date    9-June-2015
* @brief   This file use for the I2C initial configure.
*
*/

/* Includes ------------------------------------------------------------------*/
#include "i2c.h"
#include <stdio.h>
#include "system.h"

IIC_CtrlBlk_TypeDef I2C1Ctrl;
IIC_CtrlBlk_TypeDef I2C2Ctrl;

uint8_t SlaveSendArry[8] = {0xaa,0x11, 0x22, 0x33, 0x44, 0x55, 0x66,0xff};


static void IIC_IOCONFIG(void);
void I2C_Test(void);
void I2C_Configuration(void);
/**----------------------------------------------------------------------------
** @Function:		   I2C_Test
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
void I2C_Test(void)
{

//	unsigned char temp = 0;
	int i = 0;
	unsigned char arry[7] = {0x11, 0x22, 0x33, 0x44, 0x55, 0x66,0xFF};
  
  I2C2Ctrl.WrIndex = 0;


	
  #if 1
  /*
   I2C1 master  write  data to I2C2 slaver.
  */
  //IIC_CtrlBlk_TypeDef* IICCtrl1 = &IIC2_CtrlBlk;
//	for(i=0; i<8; i++)
//	{
//		IIC2_CtrlBlk.IICMasterBuffer[i] = 0;
//	}
  DEBUG("\r\n--------IIC_WriteArray starting--------\r\n");
  IIC_WriteArray(I2C1, 0x70, 0xaa, arry, 7);
  DEBUG("\r\n--------IIC_WriteArray  ending--------\r\n");
  sdelay_us(500000);
	DEBUG("\r\n-------The I2C2 Recive Data Start Printing------\r\n");
  if(IIC2_CtrlBlk.WrIndex == 8)
	{  for( i=0; i<8; i++)
		{
			DEBUG("The I2C2 Recive No.%d data is:%x\r\n", i, IIC2_CtrlBlk.IICMasterBuffer[i]);
			IIC2_CtrlBlk.IICMasterBuffer[i] = 0;
		}
			IIC2_CtrlBlk.WrIndex = 0;
  }
	DEBUG("\r\n-------The I2C2 Recive Data Print ending--------\r\n");
	//IIC_WriteArray(I2C2, 0x70, 0xaa, arry, 7);
  #endif
	//delay(100);
	sdelay_us(2000000);
	
	#if 0
  #if defined I2C_MASTER
	
  #if defined I2C_SLAVER
	unsigned char ReadArry[8] = {0};
	/*填充从机将要发送的数据*/
	for( ; i<3; i++)
	{
		 IIC2_CtrlBlk.IICSlaveBuffer[i] = SlaveSendArry[i];
	}
	IIC2_CtrlBlk.IICReadLength  = 3;
	IIC2_CtrlBlk.RdIndex  = 0;
	#endif
  /*
   I2C1 master  read data from I2C2 slaver.
  */
//	DEBUG("\r\n--------IIC_ReadArray  starting--------\r\n");
	IIC_ReadArray(I2C1, 0x70, 0xaa, 3, ReadArry);
//	DEBUG("--------IIC_ReadArray  ending--------\r\n");
 	DEBUG("\r\n-------The I2C1 Recive Data Print ending--------\r\n");
	i = 0;
	for( ; i<3; i++)
	{
		DEBUG("The I2C1 Recive No.%d data is:%x\r\n", i, ReadArry[i]);
	}
  DEBUG("\r\n-------The I2C1 Recive Data Print ending--------\r\n");
	
	#endif
	
	#endif

   
//	IIC_WriteByte(I2C1,0x70,0x80,0x55);
//	temp = IIC_ReadByte(I2C2,0x70,0x80);
//	//DEBUG("Temp = %x\r\n", temp);
	//IIC_WriteByte(I2C2,0x70,0x80,3);
	

	return;
}
/**----------------------------------------------------------------------------
** @Function:		   I2C_Configuration
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
void I2C_Configuration(void)
{

  /* --------- Config I2C1,I2C2 AFIO assignment -------------*/
	IIC_IOCONFIG();
	/* --------- IIC initiallization ---------------------*/
	/*
	1-MASTER;50-50KHz Speed; 0x00 - Slave address in slave mode;
	*/
	#if defined I2C_MASTER
	IIC_Init(I2C1,1,1,0x70);
	#endif
	
	#if defined I2C_SLAVER
	IIC_Init(I2C2,0,1,0x70);
	#endif
	//IIC_SlaveGetData(I2C2,0,1);
}

/**----------------------------------------------------------------------------
** @Function:		   IIC_IOCONFIG
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
static void IIC_IOCONFIG(void)
{
	#if 1			//IIC1, SCL-> PB6, SDA-> PB7
	IIC1_SCL_PB6;
	IIC1_SDA_PB7;	
	#endif

	#if 0			//IIC1, SCL-> PB8, SDA-> PB8
	IIC1_SCL_PB8;
	IIC1_SDA_PB9;	
	#endif

	#if 1			//IIC2, SCL-> PB10, SDA-> PB11
	IIC2_SCL_PB10;
	IIC2_SDA_PB11;	
	#endif

}	

/**----------------------------------------------------------------------------
** @Function:		   I2C1_IRQHandler
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
void I2C1_IRQHandler(void)
{
	//DEBUG("\r\nI2C1 Interrupt\r\n");
	//IIC_IRQHandler(I2C1);
	 IIC1_IRQHandler(I2C1);
}

/**----------------------------------------------------------------------------
** @Function:		   I2C2_IRQHandler
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
void I2C2_IRQHandler(void)
{
	//DEBUG("\r\nI2C2 Interrupt\r\n");
	//IIC_IRQHandler(I2C2);
	IIC2_IRQHandler(I2C2);
}


/******************* (C) COPYRIGHT 2017  *****END OF FILE****/

