//------------------------------------------------------------
//HHD32F1xx DMA demo Main Program
//
//
//------------------------------------------------------------
#include "hhd32f1xx.h"
#include "hhd_dma.h"
#include "hhd_sys.h"

DMA_DATASTRUCT_TypeDef  DMA_STRUCT;


//Main function entry
int main(void)
{
	
	/* --------- System Initialization  ----------- */
  /* 系统初始化后，MCU运行在72M时钟  -------------*/
  SystemInit();
	

  /* --------- Enable DMA1 Clock  --------------- */
  ENABLEDMA1CLK;


  /* --------- Set DMA1 CH1 source address  ----- */
  DMA_STRUCT.DMA_SRCENDPTR.all = 0x20002000;
	
  /* --------- Set DMA1 CH1 Destination address  -*/
  DMA_STRUCT.DMA_DSTENDPTR.all = 0x20002400;

  /* --------- Set DMA1 CH1 Control, 1 word single*/
	/*transfer address  ----------------------------*/
  DMA_STRUCT.DMA_CHNLCFG.bit.N_MINUS_1 = 1;	//1 transfer
	DMA_STRUCT.DMA_CHNLCFG.bit.SRC_SIZE  = 2; //word transfer
	DMA_STRUCT.DMA_CHNLCFG.bit.SRC_INC   = 2; //increment address.
	DMA_STRUCT.DMA_CHNLCFG.bit.DST_SIZE  = 2; //word transfer
	DMA_STRUCT.DMA_CHNLCFG.bit.DST_INC   = 2; //increment address.	
  DMA_STRUCT.DMA_CHNLCFG.bit.CYCLE_CTRL= 1; //can only set to 1.
	DMA_STRUCT.DMA_CHNLCFG.bit.R_POWER   = 0; //do arbitration after every transfer
	

  /* --------- Set DMA1 Base pointer address  ----*/
  DMA_SETBASEPTR(DMA1,0x20002000);
  
	/* --------- Set DMA1 CH1 Enable ---------------*/
  DMA_CHEnableSet(DMA1,0x1);

  /* --------- Issue a soft request at CH1 of DMA1*/
  DMA_SWRequest(DMA1,0x1);
	
	/* --------- Enable DMA1 to transfer data  -----*/
  DMA_Enable(DMA1);

	while (1); 
}

