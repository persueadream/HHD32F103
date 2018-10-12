//HHD32f0xx SPI flash demo Main Program

#include "hhd32f1xx.h"
#include "hhd_sys.h"
#include "hhd_spi.h"

uint32_t rdata;

void delay(void)
{
	uint32_t i=0;
	while (i++ < 0xfff);
}

void SPI_IOCONFIG(void);	

//Main function entry
int main(void)
{

	
	/* ----------- System Initialization ---------------------- */
	SystemInit();

	
	/* ----------- SPI GPIO configuration --------------------- */
	SPI_IOCONFIG();	
	
	/* ----------- SPI Flash interface initialization --------- */
	/* ----------- 8bit frame,master mode  bus timing is MODE0  */
	SPI_Open(SPI1,SPI_FRAME, 8, SPI_MASTER, SPI_MODE0);
	
	
	
	/* ----------- Set SPI CLK to 1MHz  ----------------------- */
	/* ----------- Do not set SPICLK > 1/4 CPU_clock  ----------*/
	SPI_SetClk(SPI1,1000000);

	
	/* ----------- Flush SPI FIFO ----------------------------- */
	SPI_ClearFIFO(SPI1);
	
	
	/* ----------- Send one byte data to TX FIFO -------------- */
	/* --------- 用跳线把SPI1 的MISO和MOSI连起来 -------------- */
	SPI_Write_FIFO(SPI1,0x55);
	
	
	//Polling RX FIFO is not empty, if there is more than one byte data,
	//Then start read FIFO.
	POLL_RXFIFO_NOTEMPTY(SPI1);
	
	rdata = SPI_Read_FIFO(SPI1);

  //if you have more than one byte data to transmit
	//suggest you use SPI_WritetoFIFO() to do burst transmission
	//SPI_WritetoFIFO(SPI1,srcbuf_point,number);
	while(1);
	
	/* ----------- Close SPI Port ----------------------------- */
	//SPI_Close(SPI1);

	
	
	//while(1);
}

void SPI_IOCONFIG(void)
{
	#if 1			//SPI1, SSEL-> PA4, SCK-> PA5, MISO-> PA6, MOSI-> PA7
	SPI1_SSEL_PA4;
	SPI1_SCK_PA5;	
	SPI1_MISO_PA6;
	SPI1_MOSI_PA7;	
	#endif

	#if 0			//SPI1, SSEL-> PA15, SCK-> PB3, MISO-> PB4, MOSI-> PB5
	SPI1_SSEL_PA15;
	SPI1_SCK_PB3;	
	SPI1_MISO_PB4;
	SPI1_MOSI_PB5;	
	#endif

	#if 0			//SPI2, SSEL-> PB12, SCK-> PB13, MISO-> PB14, MOSI-> PB15
	SPI2_SSEL_PB12;
	SPI2_SCK_PB13;	
	SPI2_MISO_PB14;
	SPI2_MOSI_PB15;	
	#endif

	#if 0			//SPI3, SSEL-> PA15, SCK-> PB3, MISO-> PB4, MOSI-> PB5
	SPI3_SSEL_PA15;
	SPI3_SCK_PB3;	
	SPI3_MISO_PB4;
	SPI3_MOSI_PB5;	
	#endif
	
	
}	
