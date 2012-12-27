/*
 * test_vision.cpp
 *
 *  Created on: Dec 5, 2012
 *      Author: unwin
 */


// test_i2c.cpp

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Main
#include <iostream>
#include <ostream>
#include <string>
#include <map>
#include <assert.h>
#include <boost/test/unit_test.hpp>
#include "../../log.h"
#include "../i2c.h"

#include <vector>

BOOST_AUTO_TEST_SUITE(test_i2c_suite)

BOOST_AUTO_TEST_CASE(test_i2c_inventory1)
{
	LOG << "test_i2c_inventory1  (0)";
	i2c *bus = i2c::Instance(0);
	device_map result = bus->scan_bus();

	for (device_map::iterator it = result.begin(); it != result.end(); ++it) {
		LOG << "\t" << it->second << " - Address:0x" << std::hex << it->first;
	}
}

BOOST_AUTO_TEST_CASE(test_i2c_inventory2)
{
	LOG << "test_i2c_inventory2  (1)";
	i2c *bus = i2c::Instance(1);
	device_map result = bus->scan_bus();

	for (device_map::iterator it = result.begin(); it != result.end(); ++it) {
		LOG << "\t" << it->second << " - Address:0x" << std::hex << it->first;
	}
}


BOOST_AUTO_TEST_SUITE_END()
