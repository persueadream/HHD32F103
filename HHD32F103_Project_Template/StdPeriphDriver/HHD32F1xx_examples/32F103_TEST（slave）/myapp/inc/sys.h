#ifndef __SYS_H
#define __SYS_H	

#include "system_G32F1xx.h"
#include "g32f1xx.h"
//////////////////////////////////////////////////////////////////////////////////	 
//开发板		   
////////////////////////////////////////////////////////////////////////////////// 	 

																	    
	 
//位带操作,实现51类似的GPIO控制功能
//具体实现思想,参考<<CM3权威指南>>第五章(87页~92页).
//IO口操作宏定义
#define BITBAND(addr, bitnum) ((addr & 0xF0000000)+0x2000000+((addr &0xFFFFF)<<5)+(bitnum<<2)) 
#define MEM_ADDR(addr)  *((volatile unsigned long  *)(addr)) 
#define BIT_ADDR(addr, bitnum)   MEM_ADDR(BITBAND(addr, bitnum)) 
//IO口地址映射
#define GPIOA_ODR_Addr    (GT_GPIOA_BASE+8) //0x4001080C 
#define GPIOB_ODR_Addr    (GT_GPIOB_BASE+8) //0x40010C0C 
#define GPIOC_ODR_Addr    (GT_GPIOC_BASE+8) //0x4001100C 
#define GPIOD_ODR_Addr    (GT_GPIOD_BASE+8) //0x4001140C 
#define GPIOE_ODR_Addr    (GT_GPIOE_BASE+8) //0x4001180C 
#define GPIOF_ODR_Addr    (GT_GPIOF_BASE+8) //0x40011A0C    
#define GPIOG_ODR_Addr    (GT_GPIOG_BASE+8) //0x40011E0C    

#define GPIOA_IDR_Addr    (GT_GPIOA_BASE+4) //0x40010808 
#define GPIOB_IDR_Addr    (GT_GPIOB_BASE+4) //0x40010C08 
#define GPIOC_IDR_Addr    (GT_GPIOC_BASE+4) //0x40011008 
#define GPIOD_IDR_Addr    (GT_GPIOD_BASE+4) //0x40011408 
#define GPIOE_IDR_Addr    (GT_GPIOE_BASE+4) //0x40011808 
#define GPIOF_IDR_Addr    (GT_GPIOF_BASE+4) //0x40011A08 
#define GPIOG_IDR_Addr    (GT_GPIOG_BASE+4) //0x40011E08 
 
//IO口操作,只对单一的IO口!
//确保n的值小于16!
#define PAout(n)   BIT_ADDR(GPIOA_ODR_Addr,n)  //输出 
#define PAin(n)    BIT_ADDR(GPIOA_IDR_Addr,n)  //输入 

#define PBout(n)   BIT_ADDR(GPIOB_ODR_Addr,n)  //输出 
#define PBin(n)    BIT_ADDR(GPIOB_IDR_Addr,n)  //输入 

#define PCout(n)   BIT_ADDR(GPIOC_ODR_Addr,n)  //输出 
#define PCin(n)    BIT_ADDR(GPIOC_IDR_Addr,n)  //输入 

#define PDout(n)   BIT_ADDR(GPIOD_ODR_Addr,n)  //输出 
#define PDin(n)    BIT_ADDR(GPIOD_IDR_Addr,n)  //输入 

#define PEout(n)   BIT_ADDR(GPIOE_ODR_Addr,n)  //输出 
#define PEin(n)    BIT_ADDR(GPIOE_IDR_Addr,n)  //输入

#define PFout(n)   BIT_ADDR(GPIOF_ODR_Addr,n)  //输出 
#define PFin(n)    BIT_ADDR(GPIOF_IDR_Addr,n)  //输入

#define PGout(n)   BIT_ADDR(GPIOG_ODR_Addr,n)  //输出 
#define PGin(n)    BIT_ADDR(GPIOG_IDR_Addr,n)  //输入



// //以下为汇编函数
// void WFI_SET(void);		//执行WFI指令
void INTX_DISABLE(void);//关闭所有中断
void INTX_ENABLE(void);	//开启所有中断
void MSR_MSP(uint32_t addr);	//设置堆栈地址

#endif
