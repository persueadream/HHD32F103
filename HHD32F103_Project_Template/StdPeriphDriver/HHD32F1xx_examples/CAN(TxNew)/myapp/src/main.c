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
      if((CAN->RXFIFO[3].all ==0)&(CAN->RXFIFO[4].all ==1)&(CAN->RXFIFO[5].all ==2)&(CAN->RXFIFO[6].all ==3)&(CAN->RXFIFO[7].all ==4)&(CAN->RXFIFO[8].all ==5)&(CAN->RXFIFO[9].all ==6))
      { 
          //Uart_PutStr("can ok\n");
          CAN -> SR.all  = 0x12345678 ;                   
			}
      else
      {
//           i = CAN->RXFIFO[6] ;
//           CAN -> MOD  = i ;                   
          //Uart_PutStr("can tost err\n");
          //UartEndSimulation();
      }


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
	CAN_SetMode(ResetMode);
	/*
	BIT Period= Tsyncseg + Ttseg1 + Ttseg2 = 1+3+5 = 9
	Baudrate = 1/BIT Period = 1MHz
	*/
	//TQ = 2x(1/36MHz)x2 = (1/9)us
	CAN->BTR0.all = 0x01;
	/*SAM = 1, Ttseg1 = TQ*3, Ttseg2 = TQ*5 */
	CAN->BTR1.all = 0xC7;
	//CAN->OCR = 0X03;
	CAN->MOD.all &= ~(0x80);
	//CAN->MOD &= ~(0x80);
	//CAN->CDR = 0xC4;
	CAN->EWLR.all = 10;
	
//   CAN -> FRAMEINFO.all  = 0xFF; 
     CAN->DATAINFO.FILTER.ACR[0].all = 0xff;
//   CAN -> DATAINFO[0].all = 0xFF ; ///data 1
//   CAN -> DATAINFO[1].all = 0xFF ; ///data 2
//   CAN -> DATAINFO[2].all = 0xFF ; ///data 3
// 	CAN -> DATAINFO[4].all = 0xFF ; ///data 5
//   CAN -> DATAINFO[5].all = 0xFF ; ///data 6
//   CAN -> DATAINFO[6].all = 0xFF ; ///data 7



	
	
	CAN_EnableInt(0Xff);


	CAN_SetMode(ActiveMode);
	while((CAN -> MOD.all) != 0x00);
	while( (CAN_GetStatus() & TranBufSt) != TranBufSt);
	/* --------- CAN Write TX buffer  ------------- */
//   CAN -> FRAMEINFO.all  = 0x08 ; 
//   CAN -> DATAINFO[0].all = 0x00 ; ///data 1
//   CAN -> DATAINFO[1].all = 0x00 ; ///data 2
//   CAN -> DATAINFO[2].all = 0x77 ; ///data 3
//   CAN -> DATAINFO[3].all = 0x00 ; ///data 4
//   CAN -> DATAINFO[4].all = 0x99 ; ///data 5
//   CAN -> DATAINFO[5].all = 0x00 ; ///data 6
//   CAN -> DATAINFO[6].all = 0xbb ; ///data 7
//   CAN -> DATAINFO[7].all = 0x00 ; ///data 8
// 	CAN -> DATAINFO[8].all = 0xdd ; ///data 8
// 	CAN -> DATAINFO[9].all = 0x00 ; ///data 8

  

	
	
	/* --------- When Trans buffer is empty,write Frame
     info to framinto buffer     ---------------- */
	//while( (CAN_GetStatus() & TranBufSt) != TranBufSt)
  //CAN -> FRAMEINFO  = 0x0f ; 
	
	/* --------- Enable CAN Tx Interrupt  --------- */

  
  //while((CAN_GetStatus() & TranBufSt) == TranBufSt);
 	CAN_SetCMD(TransReq);

	delay_us(2000);
  /* --------- Check Transmission Complete Status bit -----*/
	/* --------- Then Clear Transmission Command -------------*/
	 
	//while((CAN_GetStatus() & TranComplete) != TranComplete)
	while((CAN_GetStatus() & TranComplete) != TranComplete);
	CAN_SetCMD(TransReq);
// 	while((CAN_GetStatus() & TranComplete) == TranComplete)	
	

	
	
	/* --------- Clear Receive Buffer Status Register */
//	CAN_ClearStatus(TranSt);
 
 
  while (1)
	{
// 		//CAN_SetMode(ResetMode);
// 		CAN_SetMode(ActiveMode);
// // 			/* --------- CAN Write TX buffer  ------------- */
// //   CAN -> DATAINFO[0] = 0x55 ; ///data 1
// //   CAN -> DATAINFO[1] = 0x00 ; ///data 2
// //   CAN -> DATAINFO[2] = 0x77 ; ///data 3
// //   CAN -> DATAINFO[3] = 0x88 ; ///data 4
// //   CAN -> DATAINFO[4] = 0x99 ; ///data 5
// //   CAN -> DATAINFO[5] = 0xaa ; ///data 6
// //   CAN -> DATAINFO[6] = 0xbb ; ///data 7
// //   CAN -> DATAINFO[7] = 0xcc ; ///data 8
// // 	CAN -> DATAINFO[8] = 0xdd ; ///data 8
// // 	CAN -> DATAINFO[9] = 0xee ; ///data 8
// 	//	printf("Hello world!\r\n");
// 	while( (CAN_GetStatus() & TranBufSt) != TranBufSt);  
//   CAN -> FRAMEINFO  = 0x08 ; 
// // 		// 			/* --------- CAN Write TX buffer  ------------- */
//   CAN -> DATAINFO[0] = 0x55 ; ///data 1
//   CAN -> DATAINFO[1] = 0x00 ; ///data 2
//   CAN -> DATAINFO[2] = 0x77 ; ///data 3
//   CAN -> DATAINFO[3] = 0x00 ; ///data 4
//   CAN -> DATAINFO[4] = 0x99 ; ///data 5
//   CAN -> DATAINFO[5] = 0x00 ; ///data 6
//   CAN -> DATAINFO[6] = 0xbb ; ///data 7
//   CAN -> DATAINFO[7] = 0x00 ; ///data 8
// 	CAN -> DATAINFO[8] = 0xdd ; ///data 8
// 	CAN -> DATAINFO[9] = 0x00 ; ///data 8
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

