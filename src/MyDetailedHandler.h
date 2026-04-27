/*
 * MyDetailedHandler.h
 *
 *  Created on: Apr 27, 2026
 *      Author: marcus
 */

#ifndef SRC_MYDETAILEDHANDLER_H_
#define SRC_MYDETAILEDHANDLER_H_

#include <Poco/Net/InvalidCertificateHandler.h>

class MyDetailedHandler: public Poco::Net::InvalidCertificateHandler {
public:
    MyDetailedHandler(bool handle_on_server_side) : Poco::Net::InvalidCertificateHandler(handle_on_server_side) {}
    void onInvalidCertificate(const void* psender, Poco::Net::VerificationErrorArgs& args) override;
};

#endif /* SRC_MYDETAILEDHANDLER_H_ */
