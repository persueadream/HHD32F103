#include<string.h>
#include<stdio.h>
#include "hhd32f1xx.h"
#include "hhd_sys.h"
#include "hhd_can.h"
#include "system_user.h"
#include "USART_user.h"


void CAN_IRQHandler()
{
			int i;
      //CAN_DisableInt(0xff);
	    if(HHD_CAN->IR & 0x01)
			{
         for(i = 0; i<11; i++)
				 {
							printf("HHD_CAN->RXFIFO[%d] = %x\r\n", i, HHD_CAN->RXFIFO[i]);
		  	 }

			}
//       if((HHD_CAN->RXFIFO[3] ==0)&(HHD_CAN->RXFIFO[4] ==1)&(HHD_CAN->RXFIFO[5] ==2)&(HHD_CAN->RXFIFO[6] ==3)&(HHD_CAN->RXFIFO[7] ==4)&(HHD_CAN->RXFIFO[8] ==5)&(HHD_CAN->RXFIFO[9] ==6))
//       { 
//           //Uart_PutStr("can ok\n");
//           HHD_CAN -> SR  = 0x12345678 ;                   
// 			}
//       else
//       {
// //           i = HHD_CAN->RXFIFO[6] ;
// //           HHD_CAN -> MOD  = i ;                   
//           //Uart_PutStr("can tost err\n");
//           //UartEndSimulation();
//       }


}


void CAN_IOCONFIG(void)
{
	#if 1
  HHD_AFIO -> PA11 = CAN1_RX_PA11;  			//CAN1 RX config
  HHD_AFIO -> PA12 = CAN1_TX_PA12;  			//CAN1 TX config
	#else
  HHD_AFIO -> PB8  = CAN1_RX_PB8;  			//CAN1 RX config
  HHD_AFIO -> PB9  = CAN1_TX_PB9;  			//CAN1 TX config	
	#endif
}

void CAN_Init(void)
{
	
	  SYSCON->SYSAPB1CLKCTRL.bit.CANCLK = 1;
		SYSCON->APB1RESET.bit.CANRSTN=1;
		SYSCON->APB1RESET.bit.CANRSTN=0;
}

