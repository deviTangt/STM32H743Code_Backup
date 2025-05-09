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
uint16_t ADC1_DATA[ADC1_CONVERTED_DATA_BUFFER_SIZE] __attribute__((section(".ARM.__at_0x24000000")));

uint8_t PE12_state = 1;
uint32_t PE12_change_uwtick = 0;
uint32_t mark_time = 0;

uint8_t time_cal_state;
uint32_t time_cal_pre_uwTick = 0;

uint32_t ad_temp[2][AD_CHANNEL_NUM][AD_SAMPLE_NUM];
uint32_t sum = 0;
double ad_val_ready[AD_CHANNEL_NUM][2];

double bonus = 0.0;
double state1_bonus_max = 0.0;
double bonus_H = 0.0;
uint8_t state1_bonus_max_flag = 0;
uint32_t freq_H = 1;

double ST_ad_val_ready[AD_CHANNEL_NUM][2];

uint8_t phase_state = 0;

uint32_t last_mark_freq = 0;
/* USER CODE END 0 */

ADC_HandleTypeDef hadc1;
ADC_HandleTypeDef hadc3;
DMA_HandleTypeDef hdma_adc1;

uint8_t last_turn_case_check = 0;
uint8_t mark_case_check = 0;
uint32_t case_evaluate_bne_start_time = 0;
uint8_t flag_case_evaluate_bne = 0;

uint8_t flag_already_restart = 0;

uint8_t sweep_once = 0;

uint16_t bonus_wave_point_cnt = 0;
uint16_t div_dif = 0;


