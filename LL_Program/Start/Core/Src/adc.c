/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    adc.c
  * @brief   This file provides code for the configuration
  *          of the ADC instances.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "adc.h"

/* USER CODE BEGIN 0 */

//-----------------------------------------------------------------
// double MPU_Temperature_Get()
//-----------------------------------------------------------------
static uint16_t TS_CAL1;    // �ڲ��¶Ȳο�����
static uint16_t TS_CAL2;

uint16_t ADC_Value;
double Temp_oC;
//-----------------------------------------------------------------
// void MPU_Temperature_Show()
//-----------------------------------------------------------------
double Temp_MPU;

/* USER CODE END 0 */

/* ADC3 init function */
void MX_ADC3_Init(void)
{

  /* USER CODE BEGIN ADC3_Init 0 */

  LL_ADC_DeInit(ADC3);
  
  /* USER CODE END ADC3_Init 0 */

  LL_ADC_InitTypeDef ADC_InitStruct = {0};
  LL_ADC_REG_InitTypeDef ADC_REG_InitStruct = {0};
  LL_ADC_CommonInitTypeDef ADC_CommonInitStruct = {0};

  LL_RCC_SetADCClockSource(LL_RCC_ADC_CLKSOURCE_PLL2P);

  /* Peripheral clock enable */
  LL_AHB4_GRP1_EnableClock(LL_AHB4_GRP1_PERIPH_ADC3);

  /* USER CODE BEGIN ADC3_Init 1 */

  /* USER CODE END ADC3_Init 1 */

  /** Common config
  */
  LL_ADC_SetOverSamplingScope(ADC3, LL_ADC_OVS_DISABLE);
  ADC_InitStruct.Resolution = LL_ADC_RESOLUTION_16B;
  ADC_InitStruct.LowPowerMode = LL_ADC_LP_MODE_NONE;
  LL_ADC_Init(ADC3, &ADC_InitStruct);
  ADC_REG_InitStruct.TriggerSource = LL_ADC_REG_TRIG_SOFTWARE;
  ADC_REG_InitStruct.SequencerLength = LL_ADC_REG_SEQ_SCAN_DISABLE;
  ADC_REG_InitStruct.SequencerDiscont = DISABLE;
  ADC_REG_InitStruct.ContinuousMode = LL_ADC_REG_CONV_SINGLE;
  ADC_REG_InitStruct.Overrun = LL_ADC_REG_OVR_DATA_PRESERVED;
  LL_ADC_REG_Init(ADC3, &ADC_REG_InitStruct);
  LL_ADC_REG_SetDataTransferMode(ADC3, LL_ADC_REG_DR_TRANSFER);
  ADC_CommonInitStruct.Multimode = LL_ADC_MULTI_INDEPENDENT;
  LL_ADC_CommonInit(__LL_ADC_COMMON_INSTANCE(ADC3), &ADC_CommonInitStruct);

  /* Disable ADC deep power down (enabled by default after reset state) */
  LL_ADC_DisableDeepPowerDown(ADC3);
  /* Enable ADC internal voltage regulator */
  LL_ADC_EnableInternalRegulator(ADC3);
  /* Delay for ADC internal voltage regulator stabilization. */
  /* Compute number of CPU cycles to wait for, from delay in us. */
  /* Note: Variable divided by 2 to compensate partially */
  /* CPU processing cycles (depends on compilation optimization). */
  /* Note: If system core clock frequency is below 200kHz, wait time */
  /* is only a few CPU processing cycles. */
  __IO uint32_t wait_loop_index;
  wait_loop_index = ((LL_ADC_DELAY_INTERNAL_REGUL_STAB_US * (SystemCoreClock / (100000 * 2))) / 10);
  while(wait_loop_index != 0)
  {
    wait_loop_index--;
  }

  /** Configure Regular Channel
  */
  LL_ADC_REG_SetSequencerRanks(ADC3, LL_ADC_REG_RANK_1, LL_ADC_CHANNEL_TEMPSENSOR);
  LL_ADC_SetChannelSamplingTime(ADC3, LL_ADC_CHANNEL_TEMPSENSOR, LL_ADC_SAMPLINGTIME_810CYCLES_5);
  LL_ADC_SetChannelSingleDiff(ADC3, LL_ADC_CHANNEL_TEMPSENSOR, LL_ADC_SINGLE_ENDED);
  LL_ADC_SetCommonPathInternalCh(__LL_ADC_COMMON_INSTANCE(ADC3), LL_ADC_AWD_CH_TEMPSENSOR_REG);
  /* USER CODE BEGIN ADC3_Init 2 */

  LL_ADC_StartCalibration(ADC3, LL_ADC_CALIB_OFFSET, LL_ADC_SINGLE_ENDED);  // calibration
  while(LL_ADC_IsCalibrationOnGoing(ADC3));                                 // wait for the end of calibration
  LL_ADC_Enable(ADC3);                                                      // enable adc3

  //-----------------------------------------------------------------
  // double MPU_Temperature_Get()
  //-----------------------------------------------------------------
  TS_CAL1 = *(__IO uint16_t *)(0x1FF1E820);
  TS_CAL2 = *(__IO uint16_t *)(0x1FF1E840);

  /* USER CODE END ADC3_Init 2 */

}

/* USER CODE BEGIN 1 */

//-----------------------------------------------------------------
// double MPU_Temperature_Get()
//-----------------------------------------------------------------
//
// ��������: ��ȡGPU�ڲ��������¶�
// ��ڲ���1: ��
// �� �� ֵ: ��
// ע������: ��
//
//-----------------------------------------------------------------
double MPU_Temperature_Get(){
  LL_ADC_REG_StartConversion(ADC3);           // ����ADC3ת��
	while(!LL_ADC_IsActiveFlag_EOS(ADC3));    // �ȴ�ת������	
  
	ADC_Value = LL_ADC_REG_ReadConversionData16(ADC3);
  Temp_oC = ((110.0f - 30.0f) / (TS_CAL2 - TS_CAL1)) * (ADC_Value - TS_CAL1) + 30.0f;

  return Temp_oC;
}
//-----------------------------------------------------------------
// void MPU_Temperature_Show()
//-----------------------------------------------------------------
//
// ��������: ��ʾGPU�ڲ��������¶�
// ��ڲ���1: ��
// �� �� ֵ: ��
// ע������: ��
//
//-----------------------------------------------------------------
void MPU_Temperature_Show(){
  Temp_MPU = MPU_Temperature_Get();
  if (10.0 < Temp_MPU && Temp_MPU < 100.0){
    printf_s(19, "MPU Temp:%3.5f���϶�", Temp_MPU);
  }
}


/* USER CODE END 1 */
