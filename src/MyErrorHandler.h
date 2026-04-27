/*
 * MyErrorHandler.h
 *
 *  Created on: Apr 27, 2026
 *      Author: marcus
 */

#ifndef SRC_MYERRORHANDLER_H_
#define SRC_MYERRORHANDLER_H_

#include <Poco/ErrorHandler.h>

class MyErrorHandler : public Poco::ErrorHandler {
public:
    void exception(const Poco::Exception& e) override;
    void exception(const std::exception& e) override;
    void exception() override;
};

#endif /* SRC_MYERRORHANDLER_H_ */
