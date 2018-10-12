/**
* Copyright(C) 2018, 
* ALL rights reserved.
*
* @file    flash.c
* @author   MCU Application Team
* @version V0.1   MDK version:4.70.0.0
* @date    10-October-2018
* @brief   This file use for the hard abstract layer.
*/

/* Includes ------------------------------------------------------------------*/
#include "flash.h"
#include "system.h"
#include "delay.h"


/* Defines ------------------------------------------------------------------*/
#define FLASH_OFFSET_ADDR      (unsigned int)(100*1024)
#define FLASH_SAVE_ADDR        (unsigned int)(FLASH_BASE_ADDR + FLASH_OFFSET_ADDR)


u32 HHDFLASH_BUF[FLASH_SECTOR_SIZE/4];//�����512Byte
const u8 WriteData[]={"HHD32F103 FLASH TEST\r\n"};
// u32 TEXT_Buffer[]={1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
#define SIZE sizeof(WriteData)		//���鳤��
//#define SIZE 513*4	//���鳤��
void HHD_FLASH_Read(u32 ReadAddr,u32 *pBuffer,u16 NumToRead);
void HHDFLASH_Write_NoCheck(u32 WriteAddr,u32 *pBuffer,u16 NumToWrite);  
/*----------------------------------------------------------------------------
** Function name:		HHD_FLASH_Write
**
** Descriptions:		FLASH Write
**
** parameters:			
**                  
**                  
**                  
** Returned value:		none
** 
** Author:  MCU Application Team
**
** Date:10-October-2018
**
-------------------------------------------------------------------------------*/
void HHD_FLASH_Write(u32 WriteAddr,u32 *pBuffer,u32 NumToWrite)	
{
	u32 secpos;   //������ַ
	u32 secoff;   //������ƫ�Ƶ�ַ(32λ����)
	u32 secremain;//����ʣ���ַ(32λ����)
	u16 i;
	u32 offaddr;//ʵ��ƫ�Ƶ�ַ
	if((WriteAddr<FLASH_BASE_ADDR) || (WriteAddr>=FLASH_MAX_ADDR)) 
	{
		DEBUG("Out of Flash size range!\r\n");
		return;
	}
  offaddr = WriteAddr - FLASH_BASE_ADDR;
	secpos = offaddr / FLASH_SECTOR_SIZE; //������ַ0~256
	secoff = (offaddr%FLASH_SECTOR_SIZE)/4; //�������ڵ�ƫ��32λ(4�ֽ�Ϊ������λ)
	secremain = FLASH_SECTOR_SIZE/4 - secoff;//����ʣ��ռ��С32λ
	if(NumToWrite<=secremain)secremain=NumToWrite;//�����ڸ�������Χ
	while(1)
	{
		HHD_FLASH_Read(secpos*FLASH_SECTOR_SIZE+FLASH_BASE_ADDR, HHDFLASH_BUF, FLASH_SECTOR_SIZE/4);
		for(i=0; i<secremain; i++)
		{
			if(HHDFLASH_BUF[secoff+i]!=0XFFFF)break;//��Ҫ����  
		}
		if(i<secremain)//��Ҫ����
		{
			IAP_Flash_Erase(WriteAddr);	
			for(i=0; i<secremain; i++)
			{
				HHDFLASH_BUF[i+secoff] = pBuffer[i]; 
			}
			HHDFLASH_Write_NoCheck(secpos*FLASH_SECTOR_SIZE+FLASH_BASE_ADDR, HHDFLASH_BUF, FLASH_SECTOR_SIZE/4);
		}
		else//д�Ѿ������˵�,ֱ��д������ʣ������. 
		{
			HHDFLASH_Write_NoCheck(WriteAddr, pBuffer, secremain);
		}
		if(NumToWrite==secremain)break;//д�������
		else
		{
			secpos++;				//������ַ��1
			secoff=0;				//ƫ��λ��Ϊ0 	 
		  pBuffer+=secremain;  	//ָ��ƫ��
			WriteAddr+=secremain;	//д��ַƫ��	   
		  NumToWrite-=secremain;	//4�ֽ�(32λ)���ݼ�
			if(NumToWrite>(FLASH_SECTOR_SIZE/4))secremain=FLASH_SECTOR_SIZE/4;//��һ����������д����
			else secremain=NumToWrite;//��һ����������д����
		}

	}
}


