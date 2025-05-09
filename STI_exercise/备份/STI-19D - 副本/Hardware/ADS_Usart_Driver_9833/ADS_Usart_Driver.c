#include "ADS_Usart_Driver.h"

// ADSÐÅºÅ·¢ÉúÆ÷
#define STRING_MAX_LENGTH 100
//
void printf_s_2(char *format, ...){
	static char String[STRING_MAX_LENGTH];
	uint8_t i;
	va_list arg;
	va_start(arg, format);
	vsprintf(String, format, arg);
	va_end(arg);
	for (i = 0;String[i] != '\0'; i ++);
	HAL_UART_Transmit(&huart2, (uint8_t *)String, i, 10);
}
//
void printf_n_2(uint8_t *str, uint8_t size){
	HAL_UART_Transmit(&huart2, str, size, 10);
}
//
void ADS_SendFreq(uint32_t freq){
	printf_s_2("%d\r\n", freq);
}
//
