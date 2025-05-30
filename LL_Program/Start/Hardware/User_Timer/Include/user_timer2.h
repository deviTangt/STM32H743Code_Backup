#include "__HARDWARE_CONFIG__.h"
#if __HARDWARE_CONFIG__USER_TIMER_ENABLE__ & __HARDWARE_CONFIG__USER_TIMER2_ENABLE__ // begin of __HARDWARE_CONFIG__USER_TIMER2_ENABLE__
#ifndef __USER_TIMER2_H__	// begin of __USER_TIMER2_H__
#define __USER_TIMER2_H__
//*******************************// include extern .h files //************************************//
#include "main.h"
#include "dma_adc1.h"
//*******************************// define statement        //************************************//

#define TIM2CH1_CAPTURE_RECOVERY_TIME       10000

//*******************************// extern parameters       //************************************//

extern uint32_t timer2_call_cnt;

extern uint8_t TIM2CH1_CAPTURE_STA;
extern uint32_t TIM2CH1_CAPTURE_VAl[4];

extern uint32_t TIM2CH1_CAPTURE_Time, TIM2CH1_CAPTURE_Time_pre;

//*******************************// define structure unity  //************************************//
//*******************************// define parameters       //************************************//

#define TIM2CH1_CAPTURE_Period          (TIM2CH1_CAPTURE_VAl[2] - TIM2CH1_CAPTURE_VAl[0])
#define TIM2CH1_CAPTURE_DutyPeriod      (TIM2CH1_CAPTURE_VAl[1] - TIM2CH1_CAPTURE_VAl[0])

//*******************************// extern function         //************************************//

//? 通用定时器Timer2(32位) 
extern inline void timer2_config_init();
extern inline void timer2_start();
extern inline void timer2_stop();

//? 中断服务函数
extern inline void TIM2_IRQHandler_Func(void);

//*******************************// end_h                   //************************************//
#endif	// end of __USER_TIMER2_H__
#endif	// end of __HARDWARE_CONFIG__USER_TIMER2_ENABLE__
