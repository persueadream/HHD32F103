#include"PWM_user.h"

#define SystemCoreClock_100KHZ (SystemCoreClock/720)



/*----------------------------------------------------------------------------
** Function name:		TIM3_PWM_Init
**
** Descriptions:		TIM3_PWM Configer Initial,TIM3_CH2(PB5) outpur PWM wave.
**
** parameters:			arr->period, psc->prescaler
**                  
**                  
**                  
** Returned value:		none
** 
** Author: wangkui
**
** Date:2015-4-2
**
-------------------------------------------------------------------------------*/
void TIM3_PWM_Init_user(u16 arr, u16 psc)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE);
	
	/*重映射 TIM3_CH2->PB5*/
	GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5; //TIM_CH2
	/*复用推挽输出*/
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	/*初始化GPIO*/
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	
	//初始化TIM3
	TIM_TimeBaseStructure.TIM_Period = arr;
	TIM_TimeBaseStructure.TIM_Prescaler = psc;
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
	
	//初始TIM3 Channel2 PWM模式
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;
	TIM_OC2Init(TIM3, &TIM_OCInitStructure);	
	
	/*使能预装载寄存器*/
	TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);
	TIM_Cmd(TIM3, ENABLE); //
	
}
/*----------------------------------------------------------------------------
** Function name:		TIM1_PWM_Init
**
** Descriptions:		TIM1_PWM Configer Initial,7 PWM output
**
** parameters:			
**                  
**                  
**                  
** Returned value:		none
** 
** Author: wangkui
**
** Date:2015-4-2
**
-------------------------------------------------------------------------------*/


void TIM1_PWM_Init_user(void)
{
	 NVIC_InitTypeDef NVIC_InitStructure;
	 GPIO_InitTypeDef GPIO_InitStructure;
	 TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	 TIM_OCInitTypeDef  TIM_OCInitStructure;
	 uint16_t TimerPeriod = 0;
	 uint16_t Channel1Pulse = 0, Channel2Pulse = 0, Channel3Pulse = 0, Channel4Pulse = 0;
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1 | RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOE|
                         RCC_APB2Periph_GPIOB |RCC_APB2Periph_AFIO, ENABLE);
	
	  


  /* GPIOA Configuration: Channel 1, 2 and 3 as alternate function push-pull */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  /* GPIOB Configuration: Channel 1N, 2N and 3N as alternate function push-pull */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	  /* TIM1 Configuration ---------------------------------------------------
   Generate 7 PWM signals with 4 different duty cycles:
   TIM1CLK = SystemCoreClock, Prescaler = 0, TIM1 counter clock = SystemCoreClock
   SystemCoreClock is set to 72 MHz for Low-density, Medium-density, High-density
   and Connectivity line devices and to 24 MHz for Low-Density Value line and
   Medium-Density Value line devices
   
   The objective is to generate 7 PWM signal at 300 KHz:
     - TIM1_Period = (SystemCoreClock / 300) - 1
   The channel 1 and channel 1N duty cycle is set to 50%
   The channel 2 and channel 2N duty cycle is set to 37.5%
   The channel 3 and channel 3N duty cycle is set to 25%
   The channel 4 duty cycle is set to 12.5%
   The Timer pulse is calculated as follows:
     - ChannelxPulse = DutyCycle * (TIM1_Period - 1) / 100
  ----------------------------------------------------------------------- */
  /* Compute the value to be set in ARR regiter to generate signal frequency at 17.57 Khz */
  TimerPeriod = (SystemCoreClock_100KHZ / 1000 ) - 1;//从0开始计数所以需要减1
  /* Compute CCR1 value to generate a duty cycle at 50% for channel 1 and 1N */
  Channel1Pulse = (uint16_t) (((uint32_t) 5 * (TimerPeriod - 1)) / 10);
  /* Compute CCR2 value to generate a duty cycle at 37.5%  for channel 2 and 2N */
  Channel2Pulse = (uint16_t) (((uint32_t) 5 * (TimerPeriod - 1)) / 10);
  /* Compute CCR3 value to generate a duty cycle at 25%  for channel 3 and 3N */
  Channel3Pulse = (uint16_t) (((uint32_t) 50 * (TimerPeriod - 1)) / 100);

  /* Compute CCR4 value to generate a duty cycle at 12.5%  for channel 4 */
  Channel4Pulse = (uint16_t) (((uint32_t) 125 * (TimerPeriod- 1)) / 1000);

  /* Time Base configuration */
  TIM_TimeBaseStructure.TIM_Prescaler = 719;
	/* 向上计数*/
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseStructure.TIM_Period = TimerPeriod;
  TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	/*重复计数器值设置为100*/
  TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;

  TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);

  /* Channel 1, 2,3 and 4 Configuration in PWM mode */
	/*PWM2模式，TIMx_CNT < TIMx_CCRx时,通道x(1,2,3,4)为无效电平，否则为有效电平*/
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable;
  TIM_OCInitStructure.TIM_Pulse = Channel1Pulse;
	/*OC1低电平有效*/
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;
	/*OC1N高电平有效*/
  TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;
	/*当MOE=0时，死区后OC1/OC1N=0 */
	/*当MOE=1时，死区后OC1/OC1N=1 */
  TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Reset;
  TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCIdleState_Reset;

  TIM_OC1Init(TIM1, &TIM_OCInitStructure);

  TIM_OCInitStructure.TIM_Pulse = Channel2Pulse;
  TIM_OC2Init(TIM1, &TIM_OCInitStructure);

  TIM_OCInitStructure.TIM_Pulse = Channel3Pulse;
  TIM_OC3Init(TIM1, &TIM_OCInitStructure);

  TIM_OCInitStructure.TIM_Pulse = Channel4Pulse;
  TIM_OC4Init(TIM1, &TIM_OCInitStructure);
	
	/*输出比较器使能预装载(OCxPE)*/
	TIM_OC3PreloadConfig(TIM1, TIM_OCPreload_Enable);
	
	/*自动重装载预装载使能(ARPE)*/
  TIM_ARRPreloadConfig(TIM1,ENABLE);
  //开启更新中断
