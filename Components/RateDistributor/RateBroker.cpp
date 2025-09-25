/*
 * RateBroker.cpp
 *
 *  Created on: Apr 5, 2025
 *      Author: Local user
 */




#include "RateBroker.hpp"

uint32_t RateBroker::numSubs = 0;

RatedSubscriber RateBroker::subs[];

SensorDataBuf<IMUData> RateBroker::imubuf;

SensorDataBuf<ThermocoupleData> RateBroker::thermbuf;
