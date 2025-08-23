/**
 ******************************************************************************
 * File Name          : DebugTask.cpp
 * Description        : Task for controlling debug input
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include <CANTestTasks/Inc/DaughterTask.hpp>

#include <CanAutoNodeDaughter.hpp>
#include <CanAutoNodeMotherboard.hpp>
#include "Command.hpp"
#include "CubeUtils.hpp"
#include <cstring>

#include "stm32h7xx_hal.h"
#include "main.h"

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
DaughterTask::DaughterTask()
    : Task(TASK_DEBUG_QUEUE_DEPTH_OBJS){

}

/**
 * @brief Init task for RTOS
 */
void DaughterTask::InitTask() {
  // Make sure the task is not already initialized
  SOAR_ASSERT(rtTaskHandle == nullptr, "Cannot initialize Debug task twice");

  // Start the task
  BaseType_t rtValue = xTaskCreate(
      (TaskFunction_t)DaughterTask::RunTask, (const char*)"MotherboardTask",
      (uint16_t)TASK_DEBUG_STACK_DEPTH_WORDS, (void*)this,
      (UBaseType_t)TASK_DEBUG_PRIORITY, (TaskHandle_t*)&rtTaskHandle);

  // Ensure creation succeded
  SOAR_ASSERT(rtValue == pdPASS, "DebugTask::InitTask - xTaskCreate() failed");
}

// TODO: Only run thread when appropriate GPIO pin pulled HIGH (or by define)
/**
 *    @brief Runcode for the DebugTask
 */
void DaughterTask::Run(void* pvParams) {

	CanAutoNodeDaughter::LogInit logs[] = {8,5,3};
  CanAutoNodeDaughter candau(&hfdcan1,logs,sizeof(logs)/sizeof(CanAutoNodeDaughter::LogInit),123,234,"hammond");

  SOAR_PRINT("CAN Daughter (Unique ID: ");
#ifdef CANAUTONODEDEBUG
  CanAutoNode::UniqueBoardID id = candau.GetThisBoardUniqueID();
  CanAutoNode::PrintBoardID(id);
#else
  SOAR_PRINT("[CANAUTONODEDEBUG not specified]");
#endif
  SOAR_PRINT(")\nJoining network...\n");

  if(candau.TryRequestingJoiningNetwork()) {
	  SOAR_PRINT("successfully joined network!!!!!!!!!!!!!!\n");
  } else {
	  SOAR_PRINT("FAILED!!!!!!!!!!!\n");
  }
  while (1) {
    Command cm;

    qEvtQueue->Receive(cm);

    // Process the command
    if(candau.CheckCANCommands()) {

    }


    cm.Reset();
  }
}

