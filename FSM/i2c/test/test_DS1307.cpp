/*
 * test_DA1307.cpp
 *
 *  Created on: Dec 25, 2012
 *      Author: unwin
 */



#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Main
#include <boost/test/unit_test.hpp>
#include "../../log.h"
#include "../DS1307.h"
#include <ctime>

#include <vector>

BOOST_AUTO_TEST_SUITE(test_ds1307_suite)

BOOST_AUTO_TEST_CASE(test_i2c_get_time)
{
	LOG << "test_i2c_get_time";

	DS1307 *ds1307 = new DS1307(1);

	ds1307->get_time();

}

BOOST_AUTO_TEST_CASE(test_DA1307_set_get_fixed_time_components)
{
	LOG << "test_DA1307_set_get_fixed_time_components";

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

BOOST_AUTO_TEST_CASE(test_DA1307_set_get_fixed_time_seconds)
{
	LOG << "test_DA1307_set_get_fixed_time_seconds";

	DS1307 *ds1307 = new DS1307(1);

	ds1307->set_time(time(0));  // Need to add time passed in here
	ds1307->get_time();
	// Need asserts that it set it correct
}

BOOST_AUTO_TEST_CASE(test_DA1307_set_get_current_time)
{
	LOG << "test_DA1307_set_get_current_time";

	DS1307 *ds1307 = new DS1307(1);

	ds1307->set_time();  // Need to add current time passed in here
	ds1307->get_time();
	// Need asserts that it set it correct
	//BOOST_CHECK( true );
	//BOOST_ERROR( "some error 1" );
	//BOOST_REQUIRE_EQUAL( 1, 2 );
	//BOOST_FAIL( "Should never reach this line" );
}

BOOST_AUTO_TEST_SUITE_END()
