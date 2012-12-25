/*
 * test_log.cpp
 *
 *  Created on: Dec 24, 2012
 *      Author: unwin
 */

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Main
#include <boost/test/unit_test.hpp>
#include "../log.h"


#include <vector>
#include <exception>
using namespace std;

class myexception: public exception
{
  virtual const char* what() const throw()
  {
    return "My exception happened";
  }
} myex;


BOOST_AUTO_TEST_SUITE(test_i2c_suite)

BOOST_AUTO_TEST_CASE(test_default_log)
{
	BOOST_LOG_NAMED_SCOPE("test_default_log");
	LOG << "default level log";
}

BOOST_AUTO_TEST_CASE(test_notification_log)
{
	BOOST_LOG_NAMED_SCOPE("test_notification_log");
	LOG_NOTIFICATION << "notification level log";
}

BOOST_AUTO_TEST_CASE(test_warning_log)
{
	LOG_WARNING << "warning level log";
}

BOOST_AUTO_TEST_CASE(test_error_log)
{
	LOG_ERROR << "error level log";
}

BOOST_AUTO_TEST_CASE(test_critical_log)
{
	LOG_CRITICAL << "critical level log";
}

BOOST_AUTO_TEST_CASE(misc)
{

	BOOST_LOG(*Logger::Instance()->lg) << "LOGGING STARTED";
	BOOST_LOG_SEV(*Logger::Instance()->lg, critical) << "test";
	BOOST_LOG_FUNCTION();


	BOOST_LOG_SEV(*Logger::Instance()->lg, critical) << "This is a critical severity record";

	BOOST_LOG_NAMED_SCOPE("random name");
	BOOST_LOG_SEV(*Logger::Instance()->lg, error) << "This is a error severity record";

	BOOST_LOG_FUNCTION();
	try {
	    throw myex;
	} catch (exception& e) {
		LOG << "exception caught";
	}
}


BOOST_AUTO_TEST_SUITE_END()
