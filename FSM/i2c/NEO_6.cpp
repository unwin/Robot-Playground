/*
 * NEO-6.cpp
 *
 *  Created on: Dec 28, 2012
 *      Author: unwin
 */


#include "NEO_6.h"



#include <iostream>
#include <ostream>
#include <string>
#include <map>
#include <assert.h>
#include "../log.h"
#include "i2c.h"
#include "NEO_6.h"
using namespace std;


NEO_6::NEO_6(int id) {
	LOG << "entering NEO_6 constructor";
	i2c_bus_id = id;
	i2c_bus = i2c::Instance(id);
	device_id = 0x42;
	i2c_bus->connect(device_id);

	while (1) {
		//LOG <<  " BEFORE SETUP";
		setup();
		//LOG <<  " AFTER SETUP";
		//sleep(1);
	}

	LOG << "exiting NEO_6 constructor";
};

NEO_6::~NEO_6() {

};

void NEO_6::setup() {

	int fd = i2c_bus->read_register_byte(0xfd);
	int fe = i2c_bus->read_register_byte(0xfe);
	//LOG << "fd = " << fd << " fe = " << fe;


	//LOG << "does not work.";
	unsigned char buffer[255];
	buffer[0] = 0xff;
	int count = write(i2c_bus->deviceHandle, buffer, 1);
	int bytes_read = read(i2c_bus->deviceHandle, buffer, 10);
	buffer[10] = 0;

	int i = 0;

	LOG << "1 wrote " << count << " bytes, and read " << bytes_read << " resulting in " << buffer << " " << std::hex << int(buffer[i++]) << " " << int(buffer[i++]) << " " << int(buffer[i++]) << " " << int(buffer[i++]) << " " << int(buffer[i++]) << " " << int(buffer[i++]) << " " << int(buffer[i++]) << " " << int(buffer[i++]) << " " << int(buffer[i++]) << " " << int(buffer[i++]);

}
