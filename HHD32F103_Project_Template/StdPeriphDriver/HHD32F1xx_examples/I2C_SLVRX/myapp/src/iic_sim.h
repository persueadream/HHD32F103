#ifndef   __IIC_H
#define   __IIC_H
#include "stdint.h"
void IICSendData(uint8_t addr, uint32_t data);
void IICReceiveData(uint8_t addr, uint32_t *data);
#endif
