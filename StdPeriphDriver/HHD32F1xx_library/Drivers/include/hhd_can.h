/*****************************************************************************
 *   hhf_can.h:  Header file for  HHD32F1xx Family Microprocessors
 *
 *   Copyright(C) 2015,  tech. Ltd.
 *   All rights reserved.
 *
 *   History
 *   2015  ver 1.00    Prelimnary version, first Release
 *
******************************************************************************/
#ifndef __HHD_CAN_H__
#define __HHD_CAN_H__


#include "hhd32f1xx.h"


#define ENABLECAN1CLK  (SYSCON->SYSAPB1CLKCTRL.all |= (1<<25))
#define ENABLECAN2CLK  (SYSCON->SYSAPB1CLKCTRL.all |= (1<<26))

#define DISABLECAN1CLK (SYSCON->SYSAPB1CLKCTRL.all &= ~(1<<25))
#define DISABLECAN2CLK (SYSCON->SYSAPB1CLKCTRL.all &= ~(1<<26))

#define CAN1_TX_PA12 0x15
#define CAN1_TX_PB9  0x15
#define CAN1_RX_PA11 0x15
#define CAN1_RX_PB8  0x15

//Mode bit
#define SleepMode				0x10
#define ACCFMode				0x08
#define SelfTestMode		0x04
#define ListenOnlyMode	0x02
#define ResetMode				0x01
#define ActiveMode			0x00

//Interrupt enable bit
#define BEIE 0x80
#define ALIE 0x40
#define EPIE 0x20
#define WUIE 0x10
#define DOIE 0x08
#define EIE  0x04
#define TIE  0x02
#define RIE  0x01


//CMD bit
#define SelfRecReq					0x10
#define	ClearDataOverrun		0x08
#define	ReleaseRecBuf				0x04
#define AbortTrans					0x02
#define	TransReq						0x01


//Status Register bit
#define BusSt		0x80
#define	ErrorSt	0x40
#define	TranSt	0x20
#define	RecSt		0x10
#define	TranComplete	0x08
#define	TranBufSt	0x04
#define	DataOvSt	0x02
#define	RecBufSt	0x01
#if 1
//--CAN Registers BITS Field---------------------------------------------------------------------------------------
struct CAN_MOD_BITS	{
				uint32_t RM:1;							 // sleep mode
	      uint32_t LOM:1;              // Acceptance filter mode
	      uint32_t STM:1;              // Self test mode
	      uint32_t AFM:1;              // Listen only mode
	      uint32_t SM:1;               // Reset mode
				uint32_t RSVD:27;						 // 31:5 reserved
};
union CAN_MOD_REG {
				uint32_t					all;
				struct  CAN_MOD_BITS		bit;
};

struct CAN_CMR_BITS{
				uint32_t TR:1;                //Transmission Request
	      uint32_t AT:1;                //Abort Transmission
        uint32_t RRB:1;               //Release Receive Buffer
        uint32_t CDO:1;               //Clear Data Overrun
        uint32_t SRR:1;               //Self Reception Request
        uint32_t RSVD:27;             //31:5 reserved
};
union CAN_CMR_REG {
			  uint32_t					all;
				struct  CAN_CMR_BITS		bit;
};

struct CAN_SR_BITS{
				uint32_t RBS:1;              //Receive Buffer Staus    
	      uint32_t DOS:1;              //Data Overrun Status
	      uint32_t TBS:1;              //Transmit Buffer Status
	      uint32_t TCS:1;              //Transmission Complete Status
	      uint32_t RS:1;               //Receive Status
	      uint32_t TS:1;               //Transmit Status
	      uint32_t ES:1;               //Error Status
	      uint32_t BS:1;               //Bus Status
	      uint32_t RSVD:24;            //31:8 reserved
};
union CAN_SR_REG {
			  uint32_t					all;
				struct  CAN_SR_BITS		bit;
};

