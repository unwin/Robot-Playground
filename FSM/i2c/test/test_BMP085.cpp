/*
 * test_BMP085.cpp
 *
 *  Created on: Dec 29, 2012
 *      Author: unwin
 */





#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Main
#include <boost/test/unit_test.hpp>
#include "../../log.h"
#include "../BMP085.h"
#include <ctime>

#include <vector>

BOOST_AUTO_TEST_SUITE(test_BMP085_suite)

BOOST_AUTO_TEST_CASE(test_BMP085)
{
	LOG << "test_BMP085";

	BMP085 *bmp085 = new BMP085(1);

	while (1) {
		bmp085->read_data();
		sleep(1);
	}

	// Need asserts that it set it correct
	//BOOST_CHECK( true );
	//BOOST_ERROR( "some error 1" );
	//BOOST_REQUIRE_EQUAL( 1, 2 );
	//BOOST_FAIL( "Should never reach this line" );
}


BOOST_AUTO_TEST_SUITE_END()

