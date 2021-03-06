/**
* Copyright(C) 2018, 
* ALL rights reserved.
*
* @file    pwm.c
* @author   MCU Application Team
* @version V0.1   MDK version:4.70.0.0
* @date    9-Mary-2018
* @brief   This file use for the hard abstract layer.
*/

#include "pwm.h"
#include "system.h"

/*----------------------------------------------------------------------------
** Function name:		PWM_IOCONFIG
**
** Descriptions:		PWM IO port configure
**
** parameters:			
**                  
**                  
**                  
** Returned value:		none
** 
** Author:  MCU Application Team
**
** Date:9-October-2018
**
-------------------------------------------------------------------------------*/
void PWM_IOCONFIG(void)
{
		#if 1						//TIM1 PWM1-PWM8 IO assignment, group 1
		TIM1_PWM1_PA7;
		TIM1_PWM2_PA8;
		TIM1_PWM3_PB0;
		TIM1_PWM4_PA9;
		TIM1_PWM5_PB1;
		TIM1_PWM6_PA10;
		TIM1_PWM7_PA11;
		TIM1_PWM8_PA12;
	
		TIM1_BKIN_PA6;
	#endif
	
	#if 0						//TIM1 PWM1-PWM8 IO assignment, group 2
		TIM1_PWM1_PB13;
		TIM1_PWM3_PB14;
		TIM1_PWM5_PB15;
	
		TIM1_BKIN_PB12;
	#endif
	
	#if 0						//TIM1 PWM1-PWM8 IO assignment, group 3
		TIM1_PWM1_PE8;
		TIM1_PWM2_PE9;
		TIM1_PWM3_PE10;
		TIM1_PWM4_PE11;
		TIM1_PWM5_PE12;
		TIM1_PWM6_PE13;
		TIM1_PWM7_PE14;
		TIM1_PWM8_PE8;
		
		TIM1_BKIN_PE15;
	#endif
	
	#if 0						//TIM8 PWM1-PWM8 IO assignment, group 1
		TIM8_PWM1_PA7;
		TIM8_PWM2_PC6;
		TIM8_PWM3_PB0;
		TIM8_PWM4_PC7;
		TIM8_PWM5_PB1;
		TIM8_PWM6_PC8;
		TIM8_PWM7_PC9;
		TIM8_PWM8_PA0;
		
		TIM8_BKIN_PA6;
	#endif
}

/*----------------------------------------------------------------------------
** Function name:		PWM_Configuration
**
** Descriptions:		PWM Configuration
**
** parameters:			
**                  
**                  
**                  
** Returned value:		none
** 
** Author:  MCU Application Team
**
** Date:9-October-2018
**
-------------------------------------------------------------------------------*/
void PWM_Configuration(void)
{
		/* ------------- Config TIM1/PWM channel I/O assignment ------------------*/
	PWM_IOCONFIG();
	
	/* ------------- initial PWM output for test -----------------------------*/
	PWM_Init(TIM1,5000,PWM_COMPLEMENT,PWM_CENTER,PWM_POSITIVE);
	
	/* ------------- Set PWM Duty --------------------------------------------*/
	PWM_SetDuty(TIM1,PWM1 | PWM2| PWM3 | PWM4 | PWM5| PWM6 ,30);
	
	/* ------------- Set deadtime --------------------------------------------*/
	PWM_SetRiseDeadZone(TIM1,2);
	PWM_SetFallDeadZone(TIM1,2);
	
	/* --------------enable PWM fault protect---------------------------------*/
	//PWM_EnableFaultProtect(TIM1,PWMFAULT,PWM_MANUAL,ENINT);
	PWM_EnableFaultProtect(TIM1,SWFAULT,PWM_MANUAL,ENINT); // 软件产生故障，手动清除故障。
	
	NVIC_EnableIRQ(TIM1FAULT_TIM9_IRQn);
	/* ------------- Start PWM timer -----------------------------------------*/
	PWM_Start(TIM1);
}



/*----------------------------------------------------------------------------
** Function name:		PWM_Test
**
** Descriptions:		PWM Test
**
** parameters:			
**                  
**                  
**                  
** Returned value:		none
** 
** Author:  MCU Application Team
**
** Date:9-October-2018
**
-------------------------------------------------------------------------------*/
void PWM_Test(void)
{
	while (1) 
	{
		sdelay_us(10);
		PWM_TriggerSoftFault(TIM1); //produce a fault
	}
}


/*----------------------------------------------------------------------------
** Function name:		TIM1FAULT_TIM9_IRQHandler
**
** Descriptions:		
**
** parameters:			
**                  
**                  
**                  
** Returned value:		none
** 
** Author:  MCU Application Team
**
** Date:9-October-2018
**
-------------------------------------------------------------------------------*/
int TIM1FAULT_TIM9_IRQHandler()
{
	PWM_ClearFault(TIM1);
	return 0;
}