struct CAN_IR_BITS{
				uint32_t RI:1;              //Receive Interrupt   
	      uint32_t TI:1;              //Transmit Interrupt
	      uint32_t EI:1;              //Error Warning Interrupt
	      uint32_t DOI:1;             //Data Overrun Interrupt
	      uint32_t WUI:1;             //Wake-Up Interrupt
	      uint32_t EPI:1;             //Error Passive Interrupt
	      uint32_t ALI:1;             //Arbitration Lost Interrupt
	      uint32_t BEI:1;             //Bus Error Interrupt
	      uint32_t RSVD:24;           //31:8 reserved  
};
union CAN_IR_REG {
			  uint32_t					all;
				struct  CAN_IR_BITS		bit;
};

struct CAN_IER_BITS{
				uint32_t RIEN:1;              //Receive Interrupt Enable  
	      uint32_t TIEN:1;              //Transmit Interrupt Enable
	      uint32_t EIEN:1;              //Error Warning Interrupt Enable
	      uint32_t DOIEN:1;             //Data Overrun Interrupt Enable
	      uint32_t WUIEN:1;             //Wake-Up Interrupt Enable
	      uint32_t EPIEN:1;             //Error Passive Interrupt Enable
	      uint32_t ALIEN:1;             //Arbitration Lost Interrupt Enable
	      uint32_t BEIEN:1;             //Bus Error Interrupt Enable
	      uint32_t RSVD:24;           //31:8 reserved
};
union CAN_IER_REG {
			  uint32_t					all;
				struct  CAN_IER_BITS		bit;
};

struct CAN_BTR0_BITS{
				uint32_t BRP:6;              //Baud Rate Prescaler (BRP).
	      uint32_t SJW:2;              //Synchronization Jump Width (SJW)  
	      uint32_t RSVD:24;	           //31:8 reserved
};
union CAN_BTR0_REG {
			  uint32_t					all;
				struct  CAN_BTR0_BITS		bit;
};

struct CAN_BTR1_BITS{
				uint32_t TSEG1:4;              //
	      uint32_t TSEG2:3;              //
	      uint32_t SAM:1;                //Sampling 
	      uint32_t RSVD:24;	             //31:8 reserved	
};
union CAN_BTR1_REG {
			  uint32_t					all;
				struct  CAN_BTR1_BITS		bit;
};
struct CAN_OCR_BITS{
				uint32_t OCMODE:2;              //Selection of two possible output driver configurations:
	      uint32_t RSVD:30;      					//31:3 reserved	
};
union CAN_OCR_REG {
			  uint32_t					all;
				struct  CAN_OCR_BITS		bit;
};

struct CAN_ALC_BITS{
				uint32_t ALC:5;                //This read-only register records the bit position at which arbitration was lost
	      uint32_t RSVD:27;      					//31:5 reserved	
};
union CAN_ALC_REG {
			  uint32_t					all;
				struct  CAN_ALC_BITS		bit;
};

struct CAN_ECC_BITS{
				uint32_t SEGMENTCODE:5;            //Segment coede err
	      uint32_t DIRECTION:1;              //If ¡®1¡¯, the error occurred during reception. If ¡®0¡¯, the error occurred during transmission.
	      uint32_t ERRORCODE:2;              //00:Bit erro, 01:Bit Form erro, 10:Stuff error 11:Some other type of error
	      uint32_t RSVD:24;	                 //31:8 reserved	
};
union CAN_ECC_REG {
			  uint32_t					all;
				struct  CAN_ECC_BITS		bit;
};

struct CAN_EWLR_BITS{
				uint32_t EWL:8;                   // Defines the number of errors after which an Error Warning Interrupt should be generated
	      uint32_t RSVD:24;
};
union CAN_EWLR_REG {
			  uint32_t					all;
				struct  CAN_EWLR_BITS		bit;
};

struct CAN_RXERR_BITS{
				uint32_t RXERR:8;                   // Receive error counter
	      uint32_t RSVD:24;
};
union CAN_RXERR_REG {
			  uint32_t					all;
				struct  CAN_RXERR_BITS		bit;
};

