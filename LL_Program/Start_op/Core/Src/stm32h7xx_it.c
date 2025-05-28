/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    stm32h7xx_it.c
  * @brief   Interrupt Service Routines.
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
#include "main.h"
#include "stm32h7xx_it.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN TD */

/* USER CODE END TD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/* External variables --------------------------------------------------------*/

/* USER CODE BEGIN EV */

/* USER CODE END EV */

/******************************************************************************/
/*           Cortex Processor Interruption and Exception Handlers          */
/******************************************************************************/
/**
  * @brief This function handles Non maskable interrupt.
  */
void NMI_Handler(void)
{
  /* USER CODE BEGIN NonMaskableInt_IRQn 0 */

  /* USER CODE END NonMaskableInt_IRQn 0 */
  /* USER CODE BEGIN NonMaskableInt_IRQn 1 */
   while (1)
  {
  }
  /* USER CODE END NonMaskableInt_IRQn 1 */
}

/**
  * @brief This function handles Hard fault interrupt.
  */
void HardFault_Handler(void)
{
  /* USER CODE BEGIN HardFault_IRQn 0 */

  /* USER CODE END HardFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_HardFault_IRQn 0 */
    /* USER CODE END W1_HardFault_IRQn 0 */
  }
}

/**
  * @brief This function handles Memory management fault.
  */
void MemManage_Handler(void)
{
  /* USER CODE BEGIN MemoryManagement_IRQn 0 */

  /* USER CODE END MemoryManagement_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_MemoryManagement_IRQn 0 */
    /* USER CODE END W1_MemoryManagement_IRQn 0 */
  }
}

/**
  * @brief This function handles Pre-fetch fault, memory access fault.
  */
void BusFault_Handler(void)
{
  /* USER CODE BEGIN BusFault_IRQn 0 */

  /* USER CODE END BusFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_BusFault_IRQn 0 */
    /* USER CODE END W1_BusFault_IRQn 0 */
  }
}

/**
  * @brief This function handles Undefined instruction or illegal state.
  */
void UsageFault_Handler(void)
{
  /* USER CODE BEGIN UsageFault_IRQn 0 */

  /* USER CODE END UsageFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_UsageFault_IRQn 0 */
    /* USER CODE END W1_UsageFault_IRQn 0 */
  }
}

/**
  * @brief This function handles System service call via SWI instruction.
  */
void SVC_Handler(void)
{
  /* USER CODE BEGIN SVCall_IRQn 0 */

  /* USER CODE END SVCall_IRQn 0 */
  /* USER CODE BEGIN SVCall_IRQn 1 */

  /* USER CODE END SVCall_IRQn 1 */
}

/**
  * @brief This function handles Debug monitor.
  */
void DebugMon_Handler(void)
{
  /* USER CODE BEGIN DebugMonitor_IRQn 0 */

  /* USER CODE END DebugMonitor_IRQn 0 */
  /* USER CODE BEGIN DebugMonitor_IRQn 1 */

  /* USER CODE END DebugMonitor_IRQn 1 */
}

/**
  * @brief This function handles Pendable request for system service.
  */
void PendSV_Handler(void)
{
  /* USER CODE BEGIN PendSV_IRQn 0 */

  /* USER CODE END PendSV_IRQn 0 */
  /* USER CODE BEGIN PendSV_IRQn 1 */

  /* USER CODE END PendSV_IRQn 1 */
}

/**
  * @brief This function handles System tick timer.
  */
void SysTick_Handler(void)
{
  /* USER CODE BEGIN SysTick_IRQn 0 */

  /* USER CODE END SysTick_IRQn 0 */

  /* USER CODE BEGIN SysTick_IRQn 1 */

  /* USER CODE END SysTick_IRQn 1 */
}

/******************************************************************************/
/* STM32H7xx Peripheral Interrupt Handlers                                    */
/* Add here the Interrupt Handlers for the used peripherals.                  */
/* For the available peripheral interrupt handler names,                      */
/* please refer to the startup file (startup_stm32h7xx.s).                    */
/******************************************************************************/

/**
  * @brief This function handles DMA1 stream0 global interrupt.
  */
