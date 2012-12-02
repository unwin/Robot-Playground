/*
 * log.h
 *
 *  Created on: Dec 1, 2012
 *      Author: unwin
 */

#ifndef LOG_H_
#define LOG_H_


#include <boost/log/common.hpp>
#include <boost/log/formatters.hpp>
#include <boost/log/filters.hpp>

#include <boost/log/utility/init/to_file.hpp>
#include <boost/log/utility/init/to_console.hpp>
#include <boost/log/utility/init/common_attributes.hpp>

//#include <boost/log/attributes/timer.hpp>

#include <boost/log/sources/logger.hpp>
//#include <boost/log/trivial.hpp>



namespace logging = boost::log;
namespace fmt = boost::log::formatters;
namespace flt = boost::log::filters;
namespace sinks = boost::log::sinks;
namespace attrs = boost::log::attributes;
namespace src = boost::log::sources;
namespace keywords = boost::log::keywords;

using boost::shared_ptr;

enum severity_level
{
    normal,
    notification,
    warning,
    error,
    critical
};

using namespace std;

src::severity_logger< severity_level > slg;

#define LOG BOOST_LOG_SEV(slg, normal)
#define NOTIFICATION BOOST_LOG_SEV(slg, notification)
#define WARN BOOST_LOG_SEV(slg, warning)
#define ERROR BOOST_LOG_SEV(slg, error)
#define CRITICAL BOOST_LOG_SEV(slg, critical)


// The formatting logic for the severity level
template< typename CharT, typename TraitsT >
inline std::basic_ostream< CharT, TraitsT >& operator<< (
    std::basic_ostream< CharT, TraitsT >& strm,
    severity_level lvl
)
{
    static const char* const str[] =
    {
        "NORMAL",
        "NOTIFICATION",
        "WARNING",
        "ERROR",
        "CRITICAL"
    };
    if (static_cast< std::size_t >(lvl) < (sizeof(str) / sizeof(*str)))
        strm << str[lvl];
    else
        strm << static_cast< int >(lvl);
    return strm;
}

void init_logging() {

    // Create a syslog sink
	logging::init_log_to_console(
		std::clog,
		keywords::format = fmt::format("%1% <%2%> %3%")
			% fmt::date_time("TimeStamp", std::nothrow)
			//% fmt::time_duration("Uptime", std::nothrow)
			% fmt::attr< severity_level >("Severity", std::nothrow)
			% fmt::message()
	);

	// One can also use lambda expressions to setup filters and formatters
	logging::init_log_to_file
	(
		"sample.log",
		keywords::filter = flt::attr< severity_level >("Severity", std::nothrow) >= warning,
		keywords::format = fmt::format("%1% <%2%> %3%")
			% fmt::date_time("TimeStamp", std::nothrow)
			//% fmt::time_duration("Uptime", std::nothrow)
			% fmt::attr< severity_level >("Severity", std::nothrow)
			% fmt::message()
	);

	// Also let's add some commonly used attributes, like timestamp and record counter.
	logging::add_common_attributes();

	// Now our logs will be written both to the console and to the file.
	// Let's do a quick test and output something. We have to create a logger for this.
	src::logger lg;

	// And output...
	BOOST_LOG(lg) << "LOGGING STARTED";

	// Now, let's try logging with severity


	// Let's pretend we also want to profile our code, so add a special timer attribute.
	//slg.add_attribute("Uptime", attrs::timer());

}


#endif /* LOG_H_ */
