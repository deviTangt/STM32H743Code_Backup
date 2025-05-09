#include "FPGA_commute.h"

#define W_CS_L 		(HAL_GPIO_WritePin(FPGA_CS_GPIO_Port, FPGA_CS_Pin, GPIO_PIN_RESET))
#define W_CS_H 		(HAL_GPIO_WritePin(FPGA_CS_GPIO_Port, FPGA_CS_Pin, GPIO_PIN_SET))
#define W_SCL_L 	(HAL_GPIO_WritePin(GPIOE, GPIO_PIN_2, GPIO_PIN_RESET))
#define W_SCL_H 	(HAL_GPIO_WritePin(GPIOE, GPIO_PIN_2, GPIO_PIN_SET))
#define W_MO(STATE) (HAL_GPIO_WritePin(GPIOE, GPIO_PIN_6, STATE))
#define R_MI 		(HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_5))
//s
uint8_t FPGA_SPI_SwapByte(uint8_t TxData)
{
	uint8_t RxData;
	W_CS_L;
	W_SCL_H;
	for (uint8_t i = 0;i < 8;i ++){
		W_MO(((TxData >> i) & 0x01) ? GPIO_PIN_SET : GPIO_PIN_RESET);
		W_SCL_L;
		W_SCL_H;
		if (R_MI) RxData |= 0x01 << i;
	}
	//HAL_SPI_TransmitReceive(&hspi4, &TxData, &RxData, 1, 100);
	W_CS_H;
	return RxData;
}
//
void FPGA_ReadData(uint8_t *ReadDataArray, uint16_t size){
	W_CS_L;
	//FPGA_SPI_SwapByte(0xFF);
	for (int8_t i = 0;i < size;i ++){
		ReadDataArray[i] = FPGA_SPI_SwapByte(0xFF);
	}
	W_CS_H;
}
//
void FPGA_EnableSPWM(uint8_t Index, uint8_t Status){
	W_CS_L;
	FPGA_SPI_SwapByte(FPGA_CMD_EnableSPWM);
	FPGA_SPI_SwapByte(Index);
	FPGA_SPI_SwapByte(Status);
	W_CS_H;
}
//
void FPGA_ConfigSPWM(uint8_t Index, uint8_t Mode, uint32_t Freq, uint8_t Duty){
	W_CS_L;
	FPGA_SPI_SwapByte(FPGA_CMD_ConfigSPWM);
	FPGA_SPI_SwapByte(Index);
	FPGA_SPI_SwapByte(Mode);
	FPGA_SPI_SwapByte((uint8_t)(Freq >> 16));
	FPGA_SPI_SwapByte((uint8_t)(Freq >>  8));
	FPGA_SPI_SwapByte((uint8_t)(Freq >>  0));
	FPGA_SPI_SwapByte(Duty);
	W_CS_H;
}
//
