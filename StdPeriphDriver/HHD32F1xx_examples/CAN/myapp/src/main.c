
#include "hhd32f1xx.h"
#include "hhd_sys.h"
#include "hhd_can.h"

void CAN_IRQHandler()
{
			int i;

      if((HHD_CAN->RXFIFO[3] ==0)&(HHD_CAN->RXFIFO[4] ==1)&(HHD_CAN->RXFIFO[5] ==2)&(HHD_CAN->RXFIFO[6] ==3)&(HHD_CAN->RXFIFO[7] ==4)&(HHD_CAN->RXFIFO[8] ==5)&(HHD_CAN->RXFIFO[9] ==6))
      { 
          //Uart_PutStr("can ok\n");
          HHD_CAN -> SR  = 0x12345678 ;                   
			}
      else
      {
          i = HHD_CAN->RXFIFO[6] ;
          HHD_CAN -> MOD  = i ;                   
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

int main (void)
{

	
	/* --------- System Initialization  ----------- */
  /* 系统初始化后，MCU运行在72M时钟  -------------*/
  SYS_SystemInitial();


	/* --------- Enable CAN Clock  ---------------- */
  ENABLECAN1CLK;


	/* --------- Enable CAN Rx Interrupt  --------- */
	CAN_EnableInt(RIE);

	
  /* --------- CAN IO config  ------------------- */
  CAN_IOCONFIG();


	
	/* --------- CAN Write TX buffer  ------------- */
  HHD_CAN -> DATAINFO[0] = 0x0 ; ///data 1
  HHD_CAN -> DATAINFO[1] = 0x1 ; ///data 2
  HHD_CAN -> DATAINFO[2] = 0x2 ; ///data 3
  HHD_CAN -> DATAINFO[3] = 0x3 ; ///data 4
  HHD_CAN -> DATAINFO[4] = 0x4 ; ///data 5
  HHD_CAN -> DATAINFO[5] = 0x5 ; ///data 6
  HHD_CAN -> DATAINFO[6] = 0x6 ; ///data 7
  HHD_CAN -> DATAINFO[7] = 0x7 ; ///data 8


	/* --------- CAN Mode Config  ---------------- */
	CAN_SetMode(ActiveMode);
	
	
	
	/* --------- When Trans buffer is empty,write Frame
     info to framinto buffer     ---------------- */
	while( (CAN_GetStatus() & TranBufSt) != TranBufSt);  
  HHD_CAN -> FRAMEINFO  = 0x0f ; 
	


  /* --------- Check Transmission Complete Status bit -----*/
	/* --------- Then Clear Transmission Command -------------*/
	while((CAN_GetStatus() & TranComplete) == TranComplete)
		
	CAN_ClrCMD(TransReq);
	
	
	/* --------- Clear Receive Buffer Status Register */
	CAN_ClearStatus(TranSt);
 
 
  while (1); 
	 
}

