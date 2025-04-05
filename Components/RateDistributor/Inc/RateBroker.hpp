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

class RateBroker : public DataBroker {

	  /**
	   * @brief Publish data of a certain type. Note that for a rated broker, this will not
	   * immediately send to every subscriber. Each subscriber will be sent the data at the rate they request it.
	   *         NOTE: You must ensure that there is a publisher for that type
	   */
	  template <typename T>
	  static void Publish(T* dataToPublish) {
		void* buf = nullptr;
		uint32_t* num = nullptr;

		if(matchType<T,IMUData>) {
			buf = imubuf;
			num = &imunum;
		} else if(matchType<T,ThermocoupleData>) {
			buf = tcbuf;
			num = &tcnum;
		} else {
			SOAR_ASSERT(false,"that type does NOT exist.......");
			return;
		}


		static_cast<T*>(buf)[*num] = dataToPublish;
		*num++;
		if(*num >= RATEBUFSIZE) { // bad cycle NO!!! TODO!!!!!!!!!!!!
			*num = 0;
		}
	  }

	  template <typename T>
	  static void Subscribe(Task* taskToSubscribe, uint32_t rate) {
	    SOAR_PRINT("YEAH!!!!!!!!!!!!!!!!!! RATES!!!!!!!!!!!!!!");
	    DataBroker::Subscribe<T>(taskToSubscribe);

	  }


	  static void TimerCallback() {
		 SOAR_PRINT("urngle");
	  }

private:
	  static IMUData imubuf[RATEBUFSIZE];
	  static uint32_t imunum;

	  static ThermocoupleData tcbuf[RATEBUFSIZE];
	  static uint32_t tcnum;
};


#endif /* INC_RATEBROKER_HPP_ */
