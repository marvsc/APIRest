/*
 * MyErrorHandler.h
 *
 *  Created on: Apr 27, 2026
 *      Author: marcus
 */

#ifndef SRC_APIRESTERRORHANDLER_H_
#define SRC_APIRESTERRORHANDLER_H_

#include <Poco/ErrorHandler.h>

class APIRestErrorHandler : public Poco::ErrorHandler {
public:
    void exception(const Poco::Exception& e) override;
    void exception(const std::exception& e) override;
    void exception() override;
private:
    std::string get_demangled_class_name(const char* name) const;
};

#endif /* SRC_APIRESTERRORHANDLER_H_ */
