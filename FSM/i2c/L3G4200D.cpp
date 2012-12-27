/*
 * L3G4200D.cpp
 *
 *  Created on: Dec 25, 2012
 *      Author: unwin
 */


#include <iostream>
#include <ostream>
#include <string>
#include <map>
#include <assert.h>
#include "../log.h"
#include "L3G4200D.h"

using namespace std;


L3G4200D::L3G4200D(int id) {
	LOG << "entering L3G4200D constructor";
	i2c_bus_id = id;
	i2c_bus = i2c::Instance(id);
	device_id = 0x69;
	i2c_bus->connect(device_id);


	setup(250); // Configure L3G4200  - 250, 500 or 2000 deg/sec
	LOG << "exiting L3G4200D constructor";
};

L3G4200D::~L3G4200D() {

};

void L3G4200D::setup(int scale) {
	LOG << "L3G4200D setup";
	this->scale = scale;

	// Enable x, y, z and turn off power down:
	i2c_bus->write_register_byte(CTRL_REG1, 0b00001111);

	// If you'd like to adjust/use the HPF, you can edit the line below to configure CTRL_REG2:
	i2c_bus->write_register_byte(CTRL_REG2, 0b00101001);

	i2c_bus->write_register_byte(CTRL_REG3, 0b00000000);

	if (scale == 250) {
		i2c_bus->write_register_byte(CTRL_REG4, 0b01000000);
	} else if (scale == 500) {
		i2c_bus->write_register_byte(CTRL_REG4, 0b01010000);
	} else {
		i2c_bus->write_register_byte(CTRL_REG4, 0b01110000);
	}

	// CTRL_REG5 controls high-pass filtering of outputs
	i2c_bus->write_register_byte(CTRL_REG5, 0b00000000);
};

void L3G4200D::read_gyro() {
	short int x = i2c_bus->read_register_word(OUT_X_L);
	short int y = i2c_bus->read_register_word(OUT_Y_L);
	short int z = i2c_bus->read_register_word(OUT_Z_L);
	LOG << "x = " << x << " Y = " << y << " z = " << z;

};

