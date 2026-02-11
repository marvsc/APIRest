/*
 * Router.cpp
 *
 *  Created on: 24 de jun. de 2025
 *      Author: marcus.chaves
 */

#include "APIRestRequestHandlerFactory.h"

#include "Route/APIRestRequestHandler.h"

APIRestRequestHandlerFactory::APIRestRequestHandlerFactory(const std::string& upload_dir) :
        endpoints_(upload_dir), HTTPRequestHandlerFactory::HTTPRequestHandlerFactory() {}

Poco::Net::HTTPRequestHandler* APIRestRequestHandlerFactory::createRequestHandler(
        const Poco::Net::HTTPServerRequest &request) {
    auto signature = [&endpoints = endpoints_](Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response) {
        endpoints.signature(request, response);
    };
    auto verify = [&endpoints = endpoints_](Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response) {
        endpoints.verify(request, response);
    };
    return new Route::APIRestRequestHandler({
        { "/signature", signature },
        { "/verify", verify }
    });
}
