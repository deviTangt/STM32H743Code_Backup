#include "__HARDWARE_CONFIG__.h"
#if __HARDWARE_CONFIG__DMA_ADC_ENABLE__	// begin of __HARDWARE_CONFIG__DMA_ADC_ENABLE__
//*******************************// include _h files    //************************************//
#include "dma_adc.h"
//*******************************// define parameters   //************************************//
//*******************************// parameters          //************************************//

uint16_t ad_DMA_BUF[80] __attribute__((section(".ARM.__at_0x24000200")));
uint32_t ad_cnt = 0;

//*******************************// define function     //************************************//

//-----------------------------------------------------------------
// void AD_TIM4_Init()
//-----------------------------------------------------------------
//
// ��������: TIM4��ʼ�����˶�ʱ�����ڲ�������(������1M)
// ��ڲ���1: ��
// �� �� ֵ: ��
// ע������: ��
//
//-----------------------------------------------------------------
void AD_TIM4_Init(){
	//? ����TIMʱ��
	LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM4);
	
	//? ��ʱ���ṹ������
	LL_TIM_DeInit(TIM4);
	LL_TIM_InitTypeDef LL_TIM_Struct               = {0};
	                   LL_TIM_Struct.Prescaler     = 23;                          //? Ԥ��Ƶϵ��
	                   LL_TIM_Struct.Autoreload    = 9;                           //? ����ϵ��
	                   LL_TIM_Struct.CounterMode   = LL_TIM_COUNTERDIRECTION_UP;  // ����ģʽ�����ϵ���
	                   LL_TIM_Struct.ClockDivision = LL_TIM_CLOCKDIVISION_DIV1;   // ʱ�ӷ�Ƶ��1
	LL_TIM_Init(TIM4, &LL_TIM_Struct);

	//? ��������
	LL_TIM_EnableARRPreload(TIM4);								// �����Զ�װ��ģʽ
	LL_TIM_SetClockSource(TIM4, LL_TIM_CLOCKSOURCE_INTERNAL);	// �ڲ�APB1ʱ��240MHz
	LL_TIM_SetTriggerOutput(TIM4, LL_TIM_TRGO_UPDATE);			// �¼�����
	LL_TIM_DisableCounter(TIM4);								// ʧ�ܼ�����
}
 
