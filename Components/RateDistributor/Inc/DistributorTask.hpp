/*
 * DistributorTask.hpp
 *
 *  Created on: Mar 15, 2025
 *      Author: Local user
 */

#ifndef DISTRIBUTORTASK_HPP_
#define DISTRIBUTORTASK_HPP_

/* Includes ------------------------------------------------------------------*/
#include "Task.hpp"
#include "SystemDefines.hpp"
#include "UARTDriver.hpp"

/* Enums ------------------------------------------------------------------*/
enum DEBUG_TASK_COMMANDS {
  DEBUG_TASK_COMMAND_NONE = 0,
  EVENT_DEBUG_RX_COMPLETE
};

/* Macros ------------------------------------------------------------------*/
constexpr uint16_t DEBUG_RX_BUFFER_SZ_BYTES = 16;

/* Class ------------------------------------------------------------------*/
class DistributorTask : public Task {
 public:
  static DistributorTask& Inst() {
    static DistributorTask inst;
    return inst;
  }

  void InitTask();

 protected:
  static void RunTask(void* pvParams) {
    DistributorTask::Inst().Run(pvParams);
  }  // Static Task Interface, passes control to the instance Run();

  void Run(void* pvParams);  // Main run code


 private:
  DistributorTask();                             // Private constructor
  DistributorTask(const DistributorTask&);             // Prevent copy-construction
  DistributorTask& operator=(const DistributorTask&);  // Prevent assignment
};


#endif /* DISTRIBUTORTASK_HPP_ */
