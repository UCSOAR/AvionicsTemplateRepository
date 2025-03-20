/*
 * RatedSubscriber.hpp
 *
 *  Created on: Mar 15, 2025
 *      Author: Local user
 */

#ifndef INC_RATEDSUBSCRIBER_HPP_
#define INC_RATEDSUBSCRIBER_HPP_

#include "Subscriber.hpp"

class RatedSubscriber {
public:

	RatedSubscriber(Subscriber subscriber, uint16_t msPerRequest, RatedSubscriber* subscriberID, TimerCallbackFunction_t callback, uint32_t dataSize, void* dataArray)
	: msPerRequest(msPerRequest), subscriber(subscriber), dataSize(dataSize), dataArray(dataArray) {
		timer = xTimerCreate("ratetimer", msPerRequest, pdTRUE, (void*)subscriberID, callback);
		xTimerStart(timer,0);

	}

	RatedSubscriber()
	: msPerRequest(0), subscriber(), dataSize(0)
	{

	}

	const uint16_t getMsPerRequest() const {
		return msPerRequest;
	}

	Subscriber& getSubscriber() {
		return subscriber;
	}

	void operator=(const RatedSubscriber& other) {
		this->msPerRequest = other.msPerRequest;
		subscriber = other.subscriber;
		xTimerDelete(this->timer,0);
		this->timer = other.timer;

	}

	const uint32_t getDataSize() const {
		return dataSize;
	}

	void* getDataArray() const {
		return dataArray;
	}

private:

	uint16_t msPerRequest;
	Subscriber subscriber;

	TimerHandle_t timer;

	const uint32_t dataSize;
	void* dataArray;


};


#endif /* INC_RATEDSUBSCRIBER_HPP_ */
