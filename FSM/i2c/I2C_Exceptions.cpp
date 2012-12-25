/*
 * I2C_Exceptions.cpp
 *
 *  Created on: Dec 9, 2012
 *      Author: unwin
 */



#include <exception>

#include "../log.h"
#include "I2C_Exceptions.h"

using namespace std;



IoError::IoError() : exception(){
	this->reason = DEFAULT_REASON;
};

IoError::IoError(std::string reason) : exception(){
	this->reason = reason;
};

IoError::~IoError() throw () {

};

const char* IoError::what()  {
	string s = "IoError : " + this->reason + " " + std::exception::what();
	std::cout << s << std::endl;
	return s.c_str();
}

