#include "__HARDWARE_CONFIG__.h"
#if __HARDWARE_CONFIG__TJC_USART_ENABLE__
//*******************************// include _h files    //************************************//
#include "TJC_USART.h"
//*******************************// define parameters   //************************************//
//*******************************// parameters          //************************************//

uint32_t i;
static char String_Temp[STRING_MAX_LENGTH];
#if __HARDWARE_CONFIG__TJC_DMA_ENABLE__
	char DMA_TX_BUF[DMA_TX_BUF_MAX] __attribute__((section(".ARM.__at_0x24000000")));
	char DMA_RX_BUF[DMA_RX_BUF_MAX] __attribute__((section(".ARM.__at_0x24000100")));
#endif

//*******************************// define function     //************************************//

#if __HARDWARE_CONFIG__TJC_FPUTC_ENABLE__
//-----------------------------------------------------------------
// int fputc(int ch, FILE* stream)
//-----------------------------------------------------------------
//
// 函数功能: 重定向fputc函数到发送字节到USART1端口
// 入口参数1: int ch: 输入字
// 入口参数2: FILE* stream：文件流
// 返 回 值: 发送的字节
// 注意事项: 隶属TJC_USART.h
//
//-----------------------------------------------------------------
int fputc(int ch, FILE* stream){
    while(LL_USART_IsActiveFlag_TC(TJC_HDMI_UART)!=1);//等待发送完成
    LL_USART_TransmitData8(TJC_HDMI_UART, (uint8_t)ch);
    return ch;
}
#endif
//-----------------------------------------------------------------
// inline void TJC_PagaInit()
//-----------------------------------------------------------------
//
// 函数功能: 初始化TJC USART HMI界面
// 入口参数1: 无
// 注意事项: 无
//
//-----------------------------------------------------------------
inline void TJC_PagaInit(){
    printf_s_c("page main");
    printf_s_c("click b2,0");
    printf_s_c("click b4,0");
    printf_s_c("page show");
    printf_s_c("click b6,0");
}
//-----------------------------------------------------------------
// inline void TJC_SendByte(uint8_t Byte)
//-----------------------------------------------------------------
//
// 函数功能: 发送1字节到TJC_USART1端口
// 入口参数1: uint8_t Byte: 待发送字节
// 返 回 值: 无
// 注意事项: 无
//
//-----------------------------------------------------------------
inline void TJC_SendByte(uint8_t Byte){
    while(!LL_USART_IsActiveFlag_TC(TJC_HDMI_UART)); //等待发送完成
    LL_USART_TransmitData8(TJC_HDMI_UART, (uint8_t)Byte);
}
//-----------------------------------------------------------------
// inline void TJC_SendString_n(char* string, uint8_t size)
//-----------------------------------------------------------------
//
// 函数功能: 发送指定长度字符串到TJC_USART1端口
// 入口参数1: char* string: 待发送字符串
// 入口参数2: uint8_t size: 发送字符串长度
// 返 回 值: 无
// 注意事项: 无
//
//-----------------------------------------------------------------
inline void TJC_SendString_n(char* string, uint8_t size){
    for (i = 0;i < size;i ++){
        while(!LL_USART_IsActiveFlag_TC(TJC_HDMI_UART)); //等待发送完成
        LL_USART_TransmitData8(TJC_HDMI_UART, string[i]);
    }
}
//-----------------------------------------------------------------
// void TJC_SendString_s(char *format, ...)
//-----------------------------------------------------------------
//
// 函数功能: 发送格式化字符串到TJC_USART1端口,含格式化参数
// 入口参数1: char *format: 待发送格式化字符串
// 入口参数2: ... ： 格式化输入参数
// 返 回 值: 无
// 注意事项: 无
//
//-----------------------------------------------------------------
void TJC_SendString_s(char *format, ...){
	va_list arg;
	va_start(arg, format);
	vsprintf(String_Temp, format, arg);
	va_end(arg);
	for (i = 0;String_Temp[i] != '\0'; i ++){
        while(!LL_USART_IsActiveFlag_TC(TJC_HDMI_UART)); //等待发送完成
        LL_USART_TransmitData8(TJC_HDMI_UART, String_Temp[i]);
    }
}
//-----------------------------------------------------------------
// inline void TJC_SendString_sp(char *format)
//-----------------------------------------------------------------
//
// 函数功能: 发送格式化字符串到TJC_USART1端口,无格式化参数
// 入口参数1: char *format: 待发送指令字符串
// 返 回 值: 无
// 注意事项: 无
//
//-----------------------------------------------------------------
inline void TJC_SendString_sp(char *format){
	for (i = 0;format[i] != '\0'; i ++){
        while(!LL_USART_IsActiveFlag_TC(TJC_HDMI_UART)); //等待发送完成
        LL_USART_TransmitData8(TJC_HDMI_UART, format[i]);
    }
}
//-----------------------------------------------------------------
// void TJC_SendCmd_s(char *format, ...)
//-----------------------------------------------------------------
//
// 函数功能: 发送指令到TJC_USART1端口，含格式化参数
// 入口参数1: char *format: 待发送指令字符串
// 入口参数2: ... ： 格式化输入参数
// 返 回 值: 无
// 注意事项: 无
//
//-----------------------------------------------------------------
void TJC_SendCmd_s(char *format, ...){
	va_list arg;
	va_start(arg, format);
	vsprintf(String_Temp, format, arg);
	va_end(arg);
	TJC_SendString_n("\xff\xff\xff", 3);
	TJC_SendString_sp(String_Temp);
	TJC_SendString_n("\xff\xff\xff", 3);
}
//-----------------------------------------------------------------
// inline void TJC_SendCmd_sp(char *format)
//-----------------------------------------------------------------
//
// 函数功能: 发送指令到TJC_USART1端口，无格式化参数
// 入口参数1: char *format: 待发送指令字符串
// 返 回 值: 无
// 注意事项: 无
//
//-----------------------------------------------------------------
inline void TJC_SendCmd_sp(char *format){
	TJC_SendString_n("\xff\xff\xff", 3);
	TJC_SendString_sp(format);
	TJC_SendString_n("\xff\xff\xff", 3);
}
//-----------------------------------------------------------------
// inline void TJC_SendTxt_MAIN_n(uint8_t WindowIndex, uint8_t *string, uint8_t size)
//-----------------------------------------------------------------
//
// 函数功能: 发送指令到TJC_USART1端口,并在串口屏main page中的t0或barx控件显示字符串，指定长度
// 入口参数1: uint8_t WindowIndex: 窗口索引（0~12）
// 入口参数2: char* string: 待显示字符串
// 入口参数3: uint8_t size: 显示字符串长度
// 注意事项: 无
//
//-----------------------------------------------------------------
inline void TJC_SendTxt_MAIN_n(uint8_t WindowIndex, char *string, uint8_t size){
	if (WindowIndex == 0)	TJC_SendString_sp("\xff\xff\xffmain.t0.txt+=\"");
	else 					TJC_SendString_s("\xff\xff\xffmain.bar%d.txt=\"", WindowIndex);
	TJC_SendString_n(string, size);
	TJC_SendString_n("\"\xff\xff\xff", 4);
}
//-----------------------------------------------------------------
// void TJC_SendTxt_MAIN_s(uint8_t WindowIndex, char *format, ...)
//-----------------------------------------------------------------
//
// 函数功能: 发送指令到TJC_USART1端口,并在串口屏main page中的t0或barx控件显示字符串，含格式化参数
// 入口参数1: uint8_t WindowIndex: 窗口索引（0~12）
// 入口参数2: char* format: 待显示格式化字符串
// 入口参数3: ... ： 格式化输入参数
// 注意事项: 无
//
//-----------------------------------------------------------------
void TJC_SendTxt_MAIN_s(uint8_t WindowIndex, char *format, ...){
	if (WindowIndex == 0)	TJC_SendString_sp("\xff\xff\xffmain.t0.txt+=\"");
	else TJC_SendString_s("\xff\xff\xffmain.bar%d.txt=\"", WindowIndex);
	
	va_list arg;
	va_start(arg, format);
	vsprintf(String_Temp, format, arg);
	va_end(arg);
	TJC_SendString_sp(String_Temp);
	TJC_SendString_n("\"\xff\xff\xff", 4);
}
//-----------------------------------------------------------------
// inline void TJC_SendTxt_SHOW_n(uint8_t WindowIndex, char *string, uint8_t size)
//-----------------------------------------------------------------
//
// 函数功能: 发送指令到TJC_USART1端口,并在串口屏show page中的barx控件显示字符串，指定长度
// 入口参数1: uint8_t WindowIndex: 窗口索引（0~12）
// 入口参数2: char* string: 待显示字符串
// 入口参数3: uint8_t size: 显示字符串长度
// 注意事项: 无
//
//-----------------------------------------------------------------
inline void TJC_SendTxt_SHOW_n(uint8_t WindowIndex, char *string, uint8_t size){
	TJC_SendString_s("\xff\xff\xffshow.bar%d.txt=\"", WindowIndex);
	
	TJC_SendString_n(string, size);
	TJC_SendString_n("\"\xff\xff\xff", 4);
}
//-----------------------------------------------------------------
// void TJC_SendTxt_SHOW_s(uint8_t WindowIndex, char *format, ...)
//-----------------------------------------------------------------
//
// 函数功能: 发送指令到TJC_USART1端口,并在串口屏main page中的t0或barx控件显示字符串，含格式化参数
// 入口参数1: uint8_t WindowIndex: 窗口索引（0~12）
// 入口参数2: char* format: 待显示格式化字符串
// 入口参数3: ... ： 格式化输入参数
// 注意事项: 无
//
//-----------------------------------------------------------------
void TJC_SendTxt_SHOW_s(uint8_t WindowIndex, char *format, ...){
	TJC_SendString_s("\xff\xff\xffshow.bar%d.txt=\"", WindowIndex);
	
	va_list arg;
	va_start(arg, format);
	vsprintf(String_Temp, format, arg);
	va_end(arg);
	TJC_SendString_sp(String_Temp);
	TJC_SendString_n("\"\xff\xff\xff", 4);
}

