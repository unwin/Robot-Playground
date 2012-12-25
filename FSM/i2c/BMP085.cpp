/*
 * BMP085.cpp
 *
 *  Created on: Dec 22, 2012
 *      Author: unwin
 */




#include <iostream>
#include <ostream>
#include <string>
#include <map>


#include "BMP085.h"
#include "../log.h"

BMP085::BMP085(int id) : i2c(id)  {
	i2c_bus = id;
};

BMP085::~BMP085() {

};
