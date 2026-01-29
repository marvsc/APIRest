/*
 * APIRestEndpoints.cpp
 *
 *  Created on: 29 de jan. de 2026
 *      Author: marcus.chaves
 */

#include "../../include/Route/APIRestEndpoints.h"

#include <Poco/JSON/Object.h>

namespace Route {

static const std::string Route::CONTENT_TYPE_JSON = "application/json";
static const std::string Route::CONTENT_TYPE_PLAIN_TEXT = "text/plain; charset=utf-8";

void Route::APIRestEndpoints::signature(const Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response) const {
    try {
        std::string body("ASSINATURA");
        response.setStatus(Poco::Net::HTTPServerResponse::HTTP_OK);
        response.setContentType(CONTENT_TYPE_PLAIN_TEXT);
        response.send().write(body.c_str(), body.size());
    } catch (std::exception& e) {
        error(response, std::string(e.what()));
    } catch (...) {
        error(response, std::string("Unknown error"));
    }
}

void Route::APIRestEndpoints::verify(const Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response) const {
    try {
        Poco::JSON::Object body;
        body.set("JSON", "JSON");
        response.setStatus(Poco::Net::HTTPServerResponse::HTTP_OK);
        response.setContentType(CONTENT_TYPE_JSON);
        std::ostream& response_stream = response.send();
        body.stringify(response_stream);
    } catch (std::exception& e) {
        error(response, std::string(e.what()));
    } catch (...) {
        error(response, std::string("Unknown error"));
    }
}

void Route::error(Poco::Net::HTTPServerResponse& response, const std::string& error) const {
    response.setStatus(Poco::Net::HTTPServerResponse::HTTP_INTERNAL_SERVER_ERROR);
    response.setContentType(CONTENT_TYPE_PLAIN_TEXT);
    response.send().write(error.c_str(), error.size());
}

} /* namespace Route */
