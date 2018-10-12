/*******************************************************************************
*	Application: Demo code for IIC using in HHD32F0xx
*	Edition:		Version:1.0
*	Company: 		
*	Time: 			October 2016
*******************************************************************************/
#include "hhd32f1xx.h"
#include "hhd_sys.h"
#include "hhd_iic.h"

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
	/* ------- I2C1 act as master,I2C2 act as slave ------*/
	IIC_Init(I2C1,1,50,0x70);	
	IIC_Init(I2C2,0,50,0x70);
	
	/* --------- LCD Display buffer clear ----------------*/
	for(i=0;i<11;i++)
		LCD_disp_Buf[i]=0;
	
	/* --------- Send command to HT1621 ------------------*/
	IIC_WriteByte(I2C1,0x70,HT_SYSMODESET,3);
	IIC_WriteByte(I2C1,0x70,HT_DRVMODESET,0);
	IIC_WriteByte(I2C1,0x70,HT_FRMFREQSET,1);
	IIC_WriteByte(I2C1,0x70,HT_IVASET,0x00);

	/* --------- Begin send Content of display to HT1621 -*/
	while (1) 
	{
		delaynstep(10000);
		LCD_DISP_BUF_UPDATE();			
		IIC_WriteArray(I2C1,0x70,HT_WRDISPRAM,LCD_disp_Buf,11);
		IIC_WriteByte(I2C1,0x70,HT_SYSMODESET,3);

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

	#if 0			//IIC2, SCL-> PB10, SDA-> PB11
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
	uint32_t i2c_rdata=0;
	
	if(I2C2->STAT.bit.SLVRXBUFFULL==1)
	{
		i2c_rdata = IIC_GetByte(I2C2);
	}
	
}

