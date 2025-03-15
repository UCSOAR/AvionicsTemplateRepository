/*
 * RateDistributor.hpp
 *
 *  Created on: Mar 15, 2025
 *      Author: Local user
 */

#ifndef INC_RATEDISTRIBUTOR_HPP_
#define INC_RATEDISTRIBUTOR_HPP_

#define MAX_RATED_SUBSCRIBERS 10
#define MAX_RAW_SAMPLES 1000
#include <RatedSubscriber.hpp>

	// is called by a rated subscriber when it wants a sample
	void RatedCallback(TimerHandle_t timer) {

		RatedSubscriber* subs = static_cast<RatedSubscriber*>(pvTimerGetTimerID(timer));
	}

template <typename T>
class RateDistributor {
public:

	bool Subscribe(Task* subscriber, uint16_t msPerRequest) {
		SOAR_ASSERT(numRatedSubs < MAX_RATED_SUBSCRIBERS, "Too many subscribers");

		ratedsubs[numRatedSubs] = RatedSubscriber{Subscriber(),msPerRequest,&ratedsubs[numRatedSubs],RatedCallback};
		ratedsubs[numRatedSubs].getSubscriber().Init(subscriber);
		numRatedSubs++;

		return true;
	}

	void AddSample(T& sample) {
		rawsamples[0] = sample; // todo
	}

private:

	RatedSubscriber ratedsubs[MAX_RATED_SUBSCRIBERS];
	uint16_t numRatedSubs = 0;
	T rawsamples[MAX_RAW_SAMPLES];

};


#endif /* INC_RATEDISTRIBUTOR_HPP_ */
