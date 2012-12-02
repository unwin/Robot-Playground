/*
 * FSM_Exceptions.h
 *
 *  Created on: Nov 2, 2012
 *      Author: Unwin
 */

#ifndef FSM_EXCEPTIONS_H_
#define FSM_EXCEPTIONS_H_

#include <exception>
#define DEFAULT_REASON "Reason Not specified. Please MOCK the programmer."
#include "log.h"

using namespace std;

class StateException: public std::exception{
private:
	std::string reason;
public:
	StateException() : exception() {
		this->reason = DEFAULT_REASON;
	};
	StateException(std::string reason) : exception(){
		this->reason = reason;
	};
    ~StateException() throw () {

    };

    const char* what()  {
    	string s = "StateException : " + this->reason + " " + std::exception::what();
    	ERROR << s;
    	return s.c_str();
    }

};

class NotImplemented: public exception {
private:
	std::string reason;
public:
	NotImplemented() : exception(){
		this->reason = DEFAULT_REASON;
	};

	NotImplemented(std::string reason) : exception(){
		this->reason = reason;
	};

    ~NotImplemented() throw () {

    };

    const char* what()  {
		string s = "StateException : " + this->reason + " " + std::exception::what();
		ERROR << s;
		return s.c_str();
    }
};

class CommandNotFound: public exception {
private:
	std::string reason;
public:
	CommandNotFound() : exception(){
		this->reason = DEFAULT_REASON;
	};

	CommandNotFound(std::string reason) : exception(){
		this->reason = reason;
	};

    ~CommandNotFound() throw () {

    };

    const char* what()  {
		string s = "StateException : " + this->reason + " " + std::exception::what();
		std::cout << s << std::endl;
		return s.c_str();
    }

};

#endif /* FSM_EXCEPTIONS_H_ */
