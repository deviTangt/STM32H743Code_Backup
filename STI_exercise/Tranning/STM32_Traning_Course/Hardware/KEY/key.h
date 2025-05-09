#ifndef _KEY_H_
#define _KEY_H_

#include "main.h"
#include "led.h"

/**
  * 函数功能: 按键外部中断回调函数
  * 输入参数: GPIO_Pin：中断引脚
  * 返 回 值: 无
  * 说    明: 无
  */
 void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin);

#endif
