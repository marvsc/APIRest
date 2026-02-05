/*
 * APIRestRequestHandler.cpp
 *
 *  Created on: 27 de jan. de 2026
 *      Author: marcus.chaves
 */

#include "../../include/Route/APIRestRequestHandler.h"

#include <Poco/URI.h>

namespace Route {

void APIRestRequestHandler::handleRequest(Poco::Net::HTTPServerRequest &request,
        Poco::Net::HTTPServerResponse &response) {
    routes_.at(Poco::URI(request.getURI()).getPath())(request, response);
}

} /* namespace Route */
