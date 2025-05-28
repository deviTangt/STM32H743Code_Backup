#include "__HARDWARE_CONFIG__.h"
#if __HARDWARE_CONFIG__USER_TIMER_ENABLE__	// begin of __HARDWARE_CONFIG__USER_TIMER_ENABLE__
#ifndef __USER_TIMER_H__	// begin of __USER_TIMER_H__
#define __USER_TIMER_H__
//*******************************// include extern .h files //************************************//
#include "main.h"
#include "dma_adc.h"
//*******************************// define statement        //************************************//
//*******************************// extern parameters       //************************************//

extern uint32_t timer2_call_cnt;
extern uint32_t timer3_call_cnt;

//*******************************// define structure unity  //************************************//
//*******************************// define parameters       //************************************//
//*******************************// extern function         //************************************//

//? 通用定时器Timer2(32位) 
extern inline void timer2_config_init();
extern inline void timer2_start();
extern inline void timer2_stop();
extern inline void TIM2_IRQHandler_Func(void);

//? 通用定时器Timer3(16位)
extern inline void timer3_config_init();
extern inline void timer3_start();
extern inline void timer3_stop();
extern inline void TIM3_IRQHandler_Func(void);

//*******************************// end_h                   //************************************//
#endif	// end of __USER_TIMER_H__
#endif	// end of __HARDWARE_CONFIG__USER_TIMER_ENABLE__