void DMA1_Stream0_IRQHandler(void)
{
  /* USER CODE BEGIN DMA1_Stream0_IRQn 0 */

  /* USER CODE END DMA1_Stream0_IRQn 0 */
  /* USER CODE BEGIN DMA1_Stream0_IRQn 1 */
  if (LL_DMA_IsActiveFlag_TC0(DMA1)) {
    LL_DMA_ClearFlag_TC0(DMA1);  // 
    //printf_s_d("DMA INT0\r\n");
  }
  if (LL_DMA_IsActiveFlag_TE0(DMA1)) {
    LL_DMA_ClearFlag_TE0(DMA1);  // 
    printf_s_d("DMA ERR0\r\n");
  }
  /* USER CODE END DMA1_Stream0_IRQn 1 */
}

/**
  * @brief This function handles DMA1 stream1 global interrupt.
  */
void DMA1_Stream1_IRQHandler(void)
{
  /* USER CODE BEGIN DMA1_Stream1_IRQn 0 */
  #if __HARDWARE_CONFIG__TJC_RX_ENABLE__ & __HARDWARE_CONFIG__TJC_DMA_ENABLE__ // begin of __HARDWARE_CONFIG__TJC_RX_ENABLE__
    //-----------------------------------------------------------------
    //? DMA1_Stream1_IRQHandler_Func
    //-----------------------------------------------------------------
    //
    // Interrupt Excute Function: Get Received Data 
    // Detected Case: RXNE
    // Returned Value: Received Data
    // Notice: None
    //
    //-----------------------------------------------------------------
    DMA1_Stream1_IRQHandler_Func();
  #endif // end of __HARDWARE_CONFIG__TJC_RX_ENABLE__
  /* USER CODE END DMA1_Stream1_IRQn 0 */
  /* USER CODE BEGIN DMA1_Stream1_IRQn 1 */
  
  /* USER CODE END DMA1_Stream1_IRQn 1 */
}

/**
  * @brief This function handles DMA1 stream2 global interrupt.
  */
void DMA1_Stream2_IRQHandler(void)
{
  /* USER CODE BEGIN DMA1_Stream2_IRQn 0 */
  #if __HARDWARE_CONFIG__DMA_ADC_ENABLE__ // begin of __HARDWARE_CONFIG__DMA_ADC_ENABLE__
    //-----------------------------------------------------------------
    //? DMA1_Stream2_IRQHandler_Func
    //-----------------------------------------------------------------
    //
    // Interrupt Excute Function: ADC
    // Detected Case: ADC DMA Finish
    // Returned Value: None
    // Notice: None
    //
    //-----------------------------------------------------------------
    DMA1_Stream2_IRQHandler_Func();
  #endif // end of __HARDWARE_CONFIG__DMA_ADC_ENABLE__
  /* USER CODE END DMA1_Stream2_IRQn 0 */
  /* USER CODE BEGIN DMA1_Stream2_IRQn 1 */
  
  /* USER CODE END DMA1_Stream2_IRQn 1 */
}

/**
  * @brief This function handles ADC1 and ADC2 global interrupts.
  */
void ADC_IRQHandler(void)
{
  /* USER CODE BEGIN ADC_IRQn 0 */

  /* USER CODE END ADC_IRQn 0 */
  /* USER CODE BEGIN ADC_IRQn 1 */

  /* USER CODE END ADC_IRQn 1 */
}

/**
  * @brief This function handles EXTI line[9:5] interrupts.
  */
void EXTI9_5_IRQHandler(void)
{
  /* USER CODE BEGIN EXTI9_5_IRQn 0 */

  /* USER CODE END EXTI9_5_IRQn 0 */
  if (LL_EXTI_IsActiveFlag_0_31(LL_EXTI_LINE_5) != RESET)
  {
    LL_EXTI_ClearFlag_0_31(LL_EXTI_LINE_5);
    /* USER CODE BEGIN LL_EXTI_LINE_5 */
    #if __HARDWARE_CONFIG__KEY_ENABLE__ // begin of __HARDWARE_CONFIG__KEY_ENABLE__
      //-----------------------------------------------------------------
      //? EXTI5_IRQHandler_KEY_2_DETECT
      //-----------------------------------------------------------------
      //
      // Interrupt Excute Function: Upon KEY_2 pressed, then turn the lighting state of LED.
      // Detected Case: Low state of KEY_2
      // Returned Value: The lighting state of LED 
      // Notice: None
      //
      //-----------------------------------------------------------------
      if (~KEY2_ON){
        LED_TURN();
      }
    #endif // end of __HARDWARE_CONFIG__KEY_ENABLE__

    /* USER CODE END LL_EXTI_LINE_5 */
  }
  /* USER CODE BEGIN EXTI9_5_IRQn 1 */

  /* USER CODE END EXTI9_5_IRQn 1 */
}

