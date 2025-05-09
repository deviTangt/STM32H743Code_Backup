#include "__HARDWARE_CONFIG__.h"
#if __HARDWARE_CONFIG__TJC_USART_ENABLE__
#ifndef __TJC_USART_H__
#define __TJC_USART_H__
//*******************************// include extern .h files //************************************//
#include "main.h"
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
//*******************************// define statement        //************************************//

#define STRING_MAX_LENGTH       255         // 字符串栈长度最大值
#if __HARDWARE_CONFIG__TJC_printf_sn_ENABLE__
    #if __HARDWARE_CONFIG__TJC_DMA_ENABLE__  
        #define printf_s_c              TJC_DMA_SendCmd_s
        #define printf_n_m              TJC_DMA_SendTxt_MAIN_n
        #define printf_s                TJC_DMA_SendTxt_SHOW_s
        #define printf_n                TJC_DMA_SendTxt_SHOW_n
        #define printf_s_d              TJC_DMA_SendString_s
        #define printf_n_d              TJC_DMA_SendString_n
    #else 
        #define printf_s_c              TJC_SendCmd_s
        #define printf_s_m              TJC_SendTxt_MAIN_s
        #define printf_n_m              TJC_SendTxt_MAIN_n
        #define printf_s                TJC_SendTxt_SHOW_s
        #define printf_n                TJC_SendTxt_SHOW_n
        #define printf_s_d              TJC_SendString_s
        #define printf_n_d              TJC_SendString_n
    #endif // __HARDWARE_CONFIG__TJC_DMA_ENABLE__
#endif



#if __HARDWARE_CONFIG__TJC_DMA_ENABLE__     // DMA参数
    #define DMA_RX_BUF_MAX     255
    #define DMA_TX_BUF_MAX     255
#endif

//*******************************// extern parameters       //************************************//
//*******************************// define structure unity  //************************************//
//*******************************// define parameters       //************************************//
//*******************************// extern function         //************************************//

#if __HARDWARE_CONFIG__TJC_FPUTC_ENABLE__
int fputc(int ch, FILE* stream);
#endif
extern inline void TJC_PagaInit();

extern inline void TJC_SendByte(uint8_t Byte);

extern inline void TJC_SendString_n(char* string, uint8_t size);
extern void TJC_SendString_s(char *format, ...);
extern inline void TJC_SendString_sp(char *format);

extern void TJC_SendCmd_s(char *format, ...);
extern inline void TJC_SendCmd_sp(char *format);

extern inline void TJC_SendTxt_MAIN_n(uint8_t WindowIndex, char *string, uint8_t size);
extern void TJC_SendTxt_MAIN_s(uint8_t WindowIndex, char *format, ...);
extern inline void TJC_SendTxt_SHOW_n(uint8_t WindowIndex, char *string, uint8_t size);
extern void TJC_SendTxt_SHOW_s(uint8_t WindowIndex, char *format, ...);

#if __HARDWARE_CONFIG__TJC_DMA_ENABLE__
extern void DMA_TJC_UART_UART_Init();
extern void TJC_DMA_SendString_n(const char *string, uint16_t size);
extern void TJC_DMA_SendString_s(char *format, ...);
extern void TJC_DMA_SendString_sp(char *format);
extern void TJC_DMA_SendCmd_s(char *format, ...);
extern void TJC_DMA_SendCmd_sp(char *format);
extern void TJC_DMA_SendTxt_MAIN_n(uint8_t WindowIndex, char *string, uint8_t size);
extern void TJC_DMA_SendTxt_MAIN_s(uint8_t WindowIndex, char *format, ...);
extern void TJC_DMA_SendTxt_SHOW_n(uint8_t WindowIndex, char *string, uint8_t size);
extern void TJC_DMA_SendTxt_SHOW_s(uint8_t WindowIndex, char *format, ...);
#endif // end of __HARDWARE_CONFIG__TJC_DMA_ENABLE__

//*******************************// end_h                   //************************************//
#endif
#endif
