#ifndef _ADS_USART_DRIVER_H_
#define _ADS_USART_DRIVER_H_
#include "main.h"
#include "memorymap.h"
#include "usart.h"
#include "gpio.h"
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include "__HRADWARE_DEF__.h"


//
void printf_s_2(char *format, ...);
//
void printf_n_2(uint8_t *str, uint8_t size);
//
void ADS_SendFreq(uint32_t freq);
//

#endif