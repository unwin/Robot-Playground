/*
 * serial.hpp
 *
 *  Created on: Dec 15, 2012
 *      Author: unwin
 */

#ifndef SERIAL_HPP_
#define SERIAL_HPP_


#include <iostream>
#include <ostream>
#include <string>

#include <boost/thread/thread.hpp>
#include <boost/asio.hpp>
#include "../log.h"

using namespace std;
/** This code requires 'boost' to be successfully installed and when compiled will require the boost libaries to be included.
The original code source as of this writting was found here:

http://www.webalice.it/fede.tft/serial_port/serial_port.html

*/

class SimpleSerial
{
public:
    /**
     * Constructor.
     * \param port device name, example "/dev/ttyUSB0" or "COM4"
     * \param baud_rate communication speed, example 9600 or 115200
     * \throws boost::system::system_error if cannot open the
     * serial device
     */
    SimpleSerial(std::string port, unsigned int baud_rate)
    : io(), serial(io,port)
    {
        serial.set_option(boost::asio::serial_port_base::baud_rate(baud_rate));
    }

    /**
     * Write a string to the serial device.
     * \param s string to write
     * \throws boost::system::system_error on failure
     */
    void writeString(std::string s)
    {
        boost::asio::write(serial,boost::asio::buffer(s.c_str(),s.size()));
    }

    /**
     * Blocks until a line is received from the serial device. A line is denoted by a final '\n' character
     * Eventual '\n' or '\r\n' characters at the end of the string are removed.
     * \return a string containing the received line
     * \throws boost::system::system_error on failure
     */
    std::string readLine()
    {
        //Reading data char by char, code is optimized for simplicity, not speed
        using namespace boost;
        char c;
        std::string result;
        for(;;)
        {
            asio::read(serial,asio::buffer(&c,1));
            switch(c)
            {
                case '\r':
                    break;
                case '\n':
                    return result;
                default:
                    result+=c;
            }
        }
    }

private:
    boost::asio::io_service io;
    boost::asio::serial_port serial;
};


#endif /* SERIAL_HPP_ */
