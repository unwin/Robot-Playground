/*
 * NEO-6.h
 *
 *  Created on: Dec 28, 2012
 *      Author: unwin
 */

#ifndef NEO_6_H_
#define NEO_6_H_

#include "i2c.h"

class NEO_6 {
	private:
		int i2c_bus_id;
		i2c *i2c_bus;
		int device_id;
	public:
		NEO_6(int id);
		~NEO_6();
		void setup();
};



#endif /* NEO_6_H_ */
