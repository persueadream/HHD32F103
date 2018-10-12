/******************************************************************************
*	Application: Demo code for UART using in HHD32F1xx
*	Edition:		Version:1.0
*	Company: 		
*	Time: 			
******************************************************************************/
#include "hhd32f1xx.h"
#include "hhd_sys.h"
#include "hhd_uart.h"

void UART1_IOCFG(void);
void UART2_IOCFG(void);
void UART3_IOCFG(void);


/*****************************************************************************
* Function name:    Main Function
*
* Descriptions:     Initial device
*
* parameters:       None
* Returned value:   None
* 
*****************************************************************************/
int main(void)
{

	/* ----------- System initialization -------------------------------------*/
	SYS_SystemInitial();		

	
	/* G32F1xx has up to 5 UARTs in different part-number IC -----------------*/
	// Each Uart supports parity check mode.
	// 
	/* ---------- Set UART1 TX/RX GPIO config  -------------------------------*/
  UART1_IOCFG();
	
  /* ---------- Set Uart1 Baudrate to 115200, no parity check ------------- */
  UART_Open(UART1,115200,UART_NO_PARITY,UART_RX_NOT_EMPTY);
	
	
	/* ---------- Print sting ------------------------------------------------*/
	UART_PutString(UART1,"\tDemo system for UART!\n");
	
	

	/* ---------- Close Uart1 ------------------------------------------------*/
	UART_Close(UART1);
	
  return 0;

}

void UART1_IOCFG(void)
{
	/* you can config UART1 RX from PB7,
	and you can config UART1 TX to PB6 --------------------------------*/
	IOCON->PB6.bit.FUNC  = UART1_TX_to_PB6;
	IOCON->PB6.bit.PUE   = 1;
	IOCON->PB7.bit.FUNC  = UART1_RX_from_PB7;
	IOCON->PB7.bit.PUE   = 1;	
}

void UART2_IOCFG(void)
{
	/* you can config UART2 RX from PA3 or PD6,
	and you can config UART2 TX to PA2 or PD5 --------------------------------*/
	#if 1
	IOCON->PA2.bit.FUNC  = UART2_TX_to_PA2;
	IOCON->PA2.bit.PUE   = 1;
	IOCON->PA3.bit.FUNC  = UART2_RX_from_PA3;
	IOCON->PA3.bit.PUE   = 1;	
  #else
	IOCON->PD5.bit.FUNC  = UART2_TX_to_PD5;
	IOCON->PD5.bit.PUE   = 1;
	IOCON->PD6.bit.FUNC  = UART2_RX_from_PD6;
	IOCON->PD6.bit.PUE   = 1;	
	#endif
}

void UART3_IOCFG(void)
{
	/* you can config UART3 RX from PB11 or PD9,
	and you can config UART3 TX to PB10 or PD8 --------------------------------*/
	#if 1
	IOCON->PB10.bit.FUNC = UART3_TX_to_PB10;
	IOCON->PB10.bit.PUE  = 1;
	IOCON->PB11.bit.FUNC = UART3_RX_from_PB11;
	IOCON->PB11.bit.PUE  = 1;	
  #else
	IOCON->PD8.bit.FUNC  = UART3_TX_to_PD8;
	IOCON->PD8.bit.PUE   = 1;
	IOCON->PD9.bit.FUNC  = UART3_RX_from_PD9;
	IOCON->PD9.bit.PUE   = 1;	
	#endif
}





