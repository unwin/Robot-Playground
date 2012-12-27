/*
 * test_J2004A.cpp
 *
 *  Created on: Dec 26, 2012
 *      Author: unwin
 */


#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Main
#include <boost/test/unit_test.hpp>
#include "../../log.h"
#include "../J2004A.h"
#include <ctime>

#include <vector>

BOOST_AUTO_TEST_SUITE(test_j2004a_suite)

BOOST_AUTO_TEST_CASE(test_J2004A)
{
	LOG << "test_J2004A";

	J2004A *j2004a = new J2004A(1);

	j2004a->clear_display();


	// Need asserts that it set it correct
	//BOOST_CHECK( true );
	//BOOST_ERROR( "some error 1" );
	//BOOST_REQUIRE_EQUAL( 1, 2 );
	//BOOST_FAIL( "Should never reach this line" );
}

BOOST_AUTO_TEST_SUITE_END()

