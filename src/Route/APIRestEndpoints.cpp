/*
 * APIRestEndpoints.cpp
 *
 *  Created on: 29 de jan. de 2026
 *      Author: marcus.chaves
 */

#include "APIRestEndpoints.h"
#include "JSONKeysVerify.h"

#include <CMSSigner.h>
#include <SignatureRetriever.h>

#include <Poco/Logger.h>

#include <Poco/JSON/Object.h>
#include <Poco/JSON/Array.h>

#define FILE_TO_ASSIGN "File-To-Assign"
#define CERTIFICATE "Certificate"
#define PASSWORD "Password"
#define FILE_TO_VERIFY "File-To-Verify"

namespace Route {

static const std::string CONTENT_TYPE_JSON = "application/json";
static const std::string CONTENT_TYPE_PLAIN_TEXT = "text/plain; charset=utf-8";

static Poco::Logger& logger = Poco::Logger::get("APIRestEndpoints");

void APIRestEndpoints::signature(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response) {
    try {
        std::unique_ptr<Poco::Net::HTMLForm> form(get_form_data(request));
        std::string certificate(arquivos_.at(CERTIFICATE));
        std::string file_to_assign(arquivos_.at(FILE_TO_ASSIGN));
        logger.debug("Assinando arquivo %s com o certificado %s", file_to_assign, certificate);
        CMSSigner signer(file_to_assign, certificate, form->get(PASSWORD));
        std::string body(signer.assign());
        response.setStatus(Poco::Net::HTTPServerResponse::HTTP_OK);
        response.setContentType(CONTENT_TYPE_PLAIN_TEXT);
        response.send().write(body.c_str(), body.size());
        arquivos_.clear();
    } catch (Poco::Exception& e) {
        response.setStatus(Poco::Net::HTTPServerResponse::HTTP_INTERNAL_SERVER_ERROR);
        response.setContentType(CONTENT_TYPE_PLAIN_TEXT);
        response.send().write(e.displayText().c_str(), e.displayText().length());
        logger.error("Erro no processo de assinatura de arquivo: %s", e.displayText());
    } catch (std::exception& e) {
        response.setStatus(Poco::Net::HTTPServerResponse::HTTP_INTERNAL_SERVER_ERROR);
        response.setContentType(CONTENT_TYPE_PLAIN_TEXT);
        response.send().write(e.what(), std::strlen(e.what()));
        logger.error("Erro no processo de assinatura de arquivo: %s", std::string(e.what()));
    }
}

void APIRestEndpoints::verify(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response) {
    try {
        std::unique_ptr<Poco::Net::HTMLForm> form(get_form_data(request));
        std::string certificate(arquivos_.at(CERTIFICATE));
        std::string file_to_verify(arquivos_.at(FILE_TO_VERIFY));
        logger.debug("Verificando assinatura do arquivo %s com o certificado %s", file_to_verify, certificate);
        SignatureRetriever signature_retriever(certificate, form->get(PASSWORD), file_to_verify);
        Poco::JSON::Object body(Poco::JSON_PRESERVE_KEY_ORDER);
        if (signature_retriever.verify()) {
            body.set(STATUS, VALID);
            std::set<std::string> names = signature_retriever.get_signer_names();
            Poco::JSON::Array json_names;
            for (std::string name : names) {
                json_names.add(name);
            }
            body.set(SIGNER_NAME, json_names);
            std::set<std::string> times = signature_retriever.get_signing_times();
            Poco::JSON::Array json_times;
            for (std::string time : times) {
                json_times.add(time);
            }
            body.set(SIGNING_DATE, json_times);
            body.set(HASH, signature_retriever.get_hash());
            std::set<std::string> algorithms = signature_retriever.get_algorithms();
            Poco::JSON::Array json_algorithms;
            for (std::string algorithm : algorithms) {
                json_algorithms.add(algorithm);
            }
            body.set(ALGORITHM_NAME, json_algorithms);
        } else {
            body.set(STATUS, INVALID);
        }
        response.setStatus(Poco::Net::HTTPServerResponse::HTTP_OK);
        response.setContentType(CONTENT_TYPE_JSON);
        std::ostream& response_stream = response.send();
        body.stringify(response_stream);
        arquivos_.clear();
    } catch (Poco::Exception& e) {
        response.setStatus(Poco::Net::HTTPServerResponse::HTTP_INTERNAL_SERVER_ERROR);
        response.setContentType(CONTENT_TYPE_PLAIN_TEXT);
        response.send().write(e.displayText().c_str(), e.displayText().length());
        logger.error("Erro no processo de verificação de arquivo: %s", e.displayText());
    } catch (std::exception& e) {
        response.setStatus(Poco::Net::HTTPServerResponse::HTTP_INTERNAL_SERVER_ERROR);
        response.setContentType(CONTENT_TYPE_PLAIN_TEXT);
        response.send().write(e.what(), std::strlen(e.what()));
        logger.error("Erro no processo de verificação de arquivo: %s", std::string(e.what()));
    }
}

Poco::Net::HTMLForm* APIRestEndpoints::get_form_data(Poco::Net::HTTPServerRequest& request) {
    Poco::Net::HTMLForm* form = new Poco::Net::HTMLForm(request, request.stream(), file_part_handler_);
    if (!form->empty()) {
        logger.debug("Campos do formulário:");
    }
    for (auto const& entry : *form) {
        logger.debug("%s : %s", entry.first, entry.second);
    }
    return form;
}

} /* namespace Route */
