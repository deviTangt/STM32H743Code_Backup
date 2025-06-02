#include "__HARDWARE_CONFIG__.h"
#if __HARDWARE_CONFIG__USER_TIMER_ENABLE__ & __HARDWARE_CONFIG__USER_TIMER16_ENABLE__	// begin of __HARDWARE_CONFIG__USER_TIMER16_ENABLE__
//*******************************// include _h files    //************************************//
#include "user_timer16.h"
//*******************************// define parameters   //************************************//
//*******************************// parameters          //************************************//

uint32_t timer16_call_cnt = 0;

//*******************************// define function     //************************************//

//-----------------------------------------------------------------
// inline void timer16_config_init()
//-----------------------------------------------------------------
//
// ��������: timer16��ʱ�����ó�ʼ��
// ��ڲ���1: ��
// �� �� ֵ: ��
// ע������: ������APB2�����ϣ���һ�㶨ʱ����ͬ
//
//-----------------------------------------------------------------
inline void timer16_config_init(){
	//? ��ʼ��ʱ��
	LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_TIM16);

	//? �����ж�
	NVIC_SetPriority(TIM16_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(),4, 2));
    NVIC_EnableIRQ(TIM16_IRQn);

	//? ���ö�ʱ���ṹ�� 1000us
	LL_TIM_InitTypeDef TIM_InitStruct               = {0};
	                   TIM_InitStruct.Prescaler     = 240 - 1;
	                   TIM_InitStruct.CounterMode   = LL_TIM_COUNTERMODE_UP;      // Ԥ��Ƶ
	                   TIM_InitStruct.Autoreload    = 1000 - 1;                    // ����ģʽ�����ϼ���
	                   TIM_InitStruct.ClockDivision = LL_TIM_CLOCKDIVISION_DIV1;  // �Զ���װ��ֵ
	LL_TIM_Init(TIM16, &TIM_InitStruct);

	//? ��������
	LL_TIM_DisableARRPreload(TIM16);                                // �����Զ�װ��ģʽ
	LL_TIM_SetClockSource    (TIM16, LL_TIM_CLOCKSOURCE_INTERNAL);  // ����ʱ��Դ���ڲ�����
	LL_TIM_SetTriggerOutput  (TIM16, LL_TIM_TRGO_RESET);            // ��λ����
	LL_TIM_DisableMasterSlaveMode(TIM16);

  //? ��־λ
	#if __HARDWARE_CONFIG__TIMER16_INT_UPDATE_ENABLE__ // begin of __HARDWARE_CONFIG__TIMER16_INT_UPDATE_ENABLE__
		LL_TIM_ClearFlag_UPDATE(TIM16);  // ������ϼ��������־λ
		LL_TIM_EnableIT_UPDATE (TIM16);  // ʹ�ܶ�ʱ�����ϼ����ж�
  #endif // end of __HARDWARE_CONFIG__TIMER16_INT_UPDATE_ENABLE__
}
//-----------------------------------------------------------------
// inline void timer16_start()
//-----------------------------------------------------------------
//
// ��������: ������ʱ��16
// ��ڲ���1: ��
// �� �� ֵ: ��
// ע������: ��
//
//-----------------------------------------------------------------
inline void timer16_start(){
  if(__HARDWARE_CONFIG__TIMER16_INT_UPDATE_ENABLE__)
    LL_TIM_ClearFlag_UPDATE(TIM16);  // ������ϼ��������־λ
  LL_TIM_EnableCounter   (TIM16);  // ʹ�ܶ�ʱ����ʼ����
}
//-----------------------------------------------------------------
// inline void timer16_stop()
//-----------------------------------------------------------------
//
// ��������: �رն�ʱ��16
// ��ڲ���1: ��
// �� �� ֵ: ��
// ע������: ��
//
//-----------------------------------------------------------------
inline void timer16_stop(){
  if(__HARDWARE_CONFIG__TIMER16_INT_UPDATE_ENABLE__)
    LL_TIM_ClearFlag_UPDATE(TIM16);   // ������ϼ��������־λ
  LL_TIM_DisableCounter   (TIM16);  // �رն�ʱ������
}

//-----------------------------------------------------------------
// inline void TIM16_IRQHandler_Func(void)
//-----------------------------------------------------------------
//
// ��������: ��ʱ��16�жϷ�����
// ��ڲ���1: ��
// �� �� ֵ: ��
// ע������: ���˺������붨ʱ���жϷ�����TIM16_IRQHandler(void)��
//
//-----------------------------------------------------------------
inline void TIM16_IRQHandler_Func(void){
	if(LL_TIM_IsActiveFlag_UPDATE(TIM16) == SET){	//�ж϶�ʱ���Ƿ����
		LL_TIM_ClearFlag_UPDATE(TIM16);				//������ϼ��������־λ
		
		timer16_call_cnt ++;
	}
}



//*******************************// end_c               //************************************//
#endif	// end of __HARDWARE_CONFIG__USER_TIMER16_ENABLE__


#if 0 //// stm32h7xx_it.c�滻
/**
  * @brief This function handles TIM16 global interrupt.
  */
void TIM16_IRQHandler(void)
{
  /* USER CODE BEGIN TIM16_IRQn 0 */
  #if __HARDWARE_CONFIG__USER_TIMER_ENABLE__ & __HARDWARE_CONFIG__USER_TIMER16_ENABLE__ // begin of __HARDWARE_CONFIG__USER_TIMER16_ENABLE__
    //-----------------------------------------------------------------
    //-----------------------------------------------------------------
    //? TIM16_IRQHandler_Func
    //-----------------------------------------------------------------
    //
    // Interrupt Excute Function: Once TIM16->CNT reached the maximum counter value,
    //                             excute certain function.
    // Detected Case: TIM16 Up Overflow
    // Returned Value: excute certain function
    // Notice: None
    //
    //-----------------------------------------------------------------
    TIM16_IRQHandler_Func();
  #endif // end of __HARDWARE_CONFIG__USER_TIMER16_ENABLE__
  /* USER CODE END TIM16_IRQn 0 */
  /* USER CODE BEGIN TIM16_IRQn 1 */

  /* USER CODE END TIM16_IRQn 1 */
}
#endif

