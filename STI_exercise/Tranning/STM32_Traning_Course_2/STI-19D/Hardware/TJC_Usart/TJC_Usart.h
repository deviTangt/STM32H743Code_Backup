#ifndef _TJC_Usart_H_
#define _TJC_Usart_H_
#include "main.h"
#include "usart.h"
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include "__HRADWARE_DEF__.h"


//
extern void printf_s(char *format, ...);
//
extern void printf_n(uint8_t *str, uint8_t size);
//
extern void Serial_TJC_SendCmd(char *format, ...);
//
void Serial_TJC_SendTxt_n(uint8_t WindowIndex, uint8_t *str, uint8_t size);
//
void Serial_TJC_SendTxt(uint8_t WindowIndex, char *format, ...);
//
void Serial_TJC_SendTxt_n_2(uint8_t WindowIndex, uint8_t *str, uint8_t size);
//
void Serial_TJC_SendTxt_2(uint8_t WindowIndex, char *format, ...);
//
#if __SERIAL_TJC_RX_ENABLE
#define BUFFER_SIZE (100)
extern uint8_t cnt_rx;
extern uint8_t rx_buff[BUFFER_SIZE];
//
extern void TJC_Uart_Start();
//
extern void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart);
//
extern void MyUart_task();
//
#endif
//


#endif

