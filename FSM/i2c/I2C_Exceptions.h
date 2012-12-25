/*
 * I2C_Exceptions.h
 *
 *  Created on: Dec 22, 2012
 *      Author: unwin
 */

#ifndef I2C_EXCEPTIONS_H_
#define I2C_EXCEPTIONS_H_

#define DEFAULT_REASON "Reason Not specified. Please MOCK the programmer."


using namespace std;



class IoError: public exception {
private:
	std::string reason;
public:
	IoError();
	IoError(std::string reason);
    ~IoError() throw ();

    const char* what();
};

#endif /* I2C_EXCEPTIONS_H_ */
