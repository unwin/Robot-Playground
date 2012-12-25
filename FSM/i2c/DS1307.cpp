/*
 * DS1307.hpp
 *
 *  Created on: Dec 17, 2012
 *      Author: unwin
 */

#include <iostream>
#include <ostream>
#include <string>
#include <map>
#include <assert.h>
#include <ctime>

#include "../log.h"
#include "i2c.h"
#include "DS1307.h"


DS1307::DS1307(int id) : i2c(id)  {
	i2c_bus = id;
	device_id = 0x68;
	connect(device_id);
};


DS1307::~DS1307() {

};

uint8_t DS1307::bcdToDec(uint8_t val) {
  return ( (val/16*10) + (val%16) );
}

uint8_t DS1307::decToBcd(uint8_t val) {
  return ( (val/10*16) + (val%10) );
}


void DS1307::set_time(int h, int m, int s, int wd, int md, int mm, int yy) {
	LOG << "set_time - 1 - Entered";
	time_t seconds = 0;
	tm *ltm = localtime(&seconds);
	ltm->tm_sec = s & 0x7f;   // seconds of minutes from 0 to 61
	ltm->tm_min = m;   // minutes of hour from 0 to 59
	ltm->tm_hour = h;  // hours of day from 0 to 24
	ltm->tm_wday = wd;  // days since sunday
	ltm->tm_mday = md;  // day of month from 1 to 31
	ltm->tm_mon = mm;   // month of year from 0 to 11
	ltm->tm_year = yy - 1900;  // year since 1900

	char buffer[10];
	buffer[0] = 0x00; // Command
	buffer[1] = decToBcd(ltm->tm_sec & 0x7f); // Seconds
	buffer[2] = decToBcd(ltm->tm_min); // Minutes
	buffer[3] = decToBcd(ltm->tm_hour); // Hours
	buffer[4] = decToBcd(ltm->tm_wday); // DayOfWeek
	buffer[5] = decToBcd(ltm->tm_mday); // DayOfMonth
	buffer[6] = decToBcd(ltm->tm_mon); // Month
	buffer[7] = decToBcd(ltm->tm_year - 100); // Year
	write_bytes(buffer, 8);
}

void DS1307::set_time(time_t seconds) {
	LOG << "set_time - 2 - Entered";
	tm *ltm = localtime(&seconds);
	// convert now to tm struct for UTC
	tm *gmtm = gmtime(&seconds);
	LOG << "GMTIME set device to this. " << asctime(gmtm);

	LOG << "seconds " << gmtm->tm_sec;   // seconds of minutes from 0 to 61
	LOG << "Minutes " << gmtm->tm_min;   // minutes of hour from 0 to 59
	LOG << "Hours " << gmtm->tm_hour;  // hours of day from 0 to 24
	LOG << "DayOfWeek " << gmtm->tm_wday;  // days since sunday
	LOG << "DayOfMonth " << gmtm->tm_mday;  // day of month from 1 to 31
	LOG << "Month " << gmtm->tm_mon;   // month of year from 0 to 11
	LOG << "Year " << gmtm->tm_year;  // year since 1900

	char buffer[10];
	buffer[0] = 0x00; // Command
	buffer[1] = decToBcd(gmtm->tm_sec & 0x7f); // Seconds
	buffer[2] = decToBcd(gmtm->tm_min); // Minutes
	buffer[3] = decToBcd(gmtm->tm_hour); // Hours
	buffer[4] = decToBcd(gmtm->tm_wday); // DayOfWeek
	buffer[5] = decToBcd(gmtm->tm_mday); // DayOfMonth
	buffer[6] = decToBcd(gmtm->tm_mon); // Month
	LOG << "Y1 = " << gmtm->tm_year - 100;
	LOG << "Y2 = " << decToBcd(gmtm->tm_year - 100);
	buffer[7] = decToBcd(gmtm->tm_year - 100); // Year
	write_bytes(buffer, 8);


}

void DS1307::set_time() {
	LOG << "set_time - 3 - Entered";
	time_t seconds = time(0);
	tm *gmtm = gmtime(&seconds);
	char buffer[10];
	buffer[0] = 0x00; // Command
	buffer[1] = decToBcd(gmtm->tm_sec); // Seconds
	buffer[2] = decToBcd(gmtm->tm_min); // Minutes
	buffer[3] = decToBcd(gmtm->tm_hour); // Hours
	buffer[4] = decToBcd(gmtm->tm_wday); // DayOfWeek
	buffer[5] = decToBcd(gmtm->tm_mday); // DayOfMonth
	buffer[6] = decToBcd(gmtm->tm_mon); // Month
	buffer[7] = decToBcd(gmtm->tm_year - 100); // Year
	write_bytes(buffer, 8);
}

void DS1307::get_time() {
	LOG << "get_time - Entered";

	char buffer[10];

	buffer[0] = (char)0;
	write_bytes(buffer, 1);
	int bytes_read = read_bytes(7, buffer);
	assert(bytes_read == 7);
	LOG << dec << "0 - SECOND - " << int(bcdToDec(buffer[0] & 0x7f));
	LOG << dec << "1 - MINUTE - " << int(bcdToDec(buffer[1]));
	LOG << dec << "2 - HOUR - " << int(bcdToDec(buffer[2] & 0x3f)) << " " << int(buffer[2]); // UTC 8 hours behind.
	LOG << dec << "3 - DayOfWeek - " << int(bcdToDec(buffer[3]));
	LOG << dec << "4 - DayOfMonth - " << int(bcdToDec(buffer[4])) << " " << buffer[4];
	LOG << dec << "5 - Month - " << int(bcdToDec(buffer[5]));
	LOG << dec << "6 - Year - " << int(bcdToDec(buffer[6]));

}

