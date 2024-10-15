/**
 *******************************************************************************
 * @file           : IWDGTask.hpp
 *******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "Task.hpp"
#include "SystemDefines.hpp"

class IWDGTask : public Task {
public:
    static IWDGTask& Inst() {
        static IWDGTask inst;
        return inst;
    }

    void InitTask();

protected:
    static void RunTask(void* pvParams) { IWDGTask::Inst().Run(pvParams); }

    void Run(void* pvParams);

private:
    IWDGTask() : Task(TASK_IWDG_QUEUE_DEPTH_OBJS) {}
};