int main (void)
{

	uint32_t temp =0;
	uint32_t EXT_ID = 0x1F00FF00;
	temp = EXT_ID << 3;
	/* --------- System Initialization  ----------- */
  /* 系统初始化后，MCU运行在72M时钟  -------------*/
  SYS_SystemInitial();


	USART_Configuration();
	
	CAN_Init();
	/* --------- Enable CAN Clock  ---------------- */

 // ENABLECAN1CLK;
	//SYSCON->RCCCFGR.bit.PCLK1SEL = 4;//add by wangkui

  	printf("-----------------CAN Tx test!-----------------\r\n");
// 	/* --------- Enable CAN Rx Interrupt  --------- */
// 	CAN_EnableInt(RIE);

	
  /* --------- CAN IO config  ------------------- */
  CAN_IOCONFIG();

	/* --------- CAN Mode Config  ---------------- */

	

	//CAN_ClearStatus(0xff);
//	CAN_SetMode(ResetMode);
//	while((HHD_CAN -> MOD & ResetMode) !=  ResetMode)
	//CAN_SetMode(ResetMode);	// enter reser mode
	do{
		CAN_SetMode(ResetMode);
	}while(CAN->MOD.bit.RM !=  ResetMode);
	
	/*
	**                   	BIT Period= Tsyncseg + Ttseg1 + Ttseg2 
	**                    Baudrate = 1/BIT Period
	**                    Tsyncseg = 1xTQ
	**                    Ttseg1 = TQx(8xTSEG1.3 + 4xTSEG1.2 + 2xTSEG1.1 + TSEG1.0 + 1)
	**                    Ttseg2 = TQx(4xTSEG2.2 + 2xTSEG2.1 + TSEG2.0 + 1)
	**                    TQ = tclk x (32xBRP.5 + 16xBRP.4 + 8xBRP.3 + 4xBRP.2 + 2xBRP.1 + BRP.0 + 1)
	**                    tclk = 1/APB1CLK = 1/36MHZ
	*/
	/*
	BIT Period= Tsyncseg + Ttseg1 + Ttseg2 = TQ*(1+15+1+6+1) = 24*1/12 = 2us
	Baudrate = 1/BIT Period = 0.5MHz 
	*/
	//TQ = (1/36MHz)x3 = (1/12)us
	//HHD_CAN->BTR0 = 0x01;
	CAN->BTR0.bit.SJW = 0x00;
	CAN->BTR0.bit.BRP = 0x02;
	/*SAM = 1, Ttseg1 = TQ*16, Ttseg2 = TQ*7 */
	//HHD_CAN->BTR1 = 0xC7;
	CAN->BTR1.bit.SAM = 0x01;
	CAN->BTR1.bit.TSEG1 = 0xf;
	CAN->BTR1.bit.TSEG2 = 0x6;
	//HHD_CAN->OCR = 0X02;
	//HHD_CAN->MOD &= ~(0x80);
	CAN->MOD.bit.AFM = 0x00; //Sigle filter
	//HHD_CAN->MOD &= ~(0x80);
	//HHD_CAN->CDR = 0xC4;
	//HHD_CAN->EWLR = 10;
	
	//设置过滤器,可接收任何标识符
	
//  HHD_CAN -> FRAMEINFO  = 0xFF; 
//  HHD_CAN -> DATAINFO[0] = 0xFF ; ///data 1
//  HHD_CAN -> DATAINFO[1] = 0xFF ; ///data 2
//  HHD_CAN -> DATAINFO[2] = 0xFF ; ///data 3
//	HHD_CAN -> DATAINFO[4] = 0xFF ; ///data 5
//  HHD_CAN -> DATAINFO[5] = 0xFF ; ///data 6
//  HHD_CAN -> DATAINFO[6] = 0xFF ; ///data 7
   CAN->DATAINFO.FILTER.ACR[0].all = 0xff;
	 CAN->DATAINFO.FILTER.ACR[1].all = 0xff;
   CAN->DATAINFO.FILTER.ACR[2].all = 0xff;
   CAN->DATAINFO.FILTER.ACR[3].all = 0xff;
	 CAN->DATAINFO.FILTER.AMR[0].all = 0xff;
	 CAN->DATAINFO.FILTER.AMR[1].all = 0xff;
	 CAN->DATAINFO.FILTER.AMR[2].all = 0xff;
	 CAN->DATAINFO.FILTER.AMR[3].all = 0xff; 
	
	CAN_EnableInt(TIE);//开启发送中断


	//CAN_SetMode(ACCFMode|SelfTestMode);
	//CAN_SetMode(ACCFMode|SelfTestMode);
	CAN_SetMode(ACCFMode | ActiveMode);
	CAN_SetMode(ACCFMode | ActiveMode);
	while(1)
	{



	while((CAN_GetStatus() & RecSt) == RecSt);
	while((CAN_GetStatus() & TranComplete) != TranComplete);
	while((CAN_GetStatus() & TranBufSt) != TranBufSt);
		
	/* --------- CAN Write TX buffer  ------------- */
//  HHD_CAN -> FRAMEINFO  = 0x08 ; 
//  HHD_CAN -> DATAINFO[0] = 0xff ; ///data 1
//  HHD_CAN -> DATAINFO[1] = 0x00 ; ///data 2
//  HHD_CAN -> DATAINFO[2] = 0x01 ; ///data 3
//  HHD_CAN -> DATAINFO[3] = 0x02 ; ///data 4
//  HHD_CAN -> DATAINFO[4] = 0x03 ; ///data 5
//  HHD_CAN -> DATAINFO[5] = 0x04 ; ///data 6
//  HHD_CAN -> DATAINFO[6] = 0x05 ; ///data 7
//  HHD_CAN -> DATAINFO[7] = 0x06 ; ///data 8
//	HHD_CAN -> DATAINFO[8] = 0x07 ; ///data 8
//	HHD_CAN -> DATAINFO[9] = 0x08 ; ///data 8
		CAN->DATAINFO.TxDATAINFO.TxFRAME.all = 0x88;    //扩展帧模式,数据长度为8.
		CAN->DATAINFO.TxDATAINFO.TxDATA[0].all = ((temp&0xff000000) >> 24);  //Identifier
		CAN->DATAINFO.TxDATAINFO.TxDATA[1].all = ((temp&0x00ff0000) >> 16);  //Identifier
		CAN->DATAINFO.TxDATAINFO.TxDATA[2].all = ((temp&0x0000ff00) >> 8);  //Identifier 
		CAN->DATAINFO.TxDATAINFO.TxDATA[3].all = ((temp&0x000000ff));  //Identifier 
		CAN->DATAINFO.TxDATAINFO.TxDATA[4].all = 0xff;  //data1
		CAN->DATAINFO.TxDATAINFO.TxDATA[5].all = 0x00;  //data2
		CAN->DATAINFO.TxDATAINFO.TxDATA[6].all = 0xff;  //data3
		CAN->DATAINFO.TxDATAINFO.TxDATA[7].all = 0x00;  //data4
		CAN->DATAINFO.TxDATAINFO.TxDATA[8].all = 0xff;  //data5
		CAN->DATAINFO.TxDATAINFO.TxDATA[9].all = 0x00;  //data6
		CAN->DATAINFO.TxDATAINFO.TxDATA[10].all = 0xff;  //data7
		CAN->DATAINFO.TxDATAINFO.TxDATA[11].all = 0x00;  //data8

  

	
	
	/* --------- When Trans buffer is empty,write Frame
     info to framinto buffer     ---------------- */
	//while( (CAN_GetStatus() & TranBufSt) != TranBufSt)
  //HHD_CAN -> FRAMEINFO  = 0x0f ; 
	
	/* --------- Enable CAN Tx Interrupt  --------- */

  
  //while((CAN_GetStatus() & TranBufSt) == TranBufSt);
 	//CAN_SetCMD(SelfRecReq);
	CAN_SetCMD(TransReq);
	while((CAN_GetStatus() & TranComplete) != TranComplete);
	while((CAN_GetStatus() & TranBufSt) != TranBufSt)
	{
		temp = CAN->ECC.all;
		printf("ECC = %x\r\n", temp);
	
	}
	temp = CAN->ALC.all;
	printf("ALC = %x\r\n", temp);
	temp = CAN->ECC.all;
	printf("ECC = %x\r\n", temp);
	temp = CAN->SR.all;
	printf("SR = %x\r\n", temp);

	delay_us(200000);
	delay_us(200000);
	delay_us(200000);
	delay_us(200000);
	delay_us(200000);
	delay_us(200000);
  /* --------- Check Transmission Complete Status bit -----*/
	/* --------- Then Clear Transmission Command -------------*/
	// CAN_ClrCMD(TransReq);
	//while((CAN_GetStatus() & TranComplete) != TranComplete)
	//while((CAN_GetStatus() & TranComplete) != TranComplete);
		//CAN_SetCMD(TransReq);
// 	while((CAN_GetStatus() & TranComplete) == TranComplete)	
	

	
 }
	/* --------- Clear Receive Buffer Status Register */
//	CAN_ClearStatus(TranSt);
 
 
  while (1)
	{
// 		//CAN_SetMode(ResetMode);
// 		CAN_SetMode(ActiveMode);
// // 			/* --------- CAN Write TX buffer  ------------- */
// //   HHD_CAN -> DATAINFO[0] = 0x55 ; ///data 1
// //   HHD_CAN -> DATAINFO[1] = 0x00 ; ///data 2
// //   HHD_CAN -> DATAINFO[2] = 0x77 ; ///data 3
// //   HHD_CAN -> DATAINFO[3] = 0x88 ; ///data 4
// //   HHD_CAN -> DATAINFO[4] = 0x99 ; ///data 5
// //   HHD_CAN -> DATAINFO[5] = 0xaa ; ///data 6
// //   HHD_CAN -> DATAINFO[6] = 0xbb ; ///data 7
// //   HHD_CAN -> DATAINFO[7] = 0xcc ; ///data 8
// // 	HHD_CAN -> DATAINFO[8] = 0xdd ; ///data 8
// // 	HHD_CAN -> DATAINFO[9] = 0xee ; ///data 8
// 	//	printf("Hello world!\r\n");
// 	while( (CAN_GetStatus() & TranBufSt) != TranBufSt);  
//   HHD_CAN -> FRAMEINFO  = 0x08 ; 
// // 		// 			/* --------- CAN Write TX buffer  ------------- */
//   HHD_CAN -> DATAINFO[0] = 0x55 ; ///data 1
//   HHD_CAN -> DATAINFO[1] = 0x00 ; ///data 2
//   HHD_CAN -> DATAINFO[2] = 0x77 ; ///data 3
//   HHD_CAN -> DATAINFO[3] = 0x00 ; ///data 4
//   HHD_CAN -> DATAINFO[4] = 0x99 ; ///data 5
//   HHD_CAN -> DATAINFO[5] = 0x00 ; ///data 6
//   HHD_CAN -> DATAINFO[6] = 0xbb ; ///data 7
//   HHD_CAN -> DATAINFO[7] = 0x00 ; ///data 8
// 	HHD_CAN -> DATAINFO[8] = 0xdd ; ///data 8
// 	HHD_CAN -> DATAINFO[9] = 0x00 ; ///data 8
// 	
//  // CAN_SetMode(ActiveMode);
//  	CAN_SetCMD(TransReq);
//   /* --------- Check Transmission Complete Status bit -----*/
// 	/* --------- Then Clear Transmission Command -------------*/
// 	while((CAN_GetStatus() & TranComplete) != TranComplete);
// 		
// 	CAN_ClrCMD(TransReq);
// 	
// 	
// 	/* --------- Clear Receive Buffer Status Register */
// 	//CAN_ClearStatus(TranSt);
// 		delay_us(2000);
// // 		delay_us(200000);
// 		delay_us(200000);
		
	}
	 
}

