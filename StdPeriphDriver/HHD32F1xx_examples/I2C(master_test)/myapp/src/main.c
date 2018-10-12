/*******************************************************************************
*	Application: Demo code for IIC using in G32F0xx
*	Edition:		Version:1.0
*	Company: 		Gorgetek
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

uint16_t temp = 0;
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
	//IIC_Init(I2C2,0,50,0x70);

	
	/* --------- Send Data to I2C slave ------------------*/
	//IIC_WriteByte(I2C1,0x70,0x80,3);
	//IIC_SlaveGetData(I2C2,0,9);

	
	while(1)
	{
		/* --------- Send Data to I2C slave ------------------*/
	  //IIC_WriteByte(I2C1,0x70,0x80,3);
	  //IIC_SlaveGetData(I2C2,0,9);
		temp = IIC_ReadByte(I2C1, 0x70, 0x00);
		temp = IIC_ReadByte(I2C1, 0x70, 0x00);
		
	}
	
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

	#if 1			//IIC2, SCL-> PB10, SDA-> PB11
	IIC2_SCL_PB10;
	IIC2_SDA_PB11;	
	#endif
	
}	


void I2C1_IRQHandler() 
{
	IIC_IRQHandler(I2C1);
	
}

void I2C2_IRQHandler() 
{
	IIC_IRQHandler(I2C2);

	
}

