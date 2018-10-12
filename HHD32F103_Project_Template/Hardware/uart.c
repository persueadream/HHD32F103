#include "uart.h"
#include "system.h"
//#include "task.h"


#define S_LEN                     11        //传输数据长度


#ifdef __GNUC__
  /* With GCC/RAISONANCE, small printf (option LD Linker->Libraries->Small printf
     set to 'Yes') calls __io_putchar() */
  #define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
  #define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */

/*--------------------------------全局变量------------------------------------*/


/* 串口接收帧信息包 */
Frame_Info_st __frame_r={STAT_IDLE,0,{0,0,0,0,0,0,0,0}};

uint8_t SendBuffer[S_LEN] = {0xDD,0,0,0,0,0,0,0,0,0,0xCC};


/* Private function prototypes -----------------------------------------------*/
void USARTInit_user(void);
void USART_Send_user(HHD32F1_UART_TypeDef* USARTx, u8* buffer, u32 len);
void frame_get( unsigned char dat );
void frame_analay(void);
void UART1_IOCFG(void);
void UART2_IOCFG(void);
void UART3_IOCFG(void);
void UART_Test(void);



/*----------------------------------------------------------------------------
** Function name:		USART_Configuration
**
** Descriptions:		USART Configer Initial
**
** parameters:			
**                  
**                  
**                  
** Returned value:		none
** 
** Author:  MCU Application Team
**
** Date:9-June-2015
**
-------------------------------------------------------------------------------*/
void USART_Configuration(void)
{
	/* ---------- Set UART1 TX/RX GPIO config  -------------------------------*/
 UART1_IOCFG();
//	UART2_IOCFG();
//UART3_IOCFG();
	/* ---------- Set Uart1 Baudrate to 115200, no parity check ------------- */
 UART_Open(UART1,115200,UART_NO_PARITY, UART_RX_NOT_EMPTY);
  //	UART_Open(UART2,115200,UART_NO_PARITY,UART_RX_NOT_EMPTY);
  //UART_Open(UART3,115200,UART_NO_PARITY,UART_RX_NOT_EMPTY);
	
	/*使能接收中断*/
  //UART_EnableInt(UART1, UART_RX_HALF_FULL); RXHLFINT
  //UART_EnableInt(UART1, UART_RX_NOT_EMPTY | UART_PARIERRINT | UART_OVERRUNINT);
	UART_EnableInt(UART1, UART_RX_NOT_EMPTY);
  //	UART_EnableInt(UART2, UART_RX_NOT_EMPTY);
  //UART_EnableInt(UART3, UART_RX_NOT_EMPTY);
	NVIC_EnableIRQ(UART1_IRQn);
	//NVIC_EnableIRQ(UART2_IRQn);
  //NVIC_EnableIRQ(UART3_IRQn);

}
/*----------------------------------------------------------------------------
** Function name:		USART_Send_user
**
** Descriptions:		Data send
**
** parameters:			
**                  
**                  
**                  
** Returned value:		none
** 
** Author:  MCU Application Team
**
** Date:9-June-2015
**
-------------------------------------------------------------------------------*/
void USART_Send_user(HHD32F1_UART_TypeDef* USARTx, u8* buffer, u32 len)
{
// 	u32 i = 0;
// 	for(i=0; i<len; i++)
// 	{
// 		while(USART_GetITStatus(USART2, USART_FLAG_RXNE) != RESET);
// 		USART_SendData(USARTx, (uint8_t)*(buffer+i)); /*发送一个字符函数*/ 
// 		/* Loop until the end of transmission */
// 		while (USART_GetFlagStatus(USARTx, USART_FLAG_TC) == RESET)/*等待发送完成*/
// 		{
// 		
// 		}
// 	}

}

