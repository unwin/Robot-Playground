/*
 * test_NEO_6.cpp
 *
 *  Created on: Dec 28, 2012
 *      Author: unwin
 */


#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Main
#include <boost/test/unit_test.hpp>
#include "../../log.h"
#include "../NEO_6.h"
#include <ctime>

#include <vector>

BOOST_AUTO_TEST_SUITE(test_NEO_6_suite)

BOOST_AUTO_TEST_CASE(test_NEO_6)
{
	LOG << "test_NEO_6";

	NEO_6 *neo_6 = new NEO_6(1);

	// Need asserts that it set it correct
	//BOOST_CHECK( true );
	//BOOST_ERROR( "some error 1" );
	//BOOST_REQUIRE_EQUAL( 1, 2 );
	//BOOST_FAIL( "Should never reach this line" );
}

BOOST_AUTO_TEST_SUITE_END()
