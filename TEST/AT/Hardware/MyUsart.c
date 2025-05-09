#include "main.h"
#include "memorymap.h"
#include "usart.h"
#include "gpio.h"
#include <stdio.h>
#include <stdarg.h>
#include <string.h>

//
int fputc(int ch, FILE* stream){
	HAL_UART_Transmit(&huart1, (uint8_t *)ch, 1, 10);
	return ch;
}
//
void printf_s(char *format, ...){
	static char String[100];
	uint8_t i;
	va_list arg;
	va_start(arg, format);
	vsprintf(String, format, arg);
	va_end(arg);
	for (i = 0;String[i] != '\0'; i ++);
	HAL_UART_Transmit(&huart1, (uint8_t *)String, i, 10);
}
//
void printf_n(uint8_t *str, uint8_t size){
	HAL_UART_Transmit(&huart1, str, size, 10);
}
//
void Serial_TJC_SendCmd(char *format, ...){
	static char String[100];
	va_list arg;
	va_start(arg, format);
	vsprintf(String, format, arg);
	va_end(arg);
	printf_s(String);
	printf_s("\xff\xff\xff");
}
//
void Serial_TJC_SendTxt_n(uint8_t WindowIndex, uint8_t *str, uint8_t size){
	static char String[100];
	
	if (WindowIndex > 12) WindowIndex = 0;
	if (WindowIndex == 0)	printf_s("main.t0.txt+=\"");
	else 					printf_s("main.bar%d.txt=\"", WindowIndex);
	HAL_UART_Transmit(&huart1, str, size, 10);
	printf_s("\"\xff\xff\xff");
}
//
void Serial_TJC_SendTxt(uint8_t WindowIndex, char *format, ...){
	static char String[100];
	
	if (WindowIndex > 12) WindowIndex = 0;
	if (WindowIndex == 0)	printf_s("main.t0.txt+=\"");
	else 					printf_s("main.bar%d.txt=\"", WindowIndex);
	
	va_list arg;
	va_start(arg, format);
	vsprintf(String, format, arg);
	va_end(arg);
	printf_s(String);
	printf_s("\"\xff\xff\xff");
}
//
uint8_t cnt_rx = 0;
uint8_t rx_buff[256];
uint32_t rx_tick = 0;
uint8_t t;

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart){
	rx_tick = uwTick;
	HAL_UART_Receive_IT(&huart1, &rx_buff[cnt_rx ++], 1);
}
//
void MyUart_task(){
	if (cnt_rx){
		if (uwTick > rx_tick + 5 && cnt_rx > 4){
			Serial_TJC_SendTxt(2, "RX:%d", cnt_rx);
			Serial_TJC_SendTxt_n(4, rx_buff, cnt_rx);
		}
		cnt_rx = 0;
		huart1.pRxBuffPtr = rx_buff;
	}
}
//


//
/*
int count_t = 0;
int count_rx_bit = 0;
int last_RxPacketNum = 0;
void USART1_IRQHandler(void){
	count_rx_bit += 1;
	static uint8_t RxState = 0;
	static uint8_t RxPacketNum = 0;
	if (USART_GetITStatus(USART1, USART_IT_RXNE) == SET){
		uint8_t RxData = USART_ReceiveData(USART1);
		if (RxState == 0){
			if (RxData == '&') RxState = 1;
		}
		else if (RxState == 1){
			if (RxData == '&') RxState = 2;
			else RxState = 0;
		}
		else if (RxState == 2){
			if (RxData == '&'){
				RxState = 3;
			}
			else Serial_RxPacket[RxPacketNum ++] = RxData;
		}
		else if (RxState == 3){
			if (RxData == '&'){
				RxState = 0;
				Serial_Rx_flag = 1;
				count_t += 1;
				last_RxPacketNum = RxPacketNum;
				Serial_RxPacket[RxPacketNum ++] = '\&';
				Serial_RxPacket[RxPacketNum ++] = '\&';
				RxPacketNum = 0;	
			}
			else {
				RxState = 2;
				Serial_RxPacket[RxPacketNum ++] = '&';
				Serial_RxPacket[RxPacketNum ++] = RxData;
			}
		}
		USART_ClearITPendingBit(USART1, USART_IT_RXNE);
	}
}
*/
//



