#ifndef __SYS_H
#define __SYS_H	

#include "system_G32F1xx.h"
#include "g32f1xx.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������		   
////////////////////////////////////////////////////////////////////////////////// 	 

																	    
	 
//λ������,ʵ��51���Ƶ�GPIO���ƹ���
//����ʵ��˼��,�ο�<<CM3Ȩ��ָ��>>������(87ҳ~92ҳ).
//IO�ڲ����궨��
#define BITBAND(addr, bitnum) ((addr & 0xF0000000)+0x2000000+((addr &0xFFFFF)<<5)+(bitnum<<2)) 
#define MEM_ADDR(addr)  *((volatile unsigned long  *)(addr)) 
#define BIT_ADDR(addr, bitnum)   MEM_ADDR(BITBAND(addr, bitnum)) 
//IO�ڵ�ַӳ��
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
 
//IO�ڲ���,ֻ�Ե�һ��IO��!
//ȷ��n��ֵС��16!
#define PAout(n)   BIT_ADDR(GPIOA_ODR_Addr,n)  //��� 
#define PAin(n)    BIT_ADDR(GPIOA_IDR_Addr,n)  //���� 

#define PBout(n)   BIT_ADDR(GPIOB_ODR_Addr,n)  //��� 
#define PBin(n)    BIT_ADDR(GPIOB_IDR_Addr,n)  //���� 

#define PCout(n)   BIT_ADDR(GPIOC_ODR_Addr,n)  //��� 
#define PCin(n)    BIT_ADDR(GPIOC_IDR_Addr,n)  //���� 

#define PDout(n)   BIT_ADDR(GPIOD_ODR_Addr,n)  //��� 
#define PDin(n)    BIT_ADDR(GPIOD_IDR_Addr,n)  //���� 

#define PEout(n)   BIT_ADDR(GPIOE_ODR_Addr,n)  //��� 
#define PEin(n)    BIT_ADDR(GPIOE_IDR_Addr,n)  //����

#define PFout(n)   BIT_ADDR(GPIOF_ODR_Addr,n)  //��� 
#define PFin(n)    BIT_ADDR(GPIOF_IDR_Addr,n)  //����

#define PGout(n)   BIT_ADDR(GPIOG_ODR_Addr,n)  //��� 
#define PGin(n)    BIT_ADDR(GPIOG_IDR_Addr,n)  //����



// //����Ϊ��ຯ��
// void WFI_SET(void);		//ִ��WFIָ��
void INTX_DISABLE(void);//�ر������ж�
void INTX_ENABLE(void);	//���������ж�
void MSR_MSP(uint32_t addr);	//���ö�ջ��ַ

#endif
