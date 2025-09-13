/**
 ********************************************************************************
 * @file    FSBProtocolTask.cpp
 * @author  jaddina
 * @date    Sep 13, 2025
 * @brief
 ********************************************************************************
 */

/************************************
 * INCLUDES
 ************************************/
#include "FSBProtocolTask.hpp"
#include "SystemDefines.hpp"
#include "Command.hpp"
#include "stm32h7xx_hal.h"
#include "DataBroker.hpp"
#include "Task.hpp"
/************************************
 * PRIVATE MACROS AND DEFINES
 ************************************/

/************************************
 * VARIABLES
 ************************************/

/************************************
 * FUNCTION DECLARATIONS
 ************************************/



/************************************
 * FUNCTION DEFINITIONS
 ************************************/
FSBProtocolTask::FSBProtocolTask():Task(TASK_FSB_PROTOCOL_QUEUE_DEPTH_OBJS)
{

}

/**
 * @brief Initialize the FSBProtocolTask
 *        Do not modify this function aside from adding the task name
 */
void FSBProtocolTask::InitTask()
{
    // Make sure the task is not already initialized
    SOAR_ASSERT(rtTaskHandle == nullptr, "Cannot initialize watchdog task twice");

    BaseType_t rtValue =
        xTaskCreate((TaskFunction_t)FSBProtocolTask::RunTask,
            (const char*)"FSBProtocolTask",
            (uint16_t)TASK_FSB_PROTOCOL_STACK_DEPTH_WORDS,
            (void*)this,
            (UBaseType_t)TASK_FSB_PROTOCOL_DEPTH_WORD,
            (TaskHandle_t*)&rtTaskHandle);

                SOAR_ASSERT(rtValue == pdPASS, "FSBProtocolTask::InitTask() - xTaskCreate() failed");
}

void FSBProtocolTask::HandleCommand(Data test){

	//Checks for Data type
	switch (test.testEnum){

	case PRESSURE_DATA:
		PressureData testing;
		testing.pressure = 100; //random number to mimic data from test
		DataBroker::Publish<PressureData>(&testing);
		break;

	case IMU_DATA:
		IMUData testing;
		testing.accelX = 5;
		testing.accelY = 10;
		testing.accelZ = 15;
		DataBroker::Publish<IMUData>(&testing);
		break;


	case THERMOCOUPLE_DATA:
		ThermocoupleData testing;
		testing.temperature = 100;
		DataBroker::Publish<ThermocoupleData>(&testing);
		break;
	}

}


