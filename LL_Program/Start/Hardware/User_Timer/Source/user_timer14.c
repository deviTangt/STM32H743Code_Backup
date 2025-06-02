#include "__HARDWARE_CONFIG__.h"
#if __HARDWARE_CONFIG__USER_TIMER_ENABLE__ & __HARDWARE_CONFIG__USER_TIMER14_ENABLE__	// begin of __HARDWARE_CONFIG__USER_TIMER14_ENABLE__
//*******************************// include _h files    //************************************//
#include "user_timer14.h"
//*******************************// define parameters   //************************************//
//*******************************// parameters          //************************************//

uint32_t timer14_call_cnt = 0;

//*******************************// define function     //************************************//

//-----------------------------------------------------------------
// inline void timer14_config_init()
//-----------------------------------------------------------------
//
// ��������: timer14��ʱ�����ó�ʼ��
// ��ڲ���1: ��
// �� �� ֵ: ��
// ע������: ��
//
//-----------------------------------------------------------------
inline void timer14_config_init(){
	//? ��ʼ��ʱ��
	LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM14);

	//? �����ж�
	NVIC_SetPriority(TIM8_TRG_COM_TIM14_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(),4, 2));
    NVIC_EnableIRQ(TIM8_TRG_COM_TIM14_IRQn);

	//? ���ö�ʱ���ṹ�� 1000us
	LL_TIM_InitTypeDef TIM_InitStruct               = {0};
	                   TIM_InitStruct.Prescaler     = 240 - 1;
	                   TIM_InitStruct.CounterMode   = LL_TIM_COUNTERMODE_UP;      // Ԥ��Ƶ
	                   TIM_InitStruct.Autoreload    = 1000 - 1;                    // ����ģʽ�����ϼ���
	                   TIM_InitStruct.ClockDivision = LL_TIM_CLOCKDIVISION_DIV1;  // �Զ���װ��ֵ
	LL_TIM_Init(TIM14, &TIM_InitStruct);

	//? ��������
	LL_TIM_DisableARRPreload(TIM14);                                // �����Զ�װ��ģʽ
	LL_TIM_SetClockSource    (TIM14, LL_TIM_CLOCKSOURCE_INTERNAL);  // ����ʱ��Դ���ڲ�����
	LL_TIM_SetTriggerOutput  (TIM14, LL_TIM_TRGO_RESET);            // ��λ����
	LL_TIM_DisableMasterSlaveMode(TIM14);

  //? ��־λ
	#if __HARDWARE_CONFIG__TIMER14_INT_UPDATE_ENABLE__ // begin of __HARDWARE_CONFIG__TIMER14_INT_UPDATE_ENABLE__
		LL_TIM_ClearFlag_UPDATE(TIM14);  // ������ϼ��������־λ
		LL_TIM_EnableIT_UPDATE (TIM14);  // ʹ�ܶ�ʱ�����ϼ����ж�
  #endif // end of __HARDWARE_CONFIG__TIMER14_INT_UPDATE_ENABLE__
}
//-----------------------------------------------------------------
// inline void timer14_start()
//-----------------------------------------------------------------
//
// ��������: ������ʱ��14
// ��ڲ���1: ��
// �� �� ֵ: ��
// ע������: ��
//
//-----------------------------------------------------------------
inline void timer14_start(){
  if(__HARDWARE_CONFIG__TIMER14_INT_UPDATE_ENABLE__)
    LL_TIM_ClearFlag_UPDATE(TIM14);  // ������ϼ��������־λ
  LL_TIM_EnableCounter   (TIM14);  // ʹ�ܶ�ʱ����ʼ����
}
//-----------------------------------------------------------------
// inline void timer14_stop()
//-----------------------------------------------------------------
//
// ��������: �رն�ʱ��14
// ��ڲ���1: ��
// �� �� ֵ: ��
// ע������: ��
//
//-----------------------------------------------------------------
inline void timer14_stop(){
  if(__HARDWARE_CONFIG__TIMER14_INT_UPDATE_ENABLE__)
    LL_TIM_ClearFlag_UPDATE(TIM14);   // ������ϼ��������־λ
  LL_TIM_DisableCounter   (TIM14);  // �رն�ʱ������
}

//-----------------------------------------------------------------
// inline void TIM14_IRQHandler_Func(void)
//-----------------------------------------------------------------
//
// ��������: ��ʱ��14�жϷ�����
// ��ڲ���1: ��
// �� �� ֵ: ��
// ע������: ���˺������붨ʱ���жϷ�����TIM14_IRQHandler(void)��
//
//-----------------------------------------------------------------
inline void TIM14_IRQHandler_Func(void){
	if(LL_TIM_IsActiveFlag_UPDATE(TIM14) == SET){	//�ж϶�ʱ���Ƿ����
		LL_TIM_ClearFlag_UPDATE(TIM14);				//������ϼ��������־λ
		
		timer14_call_cnt ++;
	}
}



//*******************************// end_c               //************************************//
#endif	// end of __HARDWARE_CONFIG__USER_TIMER14_ENABLE__


#if 0 //// stm32h7xx_it.c�滻
/**
  * @brief This function handles TIM8 trigger and commutation interrupts and TIM14 global interrupt.
  */
void TIM8_TRG_COM_TIM14_IRQHandler(void)
{
  /* USER CODE BEGIN TIM8_TRG_COM_TIM14_IRQn 0 */
  #if __HARDWARE_CONFIG__USER_TIMER_ENABLE__ & __HARDWARE_CONFIG__USER_TIMER14_ENABLE__ // begin of __HARDWARE_CONFIG__USER_TIMER14_ENABLE__
    //-----------------------------------------------------------------
    //-----------------------------------------------------------------
    //? TIM14_IRQHandler_Func
    //-----------------------------------------------------------------
    //
    // Interrupt Excute Function: Once TIM14->CNT reached the maximum counter value,
    //                             excute certain function.
    // Detected Case: TIM14 Up Overflow
    // Returned Value: excute certain function
    // Notice: None
    //
    //-----------------------------------------------------------------
    TIM14_IRQHandler_Func();
  #endif // end of __HARDWARE_CONFIG__USER_TIMER14_ENABLE__
  /* USER CODE END TIM8_TRG_COM_TIM14_IRQn 0 */
  /* USER CODE BEGIN TIM8_TRG_COM_TIM14_IRQn 1 */

  /* USER CODE END TIM8_TRG_COM_TIM14_IRQn 1 */
}
#endif
