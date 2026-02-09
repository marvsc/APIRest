/*
 * APIRestEndpoints.h
 *
 *  Created on: 29 de jan. de 2026
 *      Author: marcus.chaves
 */

#ifndef SRC_ROUTE_APIRESTENDPOINTS_H_
#define SRC_ROUTE_APIRESTENDPOINTS_H_

#include <string>

#include <Poco/Net/HTTPServerRequest.h>
#include <Poco/Net/HTTPServerResponse.h>

#define DEFAULT_UPLOAD_DIRECTORY "./uploads/"

namespace Route {

class APIRestEndpoints {
public:
    APIRestEndpoints() {}
    virtual ~APIRestEndpoints() {}
    static void signature(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response);
    static void verify(const Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response);
private:
    static void error(Poco::Net::HTTPServerResponse& response, const std::string& error);
    static void receive_multipart_data(Poco::Net::HTTPServerRequest& request);
};

} /* namespace Route */

#endif /* SRC_ROUTE_APIRESTENDPOINTS_H_ */
