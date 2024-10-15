/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : IWDG.cpp
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
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
#include "SystemDefines.hpp"
#include "IWDGTask.hpp"
#include "stm32h7xx_hal_iwdg.h"

static void MX_IWDG1_Init(void);

int refreshIntervalValue = 4000;
int* refreshInterval = &refreshIntervalValue;
IWDG_HandleTypeDef hiwdg1;

void IWDGTask::InitTask()
{
	MX_IWDG1_Init(); // initialize watchdog

    // Start the task
    BaseType_t rtValue =
        xTaskCreate((TaskFunction_t)IWDGTask::RunTask,
            (const char*)"IWDGTask",
            (uint16_t)TASK_IWDG_STACK_DEPTH_WORDS,
			(void*)&refreshInterval,
            (UBaseType_t)TASK_IWDG_PRIORITY,
            (TaskHandle_t*)&rtTaskHandle);

    //Ensure creation succeeded
    SOAR_ASSERT(rtValue == pdPASS, "IWDGTask::InitTask() - xTaskCreate() failed");
}

void IWDGTask::Run(void * pvParams)
{
    //IWDG Task loop
    while(1) {
    	HAL_IWDG_Refresh(&hiwdg1); // refresh reload counter
    	HAL_Delay(refreshIntervalValue);
    }
}

static void MX_IWDG1_Init(void)
{
  hiwdg1.Instance = IWDG1;
  hiwdg1.Init.Prescaler = IWDG_PRESCALER_256;
  hiwdg1.Init.Window = 4095;
  hiwdg1.Init.Reload = 624;
  if (HAL_IWDG_Init(&hiwdg1) != HAL_OK){
	  HAL_NVIC_SystemReset();
  }
  }