//	TIM_ITConfig(TIM1, TIM_IT_Update, ENABLE);
	
  /*中断优先级NVIC设置*/
	NVIC_InitStructure.NVIC_IRQChannel = TIM1_UP_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
 
  /* TIM1 counter enable */
  //TIM_Cmd(TIM1, ENABLE);

  /* TIM1 Main Output Enable */
  TIM_CtrlPWMOutputs(TIM1, ENABLE);


}


/*----------------------------------------------------------------------------
** Function name:		TIM8_PWM_Init
**
** Descriptions:		TIM8_PWM Configer Initial,7 PWM output
**
** parameters:			
**                  
**                  
**                  
** Returned value:		none
** 
** Author: wangkui
**
** Date:2015-4-2
**
-------------------------------------------------------------------------------*/


void TIM8_PWM_Init_user(void)
{
		NVIC_InitTypeDef NVIC_InitStructure;
	 GPIO_InitTypeDef GPIO_InitStructure;
	 TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	 TIM_OCInitTypeDef  TIM_OCInitStructure;
	 uint16_t TimerPeriod = 0;
	 uint16_t Channel1Pulse = 0, Channel2Pulse = 0, Channel3Pulse = 0, Channel4Pulse = 0;
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8 | RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOA|
                         RCC_APB2Periph_GPIOB |RCC_APB2Periph_AFIO, ENABLE);
	
	  


  /* GPIOC Configuration: Channel 1, 2, 3 and 4 as alternate function push-pull */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8| GPIO_Pin_9;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOC, &GPIO_InitStructure);

  /* GPIOB Configuration: Channel 2N and 3N as alternate function push-pull */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	/* GPIOB Configuration: Channel 1N  as alternate function push-pull */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	  /* TIM1 Configuration ---------------------------------------------------
   Generate 7 PWM signals with 4 different duty cycles:
   TIM1CLK = SystemCoreClock, Prescaler = 0, TIM8 counter clock = SystemCoreClock
   SystemCoreClock is set to 72 MHz for Low-density, Medium-density, High-density
   and Connectivity line devices and to 24 MHz for Low-Density Value line and
   Medium-Density Value line devices
   
   The objective is to generate 7 PWM signal at 300 KHz:
     - TIM1_Period = (SystemCoreClock / 300) - 1
   The channel 1 and channel 1N duty cycle is set to 50%
   The channel 2 and channel 2N duty cycle is set to 37.5%
   The channel 3 and channel 3N duty cycle is set to 25%
   The channel 4 duty cycle is set to 12.5%
   The Timer pulse is calculated as follows:
     - ChannelxPulse = DutyCycle * (TIM8_Period - 1) / 100
  ----------------------------------------------------------------------- */
  /* Compute the value to be set in ARR regiter to generate signal frequency at 17.57 Khz */
  TimerPeriod = (SystemCoreClock_100KHZ / 2000 ) - 1;//从0开始计数所以需要减1
  /* Compute CCR1 value to generate a duty cycle at 50% for channel 1 and 1N */
  Channel1Pulse = (uint16_t) (((uint32_t) 5 * (TimerPeriod - 1)) / 10);
  /* Compute CCR2 value to generate a duty cycle at 37.5%  for channel 2 and 2N */
  Channel2Pulse = (uint16_t) (((uint32_t) 5 * (TimerPeriod - 1)) / 10);
  /* Compute CCR3 value to generate a duty cycle at 25%  for channel 3 and 3N */
  Channel3Pulse = (uint16_t) (((uint32_t) 50 * (TimerPeriod - 1)) / 100);

  /* Compute CCR4 value to generate a duty cycle at 12.5%  for channel 4 */
  Channel4Pulse = (uint16_t) (((uint32_t) 125 * (TimerPeriod- 1)) / 1000);

  /* Time Base configuration */
  TIM_TimeBaseStructure.TIM_Prescaler = 719;
	/* 向上计数*/
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseStructure.TIM_Period = TimerPeriod;
  TIM_TimeBaseStructure.TIM_ClockDivision = 0;
  TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;

  TIM_TimeBaseInit(TIM8, &TIM_TimeBaseStructure);

  /* Channel 1, 2,3 and 4 Configuration in PWM mode */
	/*PWM2模式，TIMx_CNT < TIMx_CCRx时,通道x(1,2,3,4)为无效电平，否则为有效电平*/
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable;
  TIM_OCInitStructure.TIM_Pulse = Channel1Pulse;
	/*OC1低电平有效*/
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;
	/*OC1N高电平有效*/
  TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;
	/*当MOE=0时，死区后OC1/OC1N=0 */
	/*当MOE=1时，死区后OC1/OC1N=1 */
  TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Reset;
  TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCIdleState_Reset;

  TIM_OC1Init(TIM8, &TIM_OCInitStructure);

  TIM_OCInitStructure.TIM_Pulse = Channel2Pulse;
  TIM_OC2Init(TIM8, &TIM_OCInitStructure);

  TIM_OCInitStructure.TIM_Pulse = Channel3Pulse;
  TIM_OC3Init(TIM8, &TIM_OCInitStructure);

  TIM_OCInitStructure.TIM_Pulse = Channel4Pulse;
  TIM_OC4Init(TIM8, &TIM_OCInitStructure);
	
	/*输出比较器使能预装载(OCxPE)*/
	TIM_OC3PreloadConfig(TIM8, TIM_OCPreload_Enable);
	
	/*自动重装载预装载使能(ARPE)*/
  TIM_ARRPreloadConfig(TIM8,ENABLE);
  
	  //开启更新中断
	//TIM_ITConfig(TIM8, TIM_IT_Update, ENABLE);
	
  /*中断优先级NVIC设置*/
	NVIC_InitStructure.NVIC_IRQChannel = TIM8_UP_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
 
 
  /* TIM8 counter enable */
  //TIM_Cmd(TIM8, ENABLE);

  /* TIM8 Main Output Enable */
  TIM_CtrlPWMOutputs(TIM8, ENABLE);


}




