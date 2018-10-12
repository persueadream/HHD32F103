/*******************************************************************************
*	Application: Demo code for IIC using in HHD32F0xx
*	Edition:		Version:1.0
*	Company: 		
*	Time: 			October 2015
*******************************************************************************/
#include "hhd32f1xx.h"
#include "hhd_sys.h"
#include "hhd_iic.h"


void IIC_IOCONFIG(void);

void delaynstep(int i)
{
	while(i--);
}

/*****************************************************************************
* Function name:    Main Function
*
* Descriptions:     IIC drive HT1621 LCD driver chip.
*
* parameters:       None
* Returned value:   None
* 
*****************************************************************************/
int main(void)
{
	//int i;
	
	/* --------- System initialization -------------------*/
	SystemInit();	
	
	/* --------- Config I2C1 AFIO assignment -------------*/
	IIC_IOCONFIG();	
	
	/* --------- IIC initiallization ---------------------*/
	IIC_Init(I2C1,1,50,0x70);
	

	
	/* --------- Send Data to I2C slave ------------------*/
	IIC_WriteByte(I2C1,0x70,0x80,3);


	
	while(1);
}


void IIC_IOCONFIG(void)
{
	#if 1			//IIC1, SCL-> PB6, SDA-> PB7
	IIC1_SCL_PB6;
	IIC1_SDA_PB7;	
	#endif

	#if 0			//IIC1, SCL-> PB8, SDA-> PB8
	IIC1_SCL_PB8;
	IIC1_SDA_PB9;	
	#endif

	#if 0			//IIC2, SCL-> PB10, SDA-> PB11
	IIC2_SCL_PB10;
	IIC2_SDA_PB11;	
	#endif
	
}	


void I2C1_IRQHandler() 
{
	IIC_IRQHandler(I2C1);
	
}


