/*----------- This drive is for Winbond W25Q16BV serial flash ----------------*/
/* Includes ------------------------------------------------------------------*/
#include "hhd32f1xx.h"
#include "hhd_spiflash.h"
#include "hhd_sys.h"
#include "hhd_spi.h"

//flash command
#define WREN  6		 		//write enable
#define WRDI  4		 		//write disable
#define RDSR  5		 		//read status register 1
#define WRSR  1		 		//write status register
#define READ  3		 		//read data
#define FAST_READ 0xb	//fast read
#define PP    2		 		//pagr program
#define SE4   0x20 		//4K block erase
#define SE32  0x52 		//32K block erase
#define SE64  0xd8 		//64K block erase
#define DP    0xb9	 	//power down
#define RES   0xab	 	//release power down and device ID


/*****************************************************************************
** Function name:		SPIFlashInit
**
** Descriptions:		initial SPI interface
**
** parameters:			None
** Returned value:		None
** 
*****************************************************************************/
void SPIFlashInit(void)
{
	//initial SPI
	SPI_Open(SPI1,SPI_FRAME, 8, SPI_MASTER, SPI_MODE0);
	SPI_SetClk(SPI1,1000000);
	return;	
}
/*****************************************************************************
** Function name:		SPIFlashID
**
** Descriptions:		get flash device ID
**
** parameters:			None
** Returned value:		None
** 
*****************************************************************************/
void SPIFlashID(uint8_t *  did)
{
	uint16_t data;
	SPI_Reset_SSEL_Low(SPI1); 				//force cs single low during access SPI flash
	SPI_Write_FIFO(SPI1,RES);					//isssue release power down and device ID command
	SPI_Write_FIFO(SPI1,0); 					//isssue dummy clock
	SPI_Write_FIFO(SPI1,0); 					//isssue dummy clock
	SPI_Write_FIFO(SPI1,0); 					//isssue dummy clock
 	SPI_SingleWriteRead(SPI1,&data); 	//get device id 
 	*did=(uint8_t)data;
	SPI_Set_SSEL_High(SPI1); 					//set cs signal

	return;
}
/*****************************************************************************
** Function name:		SPIFlashStatus
**
** Descriptions:		get flash status  S7-S0
**
** parameters:			sr1 pointer
** Returned value:		None
** 
*****************************************************************************/
void SPIFlashStatus(uint8_t * sr1)
{
	uint16_t data;
	SPI_Reset_SSEL_Low(SPI1); 				//force cs single low during access SPI flash
	SPI_Write_FIFO(SPI1,RDSR);				//isssue read status register 1 command
	SPI_SingleWriteRead(SPI1,&data); 	//get device id 
	*sr1=(uint8_t) data;
	SPI_Set_SSEL_High(SPI1); 					//set cs signal
	return;	
}
/*****************************************************************************
** Function name:		SPIFlashWriteEnable
**
** Descriptions:		enable flash write
**
** parameters:			None
** Returned value:		None
** 
*****************************************************************************/
void SPIFlashWriteEnable(void)
{
	SPI_Reset_SSEL_Low(SPI1); 						//force cs single low during access SPI flash
	SPI_Write_FIFO(SPI1,WREN);						//isssue write enable command
	while(SPI_TX_FIFO_Not_Empty(SPI1));  	//wait SPI not busy & transmit fifo empty 
	SPI_Set_SSEL_High(SPI1); 							//set cs signal

	return;		
}
/*****************************************************************************
** Function name:		SPIFlashRead
**
** Descriptions:		read data from specfic address
**
** parameters:			data address, return data pointer,number data to read
** Returned value:		None
** 
*****************************************************************************/
void SPIFlashRead(uint32_t addr, uint8_t * dst, uint32_t noofdata)
{
	uint16_t data;

	SPI_Reset_SSEL_Low(SPI1); 					//force cs single low during access SPI flash
	SPI_Write_FIFO(SPI1,READ);		 			//isssue Read command
	SPI_Write_FIFO(SPI1,addr>>16);		 	//isssue Read  command addr A23-A16
	SPI_Write_FIFO(SPI1,(addr & 0xFF00)>>8);		 
																			//isssue Read  command addr A15-A8
	SPI_Write_FIFO(SPI1,addr & 0xFF);		//isssue Read  command addr A7-A0

	//Receive data from flash
	while (noofdata-->0)
	{
		SPI_SingleWriteRead(SPI1,&data); 	//get one data 
		*dst++=(uint8_t) data;
	}
	SPI_Set_SSEL_High(SPI1); 						//set cs signal

	return;
}
/*****************************************************************************
** Function name:		SPIFlashRead
**
** Descriptions:		program data to flash
**
** parameters:			flash address, data pointer,number data to program
** Returned value:		None
** 
*****************************************************************************/
void SPIFlashWrite(uint32_t addr, uint8_t * src, uint8_t noofdata)
{
	uint16_t data;
	
	SPI_Reset_SSEL_Low(SPI1); 					//force cs single low during access SPI flash
	SPI_Write_FIFO(SPI1,PP);		 				//isssue PP command
	SPI_Write_FIFO(SPI1,addr>>16);		 	//isssue Read  command addr A23-A16
	SPI_Write_FIFO(SPI1,(addr & 0xFF00)>>8);		 
																			//isssue Read  command addr A15-A8
	SPI_Write_FIFO(SPI1,addr & 0xFF);		//isssue Read  command addr A7-A0

	//Receive data from flash
	while (noofdata-->0)
	{
		data=*src;
		SPI_SingleWriteRead(SPI1,&data); 	//write one data 
	}
	SPI_Set_SSEL_High(SPI1); 						//set cs signal

	return;	
}
/*****************************************************************************
** Function name:		SPIFlashSecErase
**
** Descriptions:		flash sector erase
**
** parameters:			flash address
** Returned value:		None
** 
*****************************************************************************/
void SPIFlashSecErase(uint32_t addr)
{
	SPI_Reset_SSEL_Low(SPI1); 					//force cs single low during access SPI flash
	SPI_Write_FIFO(SPI1,SE4);		 				//isssue Erase SE4/SE32/SE64 command
	SPI_Write_FIFO(SPI1,addr>>16);		 	//isssue Read  command addr A23-A16
	SPI_Write_FIFO(SPI1,(addr & 0xFF00)>>8);		 
																			//isssue Read  command addr A15-A8
	SPI_Write_FIFO(SPI1,addr & 0xFF);		//isssue Read  command addr A7-A0
	while(SPI_TX_FIFO_Not_Empty(SPI1));	//wait SPI not busy & transmit fifo empty 
	SPI_Set_SSEL_High(SPI1); 						//set cs signal
	return;	
}
	  

/******************************************************************************
**                            End Of File
******************************************************************************/
