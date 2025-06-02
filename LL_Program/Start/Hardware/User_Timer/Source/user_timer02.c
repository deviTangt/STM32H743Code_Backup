#include "__HARDWARE_CONFIG__.h"
#if __HARDWARE_CONFIG__USER_TIMER_ENABLE__ & __HARDWARE_CONFIG__USER_TIMER2_ENABLE__ // begin of __HARDWARE_CONFIG__USER_TIMER2_ENABLE__
//*******************************// include _h files    //************************************//
#include "user_timer02.h"
//*******************************// define parameters   //************************************//
//*******************************// parameters          //************************************//

uint32_t timer2_call_cnt = 0;

uint8_t TIM2CH1_CAPTURE_STA = 0;
uint32_t TIM2CH1_CAPTURE_VAl[4] = {0};

uint32_t TIM2CH1_CAPTURE_Time = 0, TIM2CH1_CAPTURE_Time_pre = 0;

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
inline void timer2_config_init(){ // ���벶��
	//? ��ʼ��ʱ��
	LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM2);
	LL_AHB4_GRP1_EnableClock(LL_AHB4_GRP1_PERIPH_GPIOA);

	//? �����ж�
	NVIC_SetPriority(TIM2_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(),4, 2));
    NVIC_EnableIRQ(TIM2_IRQn);

	/**TIM2 GPIO Configuration
	 PA0   ------> TIM2_CH1
	*/
	//? ��ʼ��GPIO
	LL_GPIO_InitTypeDef GPIO_InitStruct            = {0};
						GPIO_InitStruct.Pin        = LL_GPIO_PIN_0;
						GPIO_InitStruct.Mode       = LL_GPIO_MODE_ALTERNATE;
						GPIO_InitStruct.Speed      = LL_GPIO_SPEED_FREQ_LOW;
						GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
						GPIO_InitStruct.Pull       = LL_GPIO_PULL_NO;
						GPIO_InitStruct.Alternate  = LL_GPIO_AF_1;
	LL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	//? ���ö�ʱ���ṹ�� 5ms
	LL_TIM_InitTypeDef TIM_InitStruct               = {0};
	                   TIM_InitStruct.Prescaler     = 240 - 1;
	                   TIM_InitStruct.CounterMode   = LL_TIM_COUNTERMODE_UP;      // Ԥ��Ƶ
	                   TIM_InitStruct.Autoreload    = 4294967296 - 1;                    // ����ģʽ�����ϼ���
	                   TIM_InitStruct.ClockDivision = LL_TIM_CLOCKDIVISION_DIV1;  // �Զ���װ��ֵ
	LL_TIM_Init(TIM2, &TIM_InitStruct);


	//? ��������
	LL_TIM_EnableARRPreload      (TIM2);                                                   // �����Զ�װ��ģʽ
	LL_TIM_SetClockSource         (TIM2, LL_TIM_CLOCKSOURCE_INTERNAL);                     // ����ʱ��Դ���ڲ�����
	LL_TIM_SetTriggerOutput       (TIM2, LL_TIM_TRGO_RESET);                               // ��λ����
	LL_TIM_DisableMasterSlaveMode(TIM2);                                                   // ��������ģʽ
	LL_TIM_IC_SetActiveInput     (TIM2, LL_TIM_CHANNEL_CH1, LL_TIM_ACTIVEINPUT_DIRECTTI);  // �����ⲿֱ�Ӵ���
	LL_TIM_IC_SetPrescaler        (TIM2, LL_TIM_CHANNEL_CH1, LL_TIM_ICPSC_DIV1);           // Ԥ��Ƶ
	LL_TIM_IC_SetFilter           (TIM2, LL_TIM_CHANNEL_CH1, LL_TIM_IC_FILTER_FDIV1);      // ����
	LL_TIM_IC_SetPolarity         (TIM2, LL_TIM_CHANNEL_CH1, LL_TIM_IC_POLARITY_RISING);   // �����ش���

    //? UPDATE��־λ
	#if __HARDWARE_CONFIG__TIMER2_INT_UPDATE_ENABLE__ // begin of __HARDWARE_CONFIG__TIMER2_INT_UPDATE_ENABLE__
		LL_TIM_ClearFlag_UPDATE(TIM2);  // ������ϼ��������־λ
		LL_TIM_EnableIT_UPDATE (TIM2);  // ʹ�ܶ�ʱ�����ϼ����ж�
  	#endif // end of __HARDWARE_CONFIG__TIMER2_INT_UPDATE_ENABLE__
	//? ���벶���ж�
	#if __HARDWARE_CONFIG__TIMER2_INT_CAPTURE_ENABLE__ // begin of __HARDWARE_CONFIG__TIMER2_INT_CAPTURE_ENABLE__
		LL_TIM_ClearFlag_CC1    (TIM2);                    // ��������־λ
		LL_TIM_EnableIT_CC1     (TIM2);                    // ����ͨ��ʹ��
		LL_TIM_CC_EnableChannel(TIM2,LL_TIM_CHANNEL_CH1);  // ͨ��ʹ��
	#endif // end of __HARDWARE_CONFIG__TIMER2_INT_CAPTURE_ENABLE__
}
//-----------------------------------------------------------------
// inline void timer2_start()
//-----------------------------------------------------------------
//
// ��������: ������ʱ��2
// ��ڲ���1: ��
// �� �� ֵ: ��
// ע������: ��
//
//-----------------------------------------------------------------
inline void timer2_start(){
    if(__HARDWARE_CONFIG__TIMER2_INT_UPDATE_ENABLE__)
		LL_TIM_ClearFlag_UPDATE(TIM2);  // ������ϼ��������־λ
    LL_TIM_EnableCounter   (TIM2);  // ʹ�ܶ�ʱ����ʼ����
}
//-----------------------------------------------------------------
// inline void timer2_stop()
//-----------------------------------------------------------------
//
// ��������: �رն�ʱ��2
// ��ڲ���1: ��
// �� �� ֵ: ��
// ע������: ��
//
//-----------------------------------------------------------------
inline void timer2_stop(){
    if(__HARDWARE_CONFIG__TIMER2_INT_UPDATE_ENABLE__)
		LL_TIM_ClearFlag_UPDATE(TIM2);   // ������ϼ��������־λ
    LL_TIM_DisableCounter   (TIM2);  // �رն�ʱ������
}

