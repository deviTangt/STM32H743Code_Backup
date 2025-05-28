#include "__HARDWARE_CONFIG__.h"
#if __HARDWARE_CONFIG__CONFIG_INIT_ENABLE__	// begin of __HARDWARE_CONFIG__CONFIG_INIT_ENABLE__
//*******************************// include _h files    //************************************//

#include "config_init.h"
#include "pic.h"

//*******************************// define parameters   //************************************//
//*******************************// parameters          //************************************//
//*******************************// define function     //************************************//

//-----------------------------------------------------------------
// void config_init()
//-----------------------------------------------------------------
//
// Function Usage  : initialize various periph config
// Input Arugment 1: None
// Return Value    : None
// Something Notice: None
//
//-----------------------------------------------------------------
void config_init(){
    //? TJC USART HMI Initialized
    #if __HARDWARE_CONFIG__TJC_USART_ENABLE__ // begin of __HARDWARE_CONFIG__TJC_USART_ENABLE__
        TJC_USART_Config_Init();
    #endif // end of __HARDWARE_CONFIG__TJC_USART_ENABLE__  

    //? ADC Initialized
    #if __HARDWARE_CONFIG__DMA_ADC_ENABLE__ // begin of __HARDWARE_CONFIG__DMA_ADC_ENABLE__
        Samp_Adc_Init((uint32_t)&DMA_ADC_RX_BUF, ADC_Sequence_Channel_Num);
        #if 1   // 是否开始采样
            Start_Sample();
        #endif
    #endif // end of __HARDWARE_CONFIG__DMA_ADC_ENABLE__

    //? gpu temperature sensor adc config
    #if __HARDWARE_CONFIG__GPU_TEMP_ADC_ENABLE__ // begin of __HARDWARE_CONFIG__GPU_TEMP_ADC_ENABLE__
        gpu_temp_adc3_config_init();
    #endif // end of __HARDWARE_CONFIG__GPU_TEMP_ADC_ENABLE__
    
    //? TFT LCD Initialized
    #if __HARDWARE_CONFIG__TFTLCD_ENABLE__ // begin of __HARDWARE_CONFIG__TFTLCD_ENABLE__
        LCD_Init();
        LCD_Fill(0, 0, LCD_W, LCD_H, WHITE);
        LCD_ShowPicture(0, 0, 128, 134, gImage_HuaXiaoKe);
    #endif // end of __HARDWARE_CONFIG__TFTLCD_ENABLE__

    //? User Timer Initialized
    #if __HARDWARE_CONFIG__USER_TIMER_ENABLE__ // begin of __HARDWARE_CONFIG__USER_TIMER_ENABLE__
        //? User Timer 2
        #if __HARDWARE_CONFIG__USER_TIMER2_ENABLE__ // begin of __HARDWARE_CONFIG__USER_TIMER2_ENABLE__
            timer2_config_init();
            timer2_start();
        #endif // end of __HARDWARE_CONFIG__USER_TIMER2_ENABLE__

        //? User Timer 3
        #if __HARDWARE_CONFIG__USER_TIMER3_ENABLE__ // begin of __HARDWARE_CONFIG__USER_TIMER3_ENABLE__
            timer3_config_init();
            timer3_start();
        #endif // end of __HARDWARE_CONFIG__USER_TIMER3_ENABLE__
    #endif // end of __HARDWARE_CONFIG__USER_TIMER_ENABLE__
}

//*******************************// end_c               //************************************//
#endif	// end of __HARDWARE_CONFIG__CONFIG_INIT_ENABLE__
