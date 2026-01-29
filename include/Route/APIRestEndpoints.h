/*
 * APIRestEndpoints.h
 *
 *  Created on: 29 de jan. de 2026
 *      Author: marcus.chaves
 */

#ifndef INCLUDE_ROUTE_APIRESTENDPOINTS_H_
#define INCLUDE_ROUTE_APIRESTENDPOINTS_H_

#include <string>

#include <Poco/Net/HTTPServerRequest.h>
#include <Poco/Net/HTTPServerResponse.h>

namespace Route {

class APIRestEndpoints {
public:
    APIRestEndpoints() {}
    virtual ~APIRestEndpoints() {}
    void signature(const Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response) const;
    void verify(const Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response) const;
private:
    void error(Poco::Net::HTTPServerResponse& response, const std::string& error) const;
};

} /* namespace Route */

#endif /* INCLUDE_ROUTE_APIRESTENDPOINTS_H_ */
