#include "__HARDWARE_CONFIG__.h"
#if __HARDWARE_CONFIG__USER_TIMER_ENABLE__ & __HARDWARE_CONFIG__USER_TIMER4_ENABLE__	// begin of __HARDWARE_CONFIG__USER_TIMER4_ENABLE__
//*******************************// include _h files    //************************************//
#include "user_timer04.h"
//*******************************// define parameters   //************************************//
//*******************************// parameters          //************************************//

uint32_t timer4_call_cnt = 0;

//*******************************// define function     //************************************//

//-----------------------------------------------------------------
// inline void timer4_config_init()
//-----------------------------------------------------------------
//
// 函数功能: timer4定时器配置初始化
// 入口参数1: 无
// 返 回 值: 无
// 注意事项: 无
//
//-----------------------------------------------------------------
inline void timer4_config_init(){
	//? 初始化时钟
	LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM4);

	//? 配置中断
	NVIC_SetPriority(TIM4_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(),4, 2));
    NVIC_EnableIRQ(TIM4_IRQn);

	//? 配置定时器结构体 1000us
	LL_TIM_InitTypeDef TIM_InitStruct               = {0};
	                   TIM_InitStruct.Prescaler     = 240 - 1;
	                   TIM_InitStruct.CounterMode   = LL_TIM_COUNTERMODE_UP;      // 预分频
	                   TIM_InitStruct.Autoreload    = 1000 - 1;                    // 计数模式：向上计数
	                   TIM_InitStruct.ClockDivision = LL_TIM_CLOCKDIVISION_DIV1;  // 自动重装载值
	LL_TIM_Init(TIM4, &TIM_InitStruct);

	//? 其他配置
	LL_TIM_DisableARRPreload(TIM4);                                // 启动自动装载模式
	LL_TIM_SetClockSource    (TIM4, LL_TIM_CLOCKSOURCE_INTERNAL);  // 设置时钟源：内部晶振
	LL_TIM_SetTriggerOutput  (TIM4, LL_TIM_TRGO_RESET);            // 复位更新
	LL_TIM_DisableMasterSlaveMode(TIM4);

    //? 标志位
	LL_TIM_ClearFlag_UPDATE(TIM4);  // 清除向上计数溢出标志位
  LL_TIM_EnableIT_UPDATE (TIM4);  // 使能定时器向上计数中断
}
//-----------------------------------------------------------------
// inline void timer4_start()
//-----------------------------------------------------------------
//
// 函数功能: 开启定时器3
// 入口参数1: 无
// 返 回 值: 无
// 注意事项: 无
//
//-----------------------------------------------------------------
inline void timer4_start(){
    LL_TIM_ClearFlag_UPDATE(TIM4);  // 清除向上计数溢出标志位
    LL_TIM_EnableCounter   (TIM4);  // 使能定时器开始计数
}
//-----------------------------------------------------------------
// inline void timer4_stop()
//-----------------------------------------------------------------
//
// 函数功能: 关闭定时器3
// 入口参数1: 无
// 返 回 值: 无
// 注意事项: 无
//
//-----------------------------------------------------------------
inline void timer4_stop(){
    LL_TIM_ClearFlag_UPDATE(TIM4);   // 清除向上计数溢出标志位
    LL_TIM_DisableCounter   (TIM4);  // 关闭定时器计数
}

//-----------------------------------------------------------------
// inline void TIM4_IRQHandler_Func(void)
//-----------------------------------------------------------------
//
// 函数功能: 定时器3中断服务函数
// 入口参数1: 无
// 返 回 值: 无
// 注意事项: 将此函数加入定时器中断服务函数TIM4_IRQHandler(void)中
//
//-----------------------------------------------------------------
inline void TIM4_IRQHandler_Func(void){
	if(LL_TIM_IsActiveFlag_UPDATE(TIM4) == SET){	//判断定时器是否溢出
		LL_TIM_ClearFlag_UPDATE(TIM4);				//清除向上计数溢出标志位
		
		timer4_call_cnt ++;
	}
}



//*******************************// end_c               //************************************//
#endif	// end of __HARDWARE_CONFIG__USER_TIMER4_ENABLE__


#if 0 //// stm32h7xx_it.c替换
/**
  * @brief This function handles TIM4 global interrupt.
  */
void TIM4_IRQHandler(void)
{
  /* USER CODE BEGIN TIM4_IRQn 0 */
  #if __HARDWARE_CONFIG__USER_TIMER_ENABLE__ & __HARDWARE_CONFIG__USER_TIMER4_ENABLE__ // begin of __HARDWARE_CONFIG__USER_TIMER4_ENABLE__
    //-----------------------------------------------------------------
    //-----------------------------------------------------------------
    //? TIM4_IRQHandler_Func
    //-----------------------------------------------------------------
    //
    // Interrupt Excute Function: Once TIM4->CNT reached the maximum counter value,
    //                             excute certain function.
    // Detected Case: TIM4 Up Overflow
    // Returned Value: excute certain function
    // Notice: None
    //
    //-----------------------------------------------------------------
    TIM4_IRQHandler_Func();
  #endif // end of __HARDWARE_CONFIG__USER_TIMER4_ENABLE__
  /* USER CODE END TIM4_IRQn 0 */
  /* USER CODE BEGIN TIM4_IRQn 1 */

  /* USER CODE END TIM4_IRQn 1 */
}
#endif
