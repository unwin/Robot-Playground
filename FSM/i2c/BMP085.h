/*
 * BMP085.h
 *
 *  Created on: Dec 9, 2012
 *      Author: unwin
 */

#include "i2c.h"

class BMP085 {
	private:
		int i2c_bus_id;
		i2c *i2c_bus;
		int device_id;
		unsigned short int ac1;
		unsigned short int ac2;
		unsigned short int ac3;
		unsigned short int ac4;
		unsigned short int ac5;
		unsigned short int ac6;
		unsigned short int b1;
		unsigned short int b2;
		unsigned short int mb;
		unsigned short int mc;
		unsigned short int md;

	public:
		BMP085(int id);
		~BMP085();
		void read_data();
		//unsigned short int read_int(unsigned char address);
		void calibrate();
};








/*
int bmp085ReadInt(unsigned char address)
{
  unsigned char msb, lsb;

  Wire.beginTransmission(BMP085_ADDRESS);
  Wire.write(address);
  Wire.endTransmission();

  Wire.requestFrom(BMP085_ADDRESS, 2);
  while(Wire.available()<2)
    ;
  msb = Wire.read();
  lsb = Wire.read();

  return (int) msb<<8 | lsb;
}
*/
