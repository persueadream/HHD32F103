//HHD32f0xx SPI flash demo Main Program

#include "hhd32f1xx.h"
#include "hhd_spiflash.h"
#include "hhd_sys.h"
#include "hhd_spi.h"


void delay(void)
{
	uint32_t i=0;
	while (i++ < 0xfff);
}

void SPI_IOCONFIG(void);	

//Main function entry
int main(void)
{

	uint8_t flashid=0,flashdata[16];

	
	/* ----------- System Initialization ---------------------- */
	SystemInit();

	
	/* ----------- SPI GPIO configuration --------------------- */
	SPI_IOCONFIG();	
	
	/* ----------- SPI Flash interface initialization --------- */
	SPIFlashInit();

	
	/* ----------- Get SPI Flash Device ID -------------------- */
	SPIFlashID(&flashid);

	
	/* ----------- SPI Flash Read 16 bytes -------------------- */
	SPIFlashRead(0, flashdata, 16);

	
	
	while(1);
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
