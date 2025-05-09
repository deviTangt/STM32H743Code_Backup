/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
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
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "stdio.h"
#include "ad9833.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */
int fputc(int ch, FILE *f)
 
{
 
  HAL_UART_Transmit(&huart1, (uint8_t *)&ch, 1, 0xffff);
 
  return ch;
 
}

int fgetc(FILE *f)
{
  uint8_t ch = 0;
  HAL_UART_Receive(&huart1, &ch, 1, 0xffff);
  return ch;
}



/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
uint32_t rx_data[10];
uint32_t buf[1];
int num = 0;
int flag = 0;
int i=0;
struct ADS_Param{
	uint32_t 	freq;
	uint8_t		wave_sel;
	uint16_t	phase;
	uint32_t	sweep_freq_start;
	uint32_t	sweep_freq_end;
	uint32_t	sweep_freq_step;
	uint16_t	sweep_time_step;
	uint8_t		sweep_status;
	uint8_t		sweep_if_consistent;
}ADS_CH0, ADS_CH1;
uint8_t 	mode = 0, mode_pre = 0;
uint32_t 	param_data = 0, param_data_pre = 0;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */



/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
    

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART1_UART_Init();
  /* USER CODE BEGIN 2 */
  //HAL_UART_Receive_IT(&huart1, (uint8_t *)buf, 1);
  /*******************************************************************************************************/
  //printf("10000\n");
	ADS_CH0.freq 				= 40000;
	ADS_CH0.wave_sel 			= SIN_WAVE;
	ADS_CH0.phase 				= 530; 
	ADS_CH0.sweep_freq_start 	= 2000; 
	ADS_CH0.sweep_freq_end 		= 50000; 
	ADS_CH0.sweep_freq_step 	= 400; 
	ADS_CH0.sweep_time_step 	= 100; 
	ADS_CH0.sweep_status		= 0;
	  
	ADS_CH1.freq 				= 60000;
	ADS_CH1.wave_sel 			= TRI_WAVE;
	ADS_CH1.phase 				= 1030; 
	ADS_CH1.sweep_freq_start 	= 4000; 
	ADS_CH1.sweep_freq_end 		= 500000; 
	ADS_CH1.sweep_freq_step 	= 5000; 
	ADS_CH1.sweep_time_step 	= 100; 
	ADS_CH1.sweep_status		= 0;
  
  AD9833_WaveSeting_Double(15000,0,SIN_WAVE,1920);
    //AD9833_WaveSeting_Double(500000,0,SIN_WAVE,1030);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
      //printf("test\r\n");
      /*
      if(flag == 1){
        freq = (rx_data[3]-48)* 1000000 + (rx_data[4]-48)* 100000 + (rx_data[5]-48)* 10000 + (rx_data[6]-48)* 1000 + (rx_data[7]-48)* 100 + (rx_data[8]-48)* 10 + (rx_data[9]-48)* 1;
        AD9833_WaveSeting_Double(500000,0,SIN_WAVE,1030);
        printf("9833,启动!\r\n");
        printf("freq = %d\r\n", freq);
        for(int j = 0; j<100000 ; j++);
        HAL_UART_Receive_IT(&huart1, (uint8_t *)buf, 1);
        flag = 0;
      }*/
      
