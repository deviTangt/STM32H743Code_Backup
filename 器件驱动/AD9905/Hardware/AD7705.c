
#include "AD7705.h"
#include "gpio.h"
/*
	AD7705ģ�� / AD7705ģ�� 
      SCK   ------  PB13/SPI2_SCK		PB10 SPI2_SCK
      DOUT  ------  PB14/SPI2_MISO		PC2  SPI2_MISO
      DIN   ------  PB15/SPI3_MOSI		PC1  SPI2_MOSI
      CS    ------  PG7/NRF24L01_CSN	PA5  AD_CS_Pin
      DRDY  ------  PG6/NRF24L01_IRQ	PA6  AD_RDY_Pin
      RST   ------  PG8/NRF_CE			PA4  AD_RST_Pin
*/

#define AD7705_CS_H  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET)
#define AD7705_CS_L  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET)//CSƬѡ�궨�壬�͵�ƽ��Ч
#define AD7705_RST_H HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4, GPIO_PIN_SET)
#define AD7705_RST_L HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET)//RSTʹ�ܸ�λ�궨�壬�͵�ƽ��Ч
#define AD7705_DRDY  HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_6)  //DRDY,�͵�ƽʱ��ʾAD7705�ɶ�
/* ͨ�żĴ���bit���� */
enum
{
	/* �Ĵ���ѡ��  RS2 RS1 RS0  */
	REG_COMM	= 0x00,	/* ͨ�żĴ��� */
	REG_SETUP	= 0x10,	/* ���üĴ��� */
	REG_CLOCK	= 0x20,	/* ʱ�ӼĴ��� */
	REG_DATA	= 0x30,	/* ���ݼĴ��� */
	REG_ZERO_CH1	= 0x60,	/* CH1 ƫ�ƼĴ��� */
	REG_FULL_CH1	= 0x70,	/* CH1 �����̼Ĵ��� */
	REG_ZERO_CH2	= 0x61,	/* CH2 ƫ�ƼĴ��� */
	REG_FULL_CH2	= 0x71,	/* CH2 �����̼Ĵ��� */

	/* ��д���� */
	WRITE 		= 0x00,	/* д���� */
	READ 		= 0x08,	/* ������ */

	/* ͨ�� */
	CH_1		= 0,	/* AIN1+  AIN1- */
	CH_2		= 1,	/* AIN2+  AIN2- */
	CH_3		= 2,	/* AIN1-  AIN1- */
	CH_4		= 3		/* AIN1-  AIN2- */
};

/* ���üĴ���bit���� */
enum
{
	MD_NORMAL		= (0 << 6),	/* ����ģʽ */
	MD_CAL_SELF		= (1 << 6),	/* ��У׼ģʽ */
	MD_CAL_ZERO		= (2 << 6),	/* У׼0�̶�ģʽ */
	MD_CAL_FULL		= (3 << 6),	/* У׼���̶�ģʽ */

	GAIN_1			= (0 << 3),	/* ���� */
	GAIN_2			= (1 << 3),	/* ���� */
	GAIN_4			= (2 << 3),	/* ���� */
	GAIN_8			= (3 << 3),	/* ���� */
	GAIN_16			= (4 << 3),	/* ���� */
	GAIN_32			= (5 << 3),	/* ���� */
	GAIN_64			= (6 << 3),	/* ���� */
	GAIN_128		= (7 << 3),	/* ���� */

	/* ����˫���Ի��ǵ����Զ����ı��κ������źŵ�״̬����ֻ�ı�������ݵĴ����ת�������ϵ�У׼�� */
	BIPOLAR			= (0 << 2),	/* ˫�������� */
	UNIPOLAR		= (1 << 2),	/* ���������� */

	BUF_NO			= (0 << 1),	/* �����޻��壨�ڲ�������������) */
	BUF_EN			= (1 << 1),	/* �����л��� (�����ڲ�������) �ɴ�����迹Դ */

	FSYNC_0			= 0,
	FSYNC_1			= 1		/* ������ */
};

/* ʱ�ӼĴ���bit���� */
enum
{
	CLKDIS_0	= 0x00,		/* ʱ�����ʹ�� ������Ӿ���ʱ������ʹ�ܲ����񵴣� */
	CLKDIS_1	= 0x10,		/* ʱ�ӽ�ֹ �����ⲿ�ṩʱ��ʱ�����ø�λ���Խ�ֹMCK_OUT�������ʱ����ʡ�� */

