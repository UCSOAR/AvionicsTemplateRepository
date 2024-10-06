/*
 *  RunInterface.cpp
 *
 *  Created on: Apr 3, 2023
 *      Author: Chris (cjchanx)
 */

#include "UARTDriver.hpp"
#include "main_avionics.hpp"

extern "C" {
void run_interface() { run_main(); }

void cpp_UART8_IRQHandler() { Driver::uart8.HandleIRQ_UART(); }
}
