/*
 * ADXL345.h
 *
 *  Created on: Dec 22, 2012
 *      Author: unwin
 */

#ifndef ADXL345_H_
#define ADXL345_H_

// Registers
// test
#define DEVID 0x00 				// RO - Device ID
#define THRESH_TAP 0x1D 		// RW - Tap threshold
#define OFSX 0x1E 				// RW - X axis offset
#define OFSY 0x1F 				// RW - Y axis offset
#define OFSZ 0x20 				// RW - Z axis offset
#define DUR 0x21 				// RW - Tap duration
#define LATENT 0x22 			// RW - Tap latency
#define WINDOW 0x23				// RW - Tap window
#define THRESH_ACT 0x24			// RW - Activity threshold
#define THRESH_INACT 0x25		// RW - Inactivity threshold
#define TIME_INACT 0x26			// RW - Inactivity time
#define ACT_INACT_CONTROL 0x27	// RW - Axis enable control for ACT/INACT
#define THRESH_FF 0x28			// RW - Free-fall threshold
#define TIME_FF	0x29			// RW - Free-fall time
#define TAP_AXES 0x2A			// RW - Axis control for Tap/Double Tap
#define ACT_TAP_STATUS 0x2B     // RW - Source of Tap/Double Tap
#define BW_RATE 0x2C     		// RW - Data Rate and Power Mode control
#define POWER_CTL 0x2D   		// RW - Power Save features control
#define INT_ENABLE 0x2E  		// RW - Interrupt enable control
#define INT_MAP 0x2F     		// RW - Interrupt mapping control
#define INT_SOURCE 0x30  		// RO - Source of interrupts
#define DATA_FORMAT 0x31 		// RW - Data format control
#define DATAX0 0x32 			// RO - X axis data
#define DATAX1 0x33 			// RO - X axis data
#define DATAY0 0x34 			// RO - Y axis data
#define DATAY1 0x35 			// RO - Y axis data
#define DATAZ0 0x36 			// RO - Z axis data
#define DATAZ1 0x37 			// RO - Z axis data
#define FIFO_CTL 0x38  			// RW - FIFO control
#define FIFO_STATUS 0x39 		// RO - FIFO status

// G Range
#define G_RANGE_2G 0x00
#define G_RANGE_4G 0x01
#define G_RANGE_8G 0x02
#define G_RANGE_16G 0x03

// FIFO Mode
#define BYPASS 0x00
#define FIFO 0x01
#define STREAM 0x02
#define TRIGGER 0x03

#include "i2c.h"

class ADXL345 : public i2c {
	private:
		int i2c_bus;
		int device_id;
	public:
		ADXL345(int id);
		~ADXL345();
		bool set_g_range(char range);
		void read_acceleration();
};


#endif /* ADXL345_H_ */
