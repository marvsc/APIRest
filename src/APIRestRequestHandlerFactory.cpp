/*
 * Router.cpp
 *
 *  Created on: 24 de jun. de 2025
 *      Author: marcus.chaves
 */

#include "../include/APIRestRequestHandlerFactory.h"
#include "../include/Route/APIRestRequestHandler.h"

Poco::Net::HTTPRequestHandler* APIRestRequestHandlerFactory::createRequestHandler(
        const Poco::Net::HTTPServerRequest &request) {
    return new Route::APIRestRequestHandler;
}
