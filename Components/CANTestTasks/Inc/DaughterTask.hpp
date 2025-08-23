/**
 ******************************************************************************
 * File Name          : DebugTask.hpp
 * Description        :
 ******************************************************************************
 */
#ifndef CUBE_SYSTEM_MOTHERBOARD_TASK_HPP_
#define CUBE_SYSTEM_MOTHERBOARD_TASK_HPP_
/* Includes ------------------------------------------------------------------*/
#include "Task.hpp"
#include "SystemDefines.hpp"
#include "UARTDriver.hpp"

/* Enums ------------------------------------------------------------------*/

/* Macros ------------------------------------------------------------------*/

/* Class ------------------------------------------------------------------*/
class DaughterTask : public Task {
 public:
  static DaughterTask& Inst() {
    static DaughterTask inst;
    return inst;
  }

  void InitTask();

 protected:
  static void RunTask(void* pvParams) {
	  DaughterTask::Inst().Run(pvParams);
  }  // Static Task Interface, passes control to the instance Run();

  void Run(void* pvParams);  // Main run code

 private:
  DaughterTask();                             // Private constructor
  DaughterTask(const DaughterTask&);             // Prevent copy-construction
  DaughterTask& operator=(const DaughterTask&);  // Prevent assignment
};

#endif  // CUBE_SYSTEM_DEBUG_TASK_HPP_