//-----------------------------------------------------------------
// inline void TIM2_IRQHandler_Func(void)
//-----------------------------------------------------------------
//
// ��������: ��ʱ��2�жϷ�����
// ��ڲ���1: ��
// �� �� ֵ: ��
// ע������: ���˺������붨ʱ���жϷ�����TIM2_IRQHandler(void)��
//
//-----------------------------------------------------------------
inline void TIM2_IRQHandler_Func(void){
	if(LL_TIM_IsActiveFlag_UPDATE(TIM2) == SET){	//�ж϶�ʱ���Ƿ����
		LL_TIM_ClearFlag_UPDATE(TIM2);				//������ϼ��������־λ
		
        timer2_call_cnt ++;
		printf("Update ");
	}
	
	if(LL_TIM_IsActiveFlag_CC1(TIM2)){
		LL_TIM_DisableIT_CC1(TIM2);                    // ����ͨ��ʹ��
		LL_TIM_ClearFlag_CC1(TIM2);

		TIM2CH1_CAPTURE_Time = bsp_us;
		if (TIM2CH1_CAPTURE_Time > TIM2CH1_CAPTURE_Time_pre + TIM2CH1_CAPTURE_RECOVERY_TIME){
			TIM2CH1_CAPTURE_Time_pre = TIM2CH1_CAPTURE_Time;

			TIM2CH1_CAPTURE_VAl[TIM2CH1_CAPTURE_STA] = TIM2->CNT;
			if (TIM2CH1_CAPTURE_STA == 0){
				LL_TIM_IC_SetPolarity         (TIM2, LL_TIM_CHANNEL_CH1, LL_TIM_IC_POLARITY_FALLING);   // �½��ش���
				TIM2CH1_CAPTURE_STA = 1;
			}
			else if (TIM2CH1_CAPTURE_STA == 1){
				LL_TIM_IC_SetPolarity         (TIM2, LL_TIM_CHANNEL_CH1, LL_TIM_IC_POLARITY_RISING);   // �����ش���
				TIM2CH1_CAPTURE_STA = 2;
			}
			else if (TIM2CH1_CAPTURE_STA == 2){
				LL_TIM_IC_SetPolarity         (TIM2, LL_TIM_CHANNEL_CH1, LL_TIM_IC_POLARITY_FALLING);   // �½��ش���
				TIM2CH1_CAPTURE_STA = 3;
			}
			else {
				LL_TIM_IC_SetPolarity         (TIM2, LL_TIM_CHANNEL_CH1, LL_TIM_IC_POLARITY_RISING);   // �����ش���
				TIM2CH1_CAPTURE_STA = 0;
			}

			//printf("Captured:");
			//printf("[min:%3d sec:%02d.%03d us:%03d]\r\n", bsp_min, bsp_sec % 60, bsp_ms % 1000, bsp_us % 1000);
		}
		LL_TIM_EnableIT_CC1(TIM2);                    // ����ͨ��ʹ��
	}
}

//*******************************// end_c               //************************************//
#endif	// end of __HARDWARE_CONFIG__USER_TIMER2_ENABLE__



#if 0 //// stm32h7xx_it.c�滻
/**
  * @brief This function handles TIM2 global interrupt.
  */
void TIM2_IRQHandler(void)
{
  /* USER CODE BEGIN TIM2_IRQn 0 */
  #if __HARDWARE_CONFIG__USER_TIMER_ENABLE__ & __HARDWARE_CONFIG__USER_TIMER2_ENABLE__ // begin of __HARDWARE_CONFIG__USER_TIMER2_ENABLE__
    //-----------------------------------------------------------------
    //-----------------------------------------------------------------
    //? TIM2_IRQHandler_Func
    //-----------------------------------------------------------------
    //
    // Interrupt Excute Function: Once TIM2->CNT reached the maximum counter value,
    //                             excute certain function.
    // Detected Case: TIM3 Up Overflow
    // Returned Value: excute certain function
    // Notice: None
    //
    //-----------------------------------------------------------------
    TIM2_IRQHandler_Func();
  #endif // end of __HARDWARE_CONFIG__USER_TIMER2_ENABLE__
  /* USER CODE END TIM2_IRQn 0 */
  /* USER CODE BEGIN TIM2_IRQn 1 */

  /* USER CODE END TIM2_IRQn 1 */
}
#endif