uint32_t phase_end_ad_temp[2][4][1000];
uint16_t phase_end_cnt = 0;
/* ADC1 init function */
void MX_ADC1_Init(void)
{

  /* USER CODE BEGIN ADC1_Init 0 */

  /* USER CODE END ADC1_Init 0 */

  ADC_MultiModeTypeDef multimode = {0};
  ADC_ChannelConfTypeDef sConfig = {0};

  /* USER CODE BEGIN ADC1_Init 1 */

  /* USER CODE END ADC1_Init 1 */

  /** Common config
  */
  hadc1.Instance = ADC1;
  hadc1.Init.ClockPrescaler = ADC_CLOCK_ASYNC_DIV2;
  hadc1.Init.Resolution = ADC_RESOLUTION_16B;
  hadc1.Init.ScanConvMode = ADC_SCAN_ENABLE;
  hadc1.Init.EOCSelection = ADC_EOC_SEQ_CONV;
  hadc1.Init.LowPowerAutoWait = DISABLE;
  hadc1.Init.ContinuousConvMode = ENABLE;
  hadc1.Init.NbrOfConversion = 6;
  hadc1.Init.DiscontinuousConvMode = DISABLE;
  hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc1.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
  hadc1.Init.ConversionDataManagement = ADC_CONVERSIONDATA_DMA_CIRCULAR;
  hadc1.Init.Overrun = ADC_OVR_DATA_OVERWRITTEN;
  hadc1.Init.LeftBitShift = ADC_LEFTBITSHIFT_NONE;
  hadc1.Init.OversamplingMode = DISABLE;
  hadc1.Init.Oversampling.Ratio = 1;
  if (HAL_ADC_Init(&hadc1) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure the ADC multi-mode
  */
  multimode.Mode = ADC_MODE_INDEPENDENT;
  if (HAL_ADCEx_MultiModeConfigChannel(&hadc1, &multimode) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Regular Channel
  */
  sConfig.Channel = ADC_CHANNEL_3;
  sConfig.Rank = ADC_REGULAR_RANK_1;
  sConfig.SamplingTime = ADC_SAMPLETIME_1CYCLE_5;
  sConfig.SingleDiff = ADC_SINGLE_ENDED;
  sConfig.OffsetNumber = ADC_OFFSET_NONE;
  sConfig.Offset = 0;
  sConfig.OffsetSignedSaturation = DISABLE;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Regular Channel
  */
  sConfig.Channel = ADC_CHANNEL_4;
  sConfig.Rank = ADC_REGULAR_RANK_2;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Regular Channel
  */
  sConfig.Channel = ADC_CHANNEL_7;
  sConfig.Rank = ADC_REGULAR_RANK_3;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Regular Channel
  */
  sConfig.Channel = ADC_CHANNEL_8;
  sConfig.Rank = ADC_REGULAR_RANK_4;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Regular Channel
  */
  sConfig.Channel = ADC_CHANNEL_10;
  sConfig.Rank = ADC_REGULAR_RANK_5;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Regular Channel
  */
  sConfig.Channel = ADC_CHANNEL_11;
  sConfig.Rank = ADC_REGULAR_RANK_6;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN ADC1_Init 2 */
	HAL_Delay(100);
  if (HAL_ADCEx_Calibration_Start(&hadc1, ADC_CALIB_OFFSET, ADC_SINGLE_ENDED) != HAL_OK){
        Serial_TJC_SendTxt(0, "hadc1 error with HAL_ADCEx_Calibration_Start\r\n");
        Error_Handler();
   }
  if (HAL_ADC_Start_DMA(&hadc1, (uint32_t *)ADC1_DATA, ADC1_CONVERTED_DATA_BUFFER_SIZE) != HAL_OK){
        Serial_TJC_SendTxt(0, "hadc1 error with HAL_ADC_Start_DMA\r\n");
        Error_Handler();
   }
  /* USER CODE END ADC1_Init 2 */

}
/* ADC3 init function */
void MX_ADC3_Init(void)
{

  /* USER CODE BEGIN ADC3_Init 0 */

  /* USER CODE END ADC3_Init 0 */

  ADC_ChannelConfTypeDef sConfig = {0};

  /* USER CODE BEGIN ADC3_Init 1 */

  /* USER CODE END ADC3_Init 1 */

  /** Common config
  */
  hadc3.Instance = ADC3;
  hadc3.Init.ClockPrescaler = ADC_CLOCK_ASYNC_DIV2;
  hadc3.Init.Resolution = ADC_RESOLUTION_16B;
  hadc3.Init.ScanConvMode = ADC_SCAN_DISABLE;
  hadc3.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
  hadc3.Init.LowPowerAutoWait = DISABLE;
  hadc3.Init.ContinuousConvMode = DISABLE;
  hadc3.Init.NbrOfConversion = 1;
  hadc3.Init.DiscontinuousConvMode = DISABLE;
  hadc3.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc3.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
  hadc3.Init.ConversionDataManagement = ADC_CONVERSIONDATA_DR;
  hadc3.Init.Overrun = ADC_OVR_DATA_OVERWRITTEN;
  hadc3.Init.LeftBitShift = ADC_LEFTBITSHIFT_NONE;
  hadc3.Init.OversamplingMode = DISABLE;
  hadc3.Init.Oversampling.Ratio = 1;
  if (HAL_ADC_Init(&hadc3) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Regular Channel
  */
  sConfig.Channel = ADC_CHANNEL_TEMPSENSOR;
  sConfig.Rank = ADC_REGULAR_RANK_1;
  sConfig.SamplingTime = ADC_SAMPLETIME_810CYCLES_5;
  sConfig.SingleDiff = ADC_SINGLE_ENDED;
  sConfig.OffsetNumber = ADC_OFFSET_NONE;
  sConfig.Offset = 0;
  sConfig.OffsetSignedSaturation = DISABLE;
  if (HAL_ADC_ConfigChannel(&hadc3, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN ADC3_Init 2 */
	HAL_Delay(100);
	if (HAL_ADCEx_Calibration_Start(&hadc3, ADC_CALIB_OFFSET, ADC_SINGLE_ENDED) != HAL_OK){
        Serial_TJC_SendTxt(0, "hadc3 error with HAL_ADCEx_Calibration_Start\r\n");
        Error_Handler();
   }
  /* USER CODE END ADC3_Init 2 */

}

void HAL_ADC_MspInit(ADC_HandleTypeDef* adcHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(adcHandle->Instance==ADC1)
  {
  /* USER CODE BEGIN ADC1_MspInit 0 */

  /* USER CODE END ADC1_MspInit 0 */
    /* ADC1 clock enable */
    __HAL_RCC_ADC12_CLK_ENABLE();

    __HAL_RCC_GPIOC_CLK_ENABLE();
    __HAL_RCC_GPIOA_CLK_ENABLE();
    /**ADC1 GPIO Configuration
    PC0     ------> ADC1_INP10
    PC1     ------> ADC1_INP11
    PA6     ------> ADC1_INP3
    PA7     ------> ADC1_INP7
    PC4     ------> ADC1_INP4
    PC5     ------> ADC1_INP8
    */
    GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_4|GPIO_PIN_5;
    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_6|GPIO_PIN_7;
    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    /* ADC1 DMA Init */
    /* ADC1 Init */
    hdma_adc1.Instance = DMA2_Stream4;
    hdma_adc1.Init.Request = DMA_REQUEST_ADC1;
    hdma_adc1.Init.Direction = DMA_PERIPH_TO_MEMORY;
    hdma_adc1.Init.PeriphInc = DMA_PINC_DISABLE;
    hdma_adc1.Init.MemInc = DMA_MINC_ENABLE;
    hdma_adc1.Init.PeriphDataAlignment = DMA_PDATAALIGN_HALFWORD;
    hdma_adc1.Init.MemDataAlignment = DMA_MDATAALIGN_HALFWORD;
    hdma_adc1.Init.Mode = DMA_CIRCULAR;
    hdma_adc1.Init.Priority = DMA_PRIORITY_VERY_HIGH;
    hdma_adc1.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
    if (HAL_DMA_Init(&hdma_adc1) != HAL_OK)
    {
      Error_Handler();
    }

    __HAL_LINKDMA(adcHandle,DMA_Handle,hdma_adc1);

    /* ADC1 interrupt Init */
    HAL_NVIC_SetPriority(ADC_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(ADC_IRQn);
  /* USER CODE BEGIN ADC1_MspInit 1 */

  /* USER CODE END ADC1_MspInit 1 */
  }
  else if(adcHandle->Instance==ADC3)
  {
  /* USER CODE BEGIN ADC3_MspInit 0 */

  /* USER CODE END ADC3_MspInit 0 */
    /* ADC3 clock enable */
    __HAL_RCC_ADC3_CLK_ENABLE();
  /* USER CODE BEGIN ADC3_MspInit 1 */

  /* USER CODE END ADC3_MspInit 1 */
  }
}

void HAL_ADC_MspDeInit(ADC_HandleTypeDef* adcHandle)
{

  if(adcHandle->Instance==ADC1)
  {
  /* USER CODE BEGIN ADC1_MspDeInit 0 */

  /* USER CODE END ADC1_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_ADC12_CLK_DISABLE();

    /**ADC1 GPIO Configuration
    PC0     ------> ADC1_INP10
    PC1     ------> ADC1_INP11
    PA6     ------> ADC1_INP3
    PA7     ------> ADC1_INP7
    PC4     ------> ADC1_INP4
    PC5     ------> ADC1_INP8
    */
    HAL_GPIO_DeInit(GPIOC, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_4|GPIO_PIN_5);

    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_6|GPIO_PIN_7);

    /* ADC1 DMA DeInit */
    HAL_DMA_DeInit(adcHandle->DMA_Handle);

    /* ADC1 interrupt Deinit */
    HAL_NVIC_DisableIRQ(ADC_IRQn);
  /* USER CODE BEGIN ADC1_MspDeInit 1 */

  /* USER CODE END ADC1_MspDeInit 1 */
  }
  else if(adcHandle->Instance==ADC3)
  {
  /* USER CODE BEGIN ADC3_MspDeInit 0 */

  /* USER CODE END ADC3_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_ADC3_CLK_DISABLE();
  /* USER CODE BEGIN ADC3_MspDeInit 1 */

  /* USER CODE END ADC3_MspDeInit 1 */
  }
}

/* USER CODE BEGIN 1 */
// 获取GPU温度
float get_GPU_Temperature(uint32_t Timeout)
{

	uint16_t TS_CAL1;
	uint16_t TS_CAL2;
	float Temp_oC = 0;
	uint32_t Temp_DC = 0;

	HAL_ADC_Start(&hadc3);  /* ADC3 */

	if(HAL_OK == HAL_ADC_PollForConversion(&hadc3,Timeout))  /* Timeout */
	{
		Temp_DC = HAL_ADC_GetValue(&hadc3);
	}
	else
	{
	   Serial_TJC_SendTxt_2(28, "ADC Conversion failed! \n");
	}

    TS_CAL1 = *(__IO uint16_t *)(0x1FF1E820);
    TS_CAL2 = *(__IO uint16_t *)(0x1FF1E840);

    Temp_oC = ((110.0f - 30.0f) / (TS_CAL2 - TS_CAL1)) * (Temp_DC - TS_CAL1) + 30.0f;

    return Temp_oC;
}
// 显示GPU内核温度
void show_GPU_temprature(){
	float Temp_GPU = get_GPU_Temperature(0xF);
	if ((float)10.0 < Temp_GPU && Temp_GPU < (float)100.0)
		Serial_TJC_SendTxt_2(19, "GPU Temp:%f", Temp_GPU);
}
//
void sort_cal_ad_val_ready(){
  uint32_t i;
  for(i = 0; i < ADC1_CONVERTED_DATA_BUFFER_SIZE;i ++)
    ad_temp[PE12_state][i % AD_CHANNEL_NUM][i / AD_CHANNEL_NUM] = ADC1_DATA[i];


  for (i = 0;i < AD_CHANNEL_NUM;i ++){
    if (i % AD_CHANNEL_NUM < 4){
      sum = 0;
      insert_sort_for_quickupgrade(ad_temp[PE12_state][i], 0, AD_SAMPLE_NUM - 1);
      for (uint16_t j = AD_SAMPLE_NUM * AD_SAMPLE_RATIO_L / 10;j < AD_SAMPLE_NUM - AD_SAMPLE_NUM * AD_SAMPLE_RATIO_H / 10;j ++)
        sum += ad_temp[PE12_state][i][j];

      ad_val_ready[i][PE12_state] = sum / 1.0 / ((AD_SAMPLE_NUM - AD_SAMPLE_NUM * AD_SAMPLE_RATIO_H / 10) - (AD_SAMPLE_NUM * AD_SAMPLE_RATIO_L / 10))
                                    * 1000 * 3.3 / 65536;
    }
  }
}
//
void sort_cal_phase_end_ad_temp(uint32_t size){
  uint32_t i;

  for (i = 0;i < 4;i ++){
    sum = 0;
    insert_sort_for_quickupgrade(phase_end_ad_temp[PE12_state][i], 0, size);
    for (uint16_t j = size * AD_SAMPLE_RATIO_L / 10;j < size - size * AD_SAMPLE_RATIO_H / 10;j ++)
      sum += phase_end_ad_temp[PE12_state][i][j];

    ad_val_ready[i][PE12_state] = (double)(sum / ((size - size * AD_SAMPLE_RATIO_H / 10) - (size * AD_SAMPLE_RATIO_L / 10)));
  }
}
// 显示ADC1四通道数据
void ShowADCResult(void){
  uint16_t i;

  if (phase_state == 0){    // 1
    PE12_state = 1;
    sort_cal_ad_val_ready();
    
    #if __PHASE_END_SAMPLE__
    if (uwTick > CHARGE_SAMPLE_TIME + mark_time){
      for (i = 0;i < 4;i ++)
        phase_end_ad_temp[PE12_state][i][phase_end_cnt] = (uint32_t)ad_val_ready[i][PE12_state];
      phase_end_cnt ++; 
    }
    #endif
    if (uwTick > CHARGE_TIME + mark_time){
      sort_cal_ad_val_ready();
      #if __PHASE_END_SAMPLE__
      sort_cal_phase_end_ad_temp(phase_end_cnt);
      #endif
      HAL_GPIO_WritePin(DIGIT_SEL_GPIO_Port, DIGIT_SEL_Pin, GPIO_PIN_RESET);
      PE12_state = 0;
      phase_state = 1;
      #if __PHASE_END_SAMPLE__
      Serial_TJC_SendTxt_2(17, "(Z1)phase_end_cnt:%d", phase_end_cnt);
      #endif
      phase_end_cnt = 0;

      Serial_TJC_SendTxt_2(15, "(Z1)%4.1f / %4.1f", ad_val_ready[0][1], ad_val_ready[1][1]);
      Serial_TJC_SendTxt_2(16, "(Z1)%4.1f / %4.1f", ad_val_ready[2][1], ad_val_ready[3][1]);
    }
    else{
      HAL_GPIO_WritePin(DIGIT_SEL_GPIO_Port, DIGIT_SEL_Pin, GPIO_PIN_SET);
      PE12_state = 1;
    }
  }
  else if (phase_state == 1){     // 0
    PE12_state = 0;
    sort_cal_ad_val_ready();
    #if __PHASE_END_SAMPLE__
    if (uwTick > S1_HOLD_SAMPLE_TIME + CHARGE_TIME + mark_time){
      for (i = 0;i < 4;i ++)
        phase_end_ad_temp[PE12_state][i][phase_end_cnt] = (uint32_t)ad_val_ready[i][PE12_state];
      phase_end_cnt ++; 
    }
    #endif
    if (uwTick > CHARGE_TIME + S1_HOLD_TIME + mark_time){
      phase_state = 2;
      sort_cal_ad_val_ready();

      #if __PHASE_END_SAMPLE__
      sort_cal_phase_end_ad_temp(phase_end_cnt);
      #endif
      ad_val_ready[4][0] = 2000.0 * ad_val_ready[2][0] / (ad_val_ready[1][0] - ad_val_ready[2][0]); // Ri
      ad_val_ready[5][0] = 1954.0 * (ad_val_ready[0][0] - ad_val_ready[0][1]) / ad_val_ready[0][1]; // Ro


      check_normal();

      for (i = 0;i < 6;i ++)
        ST_ad_val_ready[i][0] = ad_val_ready[i][0];
        
      #if __TJC_DEBUG__
      Serial_TJC_SendTxt_2(5,  "(Z0)%4.2fmV / %4.2fmv\r\n", ad_val_ready[0][0], ad_val_ready[1][0]);
      Serial_TJC_SendTxt_2(6,  "(Z0)%4.2fmV / %4.2fmv\r\n", ad_val_ready[2][0], ad_val_ready[3][0]);
      #endif

      #if __PHASE_END_SAMPLE__
      Serial_TJC_SendTxt_2(18, "(Z0)phase_end_cnt:%d", phase_end_cnt);
      #endif
      phase_end_cnt = 0;

      if (sweep_once == 0){
        Serial_TJC_SendCmd("page bonus_wave");
        Serial_TJC_SendCmd("cle bonus_wave.s0.id,0");
        Write_frequency(MAIN_CH_SELECT, 1);
      }
    }
  }
  else if (phase_state == 2){ // 扫频     // 0
    if (sweep_once == 1) {
      phase_state = 3;
      HAL_GPIO_WritePin(DIGIT_SEL_GPIO_Port, DIGIT_SEL_Pin, GPIO_PIN_SET);
      PE12_state = 1;
      return;
    }

    bonus = 100.0 * ad_val_ready[0][0] / ad_val_ready[3][0];
    if (state1_bonus_max_flag == 0){
      if (bonus > state1_bonus_max && AD_freq > 700) state1_bonus_max = bonus;
      else if (bonus < state1_bonus_max * 0.85 && bonus > 5.0) state1_bonus_max_flag = 1;
    } 

    else if (state1_bonus_max_flag == 1){
      if (bonus < state1_bonus_max * 0.707){
        freq_H = Get_Frequency();
        bonus_H = bonus;
        state1_bonus_max_flag = 2;

        if (freq_H > 1000000)   Serial_TJC_SendTxt_2(14, "AD9959 Freq: %d,%03d,%03d Hz", freq_H / 1000000, freq_H / 1000, freq_H % 1000);
        else if (freq_H > 1000) Serial_TJC_SendTxt_2(14, "AD9959 Freq: %d,%03d Hz", freq_H / 1000, freq_H % 1000);
        else                     Serial_TJC_SendTxt_2(14, "AD9959 Freq: %d Hz", freq_H);
      }
    }

    // 绘制波形
    for (i = bonus_wave_point_cnt;i < (uint16_t)(120 * log10(AD_freq));i ++){
      Serial_TJC_SendCmd("add bonus_wave.s0.id,0,%d", (uint16_t)(bonus * 255 / 200));
      bonus_wave_point_cnt ++;
    }
    Serial_TJC_SendCmd("bonus_wave.t9.txt=\"-%.2f\"", bonus);
    Serial_TJC_SendCmd("bonus_wave.t8.txt=\"Max Bonus:%.2f\"", state1_bonus_max);
    Serial_TJC_SendCmd("bonus_wave.t10.txt=\"Freq:%d\"", AD_freq);
    //phase_state = 2;
    sort_cal_ad_val_ready();
    if (uwTick > CHARGE_TIME + S1_HOLD_TIME + SWEEP_DUAL_TIME + mark_time){
      phase_state = 3;
      HAL_GPIO_WritePin(DIGIT_SEL_GPIO_Port, DIGIT_SEL_Pin, GPIO_PIN_SET);
      PE12_state = 1;
      if (sweep_once == 0) {
        sweep_once = 1; 
        Serial_TJC_SendCmd("page show");
      }
    }
    PE12_state = 0;
  }
  else if (phase_state == 3){  // 0 -> 1
    phase_state = 4;
    PE12_change_uwtick = CHARGE_TIME + S1_HOLD_TIME + SWEEP_DUAL_TIME;
    HAL_GPIO_WritePin(DIGIT_SEL_GPIO_Port, DIGIT_SEL_Pin, GPIO_PIN_SET);
    Write_frequency(MAIN_CH_SELECT, 1000);
    PE12_state = 1;
    for (i = 0;i < 6;i ++)
        ad_val_ready[i][0] = ST_ad_val_ready[i][0];
    flag_case_evaluate_bne = 0;
    mark_case_check = last_turn_case_check;
  }             // toggle
  else if (phase_state == 4){ // 1
    phase_state = 0;
    HAL_GPIO_WritePin(DIGIT_SEL_GPIO_Port, DIGIT_SEL_Pin, GPIO_PIN_SET);
    PE12_state = 1;
    mark_time = uwTick;
    phase_end_cnt = 0;
    /*
    sort_cal_ad_val_ready();
    check_normal();
    if (case_evaluate == last_turn_case_check || (flag_case_evaluate_bne && case_evaluate != mark_case_check)){
      flag_case_evaluate_bne = 0;
      mark_case_check = last_turn_case_check;
    }
    else if (case_evaluate != last_turn_case_check) {
      if (flag_case_evaluate_bne == 0){
        mark_case_check = case_evaluate;
        flag_case_evaluate_bne = 1;
        case_evaluate_bne_start_time = uwTick;
      }
      else if (uwTick > case_evaluate_bne_start_time + 200 && flag_already_restart == 0){
        flag_already_restart = 1;
        last_turn_case_check = mark_case_check;
        HAL_GPIO_WritePin(DIGIT_SEL_GPIO_Port, DIGIT_SEL_Pin, GPIO_PIN_SET);
        PE12_state = 1;
        phase_state = 0;
        mark_time = uwTick;
        return;
      }
    }
    */
  }
	
  if (uwTick > time_cal_pre_uwTick + 1) {
    time_cal_pre_uwTick = uwTick;

    //sort_cal_ad_val_ready();
  }

  
  #if __TJC_DEBUG__
	Serial_TJC_SendTxt_2(7,  "CH3 PA6 val:%4.6fmV \r\n", ad_val_ready[0][PE12_state]);
	Serial_TJC_SendTxt_2(8,  "CH4 PC4 val:%4.6fmV \r\n", ad_val_ready[1][PE12_state]);
	Serial_TJC_SendTxt_2(9,  "CH7 PA7 val:%4.6fmV \r\n", ad_val_ready[2][PE12_state]);
	Serial_TJC_SendTxt_2(10,  "CH8 PC5 val:%4.6fmV \r\n", ad_val_ready[3][PE12_state]);
  #endif

  bonus = 100.0 * ad_val_ready[0][0] / ad_val_ready[3][0];
  

  if (PE12_state == 1) {
    state1_bonus_max = 0.0;
    state1_bonus_max_flag = 0;
  }

  Serial_TJC_SendTxt_2(11,  "PE12: %1d Bonus:-%4.6f \r\n", PE12_state, bonus);
  Serial_TJC_SendTxt_2(12,  "Ri:%4.2fO Ro:%4.2fO\r\n", ad_val_ready[4][0], ad_val_ready[5][0]);

  #if __TJC_DEBUG__
  Serial_TJC_SendTxt_2(13,  "Max bonus:%4.6f \r\n", state1_bonus_max);
  #endif
}
/* USER CODE END 1 */
