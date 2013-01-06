/*
 * test_L3G4200D.cpp
 *
 *  Created on: Dec 25, 2012
 *      Author: unwin
 */




#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Main
#include <boost/test/unit_test.hpp>
#include "../../log.h"
#include "../L3G4200D.h"
#include <ctime>

#include <vector>

BOOST_AUTO_TEST_SUITE(test_i2c_suite)

BOOST_AUTO_TEST_CASE(test_L3G4200D)
{
	short int x;
	short int y;
	short int z;
	LOG << "test_L3G4200D";

	L3G4200D *l3g4200d = new L3G4200D(1);

	while (1) {
		l3g4200d->read_gyro(x, y, z);
		LOG << "x = " << x << " Y = " << y << " z = " << z;
		sleep(1);
	}
	// Need asserts that it set it correct
	//BOOST_CHECK( true );
	//BOOST_ERROR( "some error 1" );
	//BOOST_REQUIRE_EQUAL( 1, 2 );
	//BOOST_FAIL( "Should never reach this line" );
}

BOOST_AUTO_TEST_SUITE_END()