	CLK_4_9152M = 0x08,
	CLK_2_4576M = 0x00,
	CLK_1M 		= 0x04,
	CLK_2M 		= 0x0C,

/*���������������*/
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
void AD7705_Init() //��ʼ������
{

	/*==�ź����ų�ʼ��==*/
	HAL_Delay(5);
	AD7705_ResetHard();		//Ӳ����λ
	HAL_Delay(5);
	AD7705_SyncSPI();      //ͬ��SPI�ӿ�ʱ��
	/*����ʱ�ӼĴ���*/
	AD7705_WriteByte(REG_CLOCK | WRITE |CH_1); //��дͨ�żĴ�������һ��дʱ�ӼĴ���
	AD7705_WriteByte(CLKDIS_0|CLK_4_9152M|FS_250HZ); //ˢ������250HZ
	AD7705_CalibSelf(1);      //�ڲ���У׼
	HAL_Delay(5);
}	
//
void AD7705_ResetHard(void)	//Ӳ����λ
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
= ���ܣ�ͬ��AD7705оƬSPI�ӿ�ʱ��
= ˵������������32��1���ɣ���ͬ���ᷢ�����ݴ�λ
==============================================*/
void AD7705_SyncSPI(void)      //ͬ��SPI�ӿ�ʱ��
{
	AD7705_CS_L;
	SPI2_ReadWriteByte(0xFF);//32��1
	SPI2_ReadWriteByte(0xFF);
	SPI2_ReadWriteByte(0xFF);
	SPI2_ReadWriteByte(0xFF);
	AD7705_CS_H;
}
/*====================================================================
=����˵���� �ȴ��ڲ�������ɣ���У׼ʱ��ϳ�����Ҫ�ȴ�
=��	   ���� ��
======================================================================*/
void AD7705_WaitDRDY(void)
{
		HAL_Delay(100);
	    while(AD7705_DRDY==1){}//DRDY=0����У׼������ͬʱ����Ҳ������ϡ�
}

void AD7705_CalibSelf(uint8_t _ch)
{
	if (_ch == 1)
	{
		/* ��У׼CH1 */
		AD7705_WriteByte(REG_SETUP | WRITE | CH_1);	/* дͨ�żĴ�������һ����д���üĴ�����ͨ��1 */
		AD7705_WriteByte(MD_CAL_SELF|GAIN_1  |UNIPOLAR|BUF_EN|FSYNC_0);/* ������У׼ *///д���üĴ����������ԡ��л��塢����Ϊ1���˲�����������У׼
		HAL_Delay(190);
		AD7705_WaitDRDY();	
	}
	else if (_ch == 2)
	{
		/* ��У׼CH2 */
		AD7705_WriteByte(REG_SETUP | WRITE | CH_2);	/* дͨ�żĴ�������һ����д���üĴ�����ͨ��2 */
		AD7705_WriteByte(MD_CAL_SELF | GAIN_1 | UNIPOLAR |BUF_EN |FSYNC_0);	/* ������У׼ */
		HAL_Delay(190);
		AD7705_WaitDRDY();
	}

}
/*=====================================================================
=����˵��������һ��8λ����
=��    �������ض�����ֵ
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
=����˵��������һ��16λ���ݣ����֣�
=��    �������ض���16λ���ݵ�ֵ
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
=����˵��������һ��24λ���ݣ�3�ֽڣ�
=��    �������ض���24λ���ݵ�ֵ
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
=����˵������ȡ������ѹֵ
=��    �������ز���ֵ
=====================================================================*/
uint16_t AD7705_ReadAdc(uint8_t _ch)
{
	uint8_t i;
	uint16_t read = 0;
	/* Ϊ�˱���ͨ���л���ɶ���ʧЧ����2�� */
	for (i = 0; i < 2; i++)
	{
		AD7705_WaitDRDY();		/* �ȴ�DRDY����Ϊ0 */
		if (_ch == 1)
		{
			AD7705_WriteByte(0x38);//0x0 011(���ݼĴ����� 1������ 0 00(ch0)
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


