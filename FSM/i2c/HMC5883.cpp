/*
 * HMC5883.cpp
 *
 *  Created on: Jan 3, 2013
 *      Author: unwin
 */



#include <iostream>
#include <ostream>
#include <string>
#include <map>
#include <assert.h>
#include "../log.h"
#include "HMC5883.h"
#include <byteswap.h>

using namespace std;

// HMC5883L
HMC5883::HMC5883(int id) {
	i2c_bus_id = id;
	device_id = 0x1E;
	i2c_bus = i2c::Instance(id);
	i2c_bus->connect(device_id);
	bool result = configure(AVG_8_SAMPLES | OUTPUT_15_HZ | NORMAL_BIAS, GA_1_3_AKA_1090_GAUSS, CONTINOUS_MEASUREMENT_MODE);
	assert(result == true);

	LOG << "exiting HMC5883 constructor";
}

HMC5883::~HMC5883() {

}

bool HMC5883::configure(char ctrl_reg_a_val, char ctrl_reg_b_val, char mode_val) {
	char val = 0;

	i2c_bus->write_register_byte(CONFIG_REG_A, ctrl_reg_a_val);
	val = i2c_bus->read_register_byte(CONFIG_REG_A);
	LOG << "CONFIG_REG_A READ = " << val << " CONFIG_REG_A write = " << ctrl_reg_a_val;
	assert(val == ctrl_reg_a_val);

	i2c_bus->write_register_byte(CONFIG_REG_B, ctrl_reg_b_val);
	val = i2c_bus->read_register_byte(CONFIG_REG_B);
	LOG << "CONFIG_REG_B READ = " << val << " CONFIG_REG_B write = " << ctrl_reg_b_val;
	assert(val == ctrl_reg_b_val);

	i2c_bus->write_register_byte(MODE_REG, mode_val);
	// dont read this one back, it will trigger locking...
	//val = i2c_bus->read_register_byte(MODE_REG);
	//LOG << "mode_val READ = " << val << " mode_val write = " << mode_val;
	//assert(val == mode_val);

	return (true);
};

float HMC5883::get_2d_heading() {
	short int x = 0;
	short int y = 0;
	short int z = 0;
	read_orientation(x, y, z);
	LOG << "RAW x = " << x << " Y = " << y << " z = " << z;
	float heading = atan2(x, y);
	float deg_heading = (heading/M_PI*180) + (heading > 0 ? 0 : 360);
	LOG << "HEADING x = " << deg_heading;
	return(deg_heading);
}


void HMC5883::read_orientation(short int &x, short int &y, short int &z) {
	bool ready = false;
	bool lock = false;

	do {
		int status = i2c_bus->read_register_byte( STATUS_REG );
		ready = status & 0x01;
		lock  = status & 0x02;
	} while ((ready == false) || (lock == true));

	assert(ready == true);
	assert(lock == false);

	x = i2c_bus->read_register_word_swapped(DATA_OUTPUT_X_MSB_REG);
	y = i2c_bus->read_register_word_swapped(DATA_OUTPUT_Y_MSB_REG);
	z = i2c_bus->read_register_word_swapped(DATA_OUTPUT_Z_MSB_REG);

};
