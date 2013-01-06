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
	// need to lock the bus when executing commands.
	private:
		i2c(int id);
		static i2c * i2c_singleton_instance0; // to handle i2c bus 0 and 1
		static i2c * i2c_singleton_instance1; // to handle i2c bus 0 and 1

		//i2c(i2c const&){deviceHandle = 0;};       					// copy constructor is private
		//i2c& operator=(i2c const&){deviceHandle = 0;return 0;};  	// assignment operator is private
	public:
		int deviceHandle;
		static i2c* Instance(int id);

		~i2c();

		void connect(int deviceI2CAddress);

		int read_bytes(int byte_count, char *buffer);
		void write_bytes(char *buffer, int byte_count);

		bool write_byte(char val);
		char read_byte();
		char read_register_byte(char reg);
		void write_register_byte(char reg, char val);
		short int read_register_word(char reg);
		short int read_register_word_swapped(char reg);
		void write_register_word(char reg, short int val);
		device_map scan_bus();


};



#endif /* I2C_H_ */
