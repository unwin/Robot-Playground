/*
 * log.h
 *
 *  Created on: Dec 1, 2012
 *      Author: unwin
 */

#ifndef LOG_H_
#define LOG_H_
#include <string>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <boost/ref.hpp>
#include <boost/bind.hpp>
#include <boost/log/core.hpp>
#include <boost/log/common.hpp>
#include <boost/log/attributes.hpp>
#include <boost/log/core/record.hpp>
#include <boost/log/attributes/value_visitation.hpp>
#include <boost/log/utility/init/from_stream.hpp>
#include <boost/log/utility/init/common_attributes.hpp>
#include <boost/log/utility/init/formatter_parser.hpp>

namespace logging = boost::log;
namespace attrs = boost::log::attributes;
namespace src = boost::log::sources;

enum severity_level
{
    normal,
    notification,
    warning,
    error,
    critical
};



class Logger{
public:
   static Logger* Instance();
   src::severity_logger< > *lg;


private:
   Logger();  // Private so that it can  not be called
   //Logger(Logger const&){};       // copy constructor is private
   //Logger& operator=(Logger const&){};  // assignment operator is private
   static Logger* logger_singleton_instance;
};




#define LOG BOOST_LOG_SEV(*Logger::Instance()->lg, normal)
#define LOG_NOTIFICATION BOOST_LOG_SEV(*Logger::Instance()->lg, notification)
#define LOG_WARNING BOOST_LOG_SEV(*Logger::Instance()->lg, warning)
#define LOG_ERROR BOOST_LOG_SEV(*Logger::Instance()->lg, error)
#define LOG_CRITICAL BOOST_LOG_SEV(*Logger::Instance()->lg, critical)



#endif /* LOG_H_ */
