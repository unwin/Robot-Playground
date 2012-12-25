/*
 * BMP085.h
 *
 *  Created on: Dec 9, 2012
 *      Author: unwin
 */

#include "i2c.h"

class BMP085 : public i2c {
	private:
		int i2c_bus;
	public:
		BMP085(int id);
		~BMP085();
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
