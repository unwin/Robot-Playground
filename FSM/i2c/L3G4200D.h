/*
 * L3G4200D.h
 *
 *  Created on: Dec 25, 2012
 *      Author: unwin
 */

#ifndef L3G4200D_H_
#define L3G4200D_H_


// Registers
// Device identification register
#define WHO_AM_I  0x0F 				// RO - Default 11010011

// Bit 0, 1 - Output Data Rate selection.
// Bit 2, 3 - Bandwidth selection
// Bit 4 - Power Down enable
// Bit 5 - X Enable
// Bit 6 - Y Enable
// Bit 7 - Z enable
#define CTRL_REG1 0x20 				// RW - Default 00000111
#define CTRL_REG2 0x21				// RW - Default 00000000
#define CTRL_REG3 0x22 				// RW - Default 00000000
#define CTRL_REG4 0x23 				// RW - Default 00000000
#define CTRL_REG5 0x24 				// RW - Default 00000000
#define REFERENCE 0x25 				// RW - Default 00000000
#define OUT_TEMP  0x26				// RO - Default output
#define STATUS_REG 0x27				// RO - Default output
#define OUT_X_L 0x28				// RO - Default output
#define OUT_X_H 0x29				// RO - Default output
#define OUT_Y_L 0x2A				// RO - Default output
#define OUT_Y_H 0x2B				// RO - Default output
#define OUT_Z_L 0x2C				// RO - Default output
#define OUT_Z_H 0x2D				// RO - Default output
#define FIFO_CTRL_REG 0x2E     		// RW - Default 00000000
#define FIFO_SRC_REG 0x2F     		// RO - Default output
#define INT1_CFG 0x30   			// RW - Default 00000000
#define INT1_SRC 0x31  				// RO - Default output
#define INT1_TSH_XH 0x32     		// RW - Default 00000000
#define INT1_TSH_XL 0x33  			// RW - Default 00000000
#define INT1_TSH_YH 0x34 			// RW - Default 00000000
#define INT1_TSH_YL 0x35 			// RW - Default 00000000
#define INT1_TSH_ZH 0x36 			// RW - Default 00000000
#define INT1_TSH_ZL 0x37 			// RW - Default 00000000
#define INT1_DURATION 0x38 			// RW - Default 00000000

#define AUTO_INCREMENT                  0x80

// G Range
//#define G_RANGE_2G 0x00
//#define G_RANGE_4G 0x01
//#define G_RANGE_8G 0x02
//#define G_RANGE_16G 0x03

// FIFO Mode
#define BYPASS 0x00
#define FIFO 0x01
#define STREAM 0x02
#define TRIGGER 0x03

#include "i2c.h"

class L3G4200D {
	private:
		int i2c_bus_id;
		i2c * i2c_bus;
		int device_id;
		int scale;
	public:
		L3G4200D(int id);
		~L3G4200D();
		void setup(int scale);
		//bool set_g_range(char range);
		void read_gyro();
};



#endif /* L3G4200D_H_ */
