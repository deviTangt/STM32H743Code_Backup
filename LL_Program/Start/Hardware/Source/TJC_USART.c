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
// ��������: �ض���fputc�����������ֽڵ�USART1�˿�
// ��ڲ���1: int ch: ������
// ��ڲ���2: FILE* stream���ļ���
// �� �� ֵ: ���͵��ֽ�
// ע������: ����TJC_USART.h
//
//-----------------------------------------------------------------
int fputc(int ch, FILE* stream){
    while(LL_USART_IsActiveFlag_TC(TJC_HDMI_UART)!=1);//�ȴ��������
    LL_USART_TransmitData8(TJC_HDMI_UART, (uint8_t)ch);
    return ch;
}
#endif
//-----------------------------------------------------------------
// inline void TJC_PagaInit()
//-----------------------------------------------------------------
//
// ��������: ��ʼ��TJC USART HMI����
// ��ڲ���1: ��
// ע������: ��
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
// ��������: ����1�ֽڵ�TJC_USART1�˿�
// ��ڲ���1: uint8_t Byte: �������ֽ�
// �� �� ֵ: ��
// ע������: ��
//
//-----------------------------------------------------------------
inline void TJC_SendByte(uint8_t Byte){
    while(!LL_USART_IsActiveFlag_TC(TJC_HDMI_UART)); //�ȴ��������
    LL_USART_TransmitData8(TJC_HDMI_UART, (uint8_t)Byte);
}
//-----------------------------------------------------------------
// inline void TJC_SendString_n(char* string, uint8_t size)
//-----------------------------------------------------------------
//
// ��������: ����ָ�������ַ�����TJC_USART1�˿�
// ��ڲ���1: char* string: �������ַ���
// ��ڲ���2: uint8_t size: �����ַ�������
// �� �� ֵ: ��
// ע������: ��
//
//-----------------------------------------------------------------
inline void TJC_SendString_n(char* string, uint8_t size){
    for (i = 0;i < size;i ++){
        while(!LL_USART_IsActiveFlag_TC(TJC_HDMI_UART)); //�ȴ��������
        LL_USART_TransmitData8(TJC_HDMI_UART, string[i]);
    }
}
//-----------------------------------------------------------------
// void TJC_SendString_s(char *format, ...)
//-----------------------------------------------------------------
//
// ��������: ���͸�ʽ���ַ�����TJC_USART1�˿�,����ʽ������
// ��ڲ���1: char *format: �����͸�ʽ���ַ���
// ��ڲ���2: ... �� ��ʽ���������
// �� �� ֵ: ��
// ע������: ��
//
//-----------------------------------------------------------------
void TJC_SendString_s(char *format, ...){
	va_list arg;
	va_start(arg, format);
	vsprintf(String_Temp, format, arg);
	va_end(arg);
	for (i = 0;String_Temp[i] != '\0'; i ++){
        while(!LL_USART_IsActiveFlag_TC(TJC_HDMI_UART)); //�ȴ��������
        LL_USART_TransmitData8(TJC_HDMI_UART, String_Temp[i]);
    }
}
//-----------------------------------------------------------------
// inline void TJC_SendString_sp(char *format)
//-----------------------------------------------------------------
//
// ��������: ���͸�ʽ���ַ�����TJC_USART1�˿�,�޸�ʽ������
// ��ڲ���1: char *format: ������ָ���ַ���
// �� �� ֵ: ��
// ע������: ��
//
//-----------------------------------------------------------------
inline void TJC_SendString_sp(char *format){
	for (i = 0;format[i] != '\0'; i ++){
        while(!LL_USART_IsActiveFlag_TC(TJC_HDMI_UART)); //�ȴ��������
        LL_USART_TransmitData8(TJC_HDMI_UART, format[i]);
    }
}
//-----------------------------------------------------------------
// void TJC_SendCmd_s(char *format, ...)
//-----------------------------------------------------------------
//
// ��������: ����ָ�TJC_USART1�˿ڣ�����ʽ������
// ��ڲ���1: char *format: ������ָ���ַ���
// ��ڲ���2: ... �� ��ʽ���������
// �� �� ֵ: ��
// ע������: ��
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
// ��������: ����ָ�TJC_USART1�˿ڣ��޸�ʽ������
// ��ڲ���1: char *format: ������ָ���ַ���
// �� �� ֵ: ��
// ע������: ��
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
// ��������: ����ָ�TJC_USART1�˿�,���ڴ�����main page�е�t0��barx�ؼ���ʾ�ַ�����ָ������
// ��ڲ���1: uint8_t WindowIndex: ����������0~12��
// ��ڲ���2: char* string: ����ʾ�ַ���
// ��ڲ���3: uint8_t size: ��ʾ�ַ�������
// ע������: ��
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
// ��������: ����ָ�TJC_USART1�˿�,���ڴ�����main page�е�t0��barx�ؼ���ʾ�ַ���������ʽ������
// ��ڲ���1: uint8_t WindowIndex: ����������0~12��
// ��ڲ���2: char* format: ����ʾ��ʽ���ַ���
// ��ڲ���3: ... �� ��ʽ���������
// ע������: ��
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
// ��������: ����ָ�TJC_USART1�˿�,���ڴ�����show page�е�barx�ؼ���ʾ�ַ�����ָ������
// ��ڲ���1: uint8_t WindowIndex: ����������0~12��
// ��ڲ���2: char* string: ����ʾ�ַ���
// ��ڲ���3: uint8_t size: ��ʾ�ַ�������
// ע������: ��
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
// ��������: ����ָ�TJC_USART1�˿�,���ڴ�����main page�е�t0��barx�ؼ���ʾ�ַ���������ʽ������
// ��ڲ���1: uint8_t WindowIndex: ����������0~12��
// ��ڲ���2: char* format: ����ʾ��ʽ���ַ���
// ��ڲ���3: ... �� ��ʽ���������
// ע������: ��
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
// ��������: ����USART DMAת�ƹ���
// ��ڲ���1: ��
// ע������: DMA_TX_BUF �� DMA_RX_BUF ���õ�ַʱ�ǵÿ������ֲ�.STMH743��Ĭ�ϵ�ַ��DTCM��0x20000000����֧��DMA1ת�ˣ�
//			�����ַ����AXI SRAM��0x24000000��
//
//-----------------------------------------------------------------
void DMA_TJC_UART_UART_Init(){
	/*��������*/
	// ʹ��DMA USART����
	LL_USART_EnableDMAReq_TX(TJC_HDMI_UART);
	// ���DMA��������ж��봫������жϱ�־λ 
	LL_DMA_ClearFlag_TC0(DMA1); // TCIF ����ڧ�ѧ֧� ��ݧѧԧ� - ���� ����������������������
	LL_DMA_ClearFlag_TE0(DMA1);	// TELF
	// ʹ��DMA��������ж��봫������ж�
	LL_DMA_EnableIT_TC(DMA1, LL_DMA_STREAM_0);	// TCIE
	LL_DMA_EnableIT_TE(DMA1, LL_DMA_STREAM_0);	// TEIE

	// ����DMA�����ַ
	LL_DMA_SetPeriphAddress(DMA1, LL_DMA_STREAM_0, (uint32_t) &TJC_HDMI_UART->TDR);

	/*��������*/
	#if __HARDWARE_CONFIG__TJC_RX_ENABLE__
	// ʹ��DMA USART����
	LL_USART_EnableDMAReq_RX(TJC_HDMI_UART); //���ѧ֧� �է�ҧ�� �ߧ� �٧ѧ���� DMA TJC_HDMI_UART (��֧�֧էѧ�� �� ���ڧ֧�)
	// ���DMA��������ж��봫������жϱ�־λ 
	LL_DMA_ClearFlag_TC1(DMA1);	// TCIF
	LL_DMA_ClearFlag_TE1(DMA1);	// TEIF
	// ʹ��DMA��������ж��봫������ж�
	LL_DMA_EnableIT_TC(DMA1, LL_DMA_STREAM_1);	// TCIE
	LL_DMA_EnableIT_TE(DMA1, LL_DMA_STREAM_1);	// TEIE

	 //���ý���������ݳ���
	 LL_DMA_SetDataLength(DMA1,LL_DMA_STREAM_1, 1);
	 //�����ڴ��ַ��Ҳ�������ý��յ�����Ҫ����
	 LL_DMA_SetMemoryAddress(DMA1,LL_DMA_STREAM_1, (uint32_t) &DMA_RX_BUF);
	 // ����DMA�����ַ
	LL_DMA_SetPeriphAddress(DMA1, LL_DMA_STREAM_0, (uint32_t) &TJC_HDMI_UART->RDR);
	 //ʹ�ܽ���DMA STREAM
	 LL_DMA_EnableStream(DMA1, LL_DMA_STREAM_1);  // ��������DMA
	 #endif
}

