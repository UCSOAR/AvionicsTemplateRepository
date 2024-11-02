/**
 ******************************************************************************
 * File Name          : IWDGTask.hpp
 * Description        :
 ******************************************************************************
*/
#ifndef IWDG_TASK_HPP_
#define IWDG_TASK_HPP_

/* Includes ------------------------------------------------------------------*/
#include "Task.hpp"
#include "SystemDefines.hpp"


/* Macros/Enums ------------------------------------------------------------*/

/* Class ------------------------------------------------------------------*/
class IWDGTask : public Task
{
public:
    static IWDGTask& Inst() {
        static IWDGTask inst;
        return inst;
    }

    void InitTask();

protected:
    static void RunTask(void* pvParams) { IWDGTask::Inst().Run(pvParams); } // Static Task Interface, passes control to the instance Run();

    void Run(void* pvParams);    // Main run code

    void HandleCommand(Command& cm);
    void HandleRequestCommand(uint16_t taskCommand);

private:
    IWDGTask();                                        // Private constructor
    IWDGTask(const IWDGTask&);                    // Prevent copy-construction
    IWDGTask& operator=(const IWDGTask&);            // Prevent assignment
};

#endif    // IWDG_TASK_HPP_
