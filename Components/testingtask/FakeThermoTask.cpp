/**
 ******************************************************************************
 * File Name          : DebugTask.cpp
 * Description        : Task for controlling debug input
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include <FakeThermoTask.hpp>

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
FakeThermoTask::FakeThermoTask()
    : Task(TASK_FAKEBAROTASK_QUEUE_DEPTH_OBJS){

}

/**
 * @brief Init task for RTOS
 */
void FakeThermoTask::InitTask() {
  // Make sure the task is not already initialized
  SOAR_ASSERT(rtTaskHandle == nullptr, "Cannot initialize FakeBaroTaskFakeBaroTaskFakeBaroTaskFakeBaroTaskFakeBaroTaskFakeBaroTaskFakeBaroTask task twice");

  // Start the task
  BaseType_t rtValue = xTaskCreate(
      (TaskFunction_t)FakeThermoTask::RunTask, (const char*)"FakeBaroTask",
      (uint16_t)TASK_FAKEBAROTASK_STACK_DEPTH_WORDS, (void*)this,
      (UBaseType_t)TASK_FAKEBAROTASK_PRIORITY, (TaskHandle_t*)&rtTaskHandle);

  // Ensure creation succeded
  SOAR_ASSERT(rtValue == pdPASS, "FakeBaroTask::InitTask - xTaskCreate() failed");
}

// TODO: Only run thread when appropriate GPIO pin pulled HIGH (or by define)
/**
 *    @brief Runcode for the DebugTask
 */

int32_t temp = 0;
void FakeThermoTask::Run(void* pvParams) {


  while (1) {
    Command cm;

    // Wait forever for a command
    qEvtQueue->Receive(cm);

    // Process the command
    if (cm.GetCommand() == DATA_COMMAND) {

    }

   	//auto e = reinterpret_cast<SensorDataBuf<ThermocoupleData>*>(RateBroker::getBufOfType<ThermocoupleData>());

   	ThermocoupleData testData = {.temperature = temp++};
   	//e->addElement(&testData);
   	RateBroker::Publish(&testData);

   	HAL_Delay(1);

    cm.Reset();



  }
}
