#ifndef _CAPTURE_FREQ_H_
#define _CAPTURE_FREQ_H_

#include "main.h"
#include "tim.h"
#include "T2Uart.h"

extern uint32_t capture_Buf[4];   //存放计数值
extern uint8_t capture_Cnt;    //状态标志位
extern uint32_t high_time;   //高电平时间

extern void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim);
extern void work_Capture();

#endif
