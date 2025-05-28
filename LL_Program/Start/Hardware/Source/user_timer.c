#include "__HARDWARE_CONFIG__.h"
#if __HARDWARE_CONFIG__USER_TIMER_ENABLE__	// begin of __HARDWARE_CONFIG__USER_TIMER_ENABLE__
//*******************************// include _h files    //************************************//
#include "user_timer.h"
//*******************************// define parameters   //************************************//
//*******************************// parameters          //************************************//

uint32_t timer2_call_cnt = 0;
uint32_t timer3_call_cnt = 0;

//*******************************// define function     //************************************//

//-----------------------------------------------------------------
// inline void timer2_config_init()
//-----------------------------------------------------------------
//
// ��������: timer2��ʱ�����ó�ʼ��
// ��ڲ���1: ��
// �� �� ֵ: ��
// ע������: ��
//
//-----------------------------------------------------------------
inline void timer2_config_init(){
	//? ��ʼ��ʱ��
	LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM2);

	//? �����ж�
	NVIC_SetPriority(TIM2_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(),4, 2));
    NVIC_EnableIRQ(TIM2_IRQn);

	//? ���ö�ʱ���ṹ�� 5ms
	LL_TIM_InitTypeDef TIM_InitStruct               = {0};
	                   TIM_InitStruct.Prescaler     = 240 - 1;
	                   TIM_InitStruct.CounterMode   = LL_TIM_COUNTERMODE_UP;      // Ԥ��Ƶ
	                   TIM_InitStruct.Autoreload    = 5000 - 1;                    // ����ģʽ�����ϼ���
	                   TIM_InitStruct.ClockDivision = LL_TIM_CLOCKDIVISION_DIV1;  // �Զ���װ��ֵ
	LL_TIM_Init(TIM2, &TIM_InitStruct);

	//? ��������
	LL_TIM_DisableARRPreload(TIM2);                                // �����Զ�װ��ģʽ
	LL_TIM_SetClockSource    (TIM2, LL_TIM_CLOCKSOURCE_INTERNAL);  // ����ʱ��Դ���ڲ�����
	LL_TIM_SetTriggerOutput  (TIM2, LL_TIM_TRGO_RESET);            // ��λ����
	LL_TIM_DisableMasterSlaveMode(TIM2);

    //? ��־λ
	LL_TIM_ClearFlag_UPDATE(TIM2);  // ������ϼ��������־λ
    LL_TIM_EnableIT_UPDATE (TIM2);  // ʹ�ܶ�ʱ�����ϼ����ж�
}
//-----------------------------------------------------------------
// inline void timer2_start()
//-----------------------------------------------------------------
//
// ��������: ������ʱ��3
// ��ڲ���1: ��
// �� �� ֵ: ��
// ע������: ��
//
//-----------------------------------------------------------------
inline void timer2_start(){
    LL_TIM_ClearFlag_UPDATE(TIM2);  // ������ϼ��������־λ
    LL_TIM_EnableCounter   (TIM2);  // ʹ�ܶ�ʱ����ʼ����
}
//-----------------------------------------------------------------
// inline void timer2_stop()
//-----------------------------------------------------------------
//
// ��������: �رն�ʱ��3
// ��ڲ���1: ��
// �� �� ֵ: ��
// ע������: ��
//
//-----------------------------------------------------------------
inline void timer2_stop(){
    LL_TIM_ClearFlag_UPDATE(TIM2);   // ������ϼ��������־λ
    LL_TIM_DisableCounter   (TIM2);  // �رն�ʱ������
}
//-----------------------------------------------------------------
// inline void TIM2_IRQHandler_Func(void)
//-----------------------------------------------------------------
//
// ��������: ��ʱ��3�жϷ�����
// ��ڲ���1: ��
// �� �� ֵ: ��
// ע������: ���˺������붨ʱ���жϷ�����TIM2_IRQHandler(void)��
//
//-----------------------------------------------------------------
inline void TIM2_IRQHandler_Func(void)
{
	if(LL_TIM_IsActiveFlag_UPDATE(TIM2) == SET){	//�ж϶�ʱ���Ƿ����
		LL_TIM_ClearFlag_UPDATE(TIM2);				//������ϼ��������־λ
		
        timer2_call_cnt ++;
	}
}

