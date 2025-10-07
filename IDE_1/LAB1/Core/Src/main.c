/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "software_timer.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
TIM_HandleTypeDef htim2;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_TIM2_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
// ================= Exercise 6: Software Timer =================
int timer0_counter = 0;
int timer0_flag = 0;
int TIMER_CYCLE = 10;   // 10ms vì timer interrupt là 10ms

void setTimer0(int duration) {
    timer0_counter = duration / TIMER_CYCLE;
    timer0_flag = 0;
}

void timer_run_0() {
    if (timer0_counter > 0) {
        timer0_counter--;
        if (timer0_counter == 0)
            timer0_flag = 1;
    }
}

const int MAX_LED_MATRIX = 8;
int index_led_matrix = 0;
uint8_t matrix_buffer[8] = {
		 0b00000000,
		 0b00111111,
		 0b01001000,
		 0b10001000,
		 0b10001000,
		 0b01001000,
		 0b00111111,
		 0b00000000
};

void turnOffAllMatrixColumn(){
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_2, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_3, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_10, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_11, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_12, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_13, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_14, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_15, GPIO_PIN_SET);
}

void setMatrixRowData(uint8_t data){
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, !((data >> 7) & 0x1));
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, !((data >> 6) & 0x1));
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10, !((data >> 5) & 0x1));
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_11, !((data >> 4) & 0x1));
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, !((data >> 3) & 0x1));
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, !((data >> 2) & 0x1));
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, !((data >> 1) & 0x1));
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, !((data >> 0) & 0x1));
}
void updateLEDMatrix(int index){
	turnOffAllMatrixColumn();
	setMatrixRowData(matrix_buffer[index]);
	switch (index){
	case 0:
		HAL_GPIO_WritePin(GPIOA,GPIO_PIN_2, RESET);
		break;
	case 1:
		HAL_GPIO_WritePin(GPIOA,GPIO_PIN_3, RESET);
		break;
	case 2:
		HAL_GPIO_WritePin(GPIOA,GPIO_PIN_10, RESET);
		break;
	case 3:
		HAL_GPIO_WritePin(GPIOA,GPIO_PIN_11, RESET);
		break;
	case 4:
		HAL_GPIO_WritePin(GPIOA,GPIO_PIN_12, RESET);
		break;
	case 5:
		HAL_GPIO_WritePin(GPIOA,GPIO_PIN_13, RESET);
		break;
	case 6:
		HAL_GPIO_WritePin(GPIOA,GPIO_PIN_14, RESET);
		break;
	case 7:
		HAL_GPIO_WritePin(GPIOA,GPIO_PIN_15, RESET);
		break;
	default:
		break;
	}
}

void shiftLeftMatrix(){
	uint8_t first_col = matrix_buffer[0];
	for (int i = 0; i < MAX_LED_MATRIX - 1; i++){
		matrix_buffer[i]= matrix_buffer[i+1];
	}
	matrix_buffer[MAX_LED_MATRIX - 1] = first_col;

}
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
  MX_TIM2_Init();
  /* USER CODE BEGIN 2 */
HAL_TIM_Base_Start_IT(&htim2);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
setTimer1(25);
setTimer2(100);
setTimer0(1000);
  while (1)
  {
	  if (timer0_flag == 1)
	  {
	  second ++;
	  if ( second >= 60) {
	   second = 0;
	  minute ++;
	  }
	  if( minute >= 60) {
	  minute = 0;
	 hour ++;
	  }
	  if( hour >=24) {
	  hour = 0;
	  }
	  updateClockBuffer () ;
		HAL_GPIO_TogglePin(RED_GPIO_Port, RED_Pin);
		HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_4);
 	  setTimer0(1000); // reset lại timer 1s
 	  shiftLeftMatrix();
     }

		if(timer1_flag ==1){
			setTimer1(25);
		    update7SEG(index_led);
		    index_led++;
		    if (index_led >= MAX_LED) index_led = 0; // quay lại 0
				  }

		if (timer2_flag == 1) {
		        setTimer2(25); // thời gian quét 10ms (100Hz)
		        updateLEDMatrix(index_led_matrix);
		        index_led_matrix++;
		        if (index_led_matrix >= 8)
		            index_led_matrix = 0;
		    }





    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
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
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief TIM2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM2_Init(void)
{

  /* USER CODE BEGIN TIM2_Init 0 */

  /* USER CODE END TIM2_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM2_Init 1 */

  /* USER CODE END TIM2_Init 1 */
  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 7999;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 9;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM2_Init 2 */

  /* USER CODE END TIM2_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  /* USER CODE BEGIN MX_GPIO_Init_1 */

  /* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4|RED_Pin
                          |GPIO_PIN_6|GPIO_PIN_7|GPIO_PIN_8|GPIO_PIN_9
                          |GPIO_PIN_10|GPIO_PIN_11|GPIO_PIN_12|GPIO_PIN_13
                          |GPIO_PIN_14|GPIO_PIN_15, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_10
                          |GPIO_PIN_11|GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14
                          |GPIO_PIN_15|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5
                          |GPIO_PIN_6|GPIO_PIN_8|GPIO_PIN_9, GPIO_PIN_RESET);

  /*Configure GPIO pins : PA2 PA3 PA4 RED_Pin
                           PA6 PA7 PA8 PA9
                           PA10 PA11 PA12 PA13
                           PA14 PA15 */
  GPIO_InitStruct.Pin = GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4|RED_Pin
                          |GPIO_PIN_6|GPIO_PIN_7|GPIO_PIN_8|GPIO_PIN_9
                          |GPIO_PIN_10|GPIO_PIN_11|GPIO_PIN_12|GPIO_PIN_13
                          |GPIO_PIN_14|GPIO_PIN_15;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : PB0 PB1 PB2 PB10
                           PB11 PB12 PB13 PB14
                           PB15 PB3 PB4 PB5
                           PB6 PB8 PB9 */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_10
                          |GPIO_PIN_11|GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14
                          |GPIO_PIN_15|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5
                          |GPIO_PIN_6|GPIO_PIN_8|GPIO_PIN_9;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /* USER CODE BEGIN MX_GPIO_Init_2 */

  /* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){
	timerRun();
	 timer_run_0();

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
#ifdef USE_FULL_ASSERT
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
