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
#include <cmath>

#include "BMP085.h"
#include "../log.h"

BMP085::BMP085(int id) {
	i2c_bus_id = id;
	device_id = 0x77;
	i2c_bus = i2c::Instance(id);
	i2c_bus->connect(device_id);

	assert(i2c_bus->read_register_byte(0xD0) == 0x55);

	// ULTRALOWPOWER works.
	// STANDARD works.
	// HIGH_RES works.
	// ULTRA_HIGH_RES works.
	over_sampling = ULTRA_HIGH_RES;

	sea_level_pressure = 101500; //pa

	get_calibration();
	LOG << "exiting BMP085 constructor";
};

BMP085::~BMP085() {

};

void BMP085::get_calibration() {

	ac1 = i2c_bus->read_register_word_swapped(CAL_AC1);
	ac2 = i2c_bus->read_register_word_swapped(CAL_AC2);
	ac3 = i2c_bus->read_register_word_swapped(CAL_AC3);
	ac4 = i2c_bus->read_register_word_swapped(CAL_AC4);
	ac5 = i2c_bus->read_register_word_swapped(CAL_AC5);
	ac6 = i2c_bus->read_register_word_swapped(CAL_AC6);

	b1 = i2c_bus->read_register_word_swapped(CAL_B1);
	b2 = i2c_bus->read_register_word_swapped(CAL_B2);
	mb = i2c_bus->read_register_word_swapped(CAL_MB);
	mc = i2c_bus->read_register_word_swapped(CAL_MC);
	md = i2c_bus->read_register_word_swapped(CAL_MD);

	LOG << "CAL_AC1 = " << ac1;
	LOG << "CAL_AC2 = " << ac2;
	LOG << "CAL_AC3 = " << ac3;
	LOG << "CAL_AC4 = " << ac4;
	LOG << "CAL_AC5 = " << ac5;
	LOG << "CAL_AC6 = " << ac6;

	LOG << "CAL_B1 = " << b1;
	LOG << "CAL_B2 = " << b2;
	LOG << "CAL_MB = " << mb;
	LOG << "CAL_MC = " << mc;
	LOG << "CAL_MD = " << md;
}

int BMP085::get_raw_temperature() {
	i2c_bus->write_register_byte(CONTROL, READ_TEMP_CMD);

	usleep(5);

	unsigned short int raw_temp = i2c_bus->read_register_word_swapped(TEMP_DATA);

	return (int)raw_temp;
}

float BMP085::get_temperature() {
	int UT, X1, X2, B5;
	float temperature;

	UT = get_raw_temperature();

	X1 = (UT - ac6) * ac5 / pow(2,15);
	X2 = mc * pow(2,11) / (X1 + md);
	B5 = X1 + X2;
	temperature = (B5+8)/pow(2,4);
	temperature /= 10;

	return temperature;
}

unsigned int BMP085::get_raw_pressure() {


	i2c_bus->write_register_byte(CONTROL, READ_PRESSURE_CMD + (over_sampling << 6));
	//LOG << "over_sampling = " << std::hex << over_sampling;
	switch (over_sampling) {
		case 0 : usleep(4500);
			     break;
		case 1 : usleep(4500);
			     break;
		case 2 : usleep(13500);
			     break;
		case 3 : usleep(25500);
			     break;
	}

	unsigned char b1 = i2c_bus->read_register_byte(0xF6);
	unsigned char b2 = i2c_bus->read_register_word(0xF7);
	unsigned char b3 = i2c_bus->read_register_byte(0xF8);
	unsigned long raw_pressure = (((unsigned long) b1 << 16) | ((unsigned long) b2 << 8) | (unsigned long) b3);


	raw_pressure = raw_pressure >> (8 - over_sampling) ;
	return raw_pressure;
}

int BMP085::get_pressure() {
	int UT, UP, B3, B5, B6, X1, X2, X3, p;
	unsigned int B4, B7;

	UT = get_raw_temperature();
	UP = get_raw_pressure();

	// do temperature calculations

	X1 = (UT - ac6) * ac5 / 32768;
	X2 = mc * pow(2,11) / (X1 + md); // x2 is 1 off, not sure why.
	B5 = X1 + X2;

	// do pressure calcs
	B6 = B5 - 4000; // off by 1 for some reason.
	X1 = (b2 * ( B6 * B6 / 4096 )) / 2048;
	X2 = (ac2 * B6) / 2048;
	X3 = X1 + X2;
	B3 = (((ac1 * 4 + X3) << over_sampling) + 2) / 4;

	X1 = (ac3 * B6) >> 13;
	X2 = (b1 * ((B6 * B6) / 4096)) / 65536;
	X3 = ((X1 + X2) + 2) / 4;

	B4 = (ac4 * (X3 + 32768)) / 32768;
	B7 = (UP - B3) * ( 50000UL >> over_sampling );

	if (B7 < 0x80000000)
		p = (B7 * 2) / B4;
	else
		p = (B7 / B4) * 2;
	X1 = (p / pow(2,8)) * (p / pow(2,8));
	X1 = (X1 * 3038) / pow(2,16);
	X2 = (-7357 * p) / pow(2,16); // shows -7858 should be -7859 a mystery
	p += ((X1 + X2 + 3791) / pow(2,4));

	return p;
}

float BMP085::get_altitude() {
  float altitude;

  float pressure = get_pressure();

  altitude = 44330 * (1.0 - pow((float)(pressure / sea_level_pressure), (float)0.1903));

  return altitude;
}
