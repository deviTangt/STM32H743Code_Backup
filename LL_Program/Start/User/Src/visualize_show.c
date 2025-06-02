#include "__HARDWARE_CONFIG__.h"
#if __HARDWARE_CONFIG__VISUALIZE_SHOW_ENABLE__	// begin of __HARDWARE_CONFIG__VISUALIZE_SHOW_ENABLE__
//*******************************// include _h files    //************************************//
#include "visualize_show.h"
//*******************************// define parameters   //************************************//
//*******************************// parameters          //************************************//
//*******************************// define function     //************************************//

//-----------------------------------------------------------------
// void visualize_show()
//-----------------------------------------------------------------
//
// 函数功能: 打印可视化调试信息
// 入口参数1: 无
// 返 回 值: 无
// 注意事项: 无
//
//-----------------------------------------------------------------
void visualize_show(){
    //? 输入捕获信息
    if (TIM2CH1_CAPTURE_STA == 3){
      if (TIM2CH1_CAPTURE_Period < 1000000){ // freq >= 1Hz
        printf_s(10, "timer2_call_cnt:%d", timer2_call_cnt);
        printf_s(11, "CAP_VAl[0]:%d", TIM2CH1_CAPTURE_VAl[0]);
        printf_s(12, "CAP_VAl[1]:%d", TIM2CH1_CAPTURE_VAl[1]);
        printf_s(13, "CAP_VAl[2]:%d", TIM2CH1_CAPTURE_VAl[2]);
        printf_s(14, "CAP_VAl[3]:%d", TIM2CH1_CAPTURE_VAl[3]);
        printf_s(15, "周期:%2d.%03ds %03dus", TIM2CH1_CAPTURE_Period / 1000000, TIM2CH1_CAPTURE_Period / 1000 % 1000, TIM2CH1_CAPTURE_Period % 1000);
        if (1000000.0 / TIM2CH1_CAPTURE_Period > 0.02)
          printf_s(16, "频率:%.3fHz", 1000000.0 / TIM2CH1_CAPTURE_Period);
        if (TIM2CH1_CAPTURE_DutyPeriod * 100 / TIM2CH1_CAPTURE_Period > 0){
          printf_s(17, "正占空比:%2d.%03d%%", TIM2CH1_CAPTURE_DutyPeriod * 100 / TIM2CH1_CAPTURE_Period, TIM2CH1_CAPTURE_DutyPeriod * 100000 / TIM2CH1_CAPTURE_Period % 1000);
          printf_s(18, "负占空比:%2d.%03d%%", (TIM2CH1_CAPTURE_Period - TIM2CH1_CAPTURE_DutyPeriod) * 100 / TIM2CH1_CAPTURE_Period, (TIM2CH1_CAPTURE_Period - TIM2CH1_CAPTURE_DutyPeriod) * 100000 / TIM2CH1_CAPTURE_Period % 1000);
        }
      }
    }

    //? 数据接收
    if (RX_tick > Rx_tick_pre + 100){
        Rx_tick_pre = RX_tick;
        // 打印接收到的数据缓冲器
        printf("Main Receive:%*s\r\n", DMA_RX_Length, DMA_RX_BUF);
        
        DMA_RX_Length = 0;
    }

    //? dma adc数据
    #if __HARDWARE_CONFIG__DMA_ADC1_ENABLE__ // begin of __HARDWARE_CONFIG__DMA_ADC1_ENABLE__
      printf_s(5, "dma_cnt:%d,%0d,%0d", dma_adc1_finish_cnt / 1000000, dma_adc1_finish_cnt / 1000 % 1000, dma_adc1_finish_cnt % 1000);
      for (uint8_t i = 0;i < 1;i ++){
        printf_s(6 + i, "AD1_val %d:%dmV", i, (DMA_ADC1_RX_BUF[i] * 3300) >> 16);
      }
    #endif // end of __HARDWARE_CONFIG__DMA_ADC1_ENABLE__
    #if __HARDWARE_CONFIG__DMA_ADC2_ENABLE__ // begin of __HARDWARE_CONFIG__DMA_ADC2_ENABLE__
      //printf_s(7, "dma_cnt:%d,%0d,%0d", dma_adc2_finish_cnt / 1000000, dma_adc2_finish_cnt / 1000 % 1000, dma_adc2_finish_cnt % 1000);
      for (uint8_t i = 0;i < 1;i ++){
        printf_s(8 + i, "AD2_val %d:%dmV", i, (DMA_ADC2_RX_BUF[i] * 3300) >> 16);
      }
    #endif // end of __HARDWARE_CONFIG__DMA_ADC3_ENABLE__
    #if __HARDWARE_CONFIG__DMA_ADC3_ENABLE__ // begin of __HARDWARE_CONFIG__DMA_ADC3_ENABLE__
      //printf_s(9, "dma_cnt:%d,%0d,%0d", dma_adc3_finish_cnt / 1000000, dma_adc3_finish_cnt / 1000 % 1000, dma_adc3_finish_cnt % 1000);
      for (uint8_t i = 0;i < 1;i ++){
        printf_s(10 + i, "AD3_val %d:%dmV", i, (DMA_ADC3_RX_BUF[i] * 3300) >> 16);
      }
    #endif // end of __HARDWARE_CONFIG__DMA_ADC3_ENABLE__
    
    //printf_s(15, "timer12_call_cnt:%d", timer12_call_cnt);
}

//*******************************// end_c               //************************************//
#endif	// end of __HARDWARE_CONFIG__VISUALIZE_SHOW_ENABLE__
