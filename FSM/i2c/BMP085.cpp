/*
 * BMP085.cpp
 *
 *  Created on: Dec 22, 2012
 *      Author: unwin
 */




#include <iostream>
#include <ostream>
#include <string>
#include <map>


#include "BMP085.h"
#include "../log.h"

BMP085::BMP085(int id) {
	i2c_bus_id = id;
	device_id = 0x53;
	i2c_bus = i2c::Instance(id);
	i2c_bus->connect(device_id);
	calibrate();

	LOG << "exiting BMP085 constructor";
};

BMP085::~BMP085() {

};

void BMP085::read_data() {

}


/*
unsigned short int BMP085::read_int(unsigned char address ) {
	unsigned short int val;
	i2c_bus->write_byte(address);
	i2c_bus->read_bytes(2, (char *)&val);
	return(val);
}
*/

void BMP085::calibrate() {
	ac1 = i2c_bus->read_register_word_swapped(0xAA);
	ac2 = i2c_bus->read_register_word_swapped(0xAC);
	ac3 = i2c_bus->read_register_word_swapped(0xAE);
	ac4 = i2c_bus->read_register_word_swapped(0xB0);
	ac5 = i2c_bus->read_register_word_swapped(0xB2);
	ac6 = i2c_bus->read_register_word_swapped(0xB4);
	b1 = i2c_bus->read_register_word_swapped(0xB6);
	b2 = i2c_bus->read_register_word_swapped(0xB8);
	mb = i2c_bus->read_register_word_swapped(0xBA);
	mc = i2c_bus->read_register_word_swapped(0xBC);
	md = i2c_bus->read_register_word_swapped(0xBE);
}