struct CAN_TXERR_BITS{
				uint32_t TXERR_:8;                   // Transmit error counter
	      uint32_t RSVD:24;
};
union CAN_TXERR_REG {
			  uint32_t					all;
				struct  CAN_RXERR_BITS		bit;
};

struct CAN_FRAMEINFO_BITS{
			  uint32_t DLC:4;                //Specify the number of data bytes included in the message being sent.
	      uint32_t RSVD0:2;              //4:5 reserved
	      uint32_t RTR:1;                //Remote transmission request.
	      uint32_t FF:1;                 //The FF bit selects the type of frame format to be transmitted
	      uint32_t RSVD1:24;	           //31:8 reserved	
};
union  CAN_FRAMEINFO_REG {
			  uint32_t					        all;
				struct  CAN_FRAMEINFO_BITS		bit;
};


struct CAN_DATAINFO_BITS{
			  uint32_t DATA:8;               //
	      uint32_t RSVD:24;	           //31:8 reserved 
};
union CAN_DATAINFO_REG {
			  uint32_t					all;
				struct  CAN_DATAINFO_BITS		bit;
};

struct CAN_ACR_BITS{
				uint32_t ACR:8;                //
	      uint32_t RSVD:24;	           //31:8 reserved 
};
union CAN_ACR_REG {
			  uint32_t					all;
				struct  CAN_ACR_BITS		bit;
};

struct CAN_AMR_BITS{
				uint32_t AMR:8;                //
	      uint32_t RSVD:24;	           //31:8 reserved 
};
union CAN_AMR_REG {
			  uint32_t					all;
				struct  CAN_AMR_BITS		bit;
};

struct CAN_RMC_BITS{
				uint32_t RMC:5;              //Receive message counter
	      uint32_t RSVD:27;	           //31:5 reserved 
};
union CAN_RMC_REG {
			  uint32_t					all;
				struct  CAN_RMC_BITS		bit;
};

struct CAN_RBSA_BITS{
				uint32_t RBSA:6;             //Receive buffer start address
	      uint32_t RSVD:26;	           //31:6 reserved 
};
union CAN_RBSA_REG {
			  uint32_t					all;
				struct  CAN_RBSA_BITS		bit;
};

struct CAN_CDR_BITS{
				uint32_t CDR:3;                //The bits CD.2 to CD.0 define the frequency at the external CLKOUT pin
	      uint32_t CLKOFF:1;             //Setting this bit allows the external CLKOUT signal to be disabled
	      uint32_t RSVD:28;	             //31:4 reserved	
};
union CAN_CDR_REG {
			  uint32_t					all;
				struct  CAN_CDR_BITS		bit;
};


struct CAN_RXFIFO_BITS{
			 uint32_t RX_DATA:8;
	     uint32_t RSVD:24;
};
union CAN_RXFIFO_REG {
			  uint32_t					all;
				struct  CAN_RXFIFO_BITS		bit;
};

struct CAN_TB_BITS{
			 uint32_t  TX_DATA:8;
	     uint32_t RSVD:24;
};
union CAN_TB_REG {
			  uint32_t					all;
				struct  CAN_TB_BITS		bit;
};
// struct CAN_ACR_BITS{
// 				uint32_t ACR:8;
// 	      uint32_t RSVD:24;
// };
// union CAN_ACR_REG{
// 				uint32_t          all;
// 	      struct CAN_ACR_BITS bit;
// };

// struct CAN_AMR_BITS{
// 				uint32_t ACR:8;
// 	      uint32_t RSVD:24;
// };
// union CAN_AMR_REG{
// 				uint32_t          all;
// 	      struct CAN_AMR_BITS bit;
// };
struct CAN_ACCEPTANCE_FILTER
{
					union CAN_ACR_REG ACR[4];
	        union CAN_AMR_REG AMR[4];
};

