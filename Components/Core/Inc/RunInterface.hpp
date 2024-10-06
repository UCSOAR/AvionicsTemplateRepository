/*
 * RunInterface.hpp
 *
 *  Created on: Apr 3, 2023
 *      Author: Chris (cjchanx)
 */

#ifndef C__IFACE_HPP_
#define C__IFACE_HPP_

/**
 * @brief Interface to run the C++ codebase in the C compiler
 */
void run_interface();

/**
 * @brief Interrupt Routing for the UART driver
 */
void cpp_UART8_IRQHandler();

#endif /* C__IFACE_HPP_ */
