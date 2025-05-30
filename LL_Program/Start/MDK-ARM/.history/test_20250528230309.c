  while (1){
    //*******************************// real time                   //************************************//
    // bspTick_mark_1_set();
    printf_s(20, "min:%3d sec:%02d.%03d us:%03d\r\n", bsp_min, bsp_sec % 60, bsp_ms % 1000, bsp_us % 1000);
    // bspTick_mark_2_set();
    // bspTick_mark_dif_show(14);

    //*******************************// while logic                 //************************************//
    /* USER CODE END WHILE */
    
    /* USER CODE BEGIN 3 */
    if (TIM2CH1_CAPTURE_STA == 3){
      printf_s(10, "timer3_call_cnt:%d", timer3_call_cnt);
      printf_s(11, "CAP_VAl[0]:%d", TIM2CH1_CAPTURE_VAl[0]);
      printf_s(12, "CAP_VAl[1]:%d", TIM2CH1_CAPTURE_VAl[1]);
      printf_s(13, "CAP_VAl[2]:%d", TIM2CH1_CAPTURE_VAl[2]);
      printf_s(14, "CAP_VAl[3]:%d", TIM2CH1_CAPTURE_VAl[3]);
      printf_s(15, "周期:%2d.%03ds %03dus", TIM2CH1_CAPTURE_Period / 1000000, TIM2CH1_CAPTURE_Period / 1000 % 1000, TIM2CH1_CAPTURE_Period % 1000);
      printf_s(16, "频率:%.3fHz", 1000000.0 / TIM2CH1_CAPTURE_Period);
      printf_s(17, "正占空比:%2d.%03d%%", TIM2CH1_CAPTURE_DutyPeriod * 100 / TIM2CH1_CAPTURE_Period, TIM2CH1_CAPTURE_DutyPeriod * 100000 / TIM2CH1_CAPTURE_Period % 1000);
      printf_s(18, "负占空比:%2d.%03d%%", (TIM2CH1_CAPTURE_Period - TIM2CH1_CAPTURE_DutyPeriod) * 100 / TIM2CH1_CAPTURE_Period, (TIM2CH1_CAPTURE_Period - TIM2CH1_CAPTURE_DutyPeriod) * 100000 / TIM2CH1_CAPTURE_Period % 1000);
    }

    if (RX_tick > Rx_tick_pre + 100){
        Rx_tick_pre = RX_tick;
        printf("Main Receive:%*s\r\n", DMA_RX_Length, DMA_RX_BUF);
        
        DMA_RX_Length = 0;
    }

    
    #if __HARDWARE_CONFIG__DMA_ADC_ENABLE__ // begin of __HARDWARE_CONFIG__DMA_ADC_ENABLE__
      printf_s(4, "dma_cnt:%d,%0d,%0d", dma_adc_finish_cnt / 1000000, dma_adc_finish_cnt / 1000 % 1000, dma_adc_finish_cnt % 1000);
      for (uint8_t i = 0;i < 2;i ++){
        printf_s(5 + i, "AD_val %d:%dmV", i, (DMA_ADC_RX_BUF[i] * 3300) >> 16);
      }
    #endif // end of __HARDWARE_CONFIG__DMA_ADC_ENABLE__
    

    //*******************************// delay logic                 //************************************//
    delay_ms(10);                                       
                                                                                                                                                                                                                                           
  }