/*****************************************************************************************************
	  Mode:	0x01 - 设置通道0频率				0.1 hz - 12Mhz
			0x02 - 设置通道0波形 			TRI_WAVE(三角波),SIN_WAVE(正弦波),SQU_WAVE(方波)
			0x03 - 设置通道0相位 			初相位， 调节该值可调整两个波形之间的相位差(并非与360度一比一对应)
			0x04 - 设置通道0扫频初始频率 	0.1 hz - 12Mhz
			0x05 - 设置通道0扫频终止频率		0.1 hz - 12Mhz
			0x06 - 设置通道0扫频步进步长		0.1 hz - 12Mhz
			0x07 - 设置通道0扫频步进间隔		1 - 65535(ms)
			0x08 - 设置通道0切换扫频模式		0 - OFF / 1 - ON	
			
			0x11 - 设置通道1频率				0.1 hz - 12Mhz
			0x12 - 设置通道1波形 			TRI_WAVE(三角波),SIN_WAVE(正弦波),SQU_WAVE(方波)
			0x13 - 设置通道1相位 			初相位， 调节该值可调整两个波形之间的相位差(并非与360度一比一对应)
			0x14 - 设置通道1扫频初始频率 	0.1 hz - 12Mhz
			0x15 - 设置通道1扫频终止频率		0.1 hz - 12Mhz
			0x16 - 设置通道1扫频步进步长		0.1 hz - 12Mhz
			0x17 - 设置通道1扫频步进间隔		1 - 65535(ms)
			0x18 - 设置通道1切换扫频模式		0 - OFF / 1 - ON
******************************************************************************************************/
      //printf("load\r\n");
      //scanf("-%2x-%llu", &mode, &param_data);
	  if (1 || !(mode == mode_pre && param_data == param_data_pre)){
		  mode_pre = mode;
		  param_data_pre = param_data;
		  switch(mode){
			  case(0x01): 	ADS_CH0.freq 				= param_data; break;
			  case(0x02): 	if 		(param_data == 0) ADS_CH0.wave_sel = TRI_WAVE;
							else if (param_data == 1) ADS_CH0.wave_sel = SIN_WAVE;
							else if (param_data == 2) ADS_CH0.wave_sel = SQU_WAVE;
							break;
			  case(0x03): 	ADS_CH0.phase 				= param_data; break;
			  case(0x04): 	ADS_CH0.sweep_freq_start 	= param_data; break;
			  case(0x05): 	ADS_CH0.sweep_freq_end 		= param_data; break;
			  case(0x06): 	ADS_CH0.sweep_freq_step 	= param_data; break;
			  case(0x07): 	ADS_CH0.sweep_time_step 	= (uint16_t)param_data; break;
			  case(0x08): 	ADS_CH0.sweep_status 		= (uint8_t)param_data; break;
			  
			  case(0x11): 	ADS_CH1.freq 				= param_data; break;
			  case(0x12): 	if 		(param_data == 0) ADS_CH1.wave_sel = TRI_WAVE;
							else if (param_data == 1) ADS_CH1.wave_sel = SIN_WAVE;
							else if (param_data == 2) ADS_CH1.wave_sel = SQU_WAVE;
							break;
			  case(0x13): 	ADS_CH1.phase 				= param_data; break;
			  case(0x14): 	ADS_CH1.sweep_freq_start 	= param_data; break;
			  case(0x15): 	ADS_CH1.sweep_freq_end 		= param_data; break;
			  case(0x16): 	ADS_CH1.sweep_freq_step 	= param_data; break;
			  case(0x17): 	ADS_CH1.sweep_time_step 	= (uint16_t)param_data; break;
			  case(0x18): 	ADS_CH1.sweep_status 		= (uint8_t)param_data; break;

			  default:	break;
		  }
		  if 	  (mode / 16 == 0)
				AD9833_WaveSeting(ADS_CH0.freq, 0, ADS_CH0.wave_sel, ADS_CH0.phase, 0);
		  else if (mode / 16 == 1)
				AD9833_WaveSeting(ADS_CH1.freq, 0, ADS_CH1.wave_sel, ADS_CH1.phase, 1);
	  }AD9833_WaveSeting_Double(15000,0,SIN_WAVE,1920);
	  
      //AD9833_WaveSeting_Double(freq,0,SIN_WAVE,1920);
      //printf("freq = %d", freq);
      
  }
      
      
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL8;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart){
    //printf("num = %d", num);
    //rx_data[num++] = buf[0];
    //num = num%10;
    /*
    for(i=0;i<10;i++){
        printf("data[%d] = %d", i, rx_data[i]);
    }
    */
    /*
    printf("recieve num0 %d\r\n",rx_data[0] );
    printf("recieve num1 %d\r\n",rx_data[1] );
    printf("recieve num2 %d\r\n",rx_data[2] );*/
    /*
    if(num>0){
        HAL_UART_Receive_IT(&huart1, (uint8_t *)buf, 1);
        //HAL_UART_Receive_IT(&huart1, (uint8_t *)rx_data, 10);
    }
    else {
        flag = 1;
    }*/
}


/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
