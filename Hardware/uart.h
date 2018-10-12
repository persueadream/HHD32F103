#ifndef __USART_USER_H__
#define __USART_USER_H__

#ifdef __cplusplus
extern "C" {
#endif

#include"hhd32f1xx.h"
#include"hhd_uart.h"
#include"hhd_sys.h"

#define STAT_IDLE      0
#define STAT_DOING1    1
#define STAT_DOING2    2
#define STAT_DOING3    3
#define STAT_DOING4    4
#define STAT_DOING5    5
#define STAT_DOING6    6
#define STAT_DOING7    7
#define STAT_DOING8    8
#define STAT_RIGHT     9
#define STAT_OK        10

#define MAX_BUF_LEN_R  8






typedef struct Frame_Info_sm
{
  unsigned char stat;
  unsigned char idx;
  unsigned char buf[MAX_BUF_LEN_R];
} Frame_Info_st;

extern Frame_Info_st __frame_r;
extern void USART_Configuration(void);
extern void USART_Send_user(HHD32F1_UART_TypeDef* USARTx, u8* buffer, u32 len);
extern void frame_get( unsigned char dat );
extern void frame_analay(void);
extern void UART_Test(void);
extern void USART_Configuration(void);
#ifdef __cplusplus
}
#endif 

#endif /*__USART_USER_H__*/


/******************* (C) COPYRIGHT 2015  *****END OF FILE****/





