/*******************************************************************************
*	Application: Demo code for GPIO using in HHD32F1xx
*	Edition:		Version:1.0
*	Company: 		
*	Time: 			
*******************************************************************************/
#include "hhd32f1xx.h"
#include "hhd_sys.h"
#include "hhd_gpio.h"
#include "hhd_timer.h"


void dly1us(int dlytime);
void TmrPWMInit( void );
/*****************************************************************************
* Function name:    Main Function
*
* Descriptions:     Initial device
*
* parameters:       None
* Returned value:   None
* 
*****************************************************************************/
#define	C_WORK_IDLE				0
#define	C_WORK_ACTIVE			1

#define	C_WORK_L					0
#define	C_WORK_M					1
#define	C_WORK_H					2

#define	C_MODE_KEY				PIN0
#define	C_SPEED_KEY				PIN1
#define F75MS			8000/2
#define F200MS			22000/2
#define F500MS			44000/2
void savesetting(unsigned int state);

int main(void)
{
	char WorkState = C_WORK_ACTIVE;
	char SpeedState = C_WORK_M;
	unsigned int TmrCnt=0;
	char KeyTmr=0;
	int InputBak, KeyState;
	int Temp1,Temp2,i;
	/* --------- System initialization ------------------*/
	SYS_SystemInitial();	
	
  /* --------- GPIOA Periph clock enable --------------*/
  ENABLEGPIOACLK;
	
	

	
	SYS_ResetDeepSleepWakeupPin();

  /* --------- Configure PA6 as output pushpull mode --*/	
//	GPIO_ConfigPinsAsOutput(GPIOA,PIN6);
	IOCON->PA6.bit.FUNC = 1;			//TIM3_CH1
	GPIO_ConfigPinsAsOutput(GPIOA,PIN6);
	GPIOA->DIR.all |= (1<<6);
	GPIOA->CLR.all |= (1<<6);
	
	GPIO_ConfigPinsAsInput(GPIOA, PIN0|PIN1);
	SYSCON->IOCONFIGCLKDIV.bit.DIV=127;
	IOCON->PA0.bit.S_MODE  =1;
	IOCON->PA1.bit.S_MODE  =1;
	
	
	TIM_Init(TIM3,1000000UL);
	TIM_RESET(TIM3);
	TmrPWMInit();

//init status
	if((*(unsigned int*)0x2000)==0xffffffff)
	{
		InputBak=C_MODE_KEY;
	}
	else
	{
		for(i=0;i<512;i+=4)
		{
			if((*(unsigned int*)(0x2000+i))!=0xffffffff)
			{
				if((*(unsigned int*)(0x2000+i+4))==0xffffffff)
				{
					WorkState=(*(unsigned int*)(0x2000+i))>>16;
					SpeedState=(*(unsigned int*)(0x2000+i))&0xff;

					if(WorkState==C_WORK_IDLE)
						InputBak=0;
					else
						InputBak=C_MODE_KEY;
					
						if(SpeedState==0)
						{
							TIM3->MR3.all=F75MS;
							TIM3->MR0.all=F75MS/2;
						}
						else if(SpeedState==2)
						{
							TIM3->MR3.all=F500MS;
							TIM3->MR0.all=F500MS/2;
						}
						else
						{
							SpeedState=1;
							TIM3->MR3.all=F200MS;
							TIM3->MR0.all=F200MS/2;
						}
							
				}
			}
		}
	}
	TIM_START(TIM3);
 
	while(1)
	{
		dly1us(2630);																				//1mS
				KeyTmr++;
				if(KeyTmr==100)
				{
					KeyTmr = 0;
					KeyState = GPIO_GetPortState(GPIOA);
					Temp1 = (InputBak^KeyState)&KeyState;  //InputBak;
					Temp2 = (InputBak^KeyState)&InputBak;
					if(Temp1&C_MODE_KEY)
					{
//						WorkState = C_WORK_IDLE;
						TmrCnt = 0;
						//GPIO_ResetPin(GPIOA,PIN2);
						TIM_STOP(TIM3);
						IOCON->PA6.bit.FUNC=0;			//TIM3_MAT0
						//dly1us(10000);
						//SYS_ResetDeepSleepWakeupPin();
						SYS_SetDeepSleepWakeupPin(C_MODE_KEY, FALL_EDGE);		  // ¿ªÆôIO»½ÐÑ
						
						savesetting(0x00000+SpeedState);
						SYS_EnterDeepSleep(0,0);	// ½øÈëË¯Ãß
						//SYS_ResetDeepSleepWakeupPin();											// ¹Ø±ÕIO»½ÐÑ
						IOCON->PA6.bit.FUNC=1;			//TIM3_CH1
						savesetting(0x10000+SpeedState);
						TIM_START(TIM3);
					}
					else if(Temp2&C_SPEED_KEY)
					{
						SpeedState++;
						if(SpeedState>=3)
							SpeedState=0;
						if(SpeedState==0)
						{
							TIM3->TC.all=0;
							TIM3->MR3.all=F75MS;
							TIM3->MR0.all=F75MS/2;
						}
						if(SpeedState==1)
						{
							TIM3->MR3.all=F200MS;
							TIM3->MR0.all=F200MS/2;
						}
						if(SpeedState==2)
						{
							
							TIM3->MR3.all=F500MS;
							TIM3->MR0.all=F500MS/2;
						}
						savesetting(0x10000+SpeedState);
					}
					InputBak = KeyState;
				}	
				
				TmrCnt++;

	//		break;
		}
	
}

void dly1us(int dlytime) 
{
 while(dlytime--);
}

void TmrPWMInit( void )
{
	TIM3->CTCR.all 	=	0x800;
	TIM3->MR3.all		=	F200MS;
	TIM3->MR0.all		=	F200MS/2;
	TIM3->PWMC.all 	= 0xf;
	TIM3->PR.all 		=	300;
}
void WAKEUP_IRQHandler()
{
	SYS_ResetDeepSleepWakeupPin();
}


#define PROGCMDMASK		0x02			//32 bit flash programming coomand mask
#define ERASECMDMASK	0x04			//sector erase command mask
#define PROGSTATMASK	0x100			//flash program state mask
#define MAXFLASHSIZE	0x100000	//max flash size		 

void EraseSector (void) {

  HHD_FMC->FLASHADDR = 0x2000;								   					//set sector address to be erased
	HHD_FMC->FLASHCTRL = ERASECMDMASK;			 							  //issue erase cmd
  while ((HHD_FMC->FLASHCTRL & PROGSTATMASK)!=0);			  //wait until erase is done
}

void savesetting(unsigned int state)
{
	int i;
	for(i=0;i<512;i+=4)
	{
		if((*(unsigned int*)(0x2000+i))==0xffffffff)
		{
			HHD_FMC->FLASHADDR = 0x2000+i;				  		//address
			HHD_FMC->PRGDATA   = state;								//data
			HHD_FMC->FLASHCTRL = PROGCMDMASK;          //command
			while ((HHD_FMC->FLASHCTRL & PROGSTATMASK)!=0);	 //wait for programming done
			return;
		}
	}

	EraseSector();
	HHD_FMC->FLASHADDR = 0x2000;				  					//address
	HHD_FMC->PRGDATA 	= state;										//data
	HHD_FMC->FLASHCTRL = PROGCMDMASK;           		//command
	while ((HHD_FMC->FLASHCTRL & PROGSTATMASK)!=0);	 				//wait for programming done
	return;
	
}

