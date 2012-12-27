/*
 * J2004A.cpp
 *
 *  Created on: Dec 26, 2012
 *      Author: unwin
 */




#include <iostream>
#include <ostream>
#include <string>
#include <map>
#include <assert.h>
#include "../log.h"
#include "i2c.h"
#include "J2004A.h"

using namespace std;


J2004A::J2004A(int id) {
	LOG << "entering J2004A constructor";
	i2c_bus_id = id;
	i2c_bus = i2c::Instance(id);
	device_id = 0x27;
	i2c_bus->connect(device_id);


	LOG << "exiting L3G4200D constructor";
};

J2004A::~J2004A() {

};

void J2004A::clear_display() {
	LOG << "J2004A clear_display";

	i2c_bus->write_byte(0x01);
	sleep(1);
	i2c_bus->write_byte(0x0f);


};