//-----------------------------------------------------------------
// void Samp_Adc_Init(uint32_t buff_Addr, uint32_t trans_Num)
//-----------------------------------------------------------------
//
// ��������: ����ADC��ʼ��
// ��ڲ���1: uint32_t buff_Addr: �������ݻ����ַ
// ��ڲ���2: uint32_t trans_Num: DMAһ�δ����С
// �� �� ֵ: ��
// ע������: ��
//
//-----------------------------------------------------------------
void Samp_Adc_Init(uint32_t buff_Addr, uint32_t trans_Num){
	//? ʹ����Ӧʱ�� 
	LL_AHB4_GRP1_EnableClock(LL_AHB4_GRP1_PERIPH_GPIOA);	// GPIOʱ��
	LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_ADC12);	// ADCʱ��
	#if __HARDWARE_CONFIG__SAMPLE_ADC_DMA_ENABLE__ // begin of __HARDWARE_CONFIG__SAMPLE_ADC_DMA_ENABLE__
		LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_DMA1); // DMAʱ��
	#endif // end of __HARDWARE_CONFIG__SAMPLE_ADC_DMA_ENABLE__

	//? ����ADCͨ��
	LL_GPIO_InitTypeDef LL_GPIO_Struct={0};
	LL_GPIO_Struct.Pin=LL_GPIO_PIN_3;  //!
	LL_GPIO_Struct.Mode=LL_GPIO_MODE_ANALOG;
	LL_GPIO_Struct.Pull=LL_GPIO_PULL_NO;
	LL_GPIO_Init(GPIOA, &LL_GPIO_Struct);	

	//? DMA����
	#if __HARDWARE_CONFIG__SAMPLE_ADC_DMA_ENABLE__ // begin of __HARDWARE_CONFIG__SAMPLE_ADC_DMA_ENABLE__
		//? DMA�ṹ������ 
		LL_DMA_DeInit(DMA1, LL_DMA_STREAM_2);
		LL_DMA_InitTypeDef LL_DMA_Struct                        = {0};
		                   LL_DMA_Struct.PeriphRequest          = LL_DMAMUX1_REQ_ADC1;                // DMA�������裺ADC1
		                   LL_DMA_Struct.Direction              = LL_DMA_DIRECTION_PERIPH_TO_MEMORY;  // DMA���䷽�����赽�Ĵ���
		                   LL_DMA_Struct.Mode                   = LL_DMA_MODE_CIRCULAR;               // DMAѭ��ģʽ������
		                   LL_DMA_Struct.Priority               = LL_DMA_PRIORITY_MEDIUM;             // DMA���ȼ�
		                   LL_DMA_Struct.NbData                 = trans_Num;                          // DMA��������
		                   LL_DMA_Struct.PeriphOrM2MSrcAddress  = (uint32_t)&ADC1->DR;                // DMA��������Դ��ADC1���ݼĴ���
		                   LL_DMA_Struct.MemoryOrM2MDstAddress  = (uint32_t)buff_Addr;                // DMA����Ŀ�ĵأ����ջ���
		                   LL_DMA_Struct.PeriphOrM2MSrcDataSize = LL_DMA_PDATAALIGN_HALFWORD;         // DMA��������Դ���ݴ�С��16bit
		                   LL_DMA_Struct.MemoryOrM2MDstDataSize = LL_DMA_MDATAALIGN_HALFWORD;         // DMA����Ŀ�ĵ����ݴ�С��16bit
		                   LL_DMA_Struct.PeriphOrM2MSrcIncMode  = LL_DMA_PERIPH_NOINCREMENT;          // DMA��������Դ����������
		                   LL_DMA_Struct.MemoryOrM2MDstIncMode  = LL_DMA_MEMORY_INCREMENT;            // DMA����Ŀ�ĵ�����������
		LL_DMA_Init(DMA1, LL_DMA_STREAM_2, &LL_DMA_Struct);  
		//? ����DMA��������ж� 
		LL_DMA_EnableIT_TC(DMA1, LL_DMA_STREAM_2);

		//? �����ж����ȼ� 
		NVIC_SetPriority(DMA1_Stream2_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 0, 0));
		NVIC_EnableIRQ(DMA1_Stream2_IRQn);
		LL_DMA_DisableStream(DMA1, LL_DMA_STREAM_2);
	#endif // end of __HARDWARE_CONFIG__SAMPLE_ADC_DMA_ENABLE__

	//? ADC��ʼ�� 
	// �˳�����ģʽ
	LL_ADC_DisableDeepPowerDown(ADC1); 	
	// �����ڲ���ѹ�� 
	LL_ADC_EnableInternalRegulator(ADC1); 
	// �ȴ��ڲ���ѹ������ 
	uint32_t wait_loop_index;
	wait_loop_index = ((LL_ADC_DELAY_INTERNAL_REGUL_STAB_US * (SystemCoreClock / (100000 * 2))) / 10);
	while(wait_loop_index != 0)  wait_loop_index--;	
	
	// ����ADC��Ƶϵ��
	LL_ADC_CommonInitTypeDef ADC_CommonInitStruct = {0};
  	ADC_CommonInitStruct.CommonClock = LL_ADC_CLOCK_ASYNC_DIV1;
  	LL_ADC_CommonInit(__LL_ADC_COMMON_INSTANCE(ADC1), &ADC_CommonInitStruct);	
	
	// BOOST λ����
	LL_ADC_SetBoostMode(ADC1, LL_ADC_BOOST_MODE_50MHZ);

	//? ����������
	LL_ADC_DeInit(ADC1);
	LL_ADC_InitTypeDef ADC_InitStruct              = {0};
	                   ADC_InitStruct.Resolution   = LL_ADC_RESOLUTION_16B;       // �����ֱ��ʣ�16bit
	                   ADC_InitStruct.LeftBitShift = LL_ADC_LEFT_BIT_SHIFT_NONE;  // �������ƶ���������
	                   ADC_InitStruct.LowPowerMode = LL_ADC_LP_MODE_NONE;         // �͹���ģʽ��������
	LL_ADC_Init(ADC1, &ADC_InitStruct);

	//! ����У׼
  	LL_ADC_StartCalibration(ADC1, LL_ADC_CALIB_OFFSET, LL_ADC_SINGLE_ENDED);  
	// �ȴ�У׼���
	while(LL_ADC_IsCalibrationOnGoing(ADC1) != 0UL);	

	//? ��������������� 
	LL_ADC_REG_InitTypeDef ADC_REG_InitStruct                  = {0};
	                       ADC_REG_InitStruct.TriggerSource    = LL_ADC_REG_TRIG_EXT_TIM4_TRGO;      // ADC����Դ��TIM4�����¼�����
	                       ADC_REG_InitStruct.DataTransferMode = LL_ADC_REG_DMA_TRANSFER_UNLIMITED;  // ���ݴ���ģʽ��������DMA����
	                       ADC_REG_InitStruct.ContinuousMode   = LL_ADC_REG_CONV_SINGLE;             // ADC��������ģʽ�����η�����
	                       ADC_REG_InitStruct.SequencerLength  = LL_ADC_REG_SEQ_SCAN_DISABLE;        // ADC�������г��ȣ�ɨ�費����
	                       ADC_REG_InitStruct.SequencerDiscont = LL_ADC_REG_SEQ_DISCONT_DISABLE;     // ADC����������ɢ
	                       ADC_REG_InitStruct.Overrun          = LL_ADC_REG_OVR_DATA_OVERWRITTEN;    // ADC�����������ݸ���
	LL_ADC_REG_Init(ADC1, &ADC_REG_InitStruct);
	LL_ADC_REG_SetTriggerEdge(ADC1, LL_ADC_REG_TRIG_EXT_RISING);  // ���ô���Դģʽ�������ش���

	//? ���ù���ͨ�� 
	#define ADC_Sequence_Channel_1 LL_ADC_CHANNEL_15
	LL_ADC_REG_SetSequencerRanks(ADC1, LL_ADC_REG_RANK_1, ADC_Sequence_Channel_1);  //! ���ò�������1 ADCͨ��
	LL_ADC_SetChannelSamplingTime(ADC1, ADC_Sequence_Channel_1, LL_ADC_SAMPLINGTIME_8CYCLES_5); // ���ò�������
	LL_ADC_SetChannelSingleDiff(ADC1, ADC_Sequence_Channel_1, LL_ADC_SINGLE_ENDED);	// ���ò���
	/* ͨ��Ԥѡ���ã�����ܹؼ� */
  ADC1->PCSEL |= (1UL << (__LL_ADC_CHANNEL_TO_DECIMAL_NB(ADC_Sequence_Channel_1) & 0x1FUL));  	
