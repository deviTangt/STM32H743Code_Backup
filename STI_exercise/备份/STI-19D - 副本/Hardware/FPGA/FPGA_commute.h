#ifndef _FPGA_COMMUTE_H_
#define _FPGA_COMMUTE_H_
#include "main.h"
#include "spi.h"
#include "FPGA_Ins.h"
//
uint8_t FPGA_SPI_SwapByte(uint8_t TxData);
//
void FPGA_ReadData(uint8_t *ReadDataArray, uint16_t size);
//
void FPGA_EnableSPWM(uint8_t Index, uint8_t Status);
//
void FPGA_ConfigSPWM(uint8_t Index, uint8_t Mode, uint32_t Freq, uint8_t Duty);
//

#endif