/*----------------------------------------------------------------------------
** Function name:		Set_PWM_Frequecny_Period_user
**
** Descriptions:		TIM1_PWM Configer Initial,7 PWM output
**
** parameters:			DutyCycle: 50,50%
**                  CompareNo: 1,2,3,4
**                  Frequency: 
**                  TIMx:TIM1~TIM8
**                  
** Returned value:		none
** 
** Author: wangkui
**
** Date:2015-4-2
**
-------------------------------------------------------------------------------*/
void Set_PWM_Frequecny_Period_user(TIM_TypeDef* TIMx, uint32_t Frequency, uint16_t CompareNo, uint16_t DutyCycle)
{
	uint16_t TPeriod = 0;
	uint16_t Pulse = 0;
	/* 周期 */
	TPeriod = (SystemCoreClock_100KHZ / Frequency ) - 1;
	/*设置周期*/
	TIM_SetAutoreload(TIMx, TPeriod);
	/*设置占空比*/
	Pulse = (uint16_t) (((uint32_t) DutyCycle * (TPeriod - 1)) / 100);
	/*CompareNo is 1,2,3,4*/
	if((CompareNo > 0) && (CompareNo < 5))
	{
		switch(CompareNo)
		{
			case 1: TIM_SetCompare1(TIMx, Pulse);
			        break;
			case 2: TIM_SetCompare2(TIMx, Pulse);
			        break;
			case 3: TIM_SetCompare3(TIMx, Pulse);
			        break;
			case 4: TIM_SetCompare4(TIMx, Pulse);
			        break;
			default:break;
		}
	}
}

