/*
 * test_vision.cpp
 *
 *  Created on: Dec 5, 2012
 *      Author: unwin
 */


// test_vision.cpp
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Main
#include <boost/test/unit_test.hpp>


BOOST_AUTO_TEST_SUITE(test_vision_suite)

BOOST_AUTO_TEST_CASE(test_vision_connected)
{
    BOOST_CHECK(2<1);
}

BOOST_AUTO_TEST_CASE(test_vision_disconnected)
{
    BOOST_CHECK(2<1);
}

BOOST_AUTO_TEST_SUITE_END()