/*----------------------------------------------------------------------------
** Function name:		frame_get
**
** Descriptions:		帧数据获得
**
** parameters:			
**                  
**                  
**                  
** Returned value:		none
** 
** Author:  MCU Application Team
**
** Date:9-June-2015
**
-------------------------------------------------------------------------------*/
void frame_get( unsigned char dat )
{
 
	switch (__frame_r.stat)
	{
		case STAT_IDLE : 
			{
			    if(dat == 0xFF)
				{
					__frame_r.stat = STAT_IDLE;
				}
				else
				{
					if( dat == 0 )
					  {
					    __frame_r.idx=0;	    
						__frame_r.buf[__frame_r.idx] = dat;
						__frame_r.stat = STAT_DOING1;
					  }
				}
				break;
			}
		case STAT_DOING1:
			{

			   	__frame_r.idx = 1;
				__frame_r.buf[__frame_r.idx] = dat;			      
	      	   	__frame_r.stat = STAT_DOING2;	
					
				break;

			}

        case STAT_DOING2:
			{
				__frame_r.idx = 2;
				__frame_r.buf[__frame_r.idx] = dat;			      
	      	    __frame_r.stat = STAT_DOING3;	
			
				break;

			}
       	case STAT_DOING3:
			{

			    __frame_r.idx = 3;
				__frame_r.buf[__frame_r.idx] = dat;			      
	      	    __frame_r.stat = STAT_DOING4;	
				break;

			}
       	case STAT_DOING4:
			{

			    __frame_r.idx = 4;
				__frame_r.buf[__frame_r.idx] = dat;			      
	      	    __frame_r.stat = STAT_DOING5;	
				break;

			}
        case STAT_DOING5:
			{
			    __frame_r.idx = 5;
				__frame_r.buf[__frame_r.idx] = dat;			      
	      	    __frame_r.stat = STAT_DOING6;	
				break;
			
			}  
	    case STAT_DOING6:
			{
			    __frame_r.idx = 6;
				__frame_r.buf[__frame_r.idx] = dat;			      
	      	    __frame_r.stat = STAT_RIGHT;	
				break;
			
			}  
		case STAT_RIGHT:
			{
				if(dat == 0xFF)
				{
					__frame_r.idx = 7;
					__frame_r.buf[__frame_r.idx] = dat;
					__frame_r.stat = STAT_OK;

				}
				break;
			}
		default:
			{
				break;
			}
	}		
 
  
}



/*----------------------------------------------------------------------------
** Function name:		frame_analay
**
** Descriptions:		帧数据分析
**
** parameters:			
**                  
**                  
**                  
** Returned value:		none
** 
** Author:  MCU Application Team
**
** Date:9-June-2015
**
-------------------------------------------------------------------------------*/
void frame_analay(void)
{
//	uint16_t value = 0;
// 	unsigned char m=0;
// 	unsigned char	n=0, o=0, p=0, q=0, r=0, s=0, t=0;
// 	//uint8_t tBuffer[8] = {0,0,0,0,0,0,0,0};
// 	m=__frame_r.buf[0]; //头
// 	n=__frame_r.buf[1]; //动作
// 	o=__frame_r.buf[2]; //数据
// 	p=__frame_r.buf[3]; 
// 	q=__frame_r.buf[4];
// 	r=__frame_r.buf[5];
// 	s=__frame_r.buf[6];
// 	t=__frame_r.buf[7]; //尾
// //	tBuffer[0] = m;
// //	tBuffer[1] = n;
// //	tBuffer[2] = o;
// //	tBuffer[3] = p;
// //	tBuffer[4] = q;
// //	tBuffer[5] = r;
// //	tBuffer[6] = s;
// //	tBuffer[7] = t;
// 	switch (m)
// 	{
// 		default:break;
// 	}
}


/**----------------------------------------------------------------------------
** @Function:		   UART1_IOCFG
**
** @Descriptions:	 UART GPIO Configuration  	
**
** @parameters:			
**                  
**                  
**                  
** @Returned: none
** 
** @Author:  MCU Application Team
**
** @Date: 28-June-2017
**
-------------------------------------------------------------------------------*/
void UART1_IOCFG(void)
{
	/* you can config UART1 RX from PB7,
	and you can config UART1 TX to PB6 --------------------------------*/
	#if 0
	IOCON->PB6.bit.FUNC  = UART1_TX_to_PB6;
	IOCON->PB6.bit.PUE   = 1;
	IOCON->PB7.bit.FUNC  = UART1_RX_from_PB7;
	IOCON->PB7.bit.PUE   = 1;	
	
 #else
	IOCON->PA9.bit.FUNC  = UART1_TX_to_PA9;
	IOCON->PA9.bit.PUE   = 1;
	IOCON->PA10.bit.FUNC = UART1_RX_from_PA10;
	IOCON->PA10.bit.PUE  = 1;	
	#endif
}

