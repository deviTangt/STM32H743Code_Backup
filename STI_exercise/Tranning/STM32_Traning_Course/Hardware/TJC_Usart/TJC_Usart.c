#include "TJC_Usart.h"

// 淘晶驰串口屏
#define STRING_MAX_LENGTH 100
//
#if 0
int fputc(int ch, FILE* stream){
	HAL_UART_Transmit(&huart1, (uint8_t *)ch, 1, 10);
	return ch;
}
#endif
//
void printf_sp(char *format){
	uint8_t i;
	for (i = 0;format[i] != '\0'; i ++);
	HAL_UART_Transmit(&huart1, (uint8_t *)format, i, 10);
}
//
void printf_s(char *format, ...){
	static char String[STRING_MAX_LENGTH];
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
	static char String[STRING_MAX_LENGTH];
	va_list arg;
	va_start(arg, format);
	vsprintf(String, format, arg);
	va_end(arg);
	printf_sp(String);
	printf_sp("\xff\xff\xff");
}
//
void Serial_TJC_SendTxt_n(uint8_t WindowIndex, uint8_t *str, uint8_t size){
	if (WindowIndex > 12) WindowIndex = 0;
	if (WindowIndex == 0)	printf_sp("\xff\xff\xffmain.t0.txt+=\"");
	else 					printf_s("\xff\xff\xffmain.bar%d.txt=\"", WindowIndex);
	HAL_UART_Transmit(&huart1, str, size, 10);
	printf_sp("\"\xff\xff\xff");
}
//
void Serial_TJC_SendTxt(uint8_t WindowIndex, char *format, ...){
	static char String[STRING_MAX_LENGTH];
	
	if (WindowIndex > 12) WindowIndex = 0;
	if (WindowIndex == 0)	printf_sp("\xff\xff\xffmain.t0.txt+=\"");
	else printf_s("\xff\xff\xffmain.bar%d.txt=\"", WindowIndex);
	
	va_list arg;
	va_start(arg, format);
	vsprintf(String, format, arg);
	va_end(arg);
	printf_sp(String);
	printf_sp("\"\xff\xff\xff");
}
//
void Serial_TJC_SendTxt_n_2(uint8_t WindowIndex, uint8_t *str, uint8_t size){
	printf_s("\xff\xff\xffshow.bar%d.txt=\"", WindowIndex);
	
	HAL_UART_Transmit(&huart1, str, size, 10);
	printf_sp("\"\xff\xff\xff");
}
//
void Serial_TJC_SendTxt_2(uint8_t WindowIndex, char *format, ...){
	static char String[STRING_MAX_LENGTH];
	
	printf_s("\xff\xff\xffshow.bar%d.txt=\"", WindowIndex);
	
	va_list arg;
	va_start(arg, format);
	vsprintf(String, format, arg);
	va_end(arg);
	printf_sp(String);
	printf_sp("\"\xff\xff\xff");
}
//
#if __SERIAL_TJC_RX_ENABLE
uint8_t cnt_rx = 0;
uint8_t rx_buff[BUFFER_SIZE];
uint32_t rx_tick = 0;
uint8_t t;
//
void TJC_Uart_Start(){
	HAL_UART_Receive_IT(&huart1, &rx_buff[cnt_rx], 1);
}
// 回调
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart){
	if (huart->Instance == USART1){
		rx_tick = uwTick;
        rx_buff[cnt_rx ++] = huart->Instance->RDR; 
        if (cnt_rx >= BUFFER_SIZE){
            cnt_rx = 0; 
        }
        HAL_UART_Receive_IT(&huart1, rx_buff, 1); 
	}
}
//
void MyUart_task(){
	if (cnt_rx){
		if (uwTick > rx_tick + 5){
			Serial_TJC_SendTxt(2, "接收数据:      接收字节:%2d", cnt_rx);
			Serial_TJC_SendTxt_n(4, rx_buff, cnt_rx);
			Serial_TJC_SendTxt(6, "%d", cnt_rx);
			cnt_rx = 0;
			huart1.pRxBuffPtr = rx_buff;
		}
	}
}
#endif
//