#if __HARDWARE_CONFIG__TJC_DMA_ENABLE__
//-----------------------------------------------------------------
// void DMA_TJC_UART_UART_Init()
//-----------------------------------------------------------------
//
// 函数功能: 配置USART DMA转移功能
// 入口参数1: 无
// 注意事项: DMA_TX_BUF 和 DMA_RX_BUF 配置地址时记得看数据手册.STMH743的默认地址域DTCM域（0x20000000）不支持DMA1转运，
//			建议地址设在AXI SRAM域（0x24000000）
//
//-----------------------------------------------------------------
void DMA_TJC_UART_UART_Init(){
	/*发送配置*/
	// 使能DMA USART请求
	LL_USART_EnableDMAReq_TX(TJC_HDMI_UART);
	// 清除DMA传输完成中断与传输错误中断标志位 
	LL_DMA_ClearFlag_TC0(DMA1); // TCIF Очищаем флаги - это ОБЯЗАТЕЛЬНО
	LL_DMA_ClearFlag_TE0(DMA1);	// TELF
	// 使能DMA传输完成中断与传输错误中断
	LL_DMA_EnableIT_TC(DMA1, LL_DMA_STREAM_0);	// TCIE
	LL_DMA_EnableIT_TE(DMA1, LL_DMA_STREAM_0);	// TEIE

	// 设置DMA外设地址
	LL_DMA_SetPeriphAddress(DMA1, LL_DMA_STREAM_0, (uint32_t) &TJC_HDMI_UART->TDR);

	/*接收配置*/
	#if __HARDWARE_CONFIG__TJC_RX_ENABLE__
	// 使能DMA USART请求
	LL_USART_EnableDMAReq_RX(TJC_HDMI_UART); //Даем добро на запрос DMA TJC_HDMI_UART (передача и прием)
	// 清除DMA传输完成中断与传输错误中断标志位 
	LL_DMA_ClearFlag_TC1(DMA1);	// TCIF
	LL_DMA_ClearFlag_TE1(DMA1);	// TEIF
	// 使能DMA传输完成中断与传输错误中断
	LL_DMA_EnableIT_TC(DMA1, LL_DMA_STREAM_1);	// TCIE
	LL_DMA_EnableIT_TE(DMA1, LL_DMA_STREAM_1);	// TEIE

	 //设置接收最大数据长度
	 LL_DMA_SetDataLength(DMA1,LL_DMA_STREAM_1, 1);
	 //设置内存地址，也就是设置接收的数据要放哪
	 LL_DMA_SetMemoryAddress(DMA1,LL_DMA_STREAM_1, (uint32_t) &DMA_RX_BUF);
	 // 设置DMA外设地址
	LL_DMA_SetPeriphAddress(DMA1, LL_DMA_STREAM_0, (uint32_t) &TJC_HDMI_UART->RDR);
	 //使能接收DMA STREAM
	 LL_DMA_EnableStream(DMA1, LL_DMA_STREAM_1);  // 启动接收DMA
	 #endif
}

