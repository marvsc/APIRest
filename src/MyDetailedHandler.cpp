/*
 * MyDetailedHandler.cpp
 *
 *  Created on: Apr 27, 2026
 *      Author: marcus
 */

#include "MyDetailedHandler.h"

#include <Poco/Net/VerificationErrorArgs.h>

void MyDetailedHandler::onInvalidCertificate(const void* psender, Poco::Net::VerificationErrorArgs& args) {
    std::printf("Certificate error: %s\n", args.errorMessage().c_str());
    std::printf("Error code: %d\n", args.errorNumber());
    std::printf("Subject: %s\n", args.certificate().subjectName().c_str());
}

