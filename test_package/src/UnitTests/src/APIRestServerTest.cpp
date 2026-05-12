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
#include <Poco/Net/StreamSocket.h>
#include <Poco/Net/HTTPServerSession.h>
#include <Poco/Net/SocketAddress.h>
#include <Poco/Net/ServerSocket.h>
#include <Poco/Net/HTTPServer.h>
#include <Poco/Net/HTTPClientSession.h>

#include "../../../../src/APIRestRequestHandlerFactory.h"

#define BUFFER_SIZE 256
#define LOCAL_IP "127.0.0.1"
#define DEFAULT_PORT 9000

#define PRINTF_MESSAGE(format, ...) \
    ([&]() { \
            char buffer[BUFFER_SIZE]; \
            std::snprintf(buffer, BUFFER_SIZE, format, ##__VA_ARGS__); \
            return std::string(buffer); \
    }())

#define CONTENT_TYPE_PLAIN_TEXT "text/plain; charset=utf-8"

CPPUNIT_TEST_SUITE_REGISTRATION(APIRestServerTest);

void APIRestServerTest::teste_rota_signature() {
    // TODO:
    // Instanciar o request handler factory
    Poco::Net::HTTPRequestHandlerFactory::Ptr router(new APIRestRequestHandlerFactory("."));
    // Instanciar o http server
    Poco::Net::HTTPServerParams::Ptr http_server_params = new Poco::Net::HTTPServerParams;
    // Iniciar o http server
    Poco::Net::HTTPServer http_server(router, Poco::Net::ServerSocket(Poco::UInt16(DEFAULT_PORT)), http_server_params);
    // Instanciar o http client session
    Poco::Net::HTTPClientSession session(LOCAL_IP, Poco::UInt16(DEFAULT_PORT));
    // Instanciar o http request
    // Preencher o header do request
    // Instanciar o html form
    // Preencher o form data
    // Submeter o form data ao request
    // Enviar o request
    // Obter o response
    // Validar response
    Poco::Net::SocketAddress socket_address(LOCAL_IP, DEFAULT_PORT);
    Poco::Net::ServerSocket server_socket(socket_address);
    Poco::Net::StreamSocket client_socket;
    client_socket.connect(socket_address);
    Poco::Net::HTTPServerSession session(server_socket.acceptConnection(), new Poco::Net::HTTPServerParams);
    Poco::Net::HTTPServerResponseImpl response(session);
    Poco::Net::HTTPServerRequestImpl request(response, session, new Poco::Net::HTTPServerParams);
    request.setMethod(Poco::Net::HTTPServerRequest::HTTP_POST);
    request.setURI("/signature");
    Poco::Net::HTMLForm form;
    form.setEncoding(Poco::Net::HTMLForm::ENCODING_MULTIPART);
    form.addPart("File-To-Assign", new Poco::Net::FilePartSource("doc.txt"));
    form.addPart("Certificate", new Poco::Net::FilePartSource("certificado_teste_hub.pfx"));
    form.add("Password", "bry123456");
    form.prepareSubmit(request);
    APIRestRequestHandlerFactory factory("upload");
    std::unique_ptr<Poco::Net::HTTPRequestHandler> handler(factory.createRequestHandler(request));
    handler->handleRequest(request, response);
    CPPUNIT_ASSERT_MESSAGE(PRINTF_MESSAGE("Status [%d], Reason [%s]", response.getStatus(), response.getReason().c_str()), response.getStatus() == Poco::Net::HTTPResponse::HTTP_OK);
    CPPUNIT_ASSERT_MESSAGE(PRINTF_MESSAGE("Content type %s incorreto", response.getContentType().c_str()), response.getContentType() == CONTENT_TYPE_PLAIN_TEXT);
    CPPUNIT_ASSERT_MESSAGE("Não retornou o conteúdo da assinatura em base 64", response.getContentLength() > 0);
}

void APIRestServerTest::teste_rota_verify() {
    // TODO:
    // Instanciar o request handler factory
    // Instanciar o http server
    // Iniciar o http server
    // Instanciar o http client session
    // Instanciar o http request
    // Preencher o header do request
    // Instanciar o html form
    // Preencher o form data
    // Submeter o form data ao request
    // Enviar o request
    // Obter o response
    // Validar response
}

