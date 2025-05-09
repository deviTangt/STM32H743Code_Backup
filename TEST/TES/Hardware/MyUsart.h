#ifndef _MyUsart_H_
#define _MyUsart_H_
#include "main.h"
#include "memorymap.h"
#include "usart.h"
#include "gpio.h"
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include "__HRADWARE_DEF__.h"


//
void printf_s(char *format, ...);
//
void printf_n(uint8_t *str, uint8_t size);
//
void Serial_TJC_SendCmd(char *format, ...);
//
void Serial_TJC_SendTxt(uint8_t WindowIndex, char *format, ...);
//
#if SERIAL_TJC_RX_ENABLE
#define BUFFER_SIZE (100)
extern uint8_t cnt_rx;
extern uint8_t rx_buff[BUFFER_SIZE];
//
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart);
//
void MyUart_task();
//
#endif
//


#endif

