/*
 * RatedBuf.hpp
 *
 *  Created on: Apr 26, 2025
 *      Author: Local user
 */

#ifndef RATEDBUF_HPP_
#define RATEDBUF_HPP_

#define RATEBUFSIZE 300


template <typename T>
struct SensorDataBuf {
	uint32_t num;
	T data[RATEBUFSIZE];


	size_t getSize() const {
		return sizeof(T);
	}

	T getAt(uint32_t index) const {
		return data[index];
	}

	T getLast() const {
		if(num == 0) {
			return T();
		}
		return data[num-1];
	}
};



#endif /* RATEDBUF_HPP_ */
