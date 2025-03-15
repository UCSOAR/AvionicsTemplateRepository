/*
 * DistributorTask.cpp
 *
 *  Created on: Mar 15, 2025
 *      Author: Local user
 */

/* Includes ------------------------------------------------------------------*/
#include "DistributorTask.hpp"
#include "Command.hpp"
#include "CubeUtils.hpp"
#include <cstring>
#include "SensorDataTypes.hpp"
#include "RateDistributor.hpp"

#include "stm32h7xx_hal.h"

// External Tasks (to send debug commands to)

/* Macros --------------------------------------------------------------------*/

/* Structs -------------------------------------------------------------------*/

/* Constants -----------------------------------------------------------------*/

/* Variables -----------------------------------------------------------------*/

/* Prototypes ----------------------------------------------------------------*/

/* Functions -----------------------------------------------------------------*/
/**
 * @brief Constructor, sets all member variables
 */
DistributorTask::DistributorTask()
    : Task(TASK_DEBUG_QUEUE_DEPTH_OBJS) {
}

/**
 * @brief Init task for RTOS
 */
void DistributorTask::InitTask() {
  // Make sure the task is not already initialized
  SOAR_ASSERT(rtTaskHandle == nullptr, "Cannot initialize Debug task twice");

  // Start the task
  BaseType_t rtValue = xTaskCreate(
      (TaskFunction_t)DistributorTask::RunTask, (const char*)"DistributorTask",
      (uint16_t)TASK_DEBUG_STACK_DEPTH_WORDS, (void*)this,
      (UBaseType_t)TASK_DEBUG_PRIORITY, (TaskHandle_t*)&rtTaskHandle);

  // Ensure creation succeded
  SOAR_ASSERT(rtValue == pdPASS, "DistributorTask::InitTask - xTaskCreate() failed");
}

/**
 *    @brief Runcode for the DistributorTask
 */
void DistributorTask::Run(void* pvParams) {

	RateDistributor<IMUData> imudist;
	imudist.Subscribe(this, 100);
  while (1) {
    Command cm;

    // Wait forever for a command
    qEvtQueue->ReceiveWait(cm);

    // Process the command
    if (cm.GetCommand() == DATA_COMMAND) {
    	// switch command target
    	// pick a rate distirbutor
    	// addsample on it
    }

    cm.Reset();
  }
}

