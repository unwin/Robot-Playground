/*
 * i2c.cpp
 *
 *  Created on: Dec 9, 2012
 *      Author: unwin
 */

#ifndef I2C_HPP_
#define I2C_HPP_

#include <vector>
#include <string>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <linux/i2c-dev.h>
#include "I2C_Exceptions.h"
#include <boost/unordered_map.hpp>
#include "../log.h"
#include "i2c.h"

using namespace std;

#define MODE_AUTO 0
#define MODE_QUICK 1
#define MODE_READ 2
#define MODE_FUNC 3


i2c::i2c(int id) {
	if (id == 0) {
		if ((deviceHandle = open("/dev/i2c-0", O_RDWR)) < 0)
			throw IoError("Could not open /dev/i2c-0");
	} else if (id == 1) {
		if ((deviceHandle = open("/dev/i2c-1", O_RDWR)) < 0)
			throw IoError("Could not open /dev/i2c-1");
	} else
		throw IoError("only /dev/i2c-o and /dev/i2c-1 are supported.");
};

i2c::~i2c() {
	close(deviceHandle);
}

void i2c::connect(int deviceI2CAddress) {
	//LOG << "in connect before it all";

	if (ioctl(deviceHandle, I2C_SLAVE, deviceI2CAddress) < 0)
		throw IoError("Could not ioctl 12c device ");

}

int i2c::read_bytes(int byte_count, char *buffer) {
	int bytes_read;
	bytes_read = read(deviceHandle, buffer, byte_count);
	LOG << "tried to read " << byte_count << " bytes but actually read " << bytes_read << " bytes from device.";
	return bytes_read;
}

void i2c::write_bytes(char *buffer, int byte_count) {
	LOG << "writing to device ";
	int count = write(deviceHandle, buffer, byte_count);
	if (count != byte_count)
		throw IoError("Did not write enough bytes, should probably loop this...");
}

device_map i2c::scan_bus() {
	device_map found_ids;

	int res;

	for (int address = 0x03; address < 0x78; address++) {

		/* Set slave address */
		connect(address);

		/* Probe this address */
		int mode = MODE_QUICK;
		switch (mode) {
			case MODE_QUICK:
				/* This is known to corrupt the Atmel AT24RF08 EEPROM */
				res = i2c_smbus_write_quick(deviceHandle, I2C_SMBUS_WRITE);
				break;
			case MODE_READ:
				/* This is known to lock SMBus on various write-only chips (mainly clock chips) */
				res = i2c_smbus_read_byte(deviceHandle);
				break;
			default:
				if ((address >= 0x30 && address <= 0x37) || (address >= 0x50 && address <= 0x5F))
					  res = i2c_smbus_read_byte(deviceHandle);
				else
					  res = i2c_smbus_write_quick(deviceHandle, I2C_SMBUS_WRITE);
		}

		if (0 == res) {
			if (0x1E == address)
				found_ids[address] = "HMC5883";
			else if (0x50 == address)
				found_ids[address] = "AT24C16";
			else if (0x53 == address)
				found_ids[address] = "ADXL345";
			else if (0x68 == address)
				found_ids[address] = "DS1307";
			else if (0x69 == address)
				found_ids[address] = "L3G4200D";
			else if (0x77 == address)
				found_ids[address] = "BMP085";
			else
				found_ids[address] = "UNKNOWN";
		}
	}
	return(found_ids);
}


#endif /* I2C_HPP_ */
