/*
 * HMC5883.h
 *
 *  Created on: Jan 3, 2013
 *      Author: unwin
 */

#ifndef HMC5883_H_
#define HMC5883_H_


#include "i2c.h"

// Registers
#define CONFIG_REG_A 0x00 			// RW -
#define CONFIG_REG_B 0x01 			// RW -
#define MODE_REG 0x02 				// RW -
#define DATA_OUTPUT_X_MSB_REG 0x03 	// RO -
#define DATA_OUTPUT_X_LSB_REG 0x04 	// RO -
#define DATA_OUTPUT_Z_MSB_REG 0x05 	// RO -
#define DATA_OUTPUT_Z_LSB_REG 0x06 	// RO -
#define DATA_OUTPUT_Y_MSB_REG 0x07 	// RO -
#define DATA_OUTPUT_Y_LSB_REG 0x08	// RO -
#define STATUS_REG 0x09				// RO -
#define IDENT_REG_A 0x0A			// RO -
#define IDENT_REG_B 0x0B			// RO -
#define IDENT_REG_C 0x0C			// RO -


// Control Register A (or 1 of each of 3 following sets)

#define AVG_1_SAMPLES 0b00000000
#define AVG_2_SAMPLES 0b00100000
#define AVG_4_SAMPLES 0b01000000
#define AVG_8_SAMPLES 0b01100000

#define OUTPUT_0_75_HZ 0b00000000
#define OUTPUT_1_5_HZ  0b00000100
#define OUTPUT_3_HZ    0b00001000
#define OUTPUT_7_5_HZ  0b00001100
#define OUTPUT_15_HZ   0b00010000
#define OUTPUT_30_HZ   0b00010100
#define OUTPUT_75_HZ   0b00011000

#define NORMAL_BIAS   0b00000000
#define POSITIE_BIAS  0b00000001
#define NEGATIVE_BIAS 0b00000010

// Control Register B

#define GA_0_88_AKA_1370_GAUSS 0b00000000
#define GA_1_3_AKA_1090_GAUSS  0b00100000 // DEFAULT
#define GA_1_9_AKA_820_GAUSS   0b01000000
#define GA_2_5_AKA_660_GAUSS   0b01100000
#define GA_4_0_AKA_440_GAUSS   0b10000000
#define GA_4_7_AKA_390_GAUSS   0b10100000
#define GA_5_6_AKA_330_GAUSS   0b11000000
#define GA_8_1_AKA_230_GAUSS   0b11100000

// Mode Register

#define CONTINOUS_MEASUREMENT_MODE 0b00000000
#define SINGLE_MEASUREMENT_MODE    0b00000001
#define IDLE_MODE                  0b00000010
#define IDLE__MODE                 0b00000011
class HMC5883 {
	private:
		int i2c_bus_id;
		i2c *i2c_bus;
		int device_id;
	public:
		HMC5883(int id);
		~HMC5883();
		bool configure(char ctrl_reg_a_val, char ctrl_reg_b_val, char mode_val);
		float get_2d_heading();
		void read_orientation(short int &x, short int &y, short int &z);
};


#endif /* HMC5883_H_ */
