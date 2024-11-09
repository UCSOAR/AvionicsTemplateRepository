/**
 ********************************************************************************
 * @file    IWDGTask.hpp
 * @author  Christy
 * @date    Nov 9, 2024
 * @brief
 ********************************************************************************
 */

#ifndef IWDGTASK_HPP_
#define IWDGTASK_HPP_

/************************************
 * INCLUDES
 ************************************/
#include "Task.hpp"
#include "SystemDefines.hpp"
/************************************
 * MACROS AND DEFINES
 ************************************/

/************************************
 * TYPEDEFS
 ************************************/

/************************************
 * CLASS DEFINITIONS
 ************************************/
class IWDGTask : public Task {
 public:
  static IWDGTask& Inst() {
    static IWDGTask inst;
    return inst;
  }

  void InitTask();

  void InitIWDG();

 protected:
  static void RunTask(void* pvParams) {
    IWDGTask::Inst().Run(pvParams);
  }  // Static Task Interface, passes control to the instance Run();

  void Run(void* pvParams);  // Main run code

  void HandleCommand(Command& cm);
  void HandleRequestCommand(uint16_t taskCommand);

 private:
  IWDGTask();                            // Private constructor
  IWDGTask(const IWDGTask&);             // Prevent copy-construction
  IWDGTask& operator=(const IWDGTask&);  // Prevent assignment
};
/************************************
 * FUNCTION DECLARATIONS
 ************************************/

#endif /* IWDGTASK_HPP_ */
