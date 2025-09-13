/**
 ********************************************************************************
 * @file    ${file_name}
 * @author  ${user}
 * @date    ${date}
 * @brief   This is a template header file to create a new task in our firmware
 * 
 * Setup Steps
 * 1. Define the Task Queue Depth in SystemDefines.hpp
 * 2. Define the Task Stack Depth in SystemDefines.hpp
 * 3. Define the Task Priority in SystemDefines.hpp
 * 4. Replace all placeholders marked with a $ sign
 ********************************************************************************
 */

 #ifndef CCENTER_TASK_HPP_
 #define CCENTER_TASK_HPP_
 
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
 class CommandCenterTask : public Task
 {
 public:
     static CommandCenterTask& Inst() {
         static CommandCenterTask inst;
         return inst;
     }
 
     void InitTask();
 
 protected:
     static void RunTask(void* pvParams) { CommandCenterTask::Inst().Run(pvParams); } // Static Task Interface, passes control to the instance Run();
     void Run(void * pvParams); // Main run code
     void HandleCommand(Command& cm);
 
 private:
     // Private Functions
     CommandCenterTask();        // Private constructor
     CommandCenterTask(const CommandCenterTask&);                        // Prevent copy-construction
     CommandCenterTask& operator=(const CommandCenterTask&);            // Prevent assignment
     std::vector<DaughterBoard> activeBoards;                                //list of all active daughterboards
 };
 
 /************************************
  * FUNCTION DECLARATIONS
  ************************************/
 
 #endif /* ${include_guard_symbol} */