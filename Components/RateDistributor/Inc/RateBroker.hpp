/*
 * RateBroker.hpp
 *
 *  Created on: Mar 29, 2025
 *      Author: Local user
 */

#ifndef INC_RATEBROKER_HPP_
#define INC_RATEBROKER_HPP_

#include "DataBroker.hpp"
#include "RatedSubscriber.hpp"
#include "RatedBuf.hpp"

#define big 16


class RateBroker : public DataBroker {

public:
	template <typename T>
	static SensorDataBufBase* getBufOfType() {
		if(std::is_same<T,IMUData>()) {
			return &imubuf;
		} else if(std::is_same<T,ThermocoupleData>()) {
			return &thermbuf;
		} else {
			SOAR_ASSERT(false,"that type does NOT exist.......");
			return nullptr;
		}
	}



	  /**
	   * @brief Publish data of a certain type. Note that for a rated broker, this will not
	   * immediately send to every subscriber. Each subscriber will be sent the data at the rate they request it.
	   *         NOTE: You must ensure that there is a publisher for that type
	   */
	  template <typename T>
	  static void Publish(T* dataToPublish) {
		//SensorDataBuf<T>* buf = getBufOfType<T>();


		//(static_cast<T*>(buf->data))[buf->num] = dataToPublish;
		static_cast<SensorDataBuf<T>*>(getBufOfType<T>())->addElement(dataToPublish);

//		if(buf->num >= RATEBUFSIZE-1) { // bad cycle NO!!! TODO!!!!!!!!!!!! CIRCCUCLKARRAE BUFFFFER!!!!!!!!!!!
//			buf->num= 0;
//		} else {
//			buf->num++;
//		}
	  }

	  template <typename T>
	  static void Subscribe(Task* taskToSubscribe, uint32_t rate) {
	    SOAR_PRINT("YEAH!!!!!!!!!!!!!!!!!! RATES!!!!!!!!!!!!!! SUBSCRIBCEE!!!!!!!!!!!!!	");
	    if(numSubs >= big) {
	    	return;
	    }
	    //DataBroker::Subscribe<T>(taskToSubscribe);
	    char timername[16];
	    snprintf(timername,sizeof(timername),"ratetimer%lu",numSubs);
	    TimerHandle_t newTimer = xTimerCreate(timername, rate, true, &subs[numSubs], RateBroker::TimerCallback<T>);
	    if(newTimer == nullptr) {
	    	SOAR_PRINT("Could not add new subscriber timer\n");
	    	return;
	    }

	    //timers[numSubs] = newTimer;
	    //SensorDataBuf<T>* buf = reinterpret_cast<SensorDataBuf<T>*>(getBufOfType<T>());
	    subs[numSubs] = RatedSubscriber(newTimer);
	    numSubs++;
	    xTimerStart(newTimer,0);

	  }




private:
	  static RatedSubscriber subs[big];
	  static uint32_t numSubs;

	  static SensorDataBuf<IMUData> imubuf;

	  static SensorDataBuf<ThermocoupleData> thermbuf;

	  template <typename T>
	  static void TimerCallback(TimerHandle_t timer) {
		  RatedSubscriber* thisSub = static_cast<RatedSubscriber*>(pvTimerGetTimerID(timer));

		  //SensorDataBuf buf;
		  Command dataCmd;

		  // rcurrently sends most recent, TODO: moving average
		  // also, race condition? what if access while num updating?
		  T last = reinterpret_cast<SensorDataBuf<T>*>(getBufOfType<T>())->getLast();
		  dataCmd.CopyDataToCommand((uint8_t*)&last,sizeof(T));
		  thisSub->getSubscriberQueueHandle()->Send(dataCmd, false);
	  }
};

#endif /* INC_RATEBROKER_HPP_ */
