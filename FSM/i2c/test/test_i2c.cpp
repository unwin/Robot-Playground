/*
 * test_vision.cpp
 *
 *  Created on: Dec 5, 2012
 *      Author: unwin
 */


// test_i2c.cpp

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Main
#include <boost/test/unit_test.hpp>
#include "../../log.h"
#include "../DS1307.h"
#include "../ADXL345.h"
#include <ctime>

#include <vector>

BOOST_AUTO_TEST_SUITE(test_i2c_suite)

BOOST_AUTO_TEST_CASE(test_i2c_inventory1)
{
	LOG << "test_i2c_inventory1  (0)";
	i2c *bus = new i2c(0);
	device_map result = bus->scan_bus();

	for (device_map::iterator it = result.begin(); it != result.end(); ++it) {
		string s = it->second;
		LOG << "\t" << it->second << " - Address:0x" << hex << it->first;
	}
}

BOOST_AUTO_TEST_CASE(test_i2c_inventory2)
{
	LOG << "test_i2c_inventory2  (1)";
	i2c *bus = new i2c(1);
	device_map result = bus->scan_bus();

	for (device_map::iterator it = result.begin(); it != result.end(); ++it) {
		LOG << "\t" << it->second << " - Address:0x" << hex << it->first;
	}
}

BOOST_AUTO_TEST_CASE(test_i2c_get_time)
{
	LOG << "test_i2c_get_time";

	DS1307 *ds1307 = new DS1307(1);

	ds1307->get_time();

}

BOOST_AUTO_TEST_CASE(test_i2c_set_get_fixed_time_components)
{
	LOG << "test_i2c_set_get_fixed_time_components";

	DS1307 *ds1307 = new DS1307(1);

	int h = 5;
	int m = 6;
	int s = 7;
	int wd = 9;
	int md = 10;
	int mm = 11;
	int yy = 2012;

	ds1307->set_time(h, m, s, wd, md, mm, yy);  // Need to add time passed in here
	ds1307->get_time();
	// Need asserts that it set it correct
}

BOOST_AUTO_TEST_CASE(test_i2c_set_get_fixed_time_seconds)
{
	LOG << "test_i2c_set_get_fixed_time_seconds";

	DS1307 *ds1307 = new DS1307(1);

	ds1307->set_time(time(0));  // Need to add time passed in here
	ds1307->get_time();
	// Need asserts that it set it correct
}

BOOST_AUTO_TEST_CASE(test_i2c_set_get_current_time)
{
	LOG << "test_i2c_set_get_current_time";

	DS1307 *ds1307 = new DS1307(1);

	ds1307->set_time();  // Need to add current time passed in here
	ds1307->get_time();
	// Need asserts that it set it correct
	//BOOST_CHECK( true );
	//BOOST_ERROR( "some error 1" );
	//BOOST_REQUIRE_EQUAL( 1, 2 );
	//BOOST_FAIL( "Should never reach this line" );
}


BOOST_AUTO_TEST_CASE(test_adxl345)
{
	LOG << "test_adxl345";

	ADXL345 *adxl345 = new ADXL345(1);

	adxl345->read_acceleration();

	// Need asserts that it set it correct
	//BOOST_CHECK( true );
	//BOOST_ERROR( "some error 1" );
	//BOOST_REQUIRE_EQUAL( 1, 2 );
	//BOOST_FAIL( "Should never reach this line" );
}


BOOST_AUTO_TEST_SUITE_END()
