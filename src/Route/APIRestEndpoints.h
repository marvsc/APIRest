/*
 * APIRestEndpoints.h
 *
 *  Created on: 29 de jan. de 2026
 *      Author: marcus.chaves
 */

#ifndef SRC_ROUTE_APIRESTENDPOINTS_H_
#define SRC_ROUTE_APIRESTENDPOINTS_H_

#include "APIRestFilePartHandler.h"

#include <string>

#include <Poco/Net/HTTPServerRequest.h>
#include <Poco/Net/HTTPServerResponse.h>

#define DEFAULT_UPLOAD_DIRECTORY "."

namespace Route {

class APIRestEndpoints {
public:
    APIRestEndpoints() : file_part_handler_() {}
    APIRestEndpoints(const std::string& upload_dir) : file_part_handler_(upload_dir) {}
    virtual ~APIRestEndpoints() {}
    void signature(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response);
    void verify(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response);
private:
    APIRestFilePartHandler file_part_handler_;
};

} /* namespace Route */

#endif /* SRC_ROUTE_APIRESTENDPOINTS_H_ */
