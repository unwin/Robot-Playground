/*
 * ADXL345.hpp
 *
 *  Created on: Dec 20, 2012
 *      Author: unwin
 */

#ifndef ADXL345_HPP_
#define ADXL345_HPP_


#include <iostream>
#include <ostream>
#include <string>
#include <map>
#include <assert.h>
#include "../log.h"
#include "ADXL345.h"

using namespace std;


ADXL345::ADXL345(int id) {
	i2c_bus_id = id;
	device_id = 0x53;
	i2c_bus = i2c::Instance(id);
	i2c_bus->connect(device_id);

	bool result = set_g_range(G_RANGE_2G); // FULL_RES must be 0, or the readings are bigger than 10 bit.
	calibrate();
	i2c_bus->write_register_byte(POWER_CTL, 0b00001000);
	LOG << "exiting ADXL345 constructor";
}

ADXL345::~ADXL345() {

}

bool ADXL345::set_g_range(char range) {
	i2c_bus->write_register_byte(DATA_FORMAT, range);

	char val = i2c_bus->read_register_byte(DATA_FORMAT);
	assert(val == range);
	return (true);
};



void ADXL345::calibrate() {
	// need to calibrate this.
	char x_off = i2c_bus->read_register_byte(X_OFFSET);
	char y_off = i2c_bus->read_register_byte(Y_OFFSET);
	char z_off = i2c_bus->read_register_byte(Z_OFFSET);
	LOG << "x_off = " << int(x_off) << "y_off = " << int(y_off) << "z_off = " << int(z_off);
}

void ADXL345::read_acceleration(float &x, float &y, float &z) {

	short int x_raw = i2c_bus->read_register_word(DATAX0);
	short int y_raw = i2c_bus->read_register_word(DATAY0);;
	short int z_raw = i2c_bus->read_register_word(DATAZ0);;


	LOG << "x_raw = " << x_raw << " y_raw = " << y_raw << " z_raw = " << z_raw;
	x = (float) x_raw * 0.0039 ;
	y = (float) y_raw * 0.0039 ;
	z = (float) z_raw * 0.0039 ;
};


#endif /* ADXL345_HPP_ */
