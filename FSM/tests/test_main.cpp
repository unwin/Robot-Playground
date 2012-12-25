/*
 * test_main.cpp
 *
 *  Created on: Dec 2, 2012
 *      Author: unwin
 */




// test_main.cpp
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Main
#include <boost/test/unit_test.hpp>

// test1.cpp
#define BOOST_TEST_DYN_LINK
#ifdef STAND_ALONE
#   define BOOST_TEST_MODULE Main
#endif
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(test1_suite)

BOOST_AUTO_TEST_CASE(Test1)
{
    BOOST_CHECK(2<1);
}

BOOST_AUTO_TEST_CASE(Test2)
{
    BOOST_CHECK(2<1);
}

BOOST_AUTO_TEST_SUITE_END()

// test2.cpp
#define BOOST_TEST_DYN_LINK
#ifdef STAND_ALONE
#   define BOOST_TEST_MODULE Main
#endif
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(test2_suite)

BOOST_AUTO_TEST_CASE(Test1)
{
    BOOST_CHECK(1<2);
}

BOOST_AUTO_TEST_SUITE_END()