//-----------------------------------------------------------------
// inline void timer3_config_init()
//-----------------------------------------------------------------
//
// ��������: timer3��ʱ�����ó�ʼ��
// ��ڲ���1: ��
// �� �� ֵ: ��
// ע������: ��
//
//-----------------------------------------------------------------
inline void timer3_config_init(){
	//? ��ʼ��ʱ��
	LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM3);

	//? �����ж�
	NVIC_SetPriority(TIM3_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(),4, 2));
    NVIC_EnableIRQ(TIM3_IRQn);

	//? ���ö�ʱ���ṹ�� 1000us
	LL_TIM_InitTypeDef TIM_InitStruct               = {0};
	                   TIM_InitStruct.Prescaler     = 240 - 1;
	                   TIM_InitStruct.CounterMode   = LL_TIM_COUNTERMODE_UP;      // Ԥ��Ƶ
	                   TIM_InitStruct.Autoreload    = 1000 - 1;                    // ����ģʽ�����ϼ���
	                   TIM_InitStruct.ClockDivision = LL_TIM_CLOCKDIVISION_DIV1;  // �Զ���װ��ֵ
	LL_TIM_Init(TIM3, &TIM_InitStruct);

	//? ��������
	LL_TIM_DisableARRPreload(TIM3);                                // �����Զ�װ��ģʽ
	LL_TIM_SetClockSource    (TIM3, LL_TIM_CLOCKSOURCE_INTERNAL);  // ����ʱ��Դ���ڲ�����
	LL_TIM_SetTriggerOutput  (TIM3, LL_TIM_TRGO_RESET);            // ��λ����
	LL_TIM_DisableMasterSlaveMode(TIM3);

    //? ��־λ
	LL_TIM_ClearFlag_UPDATE(TIM3);  // ������ϼ��������־λ
    LL_TIM_EnableIT_UPDATE (TIM3);  // ʹ�ܶ�ʱ�����ϼ����ж�
}
//-----------------------------------------------------------------
// inline void timer3_start()
//-----------------------------------------------------------------
//
// ��������: ������ʱ��3
// ��ڲ���1: ��
// �� �� ֵ: ��
// ע������: ��
//
//-----------------------------------------------------------------
inline void timer3_start(){
    LL_TIM_ClearFlag_UPDATE(TIM3);  // ������ϼ��������־λ
    LL_TIM_EnableCounter   (TIM3);  // ʹ�ܶ�ʱ����ʼ����
}
//-----------------------------------------------------------------
// inline void timer3_stop()
//-----------------------------------------------------------------
//
// ��������: �رն�ʱ��3
// ��ڲ���1: ��
// �� �� ֵ: ��
// ע������: ��
//
//-----------------------------------------------------------------
inline void timer3_stop(){
    LL_TIM_ClearFlag_UPDATE(TIM3);   // ������ϼ��������־λ
    LL_TIM_DisableCounter   (TIM3);  // �رն�ʱ������
}
//-----------------------------------------------------------------
// inline void TIM3_IRQHandler_Func(void)
//-----------------------------------------------------------------
//
// ��������: ��ʱ��3�жϷ�����
// ��ڲ���1: ��
// �� �� ֵ: ��
// ע������: ���˺������붨ʱ���жϷ�����TIM3_IRQHandler(void)��
//
//-----------------------------------------------------------------
inline void TIM3_IRQHandler_Func(void)
{
	if(LL_TIM_IsActiveFlag_UPDATE(TIM3) == SET){	//�ж϶�ʱ���Ƿ����
		LL_TIM_ClearFlag_UPDATE(TIM3);				//������ϼ��������־λ
		
		printf_s_c("add bonus_wave.s0.id,0,%d", DMA_ADC_RX_BUF[0] >> 8);
		timer3_call_cnt ++;
	}
}

//*******************************// end_c               //************************************//
#endif	// end of __HARDWARE_CONFIG__USER_TIMER_ENABLE__
