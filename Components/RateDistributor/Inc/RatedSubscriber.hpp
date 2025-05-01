/*
 * RatedSubscriber.hpp
 *
 *  Created on: Mar 15, 2025
 *      Author: Local user
 */

#ifndef INC_RATEDSUBSCRIBER_HPP_
#define INC_RATEDSUBSCRIBER_HPP_

#include "Subscriber.hpp"
#include "RateBroker.hpp"
#include "RatedBuf.hpp"

class RatedSubscriber : public Subscriber {
public:



	RatedSubscriber(TimerHandle_t timer, uint8_t* buf, uint8_t sizeOfSingleData) : timer(timer), buf(buf), sizeOfSingleData(sizeOfSingleData){

	}

	const uint8_t* getBuf() const {
		return buf;
	}

	uint8_t getSizeOfSingleData() const {
		return sizeOfSingleData;
	}

private:

	TimerHandle_t timer = nullptr;
	const uint8_t* buf = nullptr;
	const uint8_t sizeOfSingleData = 0;


};


#endif /* INC_RATEDSUBSCRIBER_HPP_ */
