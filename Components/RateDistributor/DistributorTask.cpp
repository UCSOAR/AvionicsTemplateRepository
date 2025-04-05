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
#include "DataBrokerMessageTypes.hpp"
#include "RateBroker.hpp"
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
	imudist.Subscribe(this, 100); // just for testing, no point in doing this

	RateDistributor<ThermocoupleData> thermo;


  while (1) {
    Command cm;

    // Wait forever for a command
    qEvtQueue->ReceiveWait(cm);

    // Process the command
    // We have received a sensor task
    if (cm.GetCommand() == DATA_BROKER_COMMAND) {
    	// switch command target

    	switch(static_cast<DataBrokerMessageTypes>(cm.GetTaskCommand())) {

    	case DataBrokerMessageTypes::IMU_DATA:
    		imudist.AddSample(*(IMUData*)(cm.GetDataPointer()));
    		break;

    	case DataBrokerMessageTypes::THERMOCOUPLE_DATA:
    		thermo.AddSample(*(ThermocoupleData*)(cm.GetDataPointer()));
    		break;

    	default:
    		break;
    	}
    }

    cm.Reset();
  }
}

