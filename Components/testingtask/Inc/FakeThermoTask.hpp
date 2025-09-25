/**
 ******************************************************************************
 * File Name          : DebugTask.hpp
 * Description        :
 ******************************************************************************
 */
#ifndef FAKE_BARO_TASK_HPP_
#define FAKE_BARO_TASK_HPP_
/* Includes ------------------------------------------------------------------*/
#include "Task.hpp"
#include "SystemDefines.hpp"

/* Enums ------------------------------------------------------------------*/

/* Macros ------------------------------------------------------------------*/

/* Class ------------------------------------------------------------------*/
class FakeThermoTask : public Task {
 public:
  static FakeThermoTask& Inst() {
    static FakeThermoTask inst;
    return inst;
  }

  void InitTask();


 protected:
  static void RunTask(void* pvParams) {
	  FakeThermoTask::Inst().Run(pvParams);
  }  // Static Task Interface, passes control to the instance Run();

  void Run(void* pvParams);  // Main run code
  // void HandleCommand(Command& cm);


 private:
  FakeThermoTask();                             // Private constructor
  FakeThermoTask(const FakeThermoTask&);             // Prevent copy-construction
  FakeThermoTask& operator=(const FakeThermoTask&);  // Prevent assignment
};

#endif  // CUBE_SYSTEM_DEBUG_TASK_HPP_
