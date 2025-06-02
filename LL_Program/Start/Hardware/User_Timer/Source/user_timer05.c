#include "__HARDWARE_CONFIG__.h"
#if __HARDWARE_CONFIG__USER_TIMER_ENABLE__ & __HARDWARE_CONFIG__USER_TIMER5_ENABLE__	// begin of __HARDWARE_CONFIG__USER_TIMER5_ENABLE__
//*******************************// include _h files    //************************************//
#include "user_timer05.h"
//*******************************// define parameters   //************************************//
//*******************************// parameters          //************************************//

uint32_t timer5_call_cnt = 0;

//*******************************// define function     //************************************//

//-----------------------------------------------------------------
// inline void timer5_config_init()
//-----------------------------------------------------------------
//
// ��������: timer5��ʱ�����ó�ʼ��
// ��ڲ���1: ��
// �� �� ֵ: ��
// ע������: ��
//
//-----------------------------------------------------------------
inline void timer5_config_init(){
	//? ��ʼ��ʱ��
	LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM5);

	//? �����ж�
	NVIC_SetPriority(TIM5_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(),4, 2));
    NVIC_EnableIRQ(TIM5_IRQn);

	//? ���ö�ʱ���ṹ�� 1000us
	LL_TIM_InitTypeDef TIM_InitStruct               = {0};
	                   TIM_InitStruct.Prescaler     = 240 - 1;
	                   TIM_InitStruct.CounterMode   = LL_TIM_COUNTERMODE_UP;      // Ԥ��Ƶ
	                   TIM_InitStruct.Autoreload    = 1000 - 1;                    // ����ģʽ�����ϼ���
	                   TIM_InitStruct.ClockDivision = LL_TIM_CLOCKDIVISION_DIV1;  // �Զ���װ��ֵ
	LL_TIM_Init(TIM5, &TIM_InitStruct);

	//? ��������
	LL_TIM_DisableARRPreload(TIM5);                                // �����Զ�װ��ģʽ
	LL_TIM_SetClockSource    (TIM5, LL_TIM_CLOCKSOURCE_INTERNAL);  // ����ʱ��Դ���ڲ�����
	LL_TIM_SetTriggerOutput  (TIM5, LL_TIM_TRGO_RESET);            // ��λ����
	LL_TIM_DisableMasterSlaveMode(TIM5);

  //? ��־λ
	#if __HARDWARE_CONFIG__TIMER5_INT_UPDATE_ENABLE__ // begin of __HARDWARE_CONFIG__TIMER5_INT_UPDATE_ENABLE__
		LL_TIM_ClearFlag_UPDATE(TIM5);  // ������ϼ��������־λ
		LL_TIM_EnableIT_UPDATE (TIM5);  // ʹ�ܶ�ʱ�����ϼ����ж�
  #endif // end of __HARDWARE_CONFIG__TIMER5_INT_UPDATE_ENABLE__
}
//-----------------------------------------------------------------
// inline void timer5_start()
//-----------------------------------------------------------------
//
// ��������: ������ʱ��5
// ��ڲ���1: ��
// �� �� ֵ: ��
// ע������: ��
//
//-----------------------------------------------------------------
inline void timer5_start(){
  if(__HARDWARE_CONFIG__TIMER5_INT_UPDATE_ENABLE__)
    LL_TIM_ClearFlag_UPDATE(TIM5);  // ������ϼ��������־λ
  LL_TIM_EnableCounter   (TIM5);  // ʹ�ܶ�ʱ����ʼ����
}
//-----------------------------------------------------------------
// inline void timer5_stop()
//-----------------------------------------------------------------
//
// ��������: �رն�ʱ��5
// ��ڲ���1: ��
// �� �� ֵ: ��
// ע������: ��
//
//-----------------------------------------------------------------
inline void timer5_stop(){
  if(__HARDWARE_CONFIG__TIMER5_INT_UPDATE_ENABLE__)
    LL_TIM_ClearFlag_UPDATE(TIM5);   // ������ϼ��������־λ
  LL_TIM_DisableCounter   (TIM5);  // �رն�ʱ������
}

//-----------------------------------------------------------------
// inline void TIM5_IRQHandler_Func(void)
//-----------------------------------------------------------------
//
// ��������: ��ʱ��5�жϷ�����
// ��ڲ���1: ��
// �� �� ֵ: ��
// ע������: ���˺������붨ʱ���жϷ�����TIM5_IRQHandler(void)��
//
//-----------------------------------------------------------------
inline void TIM5_IRQHandler_Func(void){
	if(LL_TIM_IsActiveFlag_UPDATE(TIM5) == SET){	//�ж϶�ʱ���Ƿ����
		LL_TIM_ClearFlag_UPDATE(TIM5);				//������ϼ��������־λ
		
		timer5_call_cnt ++;
	}
}



//*******************************// end_c               //************************************//
#endif	// end of __HARDWARE_CONFIG__USER_TIMER5_ENABLE__


#if 0 //// stm32h7xx_it.c�滻
/**
  * @brief This function handles TIM5 global interrupt.
  */
void TIM5_IRQHandler(void)
{
  /* USER CODE BEGIN TIM5_IRQn 0 */
  #if __HARDWARE_CONFIG__USER_TIMER_ENABLE__ & __HARDWARE_CONFIG__USER_TIMER5_ENABLE__ // begin of __HARDWARE_CONFIG__USER_TIMER5_ENABLE__
    //-----------------------------------------------------------------
    //-----------------------------------------------------------------
    //? TIM5_IRQHandler_Func
    //-----------------------------------------------------------------
    //
    // Interrupt Excute Function: Once TIM5->CNT reached the maximum counter value,
    //                             excute certain function.
    // Detected Case: TIM5 Up Overflow
    // Returned Value: excute certain function
    // Notice: None
    //
    //-----------------------------------------------------------------
    TIM5_IRQHandler_Func();
  #endif // end of __HARDWARE_CONFIG__USER_TIMER5_ENABLE__
  /* USER CODE END TIM5_IRQn 0 */
  /* USER CODE BEGIN TIM5_IRQn 1 */

  /* USER CODE END TIM5_IRQn 1 */
}
#endif
