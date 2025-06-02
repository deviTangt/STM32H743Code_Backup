#include "__HARDWARE_CONFIG__.h"
#if __HARDWARE_CONFIG__USER_TIMER_ENABLE__ & __HARDWARE_CONFIG__USER_TIMER15_ENABLE__	// begin of __HARDWARE_CONFIG__USER_TIMER15_ENABLE__
//*******************************// include _h files    //************************************//
#include "user_timer15.h"
//*******************************// define parameters   //************************************//
//*******************************// parameters          //************************************//

uint32_t timer15_call_cnt = 0;

//*******************************// define function     //************************************//

//-----------------------------------------------------------------
// inline void timer15_config_init()
//-----------------------------------------------------------------
//
// ��������: timer15��ʱ�����ó�ʼ��
// ��ڲ���1: ��
// �� �� ֵ: ��
// ע������: ������APB2�����ϣ���һ�㶨ʱ����ͬ
//
//-----------------------------------------------------------------
inline void timer15_config_init(){
	//? ��ʼ��ʱ��
	LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_TIM15);

	//? �����ж�
	NVIC_SetPriority(TIM15_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(),4, 2));
    NVIC_EnableIRQ(TIM15_IRQn);

	//? ���ö�ʱ���ṹ�� 1000us
	LL_TIM_InitTypeDef TIM_InitStruct               = {0};
	                   TIM_InitStruct.Prescaler     = 240 - 1;
	                   TIM_InitStruct.CounterMode   = LL_TIM_COUNTERMODE_UP;      // Ԥ��Ƶ
	                   TIM_InitStruct.Autoreload    = 1000 - 1;                    // ����ģʽ�����ϼ���
	                   TIM_InitStruct.ClockDivision = LL_TIM_CLOCKDIVISION_DIV1;  // �Զ���װ��ֵ
	LL_TIM_Init(TIM15, &TIM_InitStruct);

	//? ��������
	LL_TIM_DisableARRPreload(TIM15);                                // �����Զ�װ��ģʽ
	LL_TIM_SetClockSource    (TIM15, LL_TIM_CLOCKSOURCE_INTERNAL);  // ����ʱ��Դ���ڲ�����
	LL_TIM_SetTriggerOutput  (TIM15, LL_TIM_TRGO_RESET);            // ��λ����
	LL_TIM_DisableMasterSlaveMode(TIM15);

    //? ��־λ
	LL_TIM_ClearFlag_UPDATE(TIM15);  // ������ϼ��������־λ
    LL_TIM_EnableIT_UPDATE (TIM15);  // ʹ�ܶ�ʱ�����ϼ����ж�
}
//-----------------------------------------------------------------
// inline void timer15_start()
//-----------------------------------------------------------------
//
// ��������: ������ʱ��3
// ��ڲ���1: ��
// �� �� ֵ: ��
// ע������: ��
//
//-----------------------------------------------------------------
inline void timer15_start(){
    LL_TIM_ClearFlag_UPDATE(TIM15);  // ������ϼ��������־λ
    LL_TIM_EnableCounter   (TIM15);  // ʹ�ܶ�ʱ����ʼ����
}
//-----------------------------------------------------------------
// inline void timer15_stop()
//-----------------------------------------------------------------
//
// ��������: �رն�ʱ��3
// ��ڲ���1: ��
// �� �� ֵ: ��
// ע������: ��
//
//-----------------------------------------------------------------
inline void timer15_stop(){
    LL_TIM_ClearFlag_UPDATE(TIM15);   // ������ϼ��������־λ
    LL_TIM_DisableCounter   (TIM15);  // �رն�ʱ������
}

//-----------------------------------------------------------------
// inline void TIM15_IRQHandler_Func(void)
//-----------------------------------------------------------------
//
// ��������: ��ʱ��3�жϷ�����
// ��ڲ���1: ��
// �� �� ֵ: ��
// ע������: ���˺������붨ʱ���жϷ�����TIM15_IRQHandler(void)��
//
//-----------------------------------------------------------------
inline void TIM15_IRQHandler_Func(void){
	if(LL_TIM_IsActiveFlag_UPDATE(TIM15) == SET){	//�ж϶�ʱ���Ƿ����
		LL_TIM_ClearFlag_UPDATE(TIM15);				//������ϼ��������־λ
		
		timer15_call_cnt ++;
	}
}



//*******************************// end_c               //************************************//
#endif	// end of __HARDWARE_CONFIG__USER_TIMER15_ENABLE__


#if 0 //// stm32h7xx_it.c�滻
/**
  * @brief This function handles TIM15 global interrupt.
  */
void TIM15_IRQHandler(void)
{
  /* USER CODE BEGIN TIM15_IRQn 0 */
  #if __HARDWARE_CONFIG__USER_TIMER_ENABLE__ & __HARDWARE_CONFIG__USER_TIMER15_ENABLE__ // begin of __HARDWARE_CONFIG__USER_TIMER15_ENABLE__
    //-----------------------------------------------------------------
    //-----------------------------------------------------------------
    //? TIM15_IRQHandler_Func
    //-----------------------------------------------------------------
    //
    // Interrupt Excute Function: Once TIM15->CNT reached the maximum counter value,
    //                             excute certain function.
    // Detected Case: TIM15 Up Overflow
    // Returned Value: excute certain function
    // Notice: None
    //
    //-----------------------------------------------------------------
    TIM15_IRQHandler_Func();
  #endif // end of __HARDWARE_CONFIG__USER_TIMER15_ENABLE__
  /* USER CODE END TIM15_IRQn 0 */
  /* USER CODE BEGIN TIM15_IRQn 1 */

  /* USER CODE END TIM15_IRQn 1 */
}
#endif
