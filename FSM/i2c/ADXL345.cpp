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


ADXL345::ADXL345(int id) : i2c(id)  {
	i2c_bus = id;
	device_id = 0x53;
	connect(device_id);


	bool result = set_g_range(G_RANGE_2G);

	char buffer[10];
	buffer[0] = POWER_CTL;
	buffer[1] = 0x08;
	write_bytes(buffer, 2);
	LOG << "exiting ADXL345 constructor";
}

ADXL345::~ADXL345() {

}

bool ADXL345::set_g_range(char range) {
	char buffer[10];
	buffer[0] = DATA_FORMAT;
	buffer[1] = range;
	write_bytes(buffer, 2);

	buffer[0] = DATA_FORMAT;
	int bytes_read = read_bytes(1, buffer);
	assert(bytes_read == 1);
	return (buffer[0] == range);
};

void ADXL345::read_acceleration() {
	char buffer[10];
	buffer[0] = DATAX0;
	write_bytes(buffer, 1);
	int bytes_read = read_bytes(6, buffer);
	int x = (((int)buffer[1]) << 8) | buffer[0];
	int y = (((int)buffer[3]) << 8) | buffer[2];
	int z = (((int)buffer[5]) << 8) | buffer[4];


	assert(bytes_read == 6);
	LOG << "x = " << x << " Y = " << y << " z = " << z;
	float xd = (float) x / 65535.0 * 360.0;
	float yd = (float) y / 65535.0 * 360.0;
	float zd = (float) z / 65535.0 * 360.0;
	LOG << "xd = " << xd << " yd = " << yd << " zd = " << zd;
};


#endif /* ADXL345_HPP_ */
