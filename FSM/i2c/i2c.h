/*
 * i2c.h
 *
 *  Created on: Dec 22, 2012
 *      Author: unwin
 */

#ifndef I2C_H_
#define I2C_H_


using namespace std;
// test


#define MODE_AUTO 0
#define MODE_QUICK 1
#define MODE_READ 2
#define MODE_FUNC 3

#include <boost/unordered_map.hpp>
typedef boost::unordered_map<int, std::string> device_map;


class i2c {
	// this is a candidate for singleton and locking mechanism
	// make a test for this.

	private:
		int deviceHandle;
	public:
		i2c(int id);

		~i2c();

		void connect(int deviceI2CAddress);

		int read_bytes(int byte_count, char *buffer);


		void write_bytes(char *buffer, int byte_count);

		device_map scan_bus();


};

#endif /* I2C_H_ */