/*----------------------------------------------------------------------------
** Function name:		HHD_FLASH_Read
**
** Descriptions:		FLASH Read
**
** parameters:			
**                  
**                  
**                  
** Returned value:		none
** 
** Author:  MCU Application Team
**
** Date:10-October-2018
**
-------------------------------------------------------------------------------*/
void HHD_FLASH_Read(u32 ReadAddr,u32 *pBuffer,u16 NumToRead)   	
{
	u16 i;
	sdelay_us(5);
	for(i=0;i<NumToRead;i++)
	{
		pBuffer[i]= *((u32*)ReadAddr);//��ȡ4���ֽ�.
		ReadAddr += 4;//ƫ��4���ֽ�.	
	}
	sdelay_us(5);
}


/*----------------------------------------------------------------------------
** Function name:		HHDFLASH_Write_NoCheck
**
** Descriptions:		FLASH Write
**
** parameters:			
**                  
**                  
**                  
** Returned value:		none
** 
** Author:  MCU Application Team
**
** Date:10-October-2018
**
-------------------------------------------------------------------------------*/ 
void HHDFLASH_Write_NoCheck(u32 WriteAddr,u32 *pBuffer,u16 NumToWrite)   
{ 			 		 
	u16 i;
	IAP_Flash_Erase(WriteAddr);
	for(i=0;i<NumToWrite;i++)
	{
		 sdelay_us(50);
		 IAP_Flash_Program(WriteAddr,*pBuffer);
//		 while((HHD_FMC->FLASHCTRL&0x100) == 0x100)
//	   {
//			DEBUG("FLASH write Busy!\r\n");
//	   }
	   WriteAddr+=4;//��ַ����4.
		 pBuffer++;
		 sdelay_us(50);
	}  
} 


/*----------------------------------------------------------------------------
** Function name:		FlashTest
**
** Descriptions:		FLASH Test
**
** parameters:			
**                  
**                  
**                  
** Returned value:		none
** 
** Author:  MCU Application Team
**
** Date:10-October-2018
**
-------------------------------------------------------------------------------*/
void FlashTest(void)
{
	u8 ReadData[SIZE];
	u16  temp = SIZE;
	u16 i = 0;
	#if 0
	for(i=0; i<SIZE/4; i++)
	{
			TEXT_Buffer[i] = i;
	}
	#endif
	//DEBUG("SIZE = %d\r\n", temp);
	DEBUG("\r\n+------------------HHD32F103 FLASH TEST---------------+\r\n");
	DEBUG("\r\n---------------------Writing FLASH ------------------\r\n");
	#if 0
	for(i=0; i<SIZE/4; i++)
	{
		DEBUG("TEXT_Buffer[%d] = %d\r\n", i, TEXT_Buffer[i]);
	}
	#endif
	DEBUG("WriteData=%s\r\n", WriteData);
	HHD_FLASH_Write(FLASH_SAVE_ADDR,(u32*)WriteData,(SIZE/4));
	sdelay_us(300);
	DEBUG("\r\n---------------------Reading FLASH ------------------\r\n");
	HHD_FLASH_Read(FLASH_SAVE_ADDR,(u32*)ReadData,(SIZE/4));
	DEBUG("ReadData = %s\r\n", ReadData);
	#if 0
	for(i=0; i<SIZE/4; i++)
	{
		DEBUG("datatemp[%d] = %d\r\n", i, datatemp[i]);
	}
	#endif
	delay_ms(200);
	delay_ms(200);
	delay_ms(200);
}

