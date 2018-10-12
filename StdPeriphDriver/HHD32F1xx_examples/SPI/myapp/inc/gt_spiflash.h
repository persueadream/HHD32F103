/*****************************************************************************
 *   gt_spiflash.h:  Header file for G32F1xx Family Microprocessors
 *
 *   Copyright(C) 2015, tech. Ltd.
 *   All rights reserved.
 *
 *   History
 *   2015  ver 1.00    Prelimnary version, first Release
 *
******************************************************************************/
#ifndef __SPIFLASH_H 
#define __SPIFLASH_H
#include "g32f1xx.h"

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
