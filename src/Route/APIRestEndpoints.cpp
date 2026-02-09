/*
 * APIRestEndpoints.cpp
 *
 *  Created on: 29 de jan. de 2026
 *      Author: marcus.chaves
 */

#include "APIRestEndpoints.h"
#include <Poco/Logger.h>

#include <Poco/JSON/Object.h>
#include <Poco/Net/HTMLForm.h>
#include "APIRestFilePartHandler.h"

namespace Route {

static const std::string CONTENT_TYPE_JSON = "application/json";
static const std::string CONTENT_TYPE_PLAIN_TEXT = "text/plain; charset=utf-8";

static Poco::Logger& logger = Poco::Logger::get("APIRestEndpoints");

void APIRestEndpoints::signature(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response) {
    try {
        receive_multipart_data(request);
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

void APIRestEndpoints::verify(const Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response) {
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

void APIRestEndpoints::error(Poco::Net::HTTPServerResponse& response, const std::string& error) {
    response.setStatus(Poco::Net::HTTPServerResponse::HTTP_INTERNAL_SERVER_ERROR);
    response.setContentType(CONTENT_TYPE_PLAIN_TEXT);
    response.send().write(error.c_str(), error.size());
}

void APIRestEndpoints::receive_multipart_data(Poco::Net::HTTPServerRequest& request) {
    APIRestFilePartHandler part_handler(DEFAULT_UPLOAD_DIRECTORY);
    Poco::Net::HTMLForm form(request, request.stream(), part_handler);
    logger.information("Campos do formulário:");
    for (auto const& entry : form) {
        logger.information("%s: %s", entry.first, entry.second);
    }
}

} /* namespace Route */
