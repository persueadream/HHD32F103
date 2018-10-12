/*
* Copyright(C) 2018,HiWafer 
* ALL rights reserved.
*
* @file    main.c
* @author  MCU Application Team
* @version V0.1
* @date    10-october-2018
* @brief   Project for xxxx
*
*/

/* Includes ------------------------------------------------------------------*/

#include<string.h>
#include<stdio.h>
#include "hal.h"



/*--------------------------Private define-------------------------*/

#define TIM_5S        5     //100ms x 5 = 500ms

/*--------------------------Function volitale-------------------------*/

/*--------------------------Function declare-------------------------*/



/**----------------------------------------------------------------------------
** @Function:		   main
**
** @Descriptions:	   	
**
** @parameters:			
**                  
**                  
**                  
** @Returned: none
** 
** @Author:  MCU Application Team
**
** @Date: 2017-07-14
**
-------------------------------------------------------------------------------*/
int main(void)
{

	DeviceInit();
	while(1)
	{
/*start of testing*/		
#if 1
    
    //UART_Test();
		//PusleFrameInfoProcess();
		//SST25VF016B_Test();
	  //Delay_10us(100000);
	  //ADC_Test();
		//ADC_TempSensor();
		//IRC_TRIM_Print();
    //SPI_Test();
    //I2C_Test();
    //IO_ExtTest();
		// PWM_Test();
		//CAN_TransmitTest();
		//CAN_ReciveTest();
    //GPIO_Test();
		//LED_Test();
		//FlashTest();
		//delay_ms(200);
		//delay_us(2000000);


#endif
/*end of testing*/

  
	}
}



