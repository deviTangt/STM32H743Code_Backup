/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32h7xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define AD_P3_Pin GPIO_PIN_2
#define AD_P3_GPIO_Port GPIOE
#define AD_SD1_Pin GPIO_PIN_3
#define AD_SD1_GPIO_Port GPIOE
#define AD_SD2_Pin GPIO_PIN_4
#define AD_SD2_GPIO_Port GPIOE
#define AD_SD3_Pin GPIO_PIN_5
#define AD_SD3_GPIO_Port GPIOE
#define AD_SD0_Pin GPIO_PIN_1
#define AD_SD0_GPIO_Port GPIOA
#define AD_SCK_Pin GPIO_PIN_3
#define AD_SCK_GPIO_Port GPIOA
#define AD_IUP_Pin GPIO_PIN_4
#define AD_IUP_GPIO_Port GPIOA
#define AD_CSB_Pin GPIO_PIN_5
#define AD_CSB_GPIO_Port GPIOA
#define AD_RST_Pin GPIO_PIN_11
#define AD_RST_GPIO_Port GPIOB
#define AD_P0_Pin GPIO_PIN_6
#define AD_P0_GPIO_Port GPIOB
#define AD_P1_Pin GPIO_PIN_8
#define AD_P1_GPIO_Port GPIOB
#define AD_P2_Pin GPIO_PIN_0
#define AD_P2_GPIO_Port GPIOE
#define AD_PDC_Pin GPIO_PIN_1
#define AD_PDC_GPIO_Port GPIOE

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
