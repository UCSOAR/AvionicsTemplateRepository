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

        Command brokerData(DATA_BROKER_COMMAND);

        uint8_t* messsageData = reinterpret_cast<uint8_t*>(subs->getDataArray());

        // copy data to command
        brokerData.CopyDataToCommand(messsageData, subs->getDataSize());

        subs->getSubscriber().getSubscriberQueueHandle()->Send(brokerData);


	}

template <typename T>
class RateDistributor {
public:

	bool Subscribe(Task* subscriber, uint16_t msPerRequest) {
		SOAR_ASSERT(numRatedSubs < MAX_RATED_SUBSCRIBERS, "Too many subscribers");

		ratedsubs[numRatedSubs] = RatedSubscriber{Subscriber(),msPerRequest,&ratedsubs[numRatedSubs],RatedCallback,sizeof(T),&rawsamples};
		ratedsubs[numRatedSubs].getSubscriber().Init(subscriber);
		numRatedSubs++;

		return true;
	}

	void AddSample(T& sample) {
		SOAR_ASSERT(numSamples < MAX_RAW_SAMPLES,"Too many samples. todo: circular buffer");

		rawsamples[numSamples] = sample;
		numSamples++;
	}

private:

	RatedSubscriber ratedsubs[MAX_RATED_SUBSCRIBERS];
	uint16_t numRatedSubs = 0;
	T rawsamples[MAX_RAW_SAMPLES];
	uint32_t numSamples;

};


#endif /* INC_RATEDISTRIBUTOR_HPP_ */
