#ifndef __AD9959_H
#define __AD9959_H

#include "main.h"
#define MAIN_CH_SELECT 		1

#define CSR_ADD   0x00 // CSR  Channel Select Register(通道选择寄存器)                1 Bytes
#define FR1_ADD   0x01 // FR1  Function Register 1(功能寄存器1)                       3 Bytes
#define FR2_ADD   0x02 // FR2  Function Register 2(功能寄存器2)                       2 Bytes
#define CFR_ADD   0x03 // CFR  Channel Function Register(通道功能寄存器)              3 Bytes
#define CFTW0_ADD 0x04 // CFTW0 Channel Frequency Tuning Word 0(通道频率转换字寄存器)  4 Bytes
#define CPOW0_ADD 0x05 // CPW0 Channel Phase Offset Word 0(通道相位转换字寄存器)      2 Bytes
#define ACR_ADD   0x06 // ACR  Amplitude Control Register(幅度控制寄存器)             3 Bytes
#define LSRR_ADD  0x07 // LSR  Linear Sweep Ramp Rate(通道线性扫描寄存器)             2 Bytes
#define RDW_ADD   0x08 // RDW  LSR Rising Delta Word(通道线性向上扫描寄存器)          4 Bytes
#define FDW_ADD   0x09 // FDW  LSR Falling Delta Word(通道线性向下扫描寄存器)         4 Bytes
#define CW1       0x0A // CW1  Channel Word 1(通道字寄存器1)                         4 Bytes
#define CW2       0x0B // CW2  Channel Word 2(通道字寄存器2)                         4 Bytes
#define CW3       0x0C // CW3  Channel Word 3(通道字寄存器3)                         4 Bytes
#define CW4       0x0D // CW4  Channel Word 4(通道字寄存器4)                         4 Bytes

// AD9959 IO Operation
// IO must be a driverIO struct, VAL must be 0 or 1
#define WRT(IO, VAL) HAL_GPIO_WritePin(IO.GPIOx, IO.Pin, (VAL) ? GPIO_PIN_SET : GPIO_PIN_RESET)
#define GET(IO)      HAL_GPIO_ReadPin(IO.GPIOx, IO.Pin)

void Init_AD9959(void);
void delay_9959(uint32_t length);
void InitIO_9959(void);
void InitReset(void);
void IO_Update(void);
void WriteData_AD9959(uint8_t RegisterAddress, uint8_t NumberofRegisters, uint8_t *RegisterData, uint8_t temp);
void ReadData_AD9959(uint8_t RegisterAddress, uint8_t NumberofRegisters, uint8_t *RegisterData);
void Write_frequency(uint8_t Channel, uint32_t Freq);
void Write_Amplitude(uint8_t Channel, uint16_t Ampl);
void Write_Phase(uint8_t Channel, uint16_t Phase);

uint32_t Get_Frequency(void);
uint8_t Get_Amplitude(void);
void Sweep_Frequency(uint8_t Channel, uint32_t Start_Freq, uint32_t Stop_Freq, uint32_t Step, uint32_t time, uint8_t NO_DWELL);
void Channel_Select(uint8_t Channel);
void AD9959_error(void);
#endif

