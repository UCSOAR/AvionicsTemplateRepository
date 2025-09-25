/*
 * RatedBuf.hpp
 *
 *  Created on: Apr 26, 2025
 *      Author: Local user
 */

#include "Mutex.hpp"

#ifndef RATEDBUF_HPP_
#define RATEDBUF_HPP_

#define RATEBUFSIZE 300


struct SensorDataBufBase {

};

template <typename T>
struct SensorDataBuf : public SensorDataBufBase {
	// the number of elements from the beginning that are defined
	uint32_t validUntil = 0;
	// mostRecent should always be <= validUntil
	uint32_t mostRecent = 0;
	T data[RATEBUFSIZE];


	size_t getSize() const {
		return sizeof(T);
	}

	T getAt(uint32_t index) const {

		return data[index];
	}

	T getLast() const {

		if(validUntil == 0) {
			return T();
		}
		return data[mostRecent];

	}

	// not thread safe :)
	void addElement(const T* element) {

		buffer_lock.Lock();


		mostRecent++;
		mostRecent %= RATEBUFSIZE;
		if(validUntil < RATEBUFSIZE) {
			validUntil++;
		}

		data[mostRecent] = *element;

		buffer_lock.Unlock();
	}
private:

	Mutex buffer_lock = Mutex();

};




#endif /* RATEDBUF_HPP_ */
