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
// ע������: ��
//
//-----------------------------------------------------------------
inline void timer16_config_init(){
	//? ��ʼ��ʱ��
	LL_APB1_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_TIM16);

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
	LL_TIM_ClearFlag_UPDATE(TIM16);  // ������ϼ��������־λ
    LL_TIM_EnableIT_UPDATE (TIM16);  // ʹ�ܶ�ʱ�����ϼ����ж�
}
//-----------------------------------------------------------------
// inline void timer16_start()
//-----------------------------------------------------------------
//
// ��������: ������ʱ��3
// ��ڲ���1: ��
// �� �� ֵ: ��
// ע������: ��
//
//-----------------------------------------------------------------
inline void timer16_start(){
    LL_TIM_ClearFlag_UPDATE(TIM16);  // ������ϼ��������־λ
    LL_TIM_EnableCounter   (TIM16);  // ʹ�ܶ�ʱ����ʼ����
}
//-----------------------------------------------------------------
// inline void timer16_stop()
//-----------------------------------------------------------------
//
// ��������: �رն�ʱ��3
// ��ڲ���1: ��
// �� �� ֵ: ��
// ע������: ��
//
//-----------------------------------------------------------------
inline void timer16_stop(){
    LL_TIM_ClearFlag_UPDATE(TIM16);   // ������ϼ��������־λ
    LL_TIM_DisableCounter   (TIM16);  // �رն�ʱ������
}

//-----------------------------------------------------------------
// inline void TIM16_IRQHandler_Func(void)
//-----------------------------------------------------------------
//
// ��������: ��ʱ��3�жϷ�����
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