////
////
//#ifndef AD9959_AD9959_H
//#define AD9959_AD9959_H
//
//#include "main.h"
//#include "gpio.h"
//#include "main.h"
//#include "stdbool.h"
//
//#define AD9959_CS_1 HAL_GPIO_WritePin(CS_GPIO_Port,CS_Pin,GPIO_PIN_SET)
//#define AD9959_SCLK_1 HAL_GPIO_WritePin(SCLK_GPIO_Port,SCLK_Pin,GPIO_PIN_SET)
//#define AD9959_UPDATE_1 HAL_GPIO_WritePin(UPDATE_GPIO_Port,UPDATE_Pin,GPIO_PIN_SET)
//#define AD9959_PS0_1 HAL_GPIO_WritePin(AD9959_PS0_GPIO_Port,AD9959_PS0_Pin,GPIO_PIN_SET)
//#define AD9959_PS1_1 HAL_GPIO_WritePin(AD9959_PS1_GPIO_Port,AD9959_PS1_Pin,GPIO_PIN_SET)
//#define AD9959_PS2_1 HAL_GPIO_WritePin(AD9959_PS2_GPIO_Port,AD9959_PS2_Pin,GPIO_PIN_SET)
//#define AD9959_PS3_1 HAL_GPIO_WritePin(AD9959_PS3_GPIO_Port,AD9959_PS3_Pin,GPIO_PIN_SET)
//#define AD9959_SDIO0_1 HAL_GPIO_WritePin(SDIO0_GPIO_Port,SDIO0_Pin,GPIO_PIN_SET)
//#define AD9959_SDIO1_1 HAL_GPIO_WritePin(AD9959_SDIO1_GPIO_Port,AD9959_SDIO1_Pin,GPIO_PIN_SET)
//#define AD9959_SDIO2_1 HAL_GPIO_WritePin(AD9959_SDIO2_GPIO_Port,AD9959_SDIO2_Pin,GPIO_PIN_SET)
//#define AD9959_SDIO3_1 HAL_GPIO_WritePin(AD9959_SDIO3_GPIO_Port,AD9959_SDIO3_Pin,GPIO_PIN_SET)
//#define AD9959_PDC_1 HAL_GPIO_WritePin(AD9959_PDC_GPIO_Port,AD9959_PDC_Pin,GPIO_PIN_SET)
//#define AD9959_RESET_1 HAL_GPIO_WritePin(RESET_GPIO_Port,RESET_Pin,GPIO_PIN_SET)
//
//#define AD9959_CS_0 HAL_GPIO_WritePin(CS_GPIO_Port,CS_Pin,GPIO_PIN_RESET)
//#define AD9959_SCLK_0 HAL_GPIO_WritePin(SCLK_GPIO_Port,SCLK_Pin,GPIO_PIN_RESET)
//#define AD9959_UPDATE_0 HAL_GPIO_WritePin(UPDATE_GPIO_Port,UPDATE_Pin,GPIO_PIN_RESET)
//#define AD9959_PS0_0 HAL_GPIO_WritePin(PS0_GPIO_Port,PS0_Pin,GPIO_PIN_RESET)
//#define AD9959_PS1_0 HAL_GPIO_WritePin(PS1_GPIO_Port,PS1_Pin,GPIO_PIN_RESET)
//#define AD9959_PS2_0 HAL_GPIO_WritePin(PS2_GPIO_Port,PS2_Pin,GPIO_PIN_RESET)
//#define AD9959_PS3_0 HAL_GPIO_WritePin(PS3_GPIO_Port,PS3_Pin,GPIO_PIN_RESET)
//#define AD9959_SDIO0_0 HAL_GPIO_WritePin(SDIO0_GPIO_Port,SDIO0_Pin,GPIO_PIN_RESET)
//#define AD9959_SDIO1_0 HAL_GPIO_WritePin(SDIO1_GPIO_Port,SDIO1_Pin,GPIO_PIN_RESET)
//#define AD9959_SDIO2_0 HAL_GPIO_WritePin(SDIO2_GPIO_Port,SDIO2_Pin,GPIO_PIN_RESET)
//#define AD9959_SDIO3_0 HAL_GPIO_WritePin(SDIO3_GPIO_Port,SDIO3_Pin,GPIO_PIN_RESET)
//#define AD9959_PDC_0 HAL_GPIO_WritePin(PDC_GPIO_Port,PDC_Pin,GPIO_PIN_RESET)
//#define AD9959_RESET_0 HAL_GPIO_WritePin(RESET_GPIO_Port,RESET_Pin,GPIO_PIN_RESET)
//
//
//
//typedef enum {
//    AD9959_CHANNEL_0 = 0x10U,
//    AD9959_CHANNEL_1 = 0x20U,
//    AD9959_CHANNEL_2 = 0x40U,
//    AD9959_CHANNEL_3 = 0x80U,
//} AD9959_CHANNEL;
//
//typedef enum {
//    AD9959_REG_CSR       =   0x00U,  //CSR 通道选择寄存器
//    AD9959_REG_FR1       =   0x01U,  //FR1 功能寄存器1
//    AD9959_REG_FR2       =   0x02U,  //FR2 功能寄存器2
//    AD9959_REG_CFR       =   0x03U,  //CFR 通道功能寄存器
//    AD9959_REG_CFTW0     =   0x04U,  //CTW0 通道频率转换字寄存器
//    AD9959_REG_CPOW0     =   0x05U,  //CPW0 通道相位转换字寄存器
//    AD9959_REG_ACR       =   0x06U,  //ACR 幅度控制寄存器
//    AD9959_REG_LSRR      =   0x07U,  //LSR 通道线性扫描寄存器
//    AD9959_REG_RDW       =   0x08U,  //RDW 通道线性向上扫描寄存器
//    AD9959_REG_FDW       =   0x09U,  //FDW 通道线性向下扫描寄存器
//} AD9959_REG_ADDR;
//
//
//#define IS_AD9959_REG_ADDR(REG_ADDR)    (((REG_ADDR) == AD9959_REG_CSR  ) || \
//                                         ((REG_ADDR) == AD9959_REG_FR1  ) || \
//                                         ((REG_ADDR) == AD9959_REG_FR2  ) || \
//                                         ((REG_ADDR) == AD9959_REG_CFR  ) || \
//                                         ((REG_ADDR) == AD9959_REG_CFTW0) || \
//                                         ((REG_ADDR) == AD9959_REG_CPOW0) || \
//                                         ((REG_ADDR) == AD9959_REG_ACR  ) || \
//                                         ((REG_ADDR) == AD9959_REG_LSRR ) || \
//                                         ((REG_ADDR) == AD9959_REG_RDW  ) || \
//                                         ((REG_ADDR) == AD9959_REG_FDW  ))
//
//#define IS_AD9959_CHANNEL(CHANNEL)      (((CHANNEL) == AD9959_CHANNEL_0 ) || \
//                                         ((CHANNEL) == AD9959_CHANNEL_1 ) || \
//                                         ((CHANNEL) == AD9959_CHANNEL_2 ) || \
//                                         ((CHANNEL) == AD9959_CHANNEL_3 ))
//
//void ad9959_init(void);
//void ad9959_reset(void);
//void ad9959_io_init(void);
//void ad9959_io_update(void);
//void ad9959_write_data(AD9959_REG_ADDR register_address, uint8_t number_of_registers, const uint8_t *register_data, bool update);
//void ad9959_write_phase(AD9959_CHANNEL channel, uint16_t phase);
//void ad9959_write_frequency(AD9959_CHANNEL channel, uint32_t frequency);
//void ad9959_write_amplitude(AD9959_CHANNEL channel, uint16_t amplitude);
//
//#endif //AD9959_AD9959_H
//