void TJC_DMA_SendString_n(const char *string, uint16_t size){
	while(!LL_USART_IsActiveFlag_TC(TJC_HDMI_UART)); //等待发送完成
	strncpy(DMA_TX_BUF, string, size);

	//失能DMA串口发送数据流
	LL_DMA_DisableStream(DMA1, LL_DMA_STREAM_0);
	// 设置DMA发送长度
    LL_DMA_SetDataLength(DMA1, LL_DMA_STREAM_0, size);
	// 配置发送DMA
    LL_DMA_SetMemoryAddress(DMA1,LL_DMA_STREAM_0, (uint32_t) &DMA_TX_BUF);
	
	#if 0	// DEBUG
	printf_s_d("S1 %s", DMA_TX_BUF);
	printf_s_d("MemoryAddr: 0x%08x\t", LL_DMA_GetMemoryAddress(DMA1, LL_DMA_STREAM_0));
	printf_s_d("PeriphAddr: 0x%08x\t\r\n", LL_DMA_GetPeriphAddress(DMA1, LL_DMA_STREAM_0));

	printf_s_d("DMA_TX_BUF: 0x%08x\t", &DMA_TX_BUF);
	printf_s_d("U1->TDR:    0x%08x\t\r\n", (uint32_t)&(TJC_HDMI_UART->TDR));
	#endif
	
	//使能DMA串口发送数据流
    LL_DMA_EnableStream(DMA1, LL_DMA_STREAM_0);
}
//-----------------------------------------------------------------
// void TJC_DMA_SendString_s(char *format, ...)
//-----------------------------------------------------------------
//
// 函数功能: 发送格式化字符串到TJC_USART1端口,含格式化参数
// 入口参数1: char *format: 待发送格式化字符串
// 入口参数2: ... ： 格式化输入参数
// 返 回 值: 无
// 注意事项: 无
//
//-----------------------------------------------------------------
void TJC_DMA_SendString_s(char *format, ...){
	while(!LL_USART_IsActiveFlag_TC(TJC_HDMI_UART)); //等待发送完成
	va_list arg;
	va_start(arg, format);
	vsprintf(DMA_TX_BUF, format, arg);
	va_end(arg);

	LL_DMA_DisableStream(DMA1, LL_DMA_STREAM_0);
	LL_DMA_SetDataLength(DMA1, LL_DMA_STREAM_0, strlen(DMA_TX_BUF));
	LL_DMA_SetMemoryAddress(DMA1,LL_DMA_STREAM_0, (uint32_t) &DMA_TX_BUF);
	LL_DMA_EnableStream(DMA1, LL_DMA_STREAM_0); 
}
//-----------------------------------------------------------------
// void TJC_DMA_SendString_sp(char *format)
//-----------------------------------------------------------------
//
// 函数功能: 发送格式化字符串到TJC_USART1端口,无格式化参数
// 入口参数1: char *format: 待发送指令字符串
// 返 回 值: 无
// 注意事项: 无
//
//-----------------------------------------------------------------
void TJC_DMA_SendString_sp(char *format){
	while(!LL_USART_IsActiveFlag_TC(TJC_HDMI_UART)); //等待发送完成
	strncpy(DMA_TX_BUF, format, strlen(format));

	LL_DMA_DisableStream(DMA1, LL_DMA_STREAM_0);
	LL_DMA_SetDataLength(DMA1, LL_DMA_STREAM_0, strlen(format));
	LL_DMA_SetMemoryAddress(DMA1,LL_DMA_STREAM_0, (uint32_t) &DMA_TX_BUF);
	LL_DMA_EnableStream(DMA1, LL_DMA_STREAM_0); 
}
//-----------------------------------------------------------------
// void TJC_DMA_SendCmd_s(char *format, ...)
//-----------------------------------------------------------------
//
// 函数功能: 发送指令到TJC_USART1端口，含格式化参数
// 入口参数1: char *format: 待发送指令字符串
// 入口参数2: ... ： 格式化输入参数
// 返 回 值: 无
// 注意事项: 无
//
//-----------------------------------------------------------------
void TJC_DMA_SendCmd_s(char *format, ...){
	while(!LL_USART_IsActiveFlag_TC(TJC_HDMI_UART)); //等待发送完成
	strncpy(&DMA_TX_BUF[0], "\xff\xff\xff", 3);
	va_list arg;
	va_start(arg, format);
	vsprintf(&DMA_TX_BUF[3], format, arg);
	va_end(arg);
	i = strlen(DMA_TX_BUF);
	strncpy(&DMA_TX_BUF[i], "\xff\xff\xff", 3);

	LL_DMA_DisableStream(DMA1, LL_DMA_STREAM_0);
	LL_DMA_SetDataLength(DMA1, LL_DMA_STREAM_0, i + 3);
	LL_DMA_SetMemoryAddress(DMA1,LL_DMA_STREAM_0, (uint32_t) &DMA_TX_BUF);
	LL_DMA_EnableStream(DMA1, LL_DMA_STREAM_0); 
}
//-----------------------------------------------------------------
// void TJC_DMA_SendCmd_sp(char *format)
//-----------------------------------------------------------------
//
// 函数功能: 发送指令到TJC_USART1端口，无格式化参数
// 入口参数1: char *format: 待发送指令字符串
// 返 回 值: 无
// 注意事项: 无
//
//-----------------------------------------------------------------
void TJC_DMA_SendCmd_sp(char *format){
	while(!LL_USART_IsActiveFlag_TC(TJC_HDMI_UART)); //等待发送完成
	i = strlen(format);

	strncpy(&DMA_TX_BUF[0], "\xff\xff\xff", 3);
	strncpy(&DMA_TX_BUF[3], format, i);
	strncpy(&DMA_TX_BUF[i + 3], "\xff\xff\xff", 3);

	LL_DMA_DisableStream(DMA1, LL_DMA_STREAM_0);
	LL_DMA_SetDataLength(DMA1, LL_DMA_STREAM_0, i + 6);
	LL_DMA_SetMemoryAddress(DMA1,LL_DMA_STREAM_0, (uint32_t) &DMA_TX_BUF);
	LL_DMA_EnableStream(DMA1, LL_DMA_STREAM_0); 
}
//-----------------------------------------------------------------
// void TJC_DMA_SendTxt_MAIN_n(uint8_t WindowIndex, uint8_t *string, uint8_t size)
//-----------------------------------------------------------------
//
// 函数功能: 发送指令到TJC_USART1端口,并在串口屏main page中的t0或barx控件显示字符串，指定长度
// 入口参数1: uint8_t WindowIndex: 窗口索引（0~12）
// 入口参数2: char* string: 待显示字符串
// 入口参数3: uint8_t size: 显示字符串长度
// 注意事项: 无
//
//-----------------------------------------------------------------
void TJC_DMA_SendTxt_MAIN_n(uint8_t WindowIndex, char *string, uint8_t size){
	while(!LL_USART_IsActiveFlag_TC(TJC_HDMI_UART)); //等待发送完成
	LL_DMA_DisableStream(DMA1, LL_DMA_STREAM_0);
	if (WindowIndex == 0){
		strncpy(DMA_TX_BUF, "\xff\xff\xffmain.t0.txt+=\"", 17);
		strncpy(&DMA_TX_BUF[17], string, size);
		strncpy(&DMA_TX_BUF[17 + size], "\"\xff\xff\xff", 4);
		LL_DMA_SetDataLength(DMA1, LL_DMA_STREAM_0, 17 + size + 4);
	}
	else {
		sprintf(DMA_TX_BUF, "\xff\xff\xffmain.bar%d.txt=\"", WindowIndex);
		i = strlen(DMA_TX_BUF);
		strncpy(&DMA_TX_BUF[i], string, size);
		strncpy(&DMA_TX_BUF[i + size], "\"\xff\xff\xff", 4);
		LL_DMA_SetDataLength(DMA1, LL_DMA_STREAM_0, i + size + 4);
	}
	LL_DMA_SetMemoryAddress(DMA1,LL_DMA_STREAM_0, (uint32_t) &DMA_TX_BUF);
	LL_DMA_EnableStream(DMA1, LL_DMA_STREAM_0); 
}
//-----------------------------------------------------------------
// void TJC_DMA_SendTxt_MAIN_s(uint8_t WindowIndex, char *format, ...)
//-----------------------------------------------------------------
//
// 函数功能: 发送指令到TJC_USART1端口,并在串口屏main page中的t0或barx控件显示字符串，含格式化参数
// 入口参数1: uint8_t WindowIndex: 窗口索引（0~12）
// 入口参数2: char* format: 待显示格式化字符串
// 入口参数3: ... ： 格式化输入参数
// 注意事项: 无
//
//-----------------------------------------------------------------
void TJC_DMA_SendTxt_MAIN_s(uint8_t WindowIndex, char *format, ...){
	while(!LL_USART_IsActiveFlag_TC(TJC_HDMI_UART)); //等待发送完成
	LL_DMA_DisableStream(DMA1, LL_DMA_STREAM_0);
	if (WindowIndex == 0){
		strncpy(DMA_TX_BUF, "\xff\xff\xffmain.t0.txt+=\"", 17);
		va_list arg;
		va_start(arg, format);
		vsprintf(&DMA_TX_BUF[17], format, arg);
		va_end(arg);
		i = strlen(DMA_TX_BUF);
		strncpy(&DMA_TX_BUF[i], "\"\xff\xff\xff", 4);
		LL_DMA_SetDataLength(DMA1, LL_DMA_STREAM_0, i + 4);
	}
	else {
		sprintf(DMA_TX_BUF, "\xff\xff\xffmain.bar%d.txt=\"", WindowIndex);
		i = strlen(DMA_TX_BUF);
		va_list arg;
		va_start(arg, format);
		vsprintf(&DMA_TX_BUF[i], format, arg);
		va_end(arg);
		i = strlen(DMA_TX_BUF);
		strncpy(&DMA_TX_BUF[i], "\"\xff\xff\xff", 4);
		LL_DMA_SetDataLength(DMA1, LL_DMA_STREAM_0, i + 4);
	}
	LL_DMA_SetMemoryAddress(DMA1,LL_DMA_STREAM_0, (uint32_t) &DMA_TX_BUF);
	LL_DMA_EnableStream(DMA1, LL_DMA_STREAM_0); 
}
//-----------------------------------------------------------------
// void TJC_DMA_SendTxt_SHOW_n(uint8_t WindowIndex, char *string, uint8_t size)
//-----------------------------------------------------------------
//
// 函数功能: 发送指令到TJC_USART1端口,并在串口屏show page中的barx控件显示字符串，指定长度
// 入口参数1: uint8_t WindowIndex: 窗口索引（0~12）
// 入口参数2: char* string: 待显示字符串
// 入口参数3: uint8_t size: 显示字符串长度
// 注意事项: 无
//
//-----------------------------------------------------------------
void TJC_DMA_SendTxt_SHOW_n(uint8_t WindowIndex, char *string, uint8_t size){
	while(!LL_USART_IsActiveFlag_TC(TJC_HDMI_UART)); //等待发送完成
	LL_DMA_DisableStream(DMA1, LL_DMA_STREAM_0);

	sprintf(DMA_TX_BUF, "\xff\xff\xffshow.bar%d.txt=\"", WindowIndex);
	i = strlen(DMA_TX_BUF);
	strncpy(&DMA_TX_BUF[i], string, size);
	strncpy(&DMA_TX_BUF[i + size], "\"\xff\xff\xff", 4);
	LL_DMA_SetDataLength(DMA1, LL_DMA_STREAM_0, i + size + 4);

	LL_DMA_SetMemoryAddress(DMA1,LL_DMA_STREAM_0, (uint32_t) &DMA_TX_BUF);
	LL_DMA_EnableStream(DMA1, LL_DMA_STREAM_0); 
}
//-----------------------------------------------------------------
// void TJC_DMA_SendTxt_SHOW_s(uint8_t WindowIndex, char *format, ...)
//-----------------------------------------------------------------
//
// 函数功能: 发送指令到TJC_USART1端口,并在串口屏main page中的t0或barx控件显示字符串，含格式化参数
// 入口参数1: uint8_t WindowIndex: 窗口索引（0~12）
// 入口参数2: char* format: 待显示格式化字符串
// 入口参数3: ... ： 格式化输入参数
// 注意事项: 无
//
//-----------------------------------------------------------------
void TJC_DMA_SendTxt_SHOW_s(uint8_t WindowIndex, char *format, ...){
	while(!LL_USART_IsActiveFlag_TC(TJC_HDMI_UART)); //等待发送完成
	LL_DMA_DisableStream(DMA1, LL_DMA_STREAM_0);

	sprintf(DMA_TX_BUF, "\xff\xff\xffshow.bar%d.txt=\"", WindowIndex);
	i = strlen(DMA_TX_BUF);
	va_list arg;
	va_start(arg, format);
	vsprintf(&DMA_TX_BUF[i], format, arg);
	va_end(arg);
	i = strlen(DMA_TX_BUF);
	strncpy(&DMA_TX_BUF[i], "\"\xff\xff\xff", 4);
	LL_DMA_SetDataLength(DMA1, LL_DMA_STREAM_0, i + 4);
	
	LL_DMA_SetMemoryAddress(DMA1,LL_DMA_STREAM_0, (uint32_t) &DMA_TX_BUF);
	LL_DMA_EnableStream(DMA1, LL_DMA_STREAM_0); 
}
#endif	// end of __HARDWARE_CONFIG__TJC_DMA_ENABLE__


//*******************************// end_c               //************************************//
#endif 	// end of __HARDWARE_CONFIG__TJC_USART_ENABLE__