/**----------------------------------------------------------------------------
** @Function:		   UART2_IOCFG
**
** @Descriptions:	 UART GPIO Configuration  	
**
** @parameters:			
**                  
**                  
**                  
** @Returned: none
** 
** @Author:  MCU Application Team
**
** @Date: 28-June-2017
**
-------------------------------------------------------------------------------*/
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

/**----------------------------------------------------------------------------
** @Function:		   UART3_IOCFG
**
** @Descriptions:	 UART GPIO Configuration  	
**
** @parameters:			
**                  
**                  
**                  
** @Returned: none
** 
** @Author:  MCU Application Team
**
** @Date: 28-June-2017
**
-------------------------------------------------------------------------------*/
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

/**----------------------------------------------------------------------------
** @Function:		   UART_Test
**
** @Descriptions:	 UART test
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
void UART_Test(void)
{

 		sdelay_us(2000000);
	  DEBUG("Uart Testing!\r\n");

}


/**
  * @brief  Retargets the C library printf function to the USART.
  * @param  None
  * @retval None
  */
PUTCHAR_PROTOTYPE
{
  /* Place your implementation of fputc here */
  /* e.g. write a character to the USART */
 // USART_SendData(USART1, (uint8_t) ch); /*发送一个字符函数*/ 
	UART_ByteWrite(UART1, (uint8_t) ch);

  /* Loop until the end of transmission */
	while((UART_GetStatus(UART1) & UART_TX_EMPTY) == 1 )
	{}
//  while (USART_GetFlagStatus(UART1, USART_FLAG_TC) == RESET)/*等待发送完成*/
//  {
//  
//  }
  return ch;
}

/**----------------------------------------------------------------------------
** @Function:		   UART1_IRQHandler
**
** @Descriptions:	 UART1 interrupt
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
void UART1_IRQHandler()
{
		unsigned char recv = 0;
//		uint8_t datalen = 16;
		if(UART1->INTSTATUS.bit.RXNEINT == 1)
		{
			UART_ByteRead(UART1, &recv);
			//UartOneReciveDataProcess(recv);
			UART_ByteWrite(UART1, recv);
			while((UART_GetStatus(UART1) & UART_TX_EMPTY) == 1 )
			{;}
		}
		if(UART1->INTSTATUS.bit.PARIERRINT == 1)
		{
			
			UART_ByteRead(UART1, &recv);
			
			//UartOneReciveDataProcess(recv);
			UART_ByteWrite(UART1, recv);
			while((UART_GetStatus(UART1) & UART_TX_EMPTY) == 1 )
			{;}
			UART_ClearIntFlag(UART1);
		}
}


/**----------------------------------------------------------------------------
** @Function:		   UART2_IRQHandler
**
** @Descriptions:	 UART2 interrupt
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
void UART2_IRQHandler()
{
		unsigned char recv = 0;
//		uint8_t datalen = 16;
		if(UART2->INTSTATUS.bit.RXNEINT == 1)
		{
			UART_ByteRead(UART2, &recv);
			UART_ByteWrite(UART2, recv);
			while((UART_GetStatus(UART2) & UART_TX_EMPTY) == 1 )
			{;}
		}
}

/**----------------------------------------------------------------------------
** @Function:		   UART3_IRQHandler
**
** @Descriptions:	 UART3 interrupt
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
void UART3_IRQHandler()
{
		unsigned char recv = 0;
//		uint8_t datalen = 16;
		if(UART3->INTSTATUS.bit.RXNEINT == 1)
		{
			UART_ByteRead(UART3, &recv);
			UART_ByteWrite(UART3, recv);
			while((UART_GetStatus(UART3) & UART_TX_EMPTY) == 1 )
			{;}
		}
}
