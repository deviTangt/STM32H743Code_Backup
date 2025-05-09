#include "capture_freq.h"


uint32_t capture_Buf[4] = {0};   //存放计数值
uint8_t capture_Cnt = 0;    //状态标志位
uint32_t Freq = 0;   //高电平时间
uint32_t Duty = 0;   //高电平时间
uint32_t high_time = 0;   //高电平时间
/**
  * 函数功能: 回调函数
  * 输入参数: 无
  * 返 回 值: 无
  * 说    明：无
  */
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
	if(htim->Instance == TIM1)
	{
    if(htim->Channel == 1){   // 上升沿
      if (capture_Cnt == 1){
        capture_Buf[0] = HAL_TIM_ReadCapturedValue(&htim1,TIM_CHANNEL_1);//获取当前的捕获值.
				__HAL_TIM_SET_CAPTUREPOLARITY(&htim1,TIM_CHANNEL_1,TIM_ICPOLARITY_FALLING);  //设置为下降沿捕获
				capture_Cnt++;
      }
      else if (capture_Cnt == 2){ // 下降沿
        capture_Buf[1] = HAL_TIM_ReadCapturedValue(&htim1,TIM_CHANNEL_1);//获取当前的捕获值.
				__HAL_TIM_SET_CAPTUREPOLARITY(&htim1, TIM_CHANNEL_1, TIM_INPUTCHANNELPOLARITY_RISING); //设置为上升沿捕获
				capture_Cnt++;  
      }
      else if (capture_Cnt == 3){ // 上升沿
        capture_Buf[2] = HAL_TIM_ReadCapturedValue(&htim1,TIM_CHANNEL_1);//获取当前的捕获值.
				__HAL_TIM_SET_CAPTUREPOLARITY(&htim1,TIM_CHANNEL_1,TIM_ICPOLARITY_FALLING);  //设置为下降沿捕获
				capture_Cnt++;
      }
      else if (capture_Cnt == 4){ // 下降沿
        capture_Buf[3] = HAL_TIM_ReadCapturedValue(&htim1,TIM_CHANNEL_1);//获取当前的捕获值.
				HAL_TIM_IC_Stop_IT(&htim1,TIM_CHANNEL_1); //停止捕获   或者: __HAL_TIM_DISABLE(&htim5);
				capture_Cnt++;  
      }
    }
	}
}
//
void work_Capture(){
  switch (capture_Cnt){
    case 0:
      capture_Cnt++;
      __HAL_TIM_SET_CAPTUREPOLARITY(&htim1, TIM_CHANNEL_1, TIM_INPUTCHANNELPOLARITY_RISING); //设置为上升沿捕获
      HAL_TIM_IC_Start_IT(&htim1, TIM_CHANNEL_1);	//启动输入捕获       或者: __HAL_TIM_ENABLE(&htim5);
      break;
    case 5:
    Freq = 1000000 / (capture_Buf[2] - capture_Buf[0]);
    high_time = capture_Buf[1]- capture_Buf[0];    //高电平时间
    Duty = high_time * 100 / (capture_Buf[2] - capture_Buf[0]);
    printf("Freq:%dHz, Duty:%d\r\n", Freq, Duty);
             
    capture_Cnt = 0;  //清空标志位
    break;   
  }
}


 //




