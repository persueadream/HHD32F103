 --------------------------------
|                                |
|           更新日志             | 
|                                |
 --------------------------------
 
2017-06-29
1.函数 void IIC_WriteByte(G32F1_IIC_TypeDef *IIC,uint8_t SlaveAddress, uint8_t SubAddr, uint8_t Value)简要说明
  调用该函数后，如 IIC_WriteByte(I2C1,0x00,0xFF,0xAA);，将在中断中进行数据的处理，顺序依次是SlaveAddress,SubAddr,Value。

2016-06-30
从机接收数据时IICMasterBuffer中不存储主机发过来的地址。
1、I2C1(master) Read data from I2C2(slaver) monitor printing information
	IIC_ReadArray  starting
	IIC_M_TX_START, StatValue = 1   
	SLVADDMATCH. StatValue = 10a
	IIC_M_TX_SLAW_ACK, Transmit. StatValue = b
	SLVRXBUFFULL. StatValue = 212
	IIC_M_TX_DAT_ACK, transmit SLA with R. StatValue = 14
	SLVADDMATCH. StatValue = 14a
	IIC_M_TX_SLAW_ACK, Read, ACK. StatValue = b
	SLVTXBUFEMPTY. StatValue = 414
	IIC_M_RX_DAT_ACK, ACK. StatValue = 1d
	SLVTXBUFEMPTY. StatValue = 414
	IIC_M_RX_DAT_ACK, ACK. StatValue = 1d
	SLVTXBUFEMPTY. StatValue = 414
	IIC_M_RX_DAT_ACK, ACK. StatValue = 1d
	SLVTXBUFEMPTY. StatValue = 414
	IIC_M_RX_DAT_ACK, ACK. StatValue = 1d
	SLVTXBUFEMPTY. StatValue = 414
	IIC_M_RX_DAT_ACK, ACK. StatValue = 1d
	SLVTXBUFEMPTY. StatValue = 414
	IIC_M_RX_DAT_ACK, ACK. StatValue = 1d
	SLVTXBUFEMPTY. StatValue = 414
	IIC_M_RX_DAT_ACK, NACK. StatValue = 1d
	SLVTXBUFEMPTY. StatValue = 414
	IIC_M_RX_DAT_ACK, NACK. StatValue = 1d
	IIC_ReadArray  ending
2、I2C1(master) Write data to I2C2(slaver) monitor printing information
	IIC_WriteArray starting
	IIC_M_TX_START, StatValue = 1
	SLVADDMATCH. StatValue = 10a
	IIC_M_TX_SLAW_ACK, Transmit. StatValue = b
	SLVRXBUFFULL. StatValue = 212
	IIC_M_TX_DAT_ACK, transmit. StatValue = 14
	SLVRXBUFFULL. StatValue = 212
	IIC_M_TX_DAT_ACK, transmit. StatValue = 14
	SLVRXBUFFULL. StatValue = 212
	IIC_M_TX_DAT_ACK, transmit. StatValue = 14
	SLVRXBUFFULL. StatValue = 212
	IIC_M_TX_DAT_ACK, transmit. StatValue = 14
	SLVRXBUFFULL. StatValue = 212
	IIC_M_TX_DAT_ACK, transmit. StatValue = 14
	SLVRXBUFFULL. StatValue = 212
	IIC_M_TX_DAT_ACK, transmit. StatValue = 14
	SLVRXBUFFULL. StatValue = 212
	IIC_M_TX_DAT_ACK, transmit. StatValue = 14
	SLVRXBUFFULL. StatValue = 212
	IIC_WriteArray  ending
