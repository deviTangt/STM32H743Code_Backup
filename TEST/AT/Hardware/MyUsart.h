#ifndef _MyUsart_H_
#define _MyUsart_H_

extern uint8_t cnt_rx;
extern uint8_t rx_buff[100];

//
void printf_s(char *format, ...);
//
void printf_n(uint8_t *str, uint8_t size);
//
void Serial_TJC_SendCmd(char *format, ...);
//
void Serial_TJC_SendTxt(uint8_t WindowIndex, char *format, ...);
//
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart);
//
void MyUart_task();
//


#endif