struct CAN_TxDATAINFO
{
					union  CAN_FRAMEINFO_REG TxFRAME;
	        union  CAN_DATAINFO_REG  TxDATA[12]; 
};

struct CAN_RxDATAINFO
{
					union  CAN_FRAMEINFO_REG RxFRAME;
	        union  CAN_DATAINFO_REG  RxDATA[12]; 
};

typedef struct
{ 
  __IO   union CAN_MOD_REG  MOD;          /*!< Offset: 0x000 MOD Register    (R/W) */
  __IO   union CAN_CMR_REG  CMR;          /*!< Offset: 0x004 Command Register    (W) */
  __IO   union CAN_SR_REG SR;           /*!< Offset: 0x008 Status Register     (R) */
  __IO   union CAN_IR_REG IR;           /*!< Offset: 0x00C Interrupt Register  (R) */
  __IO   union CAN_IER_REG IER;          /*!< Offset: 0x010 Interrupt Enable Register    (R/W) */
         uint32_t  RESERVED1;
  __IO   union CAN_BTR0_REG BTR0;         /*!< Offset: 0x018 Bus Timing 0 Register    (R) */
  __IO   union CAN_BTR1_REG BTR1;         /*!< Offset: 0x01C Bus Timing 1 Register    (R) */
  __IO   union CAN_OCR_REG OCR;          /*!< Offset: 0x020 Output Control Register  (R) */
         uint32_t  RESERVED2[2];
  __IO   union CAN_ALC_REG ALC;          /*!< Offset: 0x02C Arbitration Lost Capture Register    (R) */
  __IO   union CAN_ECC_REG ECC;          /*!< Offset: 0x030 Error Code Capture Register    (R) */
  __IO   union CAN_EWLR_REG EWLR;         /*!< Offset: 0x034 Error Warning Register    (R) */
  __IO   union CAN_RXERR_REG RXERR;        /*!< Offset: 0x038 Receive Error Counter Register    (R) */
  __IO   union CAN_TXERR_REG TXERR;        /*!< Offset: 0x03C Transmit Error Register    (R) */
	//__IO	 union CAN_FRAMEINFO_REG FRAMEINFO;    /*!< Offset: 0x040 Transmit Buffer (Frame Information) Register    (W) */
 // __IO   union CAN_DATAINFO_REG DATAINFO[12]; /*!< Offset: 0x044 - 0x70 Transmit Buffer (Frame Information) Register    (W) */
	union {
  __IO   struct CAN_ACCEPTANCE_FILTER  FILTER;
	__O   struct CAN_TxDATAINFO           TxDATAINFO;
	__I    struct CAN_RxDATAINFO         RxDATAINFO;
  }DATAINFO;
  __I    union CAN_RMC_REG RMC;          /*!< Offset: 0x074 Receive Message Count Register    (R) */
  __I    union CAN_RBSA_REG RBSA;         /*!< Offset: 0x078 Receive Buffer Start Address Register    (R) */
  __IO   union CAN_CDR_REG CDR;          /*!< Offset: 0x07C Clock Divider Register    (R/W) */
  __I    union CAN_RXFIFO_REG RXFIFO[64];   /*!< Offset: 0x080 - 0x Receive FFIO    (R) */
  __O    union CAN_TB_REG TB[13];       /*!< Offset: 0x000 Transmit Buffer    (R) */
}HHD32F1_CAN_TypeDef;

#define CAN       ((HHD32F1_CAN_TypeDef     *) HHD_CAN_BASE)

#endif 


void CAN_SetMode(uint32_t mode);
void CAN_EnableInt(uint32_t intbit);
void CAN_DisableInt(uint32_t intbit);
int  CAN_GetStatus(void);
void CAN_ClearStatus(uint32_t clrbit);
void CAN_SetCMD(uint32_t cmddata);
void CAN_ClrCMD(uint32_t cmddata);

 
#endif /* end __CAN */
/*****************************************************************************
**                            End Of File
******************************************************************************/