void TJC_DMA_SendString_n(const char *string, uint16_t size){
	while(!LL_USART_IsActiveFlag_TC(TJC_HDMI_UART)); //�ȴ��������
	strncpy(DMA_TX_BUF, string, size);

	//ʧ��DMA���ڷ���������
	LL_DMA_DisableStream(DMA1, LL_DMA_STREAM_0);
	// ����DMA���ͳ���
    LL_DMA_SetDataLength(DMA1, LL_DMA_STREAM_0, size);
	// ���÷���DMA
    LL_DMA_SetMemoryAddress(DMA1,LL_DMA_STREAM_0, (uint32_t) &DMA_TX_BUF);
	
	#if 0	// DEBUG
	printf_s_d("S1 %s", DMA_TX_BUF);
	printf_s_d("MemoryAddr: 0x%08x\t", LL_DMA_GetMemoryAddress(DMA1, LL_DMA_STREAM_0));
	printf_s_d("PeriphAddr: 0x%08x\t\r\n", LL_DMA_GetPeriphAddress(DMA1, LL_DMA_STREAM_0));

	printf_s_d("DMA_TX_BUF: 0x%08x\t", &DMA_TX_BUF);
	printf_s_d("U1->TDR:    0x%08x\t\r\n", (uint32_t)&(TJC_HDMI_UART->TDR));
	#endif
	
	//ʹ��DMA���ڷ���������
    LL_DMA_EnableStream(DMA1, LL_DMA_STREAM_0);
}
//-----------------------------------------------------------------
// void TJC_DMA_SendString_s(char *format, ...)
//-----------------------------------------------------------------
//
// ��������: ���͸�ʽ���ַ�����TJC_USART1�˿�,����ʽ������
// ��ڲ���1: char *format: �����͸�ʽ���ַ���
// ��ڲ���2: ... �� ��ʽ���������
// �� �� ֵ: ��
// ע������: ��
//
//-----------------------------------------------------------------
void TJC_DMA_SendString_s(char *format, ...){
	while(!LL_USART_IsActiveFlag_TC(TJC_HDMI_UART)); //�ȴ��������
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
// ��������: ���͸�ʽ���ַ�����TJC_USART1�˿�,�޸�ʽ������
// ��ڲ���1: char *format: ������ָ���ַ���
// �� �� ֵ: ��
// ע������: ��
//
//-----------------------------------------------------------------
void TJC_DMA_SendString_sp(char *format){
	while(!LL_USART_IsActiveFlag_TC(TJC_HDMI_UART)); //�ȴ��������
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
// ��������: ����ָ�TJC_USART1�˿ڣ�����ʽ������
// ��ڲ���1: char *format: ������ָ���ַ���
// ��ڲ���2: ... �� ��ʽ���������
// �� �� ֵ: ��
// ע������: ��
//
//-----------------------------------------------------------------
void TJC_DMA_SendCmd_s(char *format, ...){
	while(!LL_USART_IsActiveFlag_TC(TJC_HDMI_UART)); //�ȴ��������
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
// ��������: ����ָ�TJC_USART1�˿ڣ��޸�ʽ������
// ��ڲ���1: char *format: ������ָ���ַ���
// �� �� ֵ: ��
// ע������: ��
//
//-----------------------------------------------------------------
void TJC_DMA_SendCmd_sp(char *format){
	while(!LL_USART_IsActiveFlag_TC(TJC_HDMI_UART)); //�ȴ��������
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
// ��������: ����ָ�TJC_USART1�˿�,���ڴ�����main page�е�t0��barx�ؼ���ʾ�ַ�����ָ������
// ��ڲ���1: uint8_t WindowIndex: ����������0~12��
// ��ڲ���2: char* string: ����ʾ�ַ���
// ��ڲ���3: uint8_t size: ��ʾ�ַ�������
// ע������: ��
//
//-----------------------------------------------------------------
void TJC_DMA_SendTxt_MAIN_n(uint8_t WindowIndex, char *string, uint8_t size){
	while(!LL_USART_IsActiveFlag_TC(TJC_HDMI_UART)); //�ȴ��������
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
// ��������: ����ָ�TJC_USART1�˿�,���ڴ�����main page�е�t0��barx�ؼ���ʾ�ַ���������ʽ������
// ��ڲ���1: uint8_t WindowIndex: ����������0~12��
// ��ڲ���2: char* format: ����ʾ��ʽ���ַ���
// ��ڲ���3: ... �� ��ʽ���������
// ע������: ��
//
//-----------------------------------------------------------------
void TJC_DMA_SendTxt_MAIN_s(uint8_t WindowIndex, char *format, ...){
	while(!LL_USART_IsActiveFlag_TC(TJC_HDMI_UART)); //�ȴ��������
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
// ��������: ����ָ�TJC_USART1�˿�,���ڴ�����show page�е�barx�ؼ���ʾ�ַ�����ָ������
// ��ڲ���1: uint8_t WindowIndex: ����������0~12��
// ��ڲ���2: char* string: ����ʾ�ַ���
// ��ڲ���3: uint8_t size: ��ʾ�ַ�������
// ע������: ��
//
//-----------------------------------------------------------------
void TJC_DMA_SendTxt_SHOW_n(uint8_t WindowIndex, char *string, uint8_t size){
	while(!LL_USART_IsActiveFlag_TC(TJC_HDMI_UART)); //�ȴ��������
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
// ��������: ����ָ�TJC_USART1�˿�,���ڴ�����main page�е�t0��barx�ؼ���ʾ�ַ���������ʽ������
// ��ڲ���1: uint8_t WindowIndex: ����������0~12��
// ��ڲ���2: char* format: ����ʾ��ʽ���ַ���
// ��ڲ���3: ... �� ��ʽ���������
// ע������: ��
//
//-----------------------------------------------------------------
void TJC_DMA_SendTxt_SHOW_s(uint8_t WindowIndex, char *format, ...){
	while(!LL_USART_IsActiveFlag_TC(TJC_HDMI_UART)); //�ȴ��������
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
