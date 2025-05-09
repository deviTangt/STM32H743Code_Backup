#ifndef _T2UART_H_
#define _T2UART_H_

#include "main.h"
#include "usart.h"

int fputc(int ch, FILE *f);
/**
  * 函数功能: 重定向c库函数getchar,scanf到DEBUG_USARTx
  * 输入参数: 无
  * 返 回 值: 无
  * 说    明：无
  */
int fgetc(FILE *f);


#endif
