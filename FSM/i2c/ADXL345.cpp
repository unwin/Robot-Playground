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


	bool result = set_g_range(G_RANGE_2G);

	char buffer[10];
	buffer[0] = POWER_CTL;
	buffer[1] = 0x08;
	i2c_bus->write_bytes(buffer, 2);
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

void ADXL345::read_acceleration() {
	int x = ((( int)i2c_bus->read_register_byte(DATAX0)) << 8) | (char)i2c_bus->read_register_byte(DATAX1);
	int y = ((( int)i2c_bus->read_register_byte(DATAY0)) << 8) | (char)i2c_bus->read_register_byte(DATAY1);
	int z = ((( int)i2c_bus->read_register_byte(DATAZ0)) << 8) | (char)i2c_bus->read_register_byte(DATAZ1);
	LOG << "x = " << x << " Y = " << y << " z = " << z;

	float xd = (float) x / 65535.0 * 360.0;
	float yd = (float) y / 65535.0 * 360.0;
	float zd = (float) z / 65535.0 * 360.0;
	LOG << "xd = " << xd << " yd = " << yd << " zd = " << zd;
};


#endif /* ADXL345_HPP_ */
