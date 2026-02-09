/*
 * APIRestRequestHandler.cpp
 *
 *  Created on: 27 de jan. de 2026
 *      Author: marcus.chaves
 */

#include "APIRestRequestHandler.h"

#include <Poco/URI.h>

namespace Route {

void APIRestRequestHandler::handleRequest(Poco::Net::HTTPServerRequest &request,
        Poco::Net::HTTPServerResponse &response) {
    std::string path(Poco::URI(request.getURI()).getPath());
    if (!path.empty() && path.back() == '/') {
        path.pop_back();
    }
    routes_.at(path)(request, response);
}

} /* namespace Route */
