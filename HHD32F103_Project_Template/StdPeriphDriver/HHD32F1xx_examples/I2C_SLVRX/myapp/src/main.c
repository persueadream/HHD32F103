/*******************************************************************************
*	Application: Demo code for IIC using in HHD32F0xx
*	Edition:		Version:1.0
*	Company: 		
*	Time: 			October 2015
*******************************************************************************/
#include "hhd32f1xx.h"
#include "hhd_sys.h"
#include "hhd_iic.h"
#include "iic_sim.h"

#define HT_WRDISPRAM        0x80
#define HT_DRVMODESET				0x82
#define HT_SYSMODESET 			0x84
#define HT_FRMFREQSET				0x86
#define HT_FLASHRREQSET			0x88
#define HT_IVASET						0x8a

uint8_t LCD_disp_Buf[12];

void IIC_IOCONFIG(void);

void delaynstep(int i)
{
	while(i--);
}

void		LCD_DISP_BUF_UPDATE()
{
/*
	*/
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
	int i;
	
	/* --------- System initialization -------------------*/
	SystemInit();	
	
	/* --------- Config I2C1 AFIO assignment -------------*/
	IIC_IOCONFIG();	
	
	/* --------- IIC initiallization ---------------------*/

//			NVIC_EnableIRQ(I2C2_IRQn);
	IIC_Init(I2C2,0,50,0xa0);
	IIC_SlaveGetData(I2C2,0,9);
//	IIC_Init(I2C1,1,50,0x70);
	/* --------- LCD Display buffer clear ----------------*/
//	IIC_SlaveResponseRd(I2C2,0,1);
//	IIC_WriteByte(I2C1,1,0x70,0x43);
	IICSendData(0x12,0x89abcdef);
	while(1)
	{
		if(IIC2_CtrlBlk.IICMasterBuffer[0]==0x43)
			break;
	}
	while(1);
}


void IIC_IOCONFIG(void)
{
	#if 1			//IIC1, SCL-> PB6, SDA-> PB7
//	IIC1_SCL_PB6;
//	IIC1_SDA_PB7;	
	HHD_AFIO->PB6 = 0x10;
	HHD_AFIO->PB7 = 0x10;
	HHD_GPIOB->OUT |= 3<<6;
	HHD_GPIOB->DIR |= (3<<6);
	#endif

	#if 0			//IIC1, SCL-> PB8, SDA-> PB8
	IIC1_SCL_PB8;
	IIC1_SDA_PB9;	
	#endif

	#if 0			//IIC2, SCL-> PB10, SDA-> PB11
	IIC2_SCL_PB10;
	IIC2_SDA_PB11;	
	#endif
	IIC2_SCL_PB10;
	IIC2_SDA_PB11;
}	


void I2C1_IRQHandler() 
{
	IIC_IRQHandler(I2C1);
	
}

void I2C2_IRQHandler() 
{
	IIC_IRQHandler(I2C2);

	
}

