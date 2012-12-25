/*
 * log.cpp
 *
 *  Created on: Dec 1, 2012
 *      Author: unwin
 */




// #define BOOST_ALL_DYN_LINK 1

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




#include "i2c/I2C_Exceptions.h"



#include "log.h"

namespace logging = boost::log;
namespace attrs = boost::log::attributes;
namespace src = boost::log::sources;

//#ifndef LOG_CPP_
//#define LOG_CPP_




//! Our custom formatter for the scope list


/*!
 * This function creates a formatter for the MyScopes attribute.
 * It effectively associates the attribute with the scope_list_formatter class
 */

BOOST_LOG_INLINE_GLOBAL_LOGGER_DEFAULT(test_lg, src::severity_logger< >)

struct scope_list_formatter
{
    typedef void result_type;
    typedef attrs::basic_named_scope< char >::value_type scope_stack;

    explicit scope_list_formatter(std::string const& name) :
        name_(name)
    {
    }
    void operator()(std::ostream& strm, logging::record const& rec) const
    {
        // We need to acquire the attribute value from the log record
        logging::visit< scope_stack >
        (
            name_,
            rec.attribute_values(),
            boost::bind(&scope_list_formatter::format, boost::ref(strm), _1)
        );
    }

private:
    //! This is where our custom formatting takes place
    static void format(std::ostream& strm, scope_stack const& scopes)
    {
        scope_stack::const_iterator it = scopes.begin(), end = scopes.end();

        for (; it != end; ++it)
        {
            strm << "\t" << it->scope_name << " [" << it->file_name << ":" << it->line << "]\n";
        }
    }

private:
    std::string name_;
};

typedef logging::formatter_types< char > types;

types::formatter_type my_scopes_formatter_factory(types::string_type const& attr_name, types::formatter_factory_args const& args) {
	return types::formatter_type(scope_list_formatter(attr_name));
}




Logger::Logger() {
    // First thing - register the custom formatter for MyScopes
    logging::register_formatter_factory("MyScopes", &my_scopes_formatter_factory);

    // Then load the settings from the file
    std::ifstream settings("settings.txt");
    if (!settings.is_open())
        throw std::runtime_error("Could not open settings.txt file");
    logging::init_from_stream(settings);

    // Add some attributes
    logging::add_common_attributes();

    logging::core::get()->add_global_attribute("MyScopes", attrs::named_scope());


	lg = &test_lg::get();

};

Logger* Logger::m_pInstance = NULL;
Logger* Logger::Instance()
{
   if (!m_pInstance) { // Only allow one instance of class to be generated.
      m_pInstance = new Logger();
   }



   return m_pInstance;
};

Logger *l = Logger::Instance();



/*
void init_logging(Logger * l) {
    // First thing - register the custom formatter for MyScopes
    logging::register_formatter_factory("MyScopes", &my_scopes_formatter_factory);

    // Then load the settings from the file
    std::ifstream settings("settings.txt");
    if (!settings.is_open())
        throw std::runtime_error("Could not open settings.txt file");
    logging::init_from_stream(settings);

    // Add some attributes
    logging::add_common_attributes();

    logging::core::get()->add_global_attribute("MyScopes", attrs::named_scope());


	src::severity_logger< >& lg = test_lg::get();
	l->lg = &lg;
}
*/
/*
int main(int argc, char** argv) {



	BOOST_LOG(*Logger::Instance()->lg) << "LOGGING STARTED";
	BOOST_LOG_SEV(*Logger::Instance()->lg, critical) << "test";
    BOOST_LOG_FUNCTION();


    BOOST_LOG_SEV(*Logger::Instance()->lg, critical) << "This is a critical severity record";

    BOOST_LOG_NAMED_SCOPE("random name");
    BOOST_LOG_SEV(*Logger::Instance()->lg, error) << "This is a error severity record";
	//throw IoError("Did not write enough bytes, should probably loop this...");
}
*/

//#endif /* LOG_CPP_ */














