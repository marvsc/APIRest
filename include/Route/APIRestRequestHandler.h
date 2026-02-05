/*
 * APIRestRequestHandler.h
 *
 *  Created on: 27 de jan. de 2026
 *      Author: marcus.chaves
 */

#ifndef INCLUDE_ROUTE_APIRESTREQUESTHANDLER_H_
#define INCLUDE_ROUTE_APIRESTREQUESTHANDLER_H_

#include <map>
#include <functional>

#include <Poco/Net/HTTPRequestHandler.h>
#include <Poco/Net/HTTPServerRequest.h>
#include <Poco/Net/HTTPServerResponse.h>

namespace Route {

class APIRestRequestHandler: public Poco::Net::HTTPRequestHandler {
public:
    APIRestRequestHandler() {}
    APIRestRequestHandler(std::map<std::string, std::function<void(Poco::Net::HTTPServerRequest&,
            Poco::Net::HTTPServerResponse&)>> routes) : routes_(routes) {}
    virtual ~APIRestRequestHandler() {
        routes_.clear();
    }
    void add_route(const std::string &route, std::function<void(Poco::Net::HTTPServerRequest&,
            Poco::Net::HTTPServerResponse&)> callback) {
        routes_.emplace(route, callback);
    }
    void handleRequest(Poco::Net::HTTPServerRequest &request,
            Poco::Net::HTTPServerResponse &response) override;
private:
    std::map<std::string, std::function<void(Poco::Net::HTTPServerRequest&,
            Poco::Net::HTTPServerResponse&)>> routes_;
};

} /* namespace Route */

#endif /* INCLUDE_ROUTE_APIRESTREQUESTHANDLER_H_ */
