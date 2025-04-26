/*
 * RatedSubscriber.hpp
 *
 *  Created on: Mar 15, 2025
 *      Author: Local user
 */

#ifndef INC_RATEDSUBSCRIBER_HPP_
#define INC_RATEDSUBSCRIBER_HPP_

#include "Subscriber.hpp"

class RatedSubscriber : public Subscriber {
public:


	RatedSubscriber()
	{

	}



private:

	TimerHandle_t timer;


};


#endif /* INC_RATEDSUBSCRIBER_HPP_ */