/**
  * @brief This function handles TIM2 global interrupt.
  */
void TIM2_IRQHandler(void)
{
  /* USER CODE BEGIN TIM2_IRQn 0 */
  #if __HARDWARE_CONFIG__USER_TIMER2_ENABLE__ & ~__HARDWARE_CONFIG__TJC_DMA_ENABLE__ // begin of __HARDWARE_CONFIG__USER_TIMER2_ENABLE__
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

/**
  * @brief This function handles TIM3 global interrupt.
  */
void TIM3_IRQHandler(void)
{
  /* USER CODE BEGIN TIM3_IRQn 0 */
  #if __HARDWARE_CONFIG__USER_TIMER3_ENABLE__ // begin of __HARDWARE_CONFIG__USER_TIMER3_ENABLE__
    //-----------------------------------------------------------------
    //-----------------------------------------------------------------
    //? TIM3_IRQHandler_Func
    //-----------------------------------------------------------------
    //
    // Interrupt Excute Function: Once TIM3->CNT reached the maximum counter value,
    //                             excute certain function.
    // Detected Case: TIM3 Up Overflow
    // Returned Value: excute certain function
    // Notice: None
    //
    //-----------------------------------------------------------------
    TIM3_IRQHandler_Func();
  #endif // end of __HARDWARE_CONFIG__USER_TIMER3_ENABLE__
  /* USER CODE END TIM3_IRQn 0 */
  /* USER CODE BEGIN TIM3_IRQn 1 */

  /* USER CODE END TIM3_IRQn 1 */
}

/**
  * @brief This function handles TIM4 global interrupt.
  */
void TIM4_IRQHandler(void)
{
  /* USER CODE BEGIN TIM4_IRQn 0 */

  /* USER CODE END TIM4_IRQn 0 */
  /* USER CODE BEGIN TIM4_IRQn 1 */

  /* USER CODE END TIM4_IRQn 1 */
}

/**
  * @brief This function handles TIM7 global interrupt.
  */
void TIM7_IRQHandler(void)
{
  /* USER CODE BEGIN TIM7_IRQn 0 */
  #if __HARDWARE_CONFIG__BSP_TIMER_ENABLE__ // begin of __HARDWARE_CONFIG__BSP_TIMER_ENABLE__
    //-----------------------------------------------------------------
    //-----------------------------------------------------------------
    //? TIM7_IRQHandler_BSP_Timer_UPDATE
    //-----------------------------------------------------------------
    //
    // Interrupt Excute Function: Once TIM7->CNT reached the maximum counter value 0xffff,
    //                             update the BspTimerCnt.
    // Detected Case: TIM7 Up Overflow
    // Returned Value: update BspTimerCnt
    // Notice: None
    //
    //-----------------------------------------------------------------
    Update_SystemTick();
  #endif // end of __HARDWARE_CONFIG__BSP_TIMER_ENABLE__
  /* USER CODE END TIM7_IRQn 0 */
  /* USER CODE BEGIN TIM7_IRQn 1 */

  /* USER CODE END TIM7_IRQn 1 */
}

/**
  * @brief This function handles UART7 global interrupt.
  */
void UART7_IRQHandler(void)
{
  /* USER CODE BEGIN UART7_IRQn 0 */
  /* USER CODE END UART7_IRQn 0 */
  /* USER CODE BEGIN UART7_IRQn 1 */
  #if __HARDWARE_CONFIG__TJC_RX_ENABLE__ // begin of __HARDWARE_CONFIG__TJC_RX_ENABLE__
    //-----------------------------------------------------------------
    //? UART7_IRQHandler_Func
    //-----------------------------------------------------------------
    //
    // Interrupt Excute Function: Get Received Data 
    // Detected Case: RXNE
    // Returned Value: Received Data
    // Notice: None
    //
    //-----------------------------------------------------------------
    UART7_IRQHandler_Func();
  #endif // end of __HARDWARE_CONFIG__TJC_RX_ENABLE__
  /* USER CODE END UART7_IRQn 1 */
}

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */
