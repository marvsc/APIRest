/*
 * Router.cpp
 *
 *  Created on: 24 de jun. de 2025
 *      Author: marcus.chaves
 */

#include "APIRestRequestHandlerFactory.h"

#include "Route/APIRestRequestHandler.h"
#include "Route/APIRestEndpoints.h"

APIRestRequestHandlerFactory::APIRestRequestHandlerFactory(const std::string& upload_dir) :
        upload_dir_(upload_dir), HTTPRequestHandlerFactory::HTTPRequestHandlerFactory() {}

Poco::Net::HTTPRequestHandler* APIRestRequestHandlerFactory::createRequestHandler(
        const Poco::Net::HTTPServerRequest &request) {
    Route::APIRestEndpoints endpoints;
    return new Route::APIRestRequestHandler({
        { "/signature", std::bind(&Route::APIRestEndpoints::signature, &endpoints, std::placeholders::_1, std::placeholders::_2, upload_dir_) },
        { "/verify", std::bind(&Route::APIRestEndpoints::verify, &endpoints, std::placeholders::_1, std::placeholders::_2, upload_dir_) }
    });
}
