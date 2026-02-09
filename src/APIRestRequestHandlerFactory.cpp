/*
 * Router.cpp
 *
 *  Created on: 24 de jun. de 2025
 *      Author: marcus.chaves
 */

#include "APIRestRequestHandlerFactory.h"

#include "Route/APIRestRequestHandler.h"
#include "Route/APIRestEndpoints.h"

Poco::Net::HTTPRequestHandler* APIRestRequestHandlerFactory::createRequestHandler(
        const Poco::Net::HTTPServerRequest &request) {
    return new Route::APIRestRequestHandler({
        { "/signature", Route::APIRestEndpoints::signature },
        { "/verify", Route::APIRestEndpoints::verify }
    });
}
