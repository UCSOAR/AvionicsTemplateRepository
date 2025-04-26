/*
 * RateBroker.hpp
 *
 *  Created on: Mar 29, 2025
 *      Author: Local user
 */

#ifndef INC_RATEBROKER_HPP_
#define INC_RATEBROKER_HPP_

#include <DataBroker.hpp>

#define RATEBUFSIZE 300

template <typename T>
struct SensorDataBuf {
	T data[RATEBUFSIZE];
	uint32_t num;
};

#define big 10

class RateBroker : public DataBroker {

	  /**
	   * @brief Publish data of a certain type. Note that for a rated broker, this will not
	   * immediately send to every subscriber. Each subscriber will be sent the data at the rate they request it.
	   *         NOTE: You must ensure that there is a publisher for that type
	   */
	  template <typename T>
	  static void Publish(T* dataToPublish) {
		SensorDataBuf<T>* buf = nullptr;

		if(matchType<T,IMUData>) {
			buf = imubuf;
		} else if(matchType<T,ThermocoupleData>) {
			buf = thermbuf;
		} else {
			SOAR_ASSERT(false,"that type does NOT exist.......");
			return;
		}


		(static_cast<T*>(buf->data))[buf->num] = dataToPublish;
		buf->num++;
		if(buf->num >= RATEBUFSIZE) { // bad cycle NO!!! TODO!!!!!!!!!!!! CIRCCUCLKARRAE BUFFFFER!!!!!!!!!!!
			buf->num= 0;
		}
	  }

	  template <typename T>
	  static void Subscribe(Task* taskToSubscribe, uint32_t rate) {
	    SOAR_PRINT("YEAH!!!!!!!!!!!!!!!!!! RATES!!!!!!!!!!!!!!");
	    if(numSubs >= big) {
	    	return;
	    }
	    //DataBroker::Subscribe<T>(taskToSubscribe);
	    char timername[16];
	    snprintf(timername,sizeof(timername),"ratetimer%d",numSubs);
	    TimerHandle_t newTimer = xTimerCreate(timername, rate, true, taskToSubscribe, RateBroker::TimerCallback);
	    if(newTimer == nullptr) {
	    	SOAR_PRINT("Could not add new subscriber timer\n");
	    	return;
	    }

	    timers[numSubs] = newTimer;
	    numSubs++;

	  }


	  static void TimerCallback(TimerHandle_t timer) {

	  }

private:
	  static TimerHandle_t timers[big];
	  static uint32_t numSubs;

	  static SensorDataBuf<IMUData> imubuf;

	  static SensorDataBuf<ThermocoupleData> thermbuf;
};


#endif /* INC_RATEBROKER_HPP_ */
