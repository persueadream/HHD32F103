//------------------------------------------------------------
//HHD32F1xx CRC demo Main Program
//
//
//------------------------------------------------------------
#include "hhd32f1xx.h"
#include "hhd_sys.h"
#include "hhd_iap.h"



	
int main(void)
{
	
	/* --------- System Initialization  ----------- */
  /* 系统初始化后，MCU运行在72M时钟  -------------*/
  SystemInit();

	/* --------- Erase sector  -------------------- */
	IAP_Flash_Erase(0x4000);

	
	/* --------- Program word  -------------------- */	
	IAP_Flash_Program(0x4000,0x12345678);

	while (1); 
}

