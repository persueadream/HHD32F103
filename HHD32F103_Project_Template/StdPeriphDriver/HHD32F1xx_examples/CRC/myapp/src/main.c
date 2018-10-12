//------------------------------------------------------------
//HHD32F1xx CRC demo Main Program
//
//
//------------------------------------------------------------
#include "hhd32f1xx.h"
#include "hhd_crc.h"
#include "hhd_sys.h"

//Main function entry
uint32_t crc_ccitt,crc_16,crc_32;
int main(void)
{
	
	uint8_t datastr[16]={1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};		  

	/* --------- System Initialization  ----------- */
  /* 系统初始化后，MCU运行在72M时钟  -------------*/
  SystemInit();
	

  /* --------- Calculate CCITT-16  -------------- */
	crc_ccitt=CRC_CCITT(datastr,16,0x0FFFF);


  /* --------- Calculate CRC-16  ---------------- */
	crc_16=CRC_16(datastr,16,0);



  /* --------- Calculate CRC-32  ---------------- */
	crc_32=CRC_32(datastr,16,0x0FFFFFFFF);



	while (1); 
}

