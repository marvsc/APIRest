/*
 * APIRestServerTest.cpp
 *
 *  Created on: 11 de mai. de 2026
 *      Author: marcus.chaves
 */

#include "../include/APIRestServerTest.h"

#include <Poco/Net/HTTPServerRequestImpl.h>
#include <Poco/Net/FilePartSource.h>
#include <Poco/Net/HTTPServerResponseImpl.h>
#include <Poco/Net/HTTPRequestHandler.h>

#include "../../../../src/APIRestRequestHandlerFactory.h"

#define BUFFER_SIZE 256

#define PRINTF_MESSAGE(format, ...) \
    ([&]() { \
            char buffer[BUFFER_SIZE]; \
            std::snprintf(buffer, BUFFER_SIZE, format, ##__VA_ARGS__); \
            return std::string(buffer); \
    }())

#define CONTENT_TYPE_PLAIN_TEXT "text/plain; charset=utf-8";

CPPUNIT_TEST_SUITE_REGISTRATION(APIRestServerTest);

void APIRestServerTest::teste_rota_signature() {
    Poco::Net::HTTPServerRequestImpl request;
    request.setURI("/signature");
    Poco::Net::HTMLForm form;
    form.setEncoding(Poco::Net::HTMLForm::ENCODING_MULTIPART);
    form.addPart("File-To-Assign", new Poco::Net::FilePartSource("doc.txt"));
    form.addPart("Certificate", new Poco::Net::FilePartSource("certificado_teste_hub.pfx"));
    form.add("Password", "bry123456");
    form.prepareSubmit(request);
    Poco::Net::HTTPServerResponseImpl response;
    APIRestRequestHandlerFactory factory("upload");
    std::unique_ptr<Poco::Net::HTTPRequestHandler> handler(factory.createRequestHandler(request));
    handler->handleRequest(request, response);
    CPPUNIT_ASSERT_MESSAGE(PRINTF_MESSAGE("Status [%d], Reason [%s]", response.getStatus(), response.getReason().c_str()), response.getStatus() == Poco::Net::HTTPResponse::HTTP_OK);
    CPPUNIT_ASSERT_MESSAGE(PRINTF_MESSAGE("Content type %s incorreto", response.getContentType().c_str()), response.getContentType() == CONTENT_TYPE_PLAIN_TEXT);
    CPPUNIT_ASSERT_MESSAGE("Não retornou o conteúdo da assinatura em base 64", response.getContentLength() > 0);
}

