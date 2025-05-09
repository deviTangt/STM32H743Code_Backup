
#include "AD7705.h"
#include "gpio.h"
/*
	AD7705模块 / AD7705模块 
      SCK   ------  PB13/SPI2_SCK		PB10 SPI2_SCK
      DOUT  ------  PB14/SPI2_MISO		PC2  SPI2_MISO
      DIN   ------  PB15/SPI3_MOSI		PC1  SPI2_MOSI
      CS    ------  PG7/NRF24L01_CSN	PA5  AD_CS_Pin
      DRDY  ------  PG6/NRF24L01_IRQ	PA6  AD_RDY_Pin
      RST   ------  PG8/NRF_CE			PA4  AD_RST_Pin
*/

#define AD7705_CS_H  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET)
#define AD7705_CS_L  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET)//CS片选宏定义，低电平有效
#define AD7705_RST_H HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4, GPIO_PIN_SET)
#define AD7705_RST_L HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET)//RST使能复位宏定义，低电平有效
#define AD7705_DRDY  HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_6)  //DRDY,低电平时表示AD7705可读
/* 通信寄存器bit定义 */
enum
{
	/* 寄存器选择  RS2 RS1 RS0  */
	REG_COMM	= 0x00,	/* 通信寄存器 */
	REG_SETUP	= 0x10,	/* 设置寄存器 */
	REG_CLOCK	= 0x20,	/* 时钟寄存器 */
	REG_DATA	= 0x30,	/* 数据寄存器 */
	REG_ZERO_CH1	= 0x60,	/* CH1 偏移寄存器 */
	REG_FULL_CH1	= 0x70,	/* CH1 满量程寄存器 */
	REG_ZERO_CH2	= 0x61,	/* CH2 偏移寄存器 */
	REG_FULL_CH2	= 0x71,	/* CH2 满量程寄存器 */

	/* 读写操作 */
	WRITE 		= 0x00,	/* 写操作 */
	READ 		= 0x08,	/* 读操作 */

	/* 通道 */
	CH_1		= 0,	/* AIN1+  AIN1- */
	CH_2		= 1,	/* AIN2+  AIN2- */
	CH_3		= 2,	/* AIN1-  AIN1- */
	CH_4		= 3		/* AIN1-  AIN2- */
};

/* 设置寄存器bit定义 */
enum
{
	MD_NORMAL		= (0 << 6),	/* 正常模式 */
	MD_CAL_SELF		= (1 << 6),	/* 自校准模式 */
	MD_CAL_ZERO		= (2 << 6),	/* 校准0刻度模式 */
	MD_CAL_FULL		= (3 << 6),	/* 校准满刻度模式 */

	GAIN_1			= (0 << 3),	/* 增益 */
	GAIN_2			= (1 << 3),	/* 增益 */
	GAIN_4			= (2 << 3),	/* 增益 */
	GAIN_8			= (3 << 3),	/* 增益 */
	GAIN_16			= (4 << 3),	/* 增益 */
	GAIN_32			= (5 << 3),	/* 增益 */
	GAIN_64			= (6 << 3),	/* 增益 */
	GAIN_128		= (7 << 3),	/* 增益 */

	/* 无论双极性还是单极性都不改变任何输入信号的状态，它只改变输出数据的代码和转换函数上的校准点 */
	BIPOLAR			= (0 << 2),	/* 双极性输入 */
	UNIPOLAR		= (1 << 2),	/* 单极性输入 */

	BUF_NO			= (0 << 1),	/* 输入无缓冲（内部缓冲器不启用) */
	BUF_EN			= (1 << 1),	/* 输入有缓冲 (启用内部缓冲器) 可处理高阻抗源 */

	FSYNC_0			= 0,
	FSYNC_1			= 1		/* 不启用 */
};

/* 时钟寄存器bit定义 */
enum
{
	CLKDIS_0	= 0x00,		/* 时钟输出使能 （当外接晶振时，必须使能才能振荡） */
	CLKDIS_1	= 0x10,		/* 时钟禁止 （当外部提供时钟时，设置该位可以禁止MCK_OUT引脚输出时钟以省电 */

	CLK_4_9152M = 0x08,
	CLK_2_4576M = 0x00,
	CLK_1M 		= 0x04,
	CLK_2M 		= 0x0C,

/*输出更新速率设置*/
	FS_20HZ     = 0X00,
	FS_25HZ     = 0x01,
	FS_100HZ    = 0x20,
	FS_200HZ    = 0x03,
	
	FS_50HZ		= 0x04,
	FS_60HZ		= 0x05,
	FS_250HZ	= 0x06,
	FS_500HZ	= 0x07,


