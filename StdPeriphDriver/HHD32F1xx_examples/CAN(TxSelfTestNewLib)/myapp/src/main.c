#include<string.h>
#include<stdio.h>
#include "hhd32f1xx.h"
#include "hhd_sys.h"
#include "hhd_can.h"
#include "system_user.h"
#include "USART_user.h"


void CAN_IRQHandler()
{
// 			int i,addr = 0, rxCNT;
//       //CAN_DisableInt(0xff);
// 	    addr = CAN->RBSA.all;
// 	    rxCNT = CAN->RMC.all;
// 	    if(CAN->IR.bit.RI == 0x01)
// 			{
// 				 if(addr < 53)
// 				 {
// 								 for(i = 0; i<11; i++)
// 					 {   
// 								
// 								printf("CAN->RXFIFO[%d] = %x\r\n", i+addr, CAN->RXFIFO[i+addr].all);
// 					 }

// 				}
//       
// 			}
// 			CAN_SetCMD(ReleaseRecBuf); // release recieve buffer
		int i;
      //CAN_DisableInt(0xff);
	    printf("\r\nCAN->DATAINFO.RxDATAINFO.RxFRAME.all = %x \r\n",CAN->DATAINFO.RxDATAINFO.RxFRAME.all);
	    if(CAN->IR.bit.RI == 0x01) //接收中断
			{
         for(i = 0; i<10; i++)
				 {
							printf("CAN->DATAINFO.RxDATAINFO.RxDATA[%d].all = %x\r\n", i, CAN->DATAINFO.RxDATAINFO.RxDATA[i].all);
		  	 }

			}
			CAN_SetCMD(ReleaseRecBuf); // release recieve buffer
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
	/* --------- System Initialization  ----------- */
  /* 系统初始化后，MCU运行在72M时钟  -------------*/
  SYS_SystemInitial();


	USART_Configuration();
	
	CAN_Init();
	/* --------- Enable CAN Clock  ---------------- */

 // ENABLECAN1CLK;
	//SYSCON->RCCCFGR.bit.PCLK1SEL = 4;//add by wangkui

  	printf("-----------------CAN test!-----------------\r\n");
// 	/* --------- Enable CAN Rx Interrupt  --------- */
// 	CAN_EnableInt(RIE);

	
  /* --------- CAN IO config  ------------------- */
  CAN_IOCONFIG();

	/* --------- CAN Mode Config  ---------------- */

	

	//CAN_ClearStatus(0xff);
	do{
			CAN_SetMode(ResetMode);
		}while(CAN->MOD.bit.RM !=  ResetMode);	
	
	/*
	BIT Period= Tsyncseg + Ttseg1 + Ttseg2 = 1+3+5 = 9
	Baudrate = 1/BIT Period = 1MHz
	*/
	//TQ = 2x(1/36MHz)x2 = (1/9)us
	//HHD_CAN->BTR0 = 0x01;
	CAN->BTR0.bit.SJW = 0x00;
	CAN->BTR0.bit.BRP = 0x01;
	/*SAM = 1, Ttseg1 = TQ*3, Ttseg2 = TQ*5 */
	//HHD_CAN->BTR1 = 0xC7;
	CAN->BTR1.bit.SAM = 0x01;
	CAN->BTR1.bit.TSEG1 = 0x7;
	CAN->BTR1.bit.TSEG2 = 0x4;
	//HHD_CAN->OCR = 0X02;
	//HHD_CAN->MOD &= ~(0x80);
		CAN->MOD.bit.AFM = 0x00; //Sigle filter
	//HHD_CAN->MOD &= ~(0x80);
	//HHD_CAN->CDR = 0xC4;
	//HHD_CAN->EWLR = 10;
	
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


	
	
	CAN_EnableInt(RIE);


	CAN_SetMode(ACCFMode|SelfTestMode);
	CAN_SetMode(ACCFMode|SelfTestMode);
	
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
//	HHD_CAN -> DATAINFO[9] = 0x08 ; ///data 
		CAN->DATAINFO.TxDATAINFO.TxFRAME.all = 0x08;
		CAN->DATAINFO.TxDATAINFO.TxDATA[0].all = 0xEA;  //Identifier
		CAN->DATAINFO.TxDATAINFO.TxDATA[1].all = 0x00;  //Identifier
		CAN->DATAINFO.TxDATAINFO.TxDATA[2].all = 0x01;  //data 1
		CAN->DATAINFO.TxDATAINFO.TxDATA[3].all = 0x02;  //data 2
		CAN->DATAINFO.TxDATAINFO.TxDATA[4].all = 0x03;  //data 3
		CAN->DATAINFO.TxDATAINFO.TxDATA[5].all = 0x04;  //data 4
		CAN->DATAINFO.TxDATAINFO.TxDATA[6].all = 0x05;  //data 5
		CAN->DATAINFO.TxDATAINFO.TxDATA[7].all = 0x06;  //data 5
		CAN->DATAINFO.TxDATAINFO.TxDATA[8].all = 0x07;  //data 7
		CAN->DATAINFO.TxDATAINFO.TxDATA[9].all = 0x08;  //data 8

  

	
	
	/* --------- When Trans buffer is empty,write Frame
     info to framinto buffer     ---------------- */
	//while( (CAN_GetStatus() & TranBufSt) != TranBufSt)
  //HHD_CAN -> FRAMEINFO  = 0x0f ; 
	
	/* --------- Enable CAN Tx Interrupt  --------- */

  
  //while((CAN_GetStatus() & TranBufSt) == TranBufSt);
 	CAN_SetCMD(SelfRecReq);
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

