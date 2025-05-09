//-----------------------------------------------------------------
// ��������:
//     ADS8688��������
// ��    ��: ���ǵ���
// ��ʼ����: 2022-06-27
// �������: 2022-06-27
// �޸�����: 
// ��ǰ�汾: V1.0
// ��ʷ�汾:
//  - V1.0: (2022-06-27)ADS8688��ʼ����Ӧ��
// ���Թ���: ����STM32���Ŀ����塢LZE_ST LINK2��DAS8688ģ��
// ˵    ��: 
//    
//-----------------------------------------------------------------

//-----------------------------------------------------------------
// ͷ�ļ�����
//-----------------------------------------------------------------
#include "ads8688.h"
//-----------------------------------------------------------------

//-----------------------------------------------------------------

//-----------------------------------------------------------------
// void GPIO_ADS8688_Configuration(void)
//-----------------------------------------------------------------
// 
// ��������: ADS8688�������ú���
// ��ڲ���: �� 
// �� �� ֵ: ��
// ע������: ��
//
//-----------------------------------------------------------------
void GPIO_ADS8688_Configuration(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	__HAL_RCC_GPIOE_CLK_ENABLE();
	
	GPIO_InitStructure.Pin = GPIO_PIN_0 | GPIO_PIN_3 | GPIO_PIN_4;
	GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH;
	GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStructure.Pull = GPIO_PULLUP;
	HAL_GPIO_Init(GPIOE, &GPIO_InitStructure);
}

//-----------------------------------------------------------------
// void ADS8688_Init(void)
//-----------------------------------------------------------------
// 
// ��������: ADS8361��ʼ��
// ��ڲ���: �� 
// �� �� ֵ: ��
// ע������: ��
//
//-----------------------------------------------------------------
void ADS8688_Init(void)
{
	
	GPIO_ADS8688_Configuration();
	SPI4_Init();
	RST_L;
	delay_us(2);
	RST_H;
	DAISY_L;

	ADS8688_Write_Command(RST);	// �����λģʽ
	delay_us(2);
	ADS8688_Write_Program(CH0_INPUT_RANGE, VREF_B_125);	// ͨ��0�����뷶ΧΪ��5.12V
	ADS8688_Write_Program(CH1_INPUT_RANGE, VREF_B_125);	// ͨ��1�����뷶ΧΪ��5.12V
	ADS8688_Write_Program(CH2_INPUT_RANGE, VREF_B_125);	// ͨ��2�����뷶ΧΪ��5.12V
	ADS8688_Write_Program(CH3_INPUT_RANGE, VREF_B_125);	// ͨ��3�����뷶ΧΪ��5.12V
	ADS8688_Write_Program(CH4_INPUT_RANGE, VREF_B_125);	// ͨ��4�����뷶ΧΪ��5.12V
	ADS8688_Write_Program(CH5_INPUT_RANGE, VREF_B_125);	// ͨ��5�����뷶ΧΪ��5.12V
	ADS8688_Write_Program(CH6_INPUT_RANGE, VREF_B_125);	// ͨ��6�����뷶ΧΪ��5.12V
	ADS8688_Write_Program(CH7_INPUT_RANGE, VREF_B_125);	// ͨ��7�����뷶ΧΪ��5.12V
	ADS8688_Write_Program(CH_PWR_DN, 0x00);
	ADS8688_Write_Program(AUTO_SEQ_EN, 0xFF);
	ADS8688_Write_Command(AUTO_RST);
}

//-----------------------------------------------------------------
// void ADS8361_Write_Command(uint16_t com)
//-----------------------------------------------------------------
// 
// ��������: д����
// ��ڲ���: com������
// �� �� ֵ: ��
// ע������: ��
//
//-----------------------------------------------------------------
void ADS8688_Write_Command(uint16_t com)
{
	uint8_t wr_data[2] = {0x00, 0x00};
	
	wr_data[0] = (uint8_t)(com >> 8);
	wr_data[1] = (uint8_t)(com &0x00FF);
	
	CS_L;
	HAL_SPI_Transmit(&SPI_Handler, wr_data, 2, 0xFFFF);
	CS_H;
}

//-----------------------------------------------------------------
// void ADS8688_Write_Program(uint8_t addr, uint8_t data)
//-----------------------------------------------------------------
// 
// ��������: д����Ĵ���
// ��ڲ���: addr: �Ĵ�����ַ
//					 data������
// �� �� ֵ: ��
// ע������: ��
//
//-----------------------------------------------------------------
void ADS8688_Write_Program(uint8_t addr, uint8_t data)
{
	uint8_t wr_data[2] = {0x00, 0x00};
	
	wr_data[0] = (addr << 1) | 0x01;
	wr_data[1] = data;
	
	CS_L;
	HAL_SPI_Transmit(&SPI_Handler, wr_data, 2, 0xFFFF);
	CS_H;
}

