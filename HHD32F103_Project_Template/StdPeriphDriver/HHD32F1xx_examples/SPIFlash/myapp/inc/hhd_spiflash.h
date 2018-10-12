/*****************************************************************************
 *   hhd_spiflash.h:  
 *
 *   Copyright(C) 2017
 *   All rights reserved.
 *
 *   History
 *   2017  ver 1.00    Prelimnary version, first Release
 *
******************************************************************************/
#ifndef __SPIFLASH_H 
#define __SPIFLASH_H
#include "hhd32f1xx.h"

void SPIFlashInit(void);
void SPIFlashID(uint8_t *  did);
void SPIFlashStatus(uint8_t * sr1);
void SPIFlashWriteEnable(void);
void SPIFlashSecErase(uint32_t addr);
void SPIFlashRead(uint32_t addr, uint8_t * dst, uint32_t noofdata);
void SPIFlashWrite(uint32_t addr, uint8_t * src, uint8_t noofdata);

#endif /* end __SPIFLASH_H */
/*****************************************************************************
**                            End Of File
******************************************************************************/
