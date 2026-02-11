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

namespace Route {

static const std::string CONTENT_TYPE_JSON = "application/json";
static const std::string CONTENT_TYPE_PLAIN_TEXT = "text/plain; charset=utf-8";

static Poco::Logger& logger = Poco::Logger::get("APIRestEndpoints");

void APIRestEndpoints::signature(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response) {
    Poco::Net::HTMLForm form(request, request.stream(), file_part_handler_);
    if (!form.empty()) {
        logger.information("Campos do formulário:");
    }
    for (auto const& entry : form) {
        logger.information("%s : %s", entry.first, entry.second);
    }
    std::string body("ASSINATURA");
    response.setStatus(Poco::Net::HTTPServerResponse::HTTP_OK);
    response.setContentType(CONTENT_TYPE_PLAIN_TEXT);
    response.send().write(body.c_str(), body.size());
}

void APIRestEndpoints::verify(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response) {
    Poco::JSON::Object body;
    body.set("JSON", "JSON");
    response.setStatus(Poco::Net::HTTPServerResponse::HTTP_OK);
    response.setContentType(CONTENT_TYPE_JSON);
    std::ostream& response_stream = response.send();
    body.stringify(response_stream);
}

} /* namespace Route */