#if __HARDWARE_CONFIG__SAMPLE_ADC_DMA_ENABLE__ // begin of __HARDWARE_CONFIG__SAMPLE_ADC_DMA_ENABLE__
  LL_ADC_REG_SetDataTransferMode(ADC1, LL_ADC_REG_DMA_TRANSFER_UNLIMITED);
#else
  LL_ADC_REG_SetDataTransferMode(ADC1, LL_ADC_REG_DR_TRANSFER);
	LL_ADC_EnableIT_EOC(ADC1);
	NVIC_SetPriority(ADC_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 0, 0));
	NVIC_EnableIRQ(ADC_IRQn);
#endif // end of __HARDWARE_CONFIG__SAMPLE_ADC_DMA_ENABLE__
	/* ��ʼ��������ʱ�� */
	AD_TIM4_Init();
}
 
//-----------------------------------------------------------------
// void Start_Sample()
//-----------------------------------------------------------------
//
// ��������: ��ʼ����
// ��ڲ���1: ��
// �� �� ֵ: ��
// ע������: ��
//
//-----------------------------------------------------------------
void Start_Sample()
{
	#if __HARDWARE_CONFIG__SAMPLE_ADC_DMA_ENABLE__ // begin of __HARDWARE_CONFIG__SAMPLE_ADC_DMA_ENABLE__	
		LL_DMA_EnableStream(DMA1, LL_DMA_STREAM_2);
	#endif // end of __HARDWARE_CONFIG__SAMPLE_ADC_DMA_ENABLE__

    LL_ADC_Enable(ADC1);
	while(LL_ADC_IsActiveFlag_ADRDY(ADC1) != SET);
	LL_ADC_REG_StartConversion(ADC1);
	LL_TIM_EnableCounter(TIM4);
}
//-----------------------------------------------------------------
// void Stop_Sample()
//-----------------------------------------------------------------
//
// ��������: ֹͣ����
// ��ڲ���1: ��
// �� �� ֵ: ��
// ע������: ��
//
//-----------------------------------------------------------------
void Stop_Sample()
{
	LL_TIM_DisableCounter(TIM4);
	LL_ADC_REG_StopConversion(ADC1);
	while(LL_ADC_REG_IsConversionOngoing(ADC1) != 0);
	LL_ADC_Disable(ADC1);
	LL_ADC_EnableDeepPowerDown(ADC1);

	#if __HARDWARE_CONFIG__SAMPLE_ADC_DMA_ENABLE__ // begin of __HARDWARE_CONFIG__SAMPLE_ADC_DMA_ENABLE__
		LL_DMA_DisableStream(DMA1, LL_DMA_STREAM_2);
		LL_DMA_ClearFlag_TC0(DMA1);
	#endif // end of __HARDWARE_CONFIG__SAMPLE_ADC_DMA_ENABLE__
}
 
