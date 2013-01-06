/*
 * test_HMC5883.cpp
 *
 *  Created on: Jan 3, 2013
 *      Author: unwin
 */







#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Main
#include <boost/test/unit_test.hpp>
#include "../../log.h"
#include "../HMC5883.h"
#include <ctime>

#include <vector>

BOOST_AUTO_TEST_SUITE(test_HMC5883_suite)

BOOST_AUTO_TEST_CASE(test_HMC5883)
{
	short int x = 0;
	short int y = 0;
	short int z = 0;
	float heading = 0;
	LOG << "test_HMC5883";

	HMC5883 *hmc5883 = new HMC5883(1);

	while (1) {
		hmc5883->read_orientation(x, y, z);
		LOG << "----------";
		heading = hmc5883->get_2d_heading();
		LOG << "RAW x = " << x << " Y = " << y << " z = " << z << " HEADING = " << heading;
		sleep(1);
	}

	// Need asserts that it set it correct
	//BOOST_CHECK( true );
	//BOOST_ERROR( "some error 1" );
	//BOOST_REQUIRE_EQUAL( 1, 2 );
	//BOOST_FAIL( "Should never reach this line" );
}


BOOST_AUTO_TEST_SUITE_END()

