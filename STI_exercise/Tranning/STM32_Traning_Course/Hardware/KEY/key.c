#include "key.h"

/**
  * 函数功能: 按键外部中断回调函数
  * 输入参数: GPIO_Pin：中断引脚
  * 返 回 值: 无
  * 说    明: 无
  */
 void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
 {
   if(GPIO_Pin==KEY_1_Pin)
   {
   
     if(HAL_GPIO_ReadPin(KEY_1_GPIO_Port,KEY_1_Pin) == GPIO_PIN_RESET)
     {
      LED_TOGGLE();
     }
     __HAL_GPIO_EXTI_CLEAR_IT(KEY_1_Pin);
   }
   else if(GPIO_Pin==KEY_2_Pin)
   {
  
     if(HAL_GPIO_ReadPin(KEY_2_GPIO_Port,KEY_2_Pin) == GPIO_PIN_RESET)
     {
      LED_TOGGLE();
     }
     __HAL_GPIO_EXTI_CLEAR_IT(KEY_2_Pin);
   }
 }
 //




