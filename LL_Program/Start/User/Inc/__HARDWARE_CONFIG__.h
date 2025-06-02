#ifndef __HARDWARE_CONFIG_H__ // begin of __HARDWARE_CONFIG_H__
#define __HARDWARE_CONFIG_H__
//*******************************// include extern .h files //************************************//
//*******************************// define statement        //************************************//

#define __HARDWARE_CONFIG__BSP_TIMER_ENABLE__           1       //! 启用板级支持包基本定时器tim7

#define __HARDWARE_CONFIG__CONFIG_INIT_ENABLE__         1       //! 启用config_init.h

#define __HARDWARE_CONFIG__VISUALIZE_SHOW_ENABLE__      1       //? 启用visualize_show.h

#define __HARDWARE_CONFIG__LED_ENABLE__                 1       // 启用LED.h
#define __HARDWARE_CONFIG__KEY_ENABLE__                 1       // 启用KEY.h 

#define __HARDWARE_CONFIG__TJC_USART_ENABLE__           1       //! 启用TJC_USART.h
    #define __HARDWARE_CONFIG__TJC_PAGE_CLEAR_ENABLE__      1       // 启用TJC_USART初始化页面刷新功能
        #define __HARDWARE_CONFIG__TJC_PAGE_JUMP_ENABLE__       1       // 启用TJC_USART初始化页面跳转功能
    #define __HARDWARE_CONFIG__TJC_FPUTC_ENABLE__           0       // 启用TJC_USART.h重定向fputc功能
    #define __HARDWARE_CONFIG__TJC_printf_sn_ENABLE__       1       //? 启用TJC_USART.h重定义printf_s和printf_n功能
    #define __HARDWARE_CONFIG__TJC_printf_ENABLE__          1       //? 启用TJC_USART.h重定义printf功能
    #define __HARDWARE_CONFIG__TJC_RX_ENABLE__              0       // 启用TJC_USART接收中断
    #define __HARDWARE_CONFIG__TJC_DMA_ENABLE__             1       //? 启用TJC_USART DMA模式

#define __HARDWARE_CONFIG__TFTLCD_ENABLE__              0       // 启用TFTLCD.h、TFTLCD_Init.h

#define __HARDWARE_CONFIG__GPU_TEMP_ADC_ENABLE__        0       // 启用gpu_temp_adc.h

#define __HARDWARE_CONFIG__DMA_ADC1_ENABLE__            1       // 启用dma_adc1.h
    #define __HARDWARE_CONFIG__SAMPLE_ADC1_DMA_ENABLE__      1       // 启用dma传输ADC1采样
    #define __HARDWARE_CONFIG__SAMPLE_ADC1_DMA_TC_ENABLE__   1       // 启用dma传输ADC1发送中断
#define __HARDWARE_CONFIG__DMA_ADC2_ENABLE__            1       // 启用dma_adc2.h
    #define __HARDWARE_CONFIG__SAMPLE_ADC2_DMA_ENABLE__      1       // 启用dma传输ADC2采样
    #define __HARDWARE_CONFIG__SAMPLE_ADC2_DMA_TC_ENABLE__   0       // 启用dma传输ADC2发送中断
#define __HARDWARE_CONFIG__DMA_ADC3_ENABLE__            1       // 启用dma_adc3.h
    #define __HARDWARE_CONFIG__SAMPLE_ADC3_DMA_ENABLE__      1       // 启用dma传输ADC3采样
    #define __HARDWARE_CONFIG__SAMPLE_ADC3_DMA_TC_ENABLE__   0       // 启用dma传输ADC3发送中断

#define __HARDWARE_CONFIG__AD9959_ENABLE__              0       // 启用ad9959.h    

#define __HARDWARE_CONFIG__USER_TIMER_ENABLE__          1       // 启用user_timer.h    
    #define __HARDWARE_CONFIG__USER_TIMER1_ENABLE__          0       // 启用timer1.h    //// 高级控制定时器Timer1(16位) 
    #define __HARDWARE_CONFIG__USER_TIMER2_ENABLE__          1       // 启用timer2.h    //? 通用定时器Timer2(32位) 
    #define __HARDWARE_CONFIG__USER_TIMER3_ENABLE__          1       // 启用timer3.h    //? 通用定时器Timer3(16位)
    #define __HARDWARE_CONFIG__USER_TIMER4_ENABLE__          0       // 启用timer4.h    //? 通用定时器Timer4(16位)
    #define __HARDWARE_CONFIG__USER_TIMER5_ENABLE__          0       // 启用timer5.h    //? 通用定时器Timer5(32位)
    #define __HARDWARE_CONFIG__USER_TIMER6_ENABLE__          0       // 启用timer6.h    //? 基本定时器Timer6(16位)
    #define __HARDWARE_CONFIG__USER_TIMER7_ENABLE__          0       // 启用timer7.h    //? 基本定时器Timer7(16位)  
    #define __HARDWARE_CONFIG__USER_TIMER8_ENABLE__          0       // 启用timer8.h    //// 高级控制定时器Timer8(16位)
    #define __HARDWARE_CONFIG__USER_TIMER12_ENABLE__         0       // 启用timer12.h   //? 基本定时器Timer12(16位)
    #define __HARDWARE_CONFIG__USER_TIMER13_ENABLE__         0       // 启用timer13.h   //? 基本定时器Timer13(16位)
    //define __HARDWARE_CONFIG__USER_TIMER14_ENABLE__        0       // 启用timer14.h   //! 基本定时器Timer14(16位) //! bsp_timer占用
    //define __HARDWARE_CONFIG__USER_TIMER15_ENABLE__        0       // 启用timer15.h   //! 基本定时器Timer15(16位) //! dma_adc1占用
    #define __HARDWARE_CONFIG__USER_TIMER16_ENABLE__         0       // 启用timer16.h   //? 基本定时器Timer16(16位)
    #define __HARDWARE_CONFIG__USER_TIMER17_ENABLE__         0       // 启用timer17.h   //? 基本定时器Timer17(16位)

//*******************************// extern parameters       //************************************//
//*******************************// define structure unity  //************************************//
//*******************************// define parameters       //************************************//
//*******************************// extern function         //************************************//
//*******************************// end_h                   //************************************//
#endif // end of __HARDWARE_CONFIG_H__