	ZERO_0		= 0x00,
	ZERO_1		= 0x80
};
//
uint8_t SPI2_ReadWriteByte(uint8_t TxData)
{
	uint8_t RxData;
	while(HAL_SPI_TransmitReceive(&hspi2, &TxData, &RxData, 1, 100)!=HAL_OK)
	{
		HAL_Delay(1);
	}
	return RxData;
}
//
void AD7705_WriteByte(uint8_t data)
{
	AD7705_CS_L;
	HAL_Delay(20);
	SPI2_ReadWriteByte(data);
	HAL_Delay(20);
	AD7705_CS_H;
}
//
void AD7705_Init() //初始化函数
{

	/*==信号引脚初始化==*/
	HAL_Delay(5);
	AD7705_ResetHard();		//硬件复位
	HAL_Delay(5);
	AD7705_SyncSPI();      //同步SPI接口时序
	/*配置时钟寄存器*/
	AD7705_WriteByte(REG_CLOCK | WRITE |CH_1); //先写通信寄存器，下一步写时钟寄存器
	AD7705_WriteByte(CLKDIS_0|CLK_4_9152M|FS_250HZ); //刷新速率250HZ
	AD7705_CalibSelf(1);      //内部自校准
	HAL_Delay(5);
}	
//
void AD7705_ResetHard(void)	//硬件复位
{
	AD7705_RST_H;
	HAL_Delay(1);
	AD7705_RST_L;
	HAL_Delay(20);
	AD7705_RST_H;
	HAL_Delay(1);
}
//
/*=============================================
= 功能：同步AD7705芯片SPI接口时序
= 说明：连续发送32个1即可，不同步会发生数据错位
==============================================*/
void AD7705_SyncSPI(void)      //同步SPI接口时序
{
	AD7705_CS_L;
	SPI2_ReadWriteByte(0xFF);//32个1
	SPI2_ReadWriteByte(0xFF);
	SPI2_ReadWriteByte(0xFF);
	SPI2_ReadWriteByte(0xFF);
	AD7705_CS_H;
}
/*====================================================================
=功能说明： 等待内部操作完成，自校准时间较长，需要等待
=参	   数： 无
======================================================================*/
void AD7705_WaitDRDY(void)
{
		HAL_Delay(100);
	    while(AD7705_DRDY==1){}//DRDY=0代表校准结束，同时数据也更新完毕。
}

void AD7705_CalibSelf(uint8_t _ch)
{
	if (_ch == 1)
	{
		/* 自校准CH1 */
		AD7705_WriteByte(REG_SETUP | WRITE | CH_1);	/* 写通信寄存器，下一步是写设置寄存器，通道1 */
		AD7705_WriteByte(MD_CAL_SELF|GAIN_1  |UNIPOLAR|BUF_EN|FSYNC_0);/* 启动自校准 *///写设置寄存器，单极性、有缓冲、增益为1、滤波器工作、自校准
		HAL_Delay(190);
		AD7705_WaitDRDY();	
	}
	else if (_ch == 2)
	{
		/* 自校准CH2 */
		AD7705_WriteByte(REG_SETUP | WRITE | CH_2);	/* 写通信寄存器，下一步是写设置寄存器，通道2 */
		AD7705_WriteByte(MD_CAL_SELF | GAIN_1 | UNIPOLAR |BUF_EN |FSYNC_0);	/* 启动自校准 */
		HAL_Delay(190);
		AD7705_WaitDRDY();
	}

}
/*=====================================================================
=功能说明：读到一个8位数据
=参    数：返回读到的值
=====================================================================*/
uint8_t AD7705_ReadByte(void)
{
	uint8_t read;
	AD7705_CS_L;
	read = SPI2_ReadWriteByte(0xFF);
	AD7705_CS_H;
	return read;
}
/*=====================================================================
=功能说明：读到一个16位数据（半字）
=参    数：返回读到16位数据的值
=====================================================================*/
uint16_t AD7705_Read2Byte(void)
{
	uint16_t read = 0;
	AD7705_CS_L;
	read = SPI2_ReadWriteByte(0xFF);
	read <<=8;
	read += SPI2_ReadWriteByte(0xFF);
	AD7705_CS_H;
	return read;
	
}
/*=====================================================================
=功能说明：读到一个24位数据（3字节）
=参    数：返回读到24位数据的值
=====================================================================*/
uint32_t AD7705_Read3Byte(void)
{
	uint32_t read = 0;
	AD7705_CS_L;
	read = SPI2_ReadWriteByte(0xFF);
	read <<=8;
	read += SPI2_ReadWriteByte(0xFF);
	read <<=8;
	read += SPI2_ReadWriteByte(0xFF);
	AD7705_CS_H;
	return read;
	
}
/*=====================================================================
=功能说明：读取采样电压值
=参    数：返回采样值
=====================================================================*/
uint16_t AD7705_ReadAdc(uint8_t _ch)
{
	uint8_t i;
	uint16_t read = 0;
	/* 为了避免通道切换造成读数失效，读2次 */
	for (i = 0; i < 2; i++)
	{
		AD7705_WaitDRDY();		/* 等待DRDY口线为0 */
		if (_ch == 1)
		{
			AD7705_WriteByte(0x38);//0x0 011(数据寄存器） 1（读） 0 00(ch0)
		}
		else if (_ch == 2)
		{
			AD7705_WriteByte(0x39);//0x0 011 1 0 01
		}
		read = AD7705_Read2Byte();
	}
	return read;	
}
//


