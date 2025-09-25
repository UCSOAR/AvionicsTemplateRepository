/*
 * ThermoSubscriberTask.hpp
 *
 *  Created on: Sep 20, 2025
 *      Author: Local user
 */

#ifndef INC_THERMOSUBSCRIBERTASK_HPP_
#define INC_THERMOSUBSCRIBERTASK_HPP_
#include "Task.hpp"

class ThermoSubscriberTask : public Task {
 public:
  static ThermoSubscriberTask& Inst() {
    static ThermoSubscriberTask inst;
    return inst;
  }

  void InitTask();


 protected:
  static void RunTask(void* pvParams) {
	  ThermoSubscriberTask::Inst().Run(pvParams);
  }  // Static Task Interface, passes control to the instance Run();

  void Run(void* pvParams);  // Main run code
  // void HandleCommand(Command& cm);


 private:
  ThermoSubscriberTask();                             // Private constructor
  ThermoSubscriberTask(const ThermoSubscriberTask&);             // Prevent copy-construction
  ThermoSubscriberTask& operator=(const ThermoSubscriberTask&);  // Prevent assignment
};




#endif /* INC_THERMOSUBSCRIBERTASK_HPP_ */
