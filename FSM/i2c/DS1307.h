/*
 * DS1307.h
 *
 *  Created on: Dec 22, 2012
 *      Author: unwin
 */

#ifndef DS1307_H_
#define DS1307_H_

#include <stdint.h>
#include "i2c.h"
#include "DS1307.h"

class DS1307 {
	private:
		int i2c_bus_id;
		i2c *i2c_bus;
		int device_id;
	public:
		DS1307(int id);
		~DS1307();

		void set_time(int h, int m, int s, int wd, int md, int mm, int yy);
		void set_time(time_t seconds);
		void set_time();

		void get_time();

		uint8_t bcdToDec(uint8_t val);
		uint8_t decToBcd(uint8_t val);
};


#endif /* DS1307_H_ */
