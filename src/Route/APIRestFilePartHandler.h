/*
 * FilePartHandler.h
 *
 *  Created on: Feb 8, 2026
 *      Author: marcus
 */

#ifndef SRC_ROUTE_APIRESTFILEPARTHANDLER_H_
#define SRC_ROUTE_APIRESTFILEPARTHANDLER_H_

#include <Poco/Net/PartHandler.h>

namespace Route {

class APIRestFilePartHandler : public Poco::Net::PartHandler {
public:
    APIRestFilePartHandler() {}
    APIRestFilePartHandler(const std::string& upload_dir) : upload_dir_(upload_dir) {}
    virtual ~APIRestFilePartHandler() {}
    void handlePart(const Poco::Net::MessageHeader& header, std::istream& stream) override;
private:
    std::string upload_dir_;
    std::string filename_;
};

} /* namespace Route */

#endif /* SRC_ROUTE_APIRESTFILEPARTHANDLER_H_ */
