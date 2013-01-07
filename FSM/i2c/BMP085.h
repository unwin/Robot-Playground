/*
 * BMP085.h
 *
 *  Created on: Dec 9, 2012
 *      Author: unwin
 */

#include "i2c.h"



#define CAL_AC1           	0xAA
#define CAL_AC2           	0xAC
#define CAL_AC3           	0xAE
#define CAL_AC4           	0xB0
#define CAL_AC5           	0xB2
#define CAL_AC6           	0xB4
#define CAL_B1            	0xB6
#define CAL_B2            	0xB8
#define CAL_MB            	0xBA
#define CAL_MC            	0xBC
#define CAL_MD            	0xBE

#define CONTROL           	0xF4
#define TEMP_DATA          	0xF6
#define PRESSURE_DATA      	0xF6
#define READ_TEMP_CMD       0x2E
#define READ_PRESSURE_CMD   0x34

#define ULTRALOWPOWER		0
#define STANDARD			1
#define HIGH_RES       		2
#define ULTRA_HIGH_RES  	3

class BMP085 {
	private:
		int i2c_bus_id;
		i2c *i2c_bus;
		int device_id;

		short int ac1;
		short int ac2;
		short int ac3;
		unsigned short int ac4;
		unsigned short int ac5;
		unsigned short int ac6;
		short int b1;
		short int b2;
		short int mb;
		short int mc;
		short int md;

		unsigned char over_sampling;
		float sea_level_pressure;

	public:
		BMP085(int id);
		~BMP085();
		void get_calibration();
		int get_raw_temperature();
		float get_temperature();
		unsigned int get_raw_pressure();
		int get_pressure();
		float get_altitude();
};
