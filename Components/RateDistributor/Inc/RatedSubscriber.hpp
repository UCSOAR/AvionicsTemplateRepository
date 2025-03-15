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

	RatedSubscriber(Subscriber subscriber, uint16_t msPerRequest, RatedSubscriber* subscriberID, TimerCallbackFunction_t callback)
	: msPerRequest(msPerRequest), subscriber(subscriber) {
		timer = xTimerCreate("ratetimer", msPerRequest, pdTRUE, (void*)subscriberID, callback);
		xTimerStart(timer,0);

	}

	RatedSubscriber()
	: msPerRequest(0), subscriber()
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

private:

	uint16_t msPerRequest;
	Subscriber subscriber;

	TimerHandle_t timer;


};


#endif /* INC_RATEDSUBSCRIBER_HPP_ */
