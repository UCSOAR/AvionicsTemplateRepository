/*
 * ThermoSubscriberTask.cpp
 *
 *  Created on: Sep 20, 2025
 *      Author: Local user
 */


#include <ThermoSubscriberTask.hpp>

#include "Command.hpp"
#include "CubeUtils.hpp"
#include <cstring>
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
ThermoSubscriberTask::ThermoSubscriberTask()
    : Task(TASK_FAKEBAROTASK_QUEUE_DEPTH_OBJS){

}

/**
 * @brief Init task for RTOS
 */
void ThermoSubscriberTask::InitTask() {
  // Make sure the task is not already initialized
  SOAR_ASSERT(rtTaskHandle == nullptr, "Cannot initialize ThermoSubscriberTaskThermoSubscriberTaskThermoSubscriberTaskThermoSubscriberTask task twice");

  // Start the task
  BaseType_t rtValue = xTaskCreate(
      (TaskFunction_t)ThermoSubscriberTask::RunTask, (const char*)"ThermoSubscriberTask",
      (uint16_t)TASK_FAKEBAROTASK_STACK_DEPTH_WORDS, (void*)this,
      (UBaseType_t)TASK_FAKEBAROTASK_PRIORITY, (TaskHandle_t*)&rtTaskHandle);

  // Ensure creation succeded
  SOAR_ASSERT(rtValue == pdPASS, "ThermoSubscriberTask::InitTask - xTaskCreate() failed");
}

// TODO: Only run thread when appropriate GPIO pin pulled HIGH (or by define)
/**
 *    @brief Runcode for the DebugTask
 */

void ThermoSubscriberTask::Run(void* pvParams) {

//   	auto e = reinterpret_cast<SensorDataBuf<ThermocoupleData>*>(RateBroker::getBufOfType<ThermocoupleData>());

   	RateBroker::Subscribe<ThermocoupleData>(this, 10);

  while (1) {
    Command cm;

    // Wait forever for a command
    qEvtQueue->Receive(cm);

    // Process the command
    if (cm.GetCommand() == DATA_COMMAND) {

    }




    cm.Reset();



  }
}

