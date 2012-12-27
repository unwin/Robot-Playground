/*
 * J2004A.h
 *
 *  Created on: Dec 26, 2012
 *      Author: unwin
 */

#ifndef J2004A_H_
#define J2004A_H_

// commands
#define LCD_CLEARDISPLAY 0x01
#define LCD_RETURNHOME 0x02
#define LCD_ENTRYMODESET 0x04
#define LCD_DISPLAYCONTROL 0x08
#define LCD_CURSORSHIFT 0x10
#define LCD_FUNCTIONSET 0x20
#define LCD_SETCGRAMADDR 0x40
#define LCD_SETDDRAMADDR 0x80

// flags for display on/off control
#define LCD_DISPLAYON 0x04
#define LCD_DISPLAYOFF 0x00
#define LCD_CURSORON 0x02
#define LCD_CURSOROFF 0x00
#define LCD_BLINKON 0x01
#define LCD_BLINKOFF 0x00

#include "i2c.h"

class J2004A {
	private:
		int i2c_bus_id;
		i2c *i2c_bus;
		int device_id;
	public:
		J2004A(int id);
		~J2004A();
		void clear_display();

};


#endif /* J2004A_H_ */