#if __HARDWARE_CONFIG__SAMPLE_ADC_DMA_ENABLE__ // begin of __HARDWARE_CONFIG__SAMPLE_ADC_DMA_ENABLE__
//-----------------------------------------------------------------
// void DMA1_Stream2_IRQHandler(void)
//-----------------------------------------------------------------
//
// ��������: DMA1_Stream2�жϷ�����
// ��ڲ���1: ��
// �� �� ֵ: ��
// ע������: ��
//
//-----------------------------------------------------------------
void DMA1_Stream2_IRQHandler(void)
{
	if(LL_DMA_IsActiveFlag_TC2(DMA1) != RESET)
	{
		LL_DMA_ClearFlag_TC2(DMA1);
        /* ���ڼ��������Ƿ�׼ȷ�ģ�1M������ʱ��DMA����1000�����ݴ��ʱ����1ms�� */ 
		//LL_GPIO_TogglePin(GPIOB, LL_GPIO_PIN_1);
        LED_TURN();
        ad_cnt ++;
	}
}
 
#else
//-----------------------------------------------------------------
// void ADC_IRQHandler(void)
//-----------------------------------------------------------------
//
// ��������: ADC1���жϷ�����
// ��ڲ���1: ��
// �� �� ֵ: ��
// ע������: ��
//
//-----------------------------------------------------------------
void ADC_IRQHandler(void)
{
	if(LL_ADC_IsActiveFlag_EOC(ADC1) != RESET)
	{
      LL_ADC_ClearFlag_EOC(ADC1);
      /* ��ʹ��DMAʱ�����������ȡ����ֵ */
	}
}
#endif // end of __HARDWARE_CONFIG__SAMPLE_ADC_DMA_ENABLE__


//*******************************// end_c               //************************************//
#endif	// end of __HARDWARE_CONFIG__DMA_ADC_ENABLE__
