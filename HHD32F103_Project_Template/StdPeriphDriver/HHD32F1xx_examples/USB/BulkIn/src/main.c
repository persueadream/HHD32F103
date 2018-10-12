#include "hhd32f1xx.h"
#include "hhd_sys.h"
#include "musbfsfc.h"
//#include "config.h"
//#include "descript.h"


int main()
{
	
	
	/* ------------ System Initial ------------------ */
	SYS_SystemInitial();
	
	
	/* ------------ Enable USB Clock & Power -------- */
	SYSCON->SYSAPB1CLKCTRL.bit.USBCLK = 1;
	SYSCON->USBCTRL.bit.PHYPD = 0;

	
	
	/* ------------ USB IO PAD Config --------------- */
	IOCON->PA11.all = 0x7;	//USB DM analog mode.
	IOCON->PA12.all = 0x7;	//USB DP analog mode.


	
	/* ------------ Initial USB Descriptor -----------*/
	InitialiseDesc();
	
	
	/* ------------ Enable USB Interrupt ------------ */
	/* USB all process are in IRQ Handler routine ----*/
	NVIC_EnableIRQ(USB_IRQn);
	
	
	while(1);
	
}
