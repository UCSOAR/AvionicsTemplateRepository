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

#ifndef ${include_guard_symbol}
#define ${include_guard_symbol}

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
class ${TaskName} : public Task
{
public:
    static ${TaskName}& Inst() {
        static ${TaskName} inst;
        return inst;
    }

    void InitTask();

protected:
    static void RunTask(void* pvParams) { ${TaskName}::Inst().Run(pvParams); } // Static Task Interface, passes control to the instance Run();
    void Run(void * pvParams); // Main run code
    void HandleCommand(Command& cm);

private:
    // Private Functions
    ${TaskName}();        // Private constructor
    ${TaskName}(const ${TaskName}&);                        // Prevent copy-construction
    ${TaskName}& operator=(const ${TaskName}&);            // Prevent assignment
};

/************************************
 * FUNCTION DECLARATIONS
 ************************************/

#endif /* ${include_guard_symbol} */
