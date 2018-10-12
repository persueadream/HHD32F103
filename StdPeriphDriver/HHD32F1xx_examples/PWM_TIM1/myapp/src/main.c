/*******************************************************************************
*	Application: Demo code for PWM using in HHD32F0xx
*	Edition:		Version:1.0
*	Company: 		
*	Time: 			September 2015
*******************************************************************************/
#include "hhd32f1xx.h"
#include "hhd_pwm.h"
#include "hhd_sys.h"

void PWM_IOCONFIG(void);
void delay1us();
//#define ENABLE_PWM
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
	/* ------------- System initialization -----------------------------------*/
	SystemInit();	
//	(*SYSCON).RCCCFGR.bit.PCLK2SEL=1;
	HHD_AFIO->PA5  = 0x230;
	HHD_GPIOA->DIR |= 1<<5;
	
	/* ------------- Config TIM1/PWM channel I/O assignment ------------------*/
	PWM_IOCONFIG();
	
	/* ------------- initial PWM output for test -----------------------------*/
	PWM_Init(TIM1,5000,PWM_COMPLEMENT,PWM_CENTER,PWM_POSITIVE);
	
	/* ------------- Set PWM Duty --------------------------------------------*/
	PWM_SetDuty(TIM1,PWM1|PWM2|PWM3|PWM4|PWM5|PWM6,40);
	
	/* ------------- Set deadtime --------------------------------------------*/
	
	/* --------------enable PWM fault protect---------------------------------*/

	/* --------------enable PWM interrupt    ---------------------------------*/
	PWM_EnableInt(TIM1,PWM_HALFINT);
	NVIC_EnableIRQ(TIM1_IRQn);
	/* --------------Set reload requency    ---------------------------------*/
	PWM_SetRelaodFreq(TIM1,1);
	/* ------------- Start PWM timer -----------------------------------------*/
	PWM_Start(TIM1);

	while (1) 
	{
		delay1us(10);

	}
}

int TIM1_IRQHandler()
{
	HHD_TIM1->CTRL &=~(1<<2);
	HHD_GPIOA->NOT=1<<5;
	return 0;
}

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

void delay1us(int dly)
{
	int i;
	while(dly--)
	{
		i=100;
		while(i--);
	}
}

