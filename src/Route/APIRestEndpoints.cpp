/*
 * APIRestEndpoints.cpp
 *
 *  Created on: 29 de jan. de 2026
 *      Author: marcus.chaves
 */

#include "APIRestEndpoints.h"

#include <PKCS12Parser.h>
#include <CMSSigner.h>

#include <Poco/Logger.h>

#include <Poco/JSON/Object.h>
#include <Poco/Net/HTMLForm.h>

#define FILE_TO_ASSIGN "File-To-Assign"
#define CERTIFICATE "Certificate"
#define PASSWORD "Password"

namespace Route {

static const std::string CONTENT_TYPE_JSON = "application/json";
static const std::string CONTENT_TYPE_PLAIN_TEXT = "text/plain; charset=utf-8";

static Poco::Logger& logger = Poco::Logger::get("APIRestEndpoints");

void APIRestEndpoints::signature(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response) {
    try {
        Poco::Net::HTMLForm form(request, request.stream(), file_part_handler_);
        if (!form.empty()) {
            logger.debug("Campos do formulário:");
        }
        for (auto const& entry : form) {
            logger.debug("%s : %s", entry.first, entry.second);
        }
        std::string certificate(arquivos_.at(CERTIFICATE));

        logger.debug("Decodificando arquivo PKCS12 %s", certificate);
        PKCS12Parser parser(certificate, form.get(PASSWORD));
        parser.parse();
        std::string file_to_assign(arquivos_.at(FILE_TO_ASSIGN));
        logger.debug("Assinando arquivo %s", file_to_assign);
        CMSSigner signer(file_to_assign, parser.get_certificate(), parser.get_private_key());
        std::string body(signer.assign());
        response.setStatus(Poco::Net::HTTPServerResponse::HTTP_OK);
        response.setContentType(CONTENT_TYPE_PLAIN_TEXT);
        response.send().write(body.c_str(), body.size());
        arquivos_.clear();
    } catch (std::exception& e) {
        response.setStatus(Poco::Net::HTTPServerResponse::HTTP_INTERNAL_SERVER_ERROR);
        response.setContentType(CONTENT_TYPE_PLAIN_TEXT);
        response.send().write(e.what(), std::strlen(e.what()));
    }
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
