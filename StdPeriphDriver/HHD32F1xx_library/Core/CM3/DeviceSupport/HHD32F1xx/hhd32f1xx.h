/*
 *-----------------------------------------------------------------------------
 * The confidential and proprietary information contained in this file may
 * only be used by a person authorised under and to the extent permitted
 * by a subsisting licensing agreement from ARM Limited.
 *
 *            (C) COPYRIGHT 2010-2011 ARM Limited.
 *                ALL RIGHTS RESERVED
 *
 * This entire notice must be reproduced on all copies of this file
 * and copies of this file may only be made by a person if such person is
 * permitted to do so under the terms of a subsisting license agreement
 * from ARM Limited.
 *
 *-----------------------------------------------------------------------------
 */


#ifndef __CMSDK_H__
#define __CMSDK_H__

#ifdef __cplusplus
 extern "C" {
#endif

/** @addtogroup CMSDK_Definitions CMSDK Definitions
  This file defines all structures and symbols for CMSDK:
    - Registers and bitfields
    - peripheral base address
    - peripheral ID
    - PIO definitions
  @{
*/


/******************************************************************************/
/*                Processor and Core Peripherals                              */
/******************************************************************************/
/** @addtogroup CMSDK_CMSIS CMSDK CMSIS Definitions
  Configuration of the Cortex-M0 Processor and Core Peripherals
  @{
*/

/*
 * ==========================================================================
 * ---------- Interrupt Number Definition -----------------------------------
 * ==========================================================================
 */

typedef enum IRQn
{
/******  Cortex-M0 Processor Exceptions Numbers ***************************************************/
  NonMaskableInt_IRQn           = -14,    /*!< 2 Non Maskable Interrupt                           */
  HardFault_IRQn                = -13,    /*!< 3 Cortex-M3 Hard Fault Interrupt                   */
  MemoryManagement_IRQn         = -12,    /*!< 4 Cortex-M3 Memory Management Interrupt            */ 
  BusFault_IRQn                 = -11,    /*!< 5 Cortex-M3 Bus Fault Interrupt                    */
  UsageFault_IRQn               = -10,    /*!< 6 Cortex-M3 Usage Fault Interrupt                  */
  SVCall_IRQn                   = -5,     /*!< 11 Cortex-M3 SV Call Interrupt                     */
  DebugMonitor_IRQn             = -4,     /*!< 12 Cortex-M3 Debug Monitor Interrupt               */
  PendSV_IRQn                   = -2,     /*!< 14 Cortex-M3 Pend SV Interrupt                     */
  SysTick_IRQn                  = -1,     /*!< 15 Cortex-M3 System Tick Interrupt                 */

/******  CMSDK Specific Interrupt Numbers *******************************************************/
  WWDT_IRQn                     = 0,     /*!< Window watchdog Interrupt                           */	
  BOD_IRQn                      = 1,     /*!< BOD Interrupt                                       */ 
  DAC_IRQn                      = 2,     /*!< BOD Interrupt                                       */     	
  RTC_IRQn                      = 3,     /*!< RTC global Interrupt                                */   
  EXTI0_IRQn                    = 6,     /*!< EXTI line0 Interrupt                                */
  EXTI1_IRQn                    = 7,     /*!< EXTI line1 Interrupt                                */
  EXTI2_IRQn                    = 8,     /*!< EXTI line2 Interrupt                                */
  EXTI3_IRQn                    = 9,     /*!< EXTI line3 Interrupt                                */
  EXTI4_IRQn                    = 10,    /*!< EXTI line4 Interrupt                                */
  DMA1_CHANNEL1_IRQn            = 11,    /*!< DMA1 channel1 Interrupt                             */
  DMA1_CHANNEL2_IRQn            = 12,    /*!< DMA1 channel2 Interrupt                             */
  DMA1_CHANNEL3_IRQn            = 13,    /*!< DMA1 channel3 Interrupt                             */
  DMA1_CHANNEL4_IRQn            = 14,    /*!< DMA1 channel4 Interrupt                             */
  DMA1_CHANNEL5_IRQn            = 15,    /*!< DMA1 channel5 Interrupt                             */
  DMA1_CHANNEL6_IRQn            = 16,    /*!< DMA1 channel6 Interrupt                             */
  DMA1_CHANNEL7_IRQn            = 17,    /*!< DMA1 channel7 Interrupt                             */
  ADC1_2_IRQn                   = 18,    /*!< ADC1 and ADC2 global Interrupt                      */
  USB_IRQn                      = 19,    /*!< USB Interrupt                                       */
  CAN_IRQn                      = 21,    /*!< CAN bus Interrupt                                   */
  EXTI9_5_IRQn                  = 23,    /*!< EXTI line9 and line5 Interrupt                      */
  TIM1FAULT_TIM9_IRQn           = 24,    /*!< TIM1 fault & TIM9 Interrupt                         */
  TIM10_IRQn                    = 25,    /*!< TIM10 Interrupt                                     */
  TIM11_IRQn                    = 26,    /*!< TIM11 Interrupt                                     */
  TIM1_IRQn                     = 27,    /*!< TIM1 Interrupt                                      */
  TIM2_IRQn                     = 28,    /*!< TIM2 Interrupt                                      */
  TIM3_IRQn                     = 29,    /*!< TIM3 Interrupt                                      */
  TIM4_IRQn                     = 30,    /*!< TIM4 Interrupt                                      */
  I2C1_IRQn                     = 31,    /*!< I2C1 Interrupt                                      */
  I2C2_IRQn                     = 33,    /*!< I2C2 Interrupt                                      */
  SPI1_IRQn                     = 35,    /*!< SPI1 Interrupt                                      */
  SPI2_IRQn                     = 36,    /*!< SPI2 Interrupt                                      */
  UART1_IRQn                    = 37,    /*!< UART1 Interrupt                                     */
  UART2_IRQn                    = 38,    /*!< UART2 Interrupt                                     */
  UART3_IRQn                    = 39,    /*!< UART3 Interrupt                                     */
  EXTI15_10_IRQn                = 40,    /*!< EXTERNAL Line[15:10] Interrupts                     */
  USBWAKEUP_IRQn                = 42,    /*!< USB WAKE up line Interrupt                          */
  TIM8FAULT_TIM12_IRQn          = 43,    /*!< TIM8 fault & TIM12 Interrupt                        */
  TIM13_IRQn                    = 44,    /*!< TIM13 Interrupt                                     */
  TIM14_IRQn                    = 45,    /*!< TIM14 Interrupt                                     */
  TIM8_IRQn                     = 46,    /*!< TIM8 Interrupt                                      */
  ADC3_IRQn                     = 47,    /*!< ADC3 Interrupt                                      */
  TIM5_IRQn                     = 50,    /*!< TIM5 Interrupt                                      */
  SPI3_IRQn                     = 51,    /*!< SPI3 Interrupt                                      */
  UART4_IRQn                    = 52,    /*!< UART4 Interrupt                                     */
  UART5_IRQn                    = 53,    /*!< UART5 Interrupt                                     */
  TIM6_IRQn                     = 54,    /*!< TIM6 Interrupt                                      */
  TIM7_IRQn                     = 55,    /*!< TIM7 Interrupt                                      */
  DMA2_CHANNEL1_IRQn            = 56,    /*!< DMA2 channel1 Interrupt                              */
  DMA2_CHANNEL2_IRQn            = 57,    /*!< DMA2 channel2 Interrupt                              */
  DMA2_CHANNEL3_IRQn            = 58,    /*!< DMA2 channel3 Interrupt                              */
  DMA2_CHANNEL4_5_IRQn          = 59,    /*!< DMA2 channel4 Interrupt                              */
  

} IRQn_Type;


/*
 * ==========================================================================
 * ----------- Processor and Core Peripheral Section ------------------------
 * ==========================================================================
 */

/* Configuration of the Cortex-M0 Processor and Core Peripherals */
#define __MPU_PRESENT             1         /*!< MPU present or not                               */
#define __NVIC_PRIO_BITS          3         /*!< Number of Bits used for Priority Levels          */
#define __Vendor_SysTickConfig    0         /*!< Set to 1 if different SysTick Config is used     */

/*@}*/ /* end of group CMSDK_CMSIS */


#include "core_cm3.h"                       /* Cortex-M3 processor and core peripherals           */
#include "system_HHD32F1xx.h"                   /* System Header                                      */


/** @addtogroup Exported_types
  * @{
  */  

/*!< STM32F10x Standard Peripheral Library old types (maintained for legacy purpose) */
typedef int32_t  s32;
typedef int16_t s16;
typedef int8_t  s8;

typedef const int32_t sc32;  /*!< Read Only */
typedef const int16_t sc16;  /*!< Read Only */
typedef const int8_t sc8;   /*!< Read Only */

typedef __IO int32_t  vs32;
typedef __IO int16_t  vs16;
typedef __IO int8_t   vs8;

typedef __I int32_t vsc32;  /*!< Read Only */
typedef __I int16_t vsc16;  /*!< Read Only */
typedef __I int8_t vsc8;   /*!< Read Only */

typedef uint32_t  u32;
typedef uint16_t u16;
typedef uint8_t  u8;

typedef const uint32_t uc32;  /*!< Read Only */
typedef const uint16_t uc16;  /*!< Read Only */
typedef const uint8_t uc8;   /*!< Read Only */

typedef __IO uint32_t  vu32;
typedef __IO uint16_t vu16;
typedef __IO uint8_t  vu8;

typedef __I uint32_t vuc32;  /*!< Read Only */
typedef __I uint16_t vuc16;  /*!< Read Only */
typedef __I uint8_t vuc8;   /*!< Read Only */

typedef enum {RESET = 0, SET = !RESET} FlagStatus, ITStatus;

typedef enum {DISABLE = 0, ENABLE = !DISABLE} FunctionalState;
#define IS_FUNCTIONAL_STATE(STATE) (((STATE) == DISABLE) || ((STATE) == ENABLE))

typedef enum {ERROR = 0, SUCCESS = !ERROR} ErrorStatus;

/******************************************************************************/
/*                Device Specific Peripheral Registers structures             */
/******************************************************************************/

#if defined ( __CC_ARM   )
#pragma anon_unions
#endif

/*------------- System Control (SYSCON) --------------------------------------*/
/** @addtogroup HHD_SYSCON HHD103 System Control Block 
  @{
*/
typedef struct
{
  __IO uint32_t SYSMEMREMAP;            /*!< Offset: 0x000 System memory remap (R/W) */
  __IO uint32_t PRESETCTRL;             /*!< Offset: 0x004 Peripheral reset control (R/W) */
  __IO uint32_t SYSPLLCTRL;             /*!< Offset: 0x008 System PLL control (R/W) */
  __IO uint32_t SYSPLLSTAT;             /*!< Offset: 0x00C System PLL status (R/ ) */
	
       uint32_t RESERVED0[4];

  __IO uint32_t SYSOSCCTRL;             /*!< Offset: 0x020 System oscillator control (R/W) */
  __IO uint32_t WDTOSCCTRL;             /*!< Offset: 0x024 Watchdog oscillator control (R/W) */
  __IO uint32_t IRCCTRL;                /*!< Offset: 0x028 IRC control (R/W) */
       uint32_t RESERVED1[1];           /*!< Offset: 0x02C RTC oscillator control (R/W) */
  
  __IO uint32_t SYSRESSTAT;             /*!< Offset: 0x030 System reset status Register (R/ ) */
       uint32_t RESERVED2[3];
	
  __IO uint32_t SYSPLLCLKSEL;           /*!< Offset: 0x040 System PLL clock source select (R/W) */	
  __IO uint32_t SYSPLLCLKUEN;           /*!< Offset: 0x044 System PLL clock source update enable (R/W) */
	
       uint32_t RESERVED3[10];

  __IO uint32_t MAINCLKSEL;             /*!< Offset: 0x070 Main clock source select (R/W) */
  __IO uint32_t MAINCLKUEN;             /*!< Offset: 0x074 Main clock source update enable (R/W) */
  __IO uint32_t SYSAHBCLKDIV;           /*!< Offset: 0x078 System AHB clock divider (R/W) */
  __IO uint32_t ADCCLKDIV;              /*!< Offset: 0x07c ADC clock divider (R/W) */

  __IO uint32_t SYSAHBCLKCTRL;          /*!< Offset: 0x080 System AHB clock control (R/W) */
  __IO uint32_t SYSAPB2CLKCTRL;         /*!< Offset: 0x084 System APB2 clock control (R/W) */
  __IO uint32_t SYSAPB1CLKCTRL;         /*!< Offset: 0x088 System APB1 clock control (R/W) */
  __IO uint32_t SYSAPB2RESET;           /*!< Offset: 0x08c System APB2 reset control (R/W) */
	
  __IO uint32_t SYSAPB1RESET;           /*!< Offset: 0x090 System APB1 reset control (R/W) */                      
  __IO uint32_t RCCCFGR;                /*!< Offset: 0x094 RCC CFGR control (R/W) */
  __IO uint32_t UARTCLKDIV;             /*!< Offset: 0x098 UART1 clock divider (R/W) */

       uint32_t RESERVED7[17];       
            
  __IO uint32_t CLKOUTCLKSEL;           /*!< Offset: 0x0E0 CLKOUT clock source select (R/W) */
  __IO uint32_t CLKOUTUEN;              /*!< Offset: 0x0E4 CLKOUT clock source update enable (R/W) */
  __IO uint32_t CLKOUTDIV;              /*!< Offset: 0x0E8 CLKOUT clock divider (R/W) */   
	
       uint32_t RESERVED8[24];   

  __IO uint32_t IOCONFIGCLKDIV;	
    	  	            
  __IO uint32_t BODCTRL;                /*!< Offset: 0x150 BOD control (R/W) */
       uint32_t RESERVED10[8];              

  __IO uint32_t INTNMI;                 /*!< Offset: 0x174 NMI interrupt source configuration control (R/W) */
       uint32_t RESERVED12[34];          

  __IO uint32_t EXTICTL;                /*!< Offset: 0x200 EXTI Control ;DSWAKECTL(R/W) */
  __IO uint32_t EXTIEN;                 /*!< Offset: 0x204 EXTI interrupt enable;DSWAKEEN (R/W) */
  __O  uint32_t EXTICLR;                /*!< Offset: 0x208 EXTI interrupt clear;DSWAKECLR (R/W) */
  __I  uint32_t EXTISTAT;               /*!< Offset: 0x208 EXTI interrupt state;DSWAKE (R/W) */
       uint32_t RESERVED13[8];

  __IO uint32_t PDSLEEPCFG;             /*!< Offset: 0x230 Power-down states in Deep-sleep mode (R/W) */
  __IO uint32_t PDAWAKECFG;             /*!< Offset: 0x234 Power-down states after wake-up (R/W) */       
  __IO uint32_t PDRUNCFG;               /*!< Offset: 0x238 Power-down configuration Register (R/W) */
} HHD_SYSCON_TypeDef;
/*@}*/ /* end of group HHD_SYSCON */

/*------------- Micro DMA controller (DMA) --------------------------*/
/** @addtogroup HHD_DMA HHD103 Micro DMA controller 
  @{
*/
typedef struct
{
  __I  uint32_t STATUS;              /*!< Offset: 0x000 DMA status register (R/) */
  __O  uint32_t CFG;
  __IO uint32_t CTRL_BASE_PTR;
  __I  uint32_t ALT_CTRL_BASE_PTR;
  __I  uint32_t WAITONREQ_STATUS;
  __O  uint32_t CHNL_SW_REQUEST;
  __IO uint32_t CHNL_USEBURST_SET;
  __O  uint32_t CHNL_USEBURST_CLR;
  
  __IO uint32_t CHNL_REQ_MASK_SET;   /*!< Offset: 0x020 Channel request mask set register (R/W) */
  __O  uint32_t CHNL_REQ_MASK_CLR;
  __IO uint32_t CHNL_ENABLE_SET;
  __O  uint32_t CHNL_ENABLE_CLR;
  __IO uint32_t CHNL_PRI_ALT_SET;
  __O  uint32_t CHNL_PRI_ALT_CLR;
  __IO uint32_t CHNL_PRIORITY_SET;
  __O  uint32_t CHNL_PRIORITY_CLR;   /*!< Offset: 0x034 Channel priority clear register (W) */
  
	   uint32_t RESERVE0[16];          /* 0x40 */
  	   
  __IO uint32_t CHNL_IRQ_STATUS;     /*!< Offset: 0x080 Channel DMA interrupt status register (R/W) */
  __IO uint32_t IRQ_ERR_ENABLE;
  __IO uint32_t CHNL_IRQ_ENABLE;     
} HHD_DMA_TypeDef;
/*@}*/ /* end of group HHD_DMA */

/*------------- Pin Connect Block (AFIO) --------------------------------*/
/** @addtogroup HHD_AFIO HHD103 I/O Configuration Block 
  @{
*/
typedef struct
{
  __IO uint32_t PA0;
  __IO uint32_t PA1;
  __IO uint32_t PA2;
  __IO uint32_t PA3;
  __IO uint32_t PA4;
  __IO uint32_t PA5;
  __IO uint32_t PA6;
  __IO uint32_t PA7;
  __IO uint32_t PA8;
  __IO uint32_t PA9;
  __IO uint32_t PA10;
  __IO uint32_t PA11;
  __IO uint32_t PA12;
  __IO uint32_t SWDIO_PA13;
  __IO uint32_t SWCLK_PA14;
  __IO uint32_t JTDI_PA15;
  __IO uint32_t PB0;
  __IO uint32_t PB1;
  __IO uint32_t PB2;
  __IO uint32_t JTDO_PB3;
  __IO uint32_t JNRST_PB4;
  __IO uint32_t PB5;
  __IO uint32_t PB6;
  __IO uint32_t PB7;
  __IO uint32_t PB8;
  __IO uint32_t PB9;
  __IO uint32_t PB10;
  __IO uint32_t PB11;
  __IO uint32_t PB12;
  __IO uint32_t PB13;
  __IO uint32_t PB14;
  __IO uint32_t PB15;
  __IO uint32_t PC0;
  __IO uint32_t PC1;
  __IO uint32_t PC2;
  __IO uint32_t PC3;
  __IO uint32_t PC4;
  __IO uint32_t PC5;
  __IO uint32_t PC6;
  __IO uint32_t PC7;
  __IO uint32_t PC8;
  __IO uint32_t PC9;
  __IO uint32_t PC10;
  __IO uint32_t PC11;
  __IO uint32_t PC12;
  __IO uint32_t PC13;
  __IO uint32_t PC14;
  __IO uint32_t PC15;
  __IO uint32_t PD0;
  __IO uint32_t PD1;
  __IO uint32_t PD2;
  __IO uint32_t PD3;
  __IO uint32_t PD4;
  __IO uint32_t PD5;
  __IO uint32_t PD6;
  __IO uint32_t PD7;
  __IO uint32_t PD8;
  __IO uint32_t PD9;
  __IO uint32_t PD10;
  __IO uint32_t PD11;
  __IO uint32_t PD12;
  __IO uint32_t PD13;
  __IO uint32_t PD14;
  __IO uint32_t PD15;
  __IO uint32_t PE0;
  __IO uint32_t PE1;
  __IO uint32_t PE2;
  __IO uint32_t PE3;
  __IO uint32_t PE4;
  __IO uint32_t PE5;
  __IO uint32_t PE6;
  __IO uint32_t PE7;
  __IO uint32_t PE8;
  __IO uint32_t PE9;
  __IO uint32_t PE10;
  __IO uint32_t PE11;
  __IO uint32_t PE12;
  __IO uint32_t PE13;
  __IO uint32_t PE14;
  __IO uint32_t PE15;
  __IO uint32_t PF0;
  __IO uint32_t PF1;
  __IO uint32_t PF2;
  __IO uint32_t PF3;
  __IO uint32_t PF4;
  __IO uint32_t PF5;
  __IO uint32_t PF6;
  __IO uint32_t PF7;
  __IO uint32_t PF8;
  __IO uint32_t PF9;
  __IO uint32_t PF10;
  __IO uint32_t PF11;
  __IO uint32_t PF12;
  __IO uint32_t PF13;
  __IO uint32_t PF14;
  __IO uint32_t PF15;
  __IO uint32_t PG0;
  __IO uint32_t PG1;
  __IO uint32_t PG2;
  __IO uint32_t PG3;
  __IO uint32_t PG4;
  __IO uint32_t PG5;
  __IO uint32_t PG6;
  __IO uint32_t PG7;
  __IO uint32_t PG8;
  __IO uint32_t PG9;
  __IO uint32_t PG10;
  __IO uint32_t PG11;
  __IO uint32_t PG12;
  __IO uint32_t PG13;
  __IO uint32_t PG14;
  __IO uint32_t PG15;
  __IO uint32_t FTMODE;
  
} HHD_AFIO_TypeDef;
/*@}*/ /* end of group HHD_AFIO */


/*------------- General Purpose Input/Output (GPIO) --------------------------*/
/** @addtogroup HHD_GPIO HHD103 General Purpose Input/Output 
  @{
*/
typedef struct
{    
  __IO uint32_t MASK;       /*!< Offset: 0x000 Pin value mask register (R/W) */
  __I  uint32_t PIN;
  __IO uint32_t OUT;
  __O  uint32_t SET;
  __O  uint32_t CLR;        /*!< Offset: 0x010 Pin output value clear register (R/W) */
  __O  uint32_t NOT;
  	   uint32_t RESERVE[2];
  __IO uint32_t DIR;        /*!< Offset: 0x020 Data direction register (R/W) */
  __IO uint32_t IS;
  __IO uint32_t IBE;
  __IO uint32_t IEV;
  __IO uint32_t IE;
  __I  uint32_t RIS;
  __I  uint32_t MIS;
  __O  uint32_t IC;
} HHD_GPIO_TypeDef;
/*@}*/ /* end of group HHD_GPIO */

/*------------- Flash Control --------------------------*/
/** @addtogroup HHD_FMC HHD103 General Purpose Input/Output 
  @{
*/
typedef struct
{    
  __IO uint32_t FLASHCTRL;      /*!< Offset: 0x000 Flash control register (R/W) */
  __IO uint32_t PRGDATA;	      /*!< Offset: 0x004 flash program data register (R/W) */
  __IO uint32_t FLASHADDR;	    /*!< Offset: 0x008 flash program/erase address register (R/W) */
  __IO uint32_t RDCYCCFG;       /*!< Offset: 0x00c Read flash cycle config (R/W) */
} HHD_FMC_TypeDef;
/*@}*/ /* end of group HHD_FMC */
  


/*------------- Comparator (COMP) --------------------------*/
/** @addtogroup HHD_COMP HHD103 Comparator 
  @{
*/
typedef struct
{
  __IO uint32_t CMP;        /*!< Offset: 0x000 Comparator control register (R/W) */
  __IO uint32_t VLAD;       /*!< Offset: 0x004 Voltage ladder register (R/W) */
} HHD_COMP_TypeDef;
/*@}*/ /* end of group HHD_COMP */

/*------------- Timer (TMR) --------------------------------------------------*/
/** @addtogroup HHD_TMR HHD103 16/32-bit Counter/Timer 
  @{
*/
typedef struct
{
  __IO uint32_t IR;                     /*!< Offset: 0x000 Interrupt Register (R/W) */
  __IO uint32_t TCR;                    /*!< Offset: 0x004 Timer Control Register (R/W) */
  __IO uint32_t TC;                     /*!< Offset: 0x008 Timer Counter Register (R/W) */
  __IO uint32_t PR;                     /*!< Offset: 0x00C Prescale Register (R/W) */
  __IO uint32_t PC;                     /*!< Offset: 0x010 Prescale Counter Register (R/W) */
  __IO uint32_t MCR;                    /*!< Offset: 0x014 Match Control Register (R/W) */
  __IO uint32_t MR[4];                  /*!< Offset: 0x018 Match Register 0 (R/W) */
  __IO uint32_t CCR;                    /*!< Offset: 0x028 Capture Control Register (R/W) */
  __I  uint32_t CR[4];                  /*!< Offset: 0x02C Capture Register 0 (R/ ) */
  __IO uint32_t EMR;                    /*!< Offset: 0x03C External Match Register (R/W) */
       uint32_t RESERVED2[12];
  __IO uint32_t CTCR;                   /*!< Offset: 0x070 Count Control Register (R/W) */
  __IO uint32_t PWMC;                   /*!< Offset: 0x074 PWM Control Register (R/W) */  
} HHD_TMR_TypeDef;
/*@}*/ /* end of group HHD_TMR */

/*------------- Timer (TMR) --------------------------------------------------*/
/** @addtogroup HHD_BASETMR HHD103 Base Timer 
  @{
*/
typedef struct
{
  __IO uint32_t IR;                     /*!< Offset: 0x000 Interrupt Register (R/W) */
  __IO uint32_t TCR;                    /*!< Offset: 0x004 Timer Control Register (R/W) */
  __IO uint32_t TC;                     /*!< Offset: 0x008 Timer Counter Register (R/W) */
  __IO uint32_t PR;                     /*!< Offset: 0x00C Prescale Register (R/W) */
  __IO uint32_t PC;                     /*!< Offset: 0x010 Prescale Counter Register (R/W) */
  __IO uint32_t MCR;                    /*!< Offset: 0x014 Match Control Register (R/W) */
  __IO uint32_t MR0;                    /*!< Offset: 0x018 Match Register 0 (R/W) */
  __IO uint32_t MR1;                    /*!< Offset: 0x01C Match Register 1 (R/W) */
} HHD_BASETMR_TypeDef;
/*@}*/ /* end of group HHD_TMR */

/*------------- RTC (RTC) ------------------------------------------------------*/
/** @addtogroup HHD_RTC HHD103 Base Timer 
  @{
*/
typedef struct
{
  __I  uint32_t DR;                     /*!< Offset: 0x000 Data Register (R/W) */
  __IO uint32_t MR;                     /*!< Offset: 0x004 MatchRegister (R/W) */
  __IO uint32_t LR;                     /*!< Offset: 0x008 Load Register (R/W) */
  __IO uint32_t CR;                     /*!< Offset: 0x00C Control Register (R/W) */
  __IO uint32_t ISCS;                   /*!< Offset: 0x010 Interrupt Control Register (R/W) */
  __I  uint32_t RIS;                    /*!< Offset: 0x014 Raw Interrupt Register (R/W) */
  __I  uint32_t MIS;                    /*!< Offset: 0x018 Masked interrupt Register (R/W) */
	__O  uint32_t ICR;                    /*!< Offset: 0x01C Interrupt Clear Register (R/W) */
} HHD_RTC_TypeDef;
/*@}*/ /* end of group HHD_RTC */


/*------------- Universal Serial BUS (BUS) -----------*/
/** @addtogroup CMSDK_UART CMSDK Universal Serial BUS
  memory mapped structure for CMSDK_USB
  @{
*/
typedef struct
{ 
  __IO   uint32_t  FADDR;         /*!< Offset: 0x000 Function Address Register    (R/W) */
  __IO   uint32_t  POWER;         /*!< Offset: 0x004 Power Management Register  (R/W) */
  __I    uint32_t  INTRIN1;       /*!< Offset: 0x008 Interrupt In0 Register (R/) */
  __I    uint32_t  INTRIN2;       /*!< Offset: 0x00C Interrupt In1 Register (R/) */
  __I    uint32_t  INTROUT1;      /*!< Offset: 0x010 Interrupt Out1 Register (R/) */
  __I    uint32_t  INTROUT2;      /*!< Offset: 0x014 Interrupt Out2 Register (R/) */
  __I    uint32_t  INTRUSB;       /*!< Offset: 0x018 USB Interrupt Register (R/) */
  __IO   uint32_t  INTRIN1E;      /*!< Offset: 0x01C INTRIN1 Interrupt Enable Register (R/W) */
  __IO   uint32_t  INTRIN2E;      /*!< Offset: 0x020 INTRIN2 Interrupt Enable Register (R/W) */
  __IO   uint32_t  INTROUT1E;     /*!< Offset: 0x024 INTROUT1 Interrupt Enable Register (R/W) */
  __IO   uint32_t  INTROUT2E;     /*!< Offset: 0x028 INTROUT1 Interrupt Enable Register (R/W) */
  __IO   uint32_t  INTRUSBE;      /*!< Offset: 0x02C INTRUSB Interrupt Enable Register (R/W) */
  __IO   uint32_t  FRAME1;        /*!< Offset: 0x030 Frame Number bits 0~7 Register (R/W) */
  __IO   uint32_t  FRAME2;        /*!< Offset: 0x034 Frame Number bits 8~10 Register (R/W) */
  __IO   uint32_t  INDEX;         /*!< Offset: 0x038 Index Register (R/W) */
         uint32_t  RESEVRED0;
  __IO   uint32_t  INMAXP;        /*!< Offset: 0x040 Maximum Packet Size Register (R/W) */
  union {
    __IO   uint32_t  CSR0;        /*!< Offset: 0x044 Endpoint0 Control Status Register (R/ ) */
    __IO   uint32_t  INCSR1;      /*!< Offset: 0x044 In Control Status Register1 ( /W) */
    };
  __IO   uint32_t  INCSR2;        /*!< Offset: 0x048 In Control Status Register2 (R/W) */
  __IO   uint32_t  OUTMAXP;       /*!< Offset: 0x04C Maximum Out Packet Size Register (R/W) */
  __IO   uint32_t  OUTCSR1;       /*!< Offset: 0x050 Out Control Status  Register1 (R/W) */
  __IO   uint32_t  OUTCSR2;       /*!< Offset: 0x054 Out Control Status  Register2 (R/W) */
  union {
    __I   uint32_t  COUNT0;       /*!< Offset: 0x058 Endpoint0 Data Number Register (R/W) */
    __I   uint32_t  OUTCOUNT1;    /*!< Offset: 0x058 Data Number Low Register (R/W) */
    };
  __I   uint32_t  OUTCOUNT2;      /*!< Offset: 0x05C data Number High Register (R/W) */
        uint32_t  RESEVRED1[8];
  __IO  uint32_t  FIFO[8];        /*!< Offset: 0x080 FIFO Register (R/W) */
} HHD_USB_TypeDef;


/*------------- CAN BUS (CAN) -----------*/
/** @addtogroup CMSDK_CAN CMSDK Universal Asynchronous Receiver/Transmitter
  memory mapped structure for CMSDK_CAN
  @{
*/
typedef struct
{ 
  __IO   uint32_t  MOD;          /*!< Offset: 0x000 MOD Register    (R/W) */
  __IO   uint32_t  CMR;          /*!< Offset: 0x004 Command Register    (W) */
  __IO   uint32_t  SR;           /*!< Offset: 0x008 Status Register     (R) */
  __IO   uint32_t  IR;           /*!< Offset: 0x00C Interrupt Register  (R) */
  __IO   uint32_t  IER;          /*!< Offset: 0x010 Interrupt Enable Register    (R/W) */
         uint32_t  RESERVED1;
  __IO   uint32_t  BTR0;         /*!< Offset: 0x018 Bus Timing 0 Register    (R) */
  __IO   uint32_t  BTR1;         /*!< Offset: 0x01C Bus Timing 1 Register    (R) */
  __IO   uint32_t  OCR;          /*!< Offset: 0x020 Output Control Register  (R) */
         uint32_t  RESERVED2[2];
  __IO   uint32_t  ALC;          /*!< Offset: 0x02C Arbitration Lost Capture Register    (R) */
  __IO   uint32_t  ECC;          /*!< Offset: 0x030 Error Code Capture Register    (R) */
  __IO   uint32_t  EWLR;         /*!< Offset: 0x034 Error Warning Register    (R) */
  __IO   uint32_t  RXERR;        /*!< Offset: 0x038 Receive Error Counter Register    (R) */
  __IO   uint32_t  TXERR;        /*!< Offset: 0x03C Transmit Error Register    (R) */
	__IO	 uint32_t  FRAMEINFO;    /*!< Offset: 0x040 Transmit Buffer (Frame Information) Register    (W) */
  __IO   uint32_t  DATAINFO[12]; /*!< Offset: 0x044 - 0x70 Transmit Buffer (Frame Information) Register    (W) */
  __I    uint32_t  RMC;          /*!< Offset: 0x074 Receive Message Count Register    (R) */
  __I    uint32_t  RBSA;         /*!< Offset: 0x078 Receive Buffer Start Address Register    (R) */
  __IO   uint32_t  CDR;          /*!< Offset: 0x07C Clock Divider Register    (R/W) */
  __I    uint32_t  RXFIFO[64];   /*!< Offset: 0x080 - 0x Receive FFIO    (R) */
  __O    uint32_t  TB[13];       /*!< Offset: 0x000 Transmit Buffer    (R) */
}HHD_CAN_TypeDef;


/*------------- Universal Asynchronous Receiver Transmitter (UART) -----------*/
/** @addtogroup CMSDK_UART CMSDK Universal Asynchronous Receiver/Transmitter
  memory mapped structure for CMSDK_UART
  @{
*/
typedef struct
{
  __IO   uint32_t  DATA;          /*!< Offset: 0x000 Data Register    (R/W) */
  __IO   uint32_t  STATE;         /*!< Offset: 0x004 Status Register  (R/W) */
  __IO   uint32_t  CTRL;          /*!< Offset: 0x008 Control Register (R/W) */
  union {
    __I    uint32_t  INTSTATUS;   /*!< Offset: 0x00C Interrupt Status Register (R/ ) */
    __O    uint32_t  INTCLEAR;    /*!< Offset: 0x00C Interrupt Clear Register ( /W) */
    };
  __IO   uint32_t  BAUDDIV;       /*!< Offset: 0x010 Baudrate Divider Register (R/W) */

} HHD_UART_TypeDef;

/*--------------------PWM module------------------------------------------------*/
typedef struct
{
  __IO uint32_t CTRL;                   /*!< Offset: 0 control register (R/W) */
  __IO uint32_t FCTRL;                  /*!< Offset: 0x04 Fault control Register (R/W) */
  __IO uint32_t FLTACK;                 /*!< Offset: 0x08 Fault Status/Acknowldge Register (R/W)  */
  __IO uint32_t OUT;                    /*!< Offset: 0x0c Output Control Register (R/W) */
  __IO uint32_t CNTR;                   /*!< Offset: 0x10 Counter Register (R)  */
  __IO uint32_t CMOD;                   /*!< Offset: 0x14 Count Modulo Register (R/W)  */
  __IO uint32_t VAL[6];                 /*!< Offset: 0x18 Value Register 0 (R/W) */
       uint32_t RESERVED1[2];
  __IO uint32_t DTIM0;                  /*!< Offset: 0x38 Deadtime Register 0 (R/W)*/
  __IO uint32_t DTIM1;                  /*!< Offset: 0x3C Deadtime Register 1 (R/W)*/
  __IO uint32_t DMAP0;                  /*!< Offset: 0x40 Disable Mapping Register 0 (R/W) */
  __IO uint32_t DMAP1;                  /*!< Offset: 0x44 Disable Mapping Register 1 (R/W) */
  __IO uint32_t CNFG;                   /*!< Offset: 0x48 Config Register (R/W) */
  __IO uint32_t CCTRL;                  /*!< Offset: 0x4C Channel Control Register (R/W) */
  __IO uint32_t FPORTCTRL;              /*!< Offset:  0x50 Port Register (R/W) */
  __IO uint32_t ICCTRL;                 /*!< Offset: 0x54 Internal Correction Control Register (R/W) */
       uint32_t RESERVED2[2];
  __IO uint32_t INVCTRL;                /*!< Offset: 0x60 Invert output Control Register (R/W) */
  __IO uint32_t CNTRINI;                /*!< Offset: 0x64 Counter Init Register (R/W) */ 
}HHD_PWM_TypeDef;


/*------------- Watchdog Timer (WDT) -----------------------------------------*/
/** @addtogroup HHD_WDT HHD103 WatchDog Timer 
  @{
*/
typedef struct
{
  __IO uint32_t MOD;                    /*!< Offset: 0x000 Watchdog mode register (R/W) */
  __IO uint32_t TC;                     /*!< Offset: 0x004 Watchdog timer constant register (R/W) */
  __O  uint32_t FEED;                   /*!< Offset: 0x008 Watchdog feed sequence register ( /W) */
  __I  uint32_t TV;                     /*!< Offset: 0x00C Watchdog timer value register (R/ ) */
  __IO uint32_t WDCLKSEL;               /*!< Offset: 0x010 Watchdog clock source selectuin register (R/W ) */ 
  __IO uint32_t WARNINT;                /*!< Offset: 0x014 Watchdog Warning Interrupt compare value register (R/W ) */
  __IO uint32_t WINDOW;                 /*!< Offset: 0x018 Watchdog Window compare value register (R/W ) */  
} HHD_WDT_TypeDef;
/*@}*/ /* end of group HHD_WDT */

/*------------- power Management Unit (PMU) -----------------------------------------*/
/** @addtogroup HHD_WDT HHD103 WatchDog Timer 
  @{
*/
typedef struct
{
  __IO uint32_t PCON;                    /*!< Offset: 0x000 Power Control Register (R/W) */
       uint32_t reserved[4];
  __IO uint32_t SYSCON;                  /*!< Offset: 0x014 System Config Register (R/W) */
} HHD_PMU_TypeDef;
/*@}*/ /* end of group HHD_WDT */


/*------------- Inter-Integrated Circuit (I2C) -------------------------------*/
/** @addtogroup HHD_I2C HHD103 I2C-Bus Interface 
  @{
*/
typedef struct
{
  __IO uint32_t CONSET;                 /*!< Offset: 0x000 I2C Control Set Register (R/W) */
  __I  uint32_t STAT;                   /*!< Offset: 0x004 I2C Status Register (R/ ) */
  __IO uint32_t DAT;                    /*!< Offset: 0x008 I2C Data Register (R/W) */
  __IO uint32_t ADR0;                   /*!< Offset: 0x00C I2C Slave Address Register 0 (R/W) */
  __IO uint32_t SCLH;                   /*!< Offset: 0x010 SCH Duty Cycle Register High Half Word (R/W) */
  __IO uint32_t SCLL;                   /*!< Offset: 0x014 SCL Duty Cycle Register Low Half Word (R/W) */
  __O  uint32_t CONCLR;                 /*!< Offset: 0x018 I2C Control Clear Register ( /W) */
  __IO uint32_t MMCTRL;                 /*!< Offset: 0x01C Monitor mode control register (R/W) */
  __IO uint32_t ADR1;                   /*!< Offset: 0x020 I2C Slave Address Register 1 (R/W) */
  __IO uint32_t ADR2;                   /*!< Offset: 0x024 I2C Slave Address Register 2 (R/W) */
  __IO uint32_t ADR3;                   /*!< Offset: 0x028 I2C Slave Address Register 3 (R/W) */
  __I  uint32_t DATA_BUFFER;            /*!< Offset: 0x02C Data buffer register ( /W) */
  __IO uint32_t MASK0;                  /*!< Offset: 0x030 I2C Slave address mask register 0 (R/W) */
  __IO uint32_t MASK1;                  /*!< Offset: 0x034 I2C Slave address mask register 1 (R/W) */
  __IO uint32_t MASK2;                  /*!< Offset: 0x038 I2C Slave address mask register 2 (R/W) */
  __IO uint32_t MASK3;                  /*!< Offset: 0x03C I2C Slave address mask register 3 (R/W) */
} HHD_I2C_TypeDef;
/*@}*/ /* end of group HHD_I2C */
  

/*------------- Serial Peripheral Interface (SPI) -----------------------*/
/** @addtogroup HHD_SPI HHD103 Serial Peripheral Interface 
  @{
*/
typedef struct
{
  __IO uint32_t CR0;                    /*!< Offset: 0x000 Control Register 0 (R/W) */
  __IO uint32_t CR1;                    /*!< Offset: 0x004 Control Register 1 (R/W) */
  __IO uint32_t DR;                     /*!< Offset: 0x008 Data Register (R/W) */
  __I  uint32_t SR;                     /*!< Offset: 0x00C Status Registe (R/ ) */
  __IO uint32_t CPSR;                   /*!< Offset: 0x010 Clock Prescale Register (R/W) */
  __IO uint32_t IMSC;                   /*!< Offset: 0x014 Interrupt Mask Set and Clear Register (R/W) */
  __IO uint32_t RIS;                    /*!< Offset: 0x018 Raw Interrupt Status Register (R/W) */
  __IO uint32_t MIS;                    /*!< Offset: 0x01C Masked Interrupt Status Register (R/W) */
  __IO uint32_t ICR;                    /*!< Offset: 0x020 Interrupt Clear Register (R/W) */
  __IO uint32_t DMACR;                  /*!< Offset: 0x024 DMA Control Register (R/W) */
} HHD_SPI_TypeDef;
/*@}*/ /* end of group HHD_SPI */


/*------------- Analog-to-Digital Converter (ADC) ----------------------------*/
/** @addtogroup HHD_ADC HHD103 Analog-to-Digital Converter 
  @{
*/
typedef struct
{
  __IO uint32_t CR;                     /*!< Offset: 0x000       A/D Control Register (R/W) */
  __IO uint32_t GDR;                    /*!< Offset: 0x004       A/D Global Data Register (R/W) */
  __IO uint32_t CHSEL;                  /*!< Offset: 0x008       A/D Channel Select Register (R/W) */
  __IO uint32_t INTEN;                  /*!< Offset: 0x00C       A/D Interrupt Enable Register (R/W) */
  __IO uint32_t DR[4];                  /*!< Offset: 0x010-0x01C A/D Channel 0..7 Data Register (R/W) */
  __IO uint32_t HL0;                    /*!< Offset: 0x020       A/D High Limit data0 Register (R/W) */
  __IO uint32_t HL1;                    /*!< Offset: 0x024       A/D High Limit Data1 Register (R/W) */
  __IO uint32_t LL0;                    /*!< Offset: 0x028       A/D Low Limit Data0 Register (R/W) */
  __IO uint32_t LL1;                    /*!< Offset: 0x02C       A/D Low Limit Data1 Register (R/W) */
  __I  uint32_t INTSTAT;                /*!< Offset: 0x030       A/D Interrupt Status Register (R) */
  __IO uint32_t DIV;                    /*!< Offset: 0x034       A/D Clock Divider Register (R/W) */
  __IO uint32_t PWMFLT;
  __IO uint32_t MUXCR;                  /*!< Offset: 0x038       A/D Channel Mux Control Register (R/W) */
  __IO uint32_t SWTRIG;                 /*!< Offset: 0x034       A/D Software Control Register (R/W) */
} HHD_ADC_TypeDef;


/*@}*/ /* end of group HHD_ADC */

/*@}*/ /* end of group HHD_ADC */

/*-------------- Digital-to-Analog Converter (DAC) ----------------------------*/
/** @addtogroup HHD_DAC HHD103 Digital-to-Analog Converter
  @{
*/
typedef struct
{
  __IO uint32_t DAC1CTRL;
  __O  uint32_t DAC1BUF;
       uint32_t RESV[2];
  __IO uint32_t DAC2CTRL;
  __O  uint32_t DAC2BUF;
}HHD_DAC_TypeDef;

/*@}*/ /* end of group HHD_DAC */

/*------------- CRC Interface ----------------------------*/
/** @addtogroup CRC Engine 
  @{
*/
typedef struct
{
  __IO uint32_t MODE;
  __IO uint32_t SEED;
  union {
  __I  uint32_t SUM;
  __O  uint32_t WR_DATA_DWORD;
  __O  uint16_t WR_DATA_WORD;
       uint16_t RESERVED_WORD;
  __O  uint8_t  WR_DATA_BYTE;
       uint8_t  RESERVED_BYTE[3];
  };
} HHD_CRC_TypeDef;

/**
  * @brief Configure information block (CIB)
  */

typedef struct {                                    /*!< CIB Structure                                                         */
  __I  uint32_t  RESERVED0;
  __I  uint32_t  FUNCDESC;                          /*!< Device function description                                           */
  __I  uint32_t  DID;                               /*!< Device ID                                                             */
  __I  uint32_t  VERID;                             /*!< Hardware version                                                      */
  __I  uint32_t  UNIQUEID0;                         /*!< Unique device serial no- low 32-bit                                   */
  __I  uint32_t  UNIQUEID1;                         /*!< Unique device serial no- high 32-bit                                  */
  __I  uint32_t  IRCTRIM;                           /*!< Internal IRC trim bits                                                */
} HHD_CIB_Type;



/*@}*/ /* end of group HHD_FMC */


#if defined ( __CC_ARM   )
#pragma no_anon_unions
#endif

/******************************************************************************/
/*                         Peripheral memory map                              */
/******************************************************************************/
/* Base addresses                                                             */
#define HHD_FLASH_BASE        (0x00000000UL)
#define HHD_RAM_BASE          (0x20000000UL)
#define HHD_APB1_BASE         (0x40000000UL)
#define HHD_APB2_BASE         (0x40010000UL)
#define HHD_AHB_BASE          (0x40020000UL)
#define HHD_CIB_BASE          (0x1FFF1400UL)

/* APB0 peripherals                                                           */
#define HHD_TIM2_BASE         (HHD_APB1_BASE + 0x0000)
#define HHD_TIM3_BASE         (HHD_APB1_BASE + 0x0400)
#define HHD_TIM4_BASE         (HHD_APB1_BASE + 0x0800)
#define HHD_TIM5_BASE         (HHD_APB1_BASE + 0x0c00)
#define HHD_TIM6_BASE         (HHD_APB1_BASE + 0x1000)
#define HHD_TIM7_BASE         (HHD_APB1_BASE + 0x1400)
#define HHD_TIM12_BASE        (HHD_APB1_BASE + 0x1800)
#define HHD_TIM13_BASE        (HHD_APB1_BASE + 0x1c00)
#define HHD_TIM14_BASE        (HHD_APB1_BASE + 0x2000)
#define HHD_RTC_BASE          (HHD_APB1_BASE + 0x2800)
#define HHD_WWDT_BASE         (HHD_APB1_BASE + 0x2c00)
#define HHD_IWDT_BASE         (HHD_APB1_BASE + 0x3000)
#define HHD_SPI2_BASE         (HHD_APB1_BASE + 0x3800)
#define HHD_SPI3_BASE         (HHD_APB1_BASE + 0x3c00)
#define HHD_UART2_BASE        (HHD_APB1_BASE + 0x4400)
#define HHD_UART3_BASE        (HHD_APB1_BASE + 0x4800)
#define HHD_UART4_BASE        (HHD_APB1_BASE + 0x4c00)
#define HHD_UART5_BASE        (HHD_APB1_BASE + 0x5000)
#define HHD_I2C1_BASE         (HHD_APB1_BASE + 0x5400)
#define HHD_I2C2_BASE         (HHD_APB1_BASE + 0x5800)
#define HHD_USB_BASE          (HHD_APB1_BASE + 0x5c00)
#define HHD_USBSRAM_BASE      (HHD_APB1_BASE + 0x6000)
#define HHD_CAN_BASE          (HHD_APB1_BASE + 0x6400)
#define HHD_BKP_BASE          (HHD_APB1_BASE + 0x6c00)
#define HHD_PWR_BASE          (HHD_APB1_BASE + 0x7000)
#define HHD_DAC_BASE          (HHD_APB1_BASE + 0x7400)

#define HHD_AFIO_BASE         (HHD_APB2_BASE + 0x0000)
#define HHD_EXTI_BASE         (HHD_APB2_BASE + 0x0400)
#define HHD_GPIOA_BASE        (HHD_APB2_BASE + 0x0800)
#define HHD_GPIOB_BASE        (HHD_APB2_BASE + 0x0C00)
#define HHD_GPIOC_BASE        (HHD_APB2_BASE + 0x1000)
#define HHD_GPIOD_BASE        (HHD_APB2_BASE + 0x1400)
#define HHD_GPIOE_BASE        (HHD_APB2_BASE + 0x1800)
#define HHD_GPIOF_BASE        (HHD_APB2_BASE + 0x1c00)
#define HHD_GPIOG_BASE        (HHD_APB2_BASE + 0x2000)
#define HHD_ADC1_BASE         (HHD_APB2_BASE + 0x2400)
#define HHD_ADC2_BASE         (HHD_APB2_BASE + 0x2800)
#define HHD_TIM1_BASE         (HHD_APB2_BASE + 0x2c00)
#define HHD_SPI1_BASE         (HHD_APB2_BASE + 0x3000)
#define HHD_TIM8_BASE         (HHD_APB2_BASE + 0x3400)
#define HHD_UART1_BASE        (HHD_APB2_BASE + 0x3800)
#define HHD_ADC3_BASE         (HHD_APB2_BASE + 0x3c00)
#define HHD_TIM9_BASE         (HHD_APB2_BASE + 0x4c00)
#define HHD_TIM10_BASE        (HHD_APB2_BASE + 0x5000)
#define HHD_TIM11_BASE        (HHD_APB2_BASE + 0x5400)

#define HHD_DMA1_BASE         (HHD_AHB_BASE  + 0x0000)
#define HHD_DMA2_BASE         (HHD_AHB_BASE  + 0x0400)
#define HHD_SYSCON_BASE       (HHD_AHB_BASE  + 0x1000)
#define HHD_FMC_BASE          (HHD_AHB_BASE  + 0x2000)
#define HHD_CRC_BASE          (HHD_AHB_BASE  + 0x3000)

/******************************************************************************/
/*                         Peripheral declaration                             */
/******************************************************************************/
#define HHD_CIB               ((HHD_CIB_Type       *) HHD_CIB_BASE)
#define HHD_WWDT              ((HHD_WDT_TypeDef    *) HHD_WWDT_BASE)
#define HHD_IWDT              ((HHD_WDT_TypeDef    *) HHD_IWDT_BASE)
#define HHD_UART1             ((HHD_UART_TypeDef   *) HHD_UART1_BASE)
#define HHD_UART2             ((HHD_UART_TypeDef   *) HHD_UART2_BASE)
#define HHD_UART3             ((HHD_UART_TypeDef   *) HHD_UART3_BASE)
#define HHD_UART4             ((HHD_UART_TypeDef   *) HHD_UART4_BASE)
#define HHD_UART5             ((HHD_UART_TypeDef   *) HHD_UART5_BASE)
#define HHD_TIM6              ((HHD_BASETMR_TypeDef *) HHD_TIM6_BASE)
#define HHD_TIM7              ((HHD_BASETMR_TypeDef *) HHD_TIM7_BASE)
#define HHD_TIM2              ((HHD_TMR_TypeDef    *) HHD_TIM2_BASE)
#define HHD_TIM3              ((HHD_TMR_TypeDef    *) HHD_TIM3_BASE)
#define HHD_TIM4              ((HHD_TMR_TypeDef    *) HHD_TIM4_BASE)
#define HHD_TIM5              ((HHD_TMR_TypeDef    *) HHD_TIM4_BASE)
#define HHD_TIM9              ((HHD_TMR_TypeDef    *) HHD_TIM4_BASE)
#define HHD_TIM10             ((HHD_TMR_TypeDef    *) HHD_TIM4_BASE)
#define HHD_TIM11             ((HHD_TMR_TypeDef    *) HHD_TIM4_BASE)
#define HHD_TIM12             ((HHD_TMR_TypeDef    *) HHD_TIM4_BASE)
#define HHD_TIM13             ((HHD_TMR_TypeDef    *) HHD_TIM4_BASE)
#define HHD_TIM14             ((HHD_TMR_TypeDef    *) HHD_TIM4_BASE)
#define HHD_RTC							 ((HHD_RTC_TypeDef    *) HHD_RTC_BASE)
#define HHD_ADC1              ((HHD_ADC_TypeDef    *) HHD_ADC1_BASE)
#define HHD_ADC2              ((HHD_ADC_TypeDef    *) HHD_ADC2_BASE)
#define HHD_ADC3              ((HHD_ADC_TypeDef    *) HHD_ADC3_BASE)
#define HHD_DAC               ((HHD_DAC_TypeDef    *) HHD_DAC_BASE)
#define HHD_I2C1              ((HHD_I2C_TypeDef    *) HHD_I2C1_BASE)
#define HHD_I2C2              ((HHD_I2C_TypeDef    *) HHD_I2C2_BASE)
#define HHD_USB               ((HHD_USB_TypeDef    *) HHD_USB_BASE )
#define HHD_CAN               ((HHD_CAN_TypeDef    *) HHD_CAN_BASE )
#define HHD_AFIO              ((HHD_AFIO_TypeDef   *) HHD_AFIO_BASE )
#define HHD_SYSCON            ((HHD_SYSCON_TypeDef *) HHD_SYSCON_BASE)
#define HHD_TIM1              ((HHD_PWM_TypeDef    *) HHD_TIM1_BASE)
#define HHD_TIM8              ((HHD_PWM_TypeDef    *) HHD_TIM8_BASE)
#define HHD_FMC               ((HHD_FMC_TypeDef    *) HHD_FMC_BASE)
#define HHD_CRC               ((HHD_CRC_TypeDef    *) HHD_CRC_BASE)
#define HHD_GPIOA             ((HHD_GPIO_TypeDef   *) HHD_GPIOA_BASE )
#define HHD_GPIOB             ((HHD_GPIO_TypeDef   *) HHD_GPIOB_BASE )
#define HHD_GPIOC             ((HHD_GPIO_TypeDef   *) HHD_GPIOC_BASE )
#define HHD_GPIOD             ((HHD_GPIO_TypeDef   *) HHD_GPIOD_BASE )
#define HHD_GPIOE             ((HHD_GPIO_TypeDef   *) HHD_GPIOE_BASE )
#define HHD_GPIOF             ((HHD_GPIO_TypeDef   *) HHD_GPIOF_BASE )
#define HHD_GPIOG             ((HHD_GPIO_TypeDef   *) HHD_GPIOG_BASE )
#define HHD_DMA1              ((HHD_DMA_TypeDef    *) HHD_DMA1_BASE )
#define HHD_DMA2              ((HHD_DMA_TypeDef    *) HHD_DMA2_BASE )
#define HHD_PMU               ((HHD_PMU_TypeDef    *) HHD_PWR_BASE )
#define HHD_SPI1              ((HHD_SPI_TypeDef    *) HHD_SPI1_BASE )
#define HHD_SPI2              ((HHD_SPI_TypeDef    *) HHD_SPI2_BASE )
#define HHD_SPI3              ((HHD_SPI_TypeDef    *) HHD_SPI3_BASE )


/**
  * @}
  */

 /**
  * @}
  */ 

#ifdef USE_STDPERIPH_DRIVER
  #include "hhd32f10x_conf.h"
#endif


#ifdef __cplusplus
}
#endif


#endif  /* __CMSDK_H__ */