//-----------------------------------------------------------------
// uint8_t ADS8361_Read_Program(uint8_t addr)
//-----------------------------------------------------------------
// 
// ��������: ������Ĵ���
// ��ڲ���: addr: �Ĵ�����ַ
// �� �� ֵ: ��ȡ������
// ע������: ��
//
//-----------------------------------------------------------------
uint8_t ADS8688_Read_Program(uint8_t addr)
{
	uint8_t Rxdata;
	uint8_t wr_data[2] = {0x00, 0x00};
	
	wr_data[0] = addr << 1;
	
	CS_L;
	HAL_SPI_Transmit(&SPI_Handler, wr_data, 2, 0xFFFF);
	HAL_SPI_Receive(&SPI_Handler, &Rxdata, 1, 0xFFFF);
	CS_H;
	
	return Rxdata;
}

//-----------------------------------------------------------------
// void Get_AUTO_RST_Mode_ADC_Data(uint8_t ch_num, uint16_t *data)
//-----------------------------------------------------------------
// 
// ��������: ��ȡAUTO_RSTģʽ�µ��������
// ��ڲ���: ch_num��ͨ����������AUTO_SEQ_EN���õĲ����йأ�
//					 *data����ȡ�õ�������
// �� �� ֵ: ��
// ע������: ��
//
//-----------------------------------------------------------------
void Get_AUTO_RST_Mode_ADC_Data(uint8_t ch_num, uint16_t *data)
{
	uint8_t Rxdata[4],i;
	uint8_t wr_data[4] = {0x00, 0x00, 0x00, 0x00};
	
	
	for(i=0; i<ch_num; i++) 
	{
		CS_L;
		HAL_SPI_TransmitReceive(&SPI_Handler, (uint8_t *)wr_data, (uint8_t *)Rxdata, 4, 0xFFFF);
		CS_H;
		*(data+i) = ((uint16_t)Rxdata[2] << 8) | Rxdata[3];
	}
}
//
uint16_t adc8688_data[8];
//
void show_AD8688_data(){
	Get_AUTO_RST_Mode_ADC_Data(8, adc8688_data);
	for(uint8_t i=0; i < 8; i++)
	{
		Serial_TJC_SendTxt(i + 3, "CH%1d: %10.4lfmV  D: %04X", 
							i, ((double)adc8688_data[i]-32768)*10240.0/65536, (uint16_t)adc8688_data[i]);
	}
	/*
	// ��ȡͨ��0������
	Get_MAN_CH_Data(MAN_CH_0, &adc_data);
	Serial_TJC_SendTxt(3, "CH0: %10.4lfmV  D: %04X", 
							((double)adc_data-32768)*10240.0/65536, (uint16_t)adc_data);

		
	// ��ȡͨ��1������
	Get_MAN_CH_Data(MAN_CH_1, &adc_data);
	Serial_TJC_SendTxt(4, "CH1: %10.4lfmV  D: %04X", 
							((double)adc_data-32768)*10240.0/65536, (uint16_t)adc_data);
		
	// ��ȡͨ��2������
	Get_MAN_CH_Data(MAN_CH_2, &adc_data);
	Serial_TJC_SendTxt(5, "CH2: %10.4lfmV  D: %04X", 
							((double)adc_data-32768)*10240.0/65536, (uint16_t)adc_data);
		
	// ��ȡͨ��3������
	Get_MAN_CH_Data(MAN_CH_3, &adc_data);
	Serial_TJC_SendTxt(6, "CH3: %10.4lfmV  D: %04X", 
							((double)adc_data-32768)*10240.0/65536, (uint16_t)adc_data);
		
	// ��ȡͨ��4������
	Get_MAN_CH_Data(MAN_CH_4, &adc_data);
	Serial_TJC_SendTxt(7, "CH4: %10.4lfmV  D: %04X", 
							((double)adc_data-32768)*10240.0/65536, (uint16_t)adc_data);
		
	// ��ȡͨ��5������
	Get_MAN_CH_Data(MAN_CH_5, &adc_data);
	Serial_TJC_SendTxt(8, "CH5: %10.4lfmV  D: %04X", 
							((double)adc_data-32768)*10240.0/65536, (uint16_t)adc_data);
		
	// ��ȡͨ��6������
	Get_MAN_CH_Data(MAN_CH_6, &adc_data);
	Serial_TJC_SendTxt(9, "CH6: %10.4lfmV  D: %04X", 
							((double)adc_data-32768)*10240.0/65536, (uint16_t)adc_data);
		
	// ��ȡͨ��7������
	Get_MAN_CH_Data(MAN_CH_7, &adc_data);
	Serial_TJC_SendTxt(10, "CH7: %10.4lfmV  D: %04X", 
							((double)adc_data-32768)*10240.0/65536, (uint16_t)adc_data);
		
	// ��ȡAUXͨ�������ݣ����뷶ΧΪ0~4.096V��
	Get_MAN_CH_Data(MAN_AUX, &aux_data);
	Get_MAN_CH_Data(MAN_AUX, &aux_data);
	Serial_TJC_SendTxt(2, "AUX: %10.4lfmV  D: %04X", 
							(double)aux_data*4096.0/65536, (uint16_t)aux_data);
	Get_MAN_CH_Data(MAN_CH_0, &adc_data);
	*/
}
//

