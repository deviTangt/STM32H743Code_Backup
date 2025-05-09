/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    adc.h
  * @brief   This file contains all the function prototypes for
  *          the adc.c file
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
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __ADC_H__
#define __ADC_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* USER CODE BEGIN Includes */
#include "TJC_Usart.h"
#include "sort_code.h"
#include "ad9959.h"
/* USER CODE END Includes */

extern ADC_HandleTypeDef hadc1;

extern ADC_HandleTypeDef hadc3;

/* USER CODE BEGIN Private defines */
#define AD_CHANNEL_NUM		6
#define AD_CHANNEL_USE		4
#define	AD_SAMPLE_NUM 		500
#define	AD_SAMPLE_RATIO_L 		3
#define	AD_SAMPLE_RATIO_H 		3
#define ADC1_CONVERTED_DATA_BUFFER_SIZE ((uint32_t)  (AD_CHANNEL_NUM * AD_SAMPLE_NUM))

#define CHARGE_SAMPLE_TIME        300
#define CHARGE_TIME               600

#define S1_HOLD_SAMPLE_TIME       300
#define S1_HOLD_TIME              600

#define SWEEP_FAST_ENABLE 0

#if SWEEP_FAST_ENABLE
#define SWEEP_TIME_1              10    // 1 - 1k
#define SWEEP_FREQ_1              1000
#define SWEEP_TIME_2              10    // 1k - 10k
#define SWEEP_FREQ_2              10000
#define SWEEP_TIME_3              10    // 10k - 300k
#define SWEEP_FREQ_3              300000
#define SWEEP_TIME_4              10    // 300k - 1M 
#define SWEEP_FREQ_4              1000000
#else //
#define SWEEP_TIME_1              10000    // 1 - 1k
#define SWEEP_FREQ_1              1000
#define SWEEP_TIME_2              10000    // 1k - 10k
#define SWEEP_FREQ_2              10000
#define SWEEP_TIME_3              6000    // 10k - 300k
#define SWEEP_FREQ_3              300000
#define SWEEP_TIME_4              6000    // 300k - 1M 
#define SWEEP_FREQ_4              1000000
#endif //

#define SWEEP_DUAL_TIME           (SWEEP_TIME_1 + SWEEP_TIME_2 + SWEEP_TIME_3 + SWEEP_TIME_4)
// parameters
extern double ad_val_ready[AD_CHANNEL_NUM][2];
extern uint8_t PE12_state;
extern uint8_t phase_state;
extern uint8_t case_evaluate;
extern uint32_t mark_time;
extern uint32_t AD_freq;
/* USER CODE END Private defines */

void MX_ADC1_Init(void);
void MX_ADC3_Init(void);

/* USER CODE BEGIN Prototypes */
float get_GPU_Temperature(uint32_t Timeout);
void show_GPU_temprature();
//
void ShowADCResult(void);
//
extern void check_normal();
//
extern void judge_circuit_case();
/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif

#endif /* __ADC_H__ */

