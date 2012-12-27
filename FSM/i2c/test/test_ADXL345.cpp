/*
 * test_ADXL345.cpp
 *
 *  Created on: Dec 25, 2012
 *      Author: unwin
 */



#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Main
#include <boost/test/unit_test.hpp>
#include "../../log.h"
#include "../ADXL345.h"
#include <ctime>

#include <vector>

BOOST_AUTO_TEST_SUITE(test_adxl345_suite)

BOOST_AUTO_TEST_CASE(test_adxl345)
{
	LOG << "test_adxl345";

	ADXL345 *adxl345 = new ADXL345(1);

	adxl345->read_acceleration();
	while (1) {
		adxl345->read_acceleration();
		sleep(1);
	}
	// Need asserts that it set it correct
	//BOOST_CHECK( true );
	//BOOST_ERROR( "some error 1" );
	//BOOST_REQUIRE_EQUAL( 1, 2 );
	//BOOST_FAIL( "Should never reach this line" );
}


BOOST_AUTO_TEST_SUITE_END()

