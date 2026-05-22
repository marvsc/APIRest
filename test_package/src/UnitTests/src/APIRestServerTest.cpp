
#include "../include/APIRestServerTest.h"

#include "../include/APIRestServerTestMacros.h"

#include <string>
#include <OpenSSLUtils.h>

#include <Poco/StreamCopier.h>

#include <Poco/Net/FilePartSource.h>
#include <Poco/Net/ServerSocket.h>
#include <Poco/Net/HTTPServer.h>
#include <Poco/Net/HTTPClientSession.h>
#include <Poco/Net/HTTPRequest.h>
#include <Poco/JSON/Parser.h>
#include <Poco/JSON/Object.h>

#include "../../../../src/APIRestRequestHandlerFactory.h"

#include "../../../../src/Route/JSONKeysVerify.h"

// Registra o suite de testes
CPPUNIT_TEST_SUITE_REGISTRATION(APIRestServerTest);

void APIRestServerTest::teste_rota_signature() {
    // Instancia o roteador
    Poco::Net::HTTPRequestHandlerFactory::Ptr router(new APIRestRequestHandlerFactory(UPLOAD_PATH));

    // Instancia parâmetros default para o servidor
    Poco::Net::HTTPServerParams::Ptr http_server_params = new Poco::Net::HTTPServerParams;

    // Instancia um servidor simples para testar o core do rest
    Poco::Net::HTTPServer http_server(router, Poco::Net::ServerSocket(Poco::UInt16(DEFAULT_PORT)),
            http_server_params);

    // Inicializa o servidor sem travar a thread principal para fazer conexão de testes
    http_server.start();

    // Instancia cliente
    Poco::Net::HTTPClientSession session(LOCAL_IP, Poco::UInt16(DEFAULT_PORT));

    // Instancia requisição definindo a rota a acessar
    Poco::Net::HTTPRequest request_header(Poco::Net::HTTPRequest::HTTP_POST, SIGNATURE_PATH,
            Poco::Net::HTTPRequest::HTTP_1_1);

    // Preenche o form multidata
    Poco::Net::HTMLForm form_data;
    form_data.setEncoding(Poco::Net::HTMLForm::ENCODING_MULTIPART);
    form_data.addPart(FILE_TO_ASSIGN, new Poco::Net::FilePartSource(FILE_TO_ASSIGN_PATH));
    form_data.addPart(CERTIFICATE, new Poco::Net::FilePartSource(CERTIFICATE_PATH));

    // Por segurança, a senha do arquivo PKCS12 é recebida criptografada usando algoritmo
    //  AES 256 CBC.
    form_data.add(PASSWORD, OpenSSLUtils::decrypt_aes_256_cbc(std::getenv(PKCS12_ENVVAR_PASSWORD), AES_KEY,
            reinterpret_cast<const unsigned char*>(AES_INITIALIZATION_VECTOR)));

    // Associa o form multidata a requisição
    form_data.prepareSubmit(request_header);

    // Envia o cabeçalho da requisição e abre um stream para o corpo da requisição
    std::ostream& request_body = session.sendRequest(request_header);

    // Escreve o form multidata no corpo da requisição
    form_data.write(request_body);
    Poco::Net::HTTPResponse response_header;

    // Abre um stream para a resposta
    std::istream& response_body = session.receiveResponse(response_header);

    // Recebe a resposta em uma string
    std::string body;
    Poco::StreamCopier::copyToString(response_body, body);

    // Para o servidor
    http_server.stop();
    CPPUNIT_ASSERT_MESSAGE(PRINTF_MESSAGE("Status [%d], Reason [%s]", response_header.getStatus(),
            response_header.getReason().c_str()),
            response_header.getStatus() == Poco::Net::HTTPResponse::HTTP_OK);
    CPPUNIT_ASSERT_MESSAGE(PRINTF_MESSAGE("Content type %s incorreto",
            response_header.getContentType().c_str()),
            response_header.getContentType() == CONTENT_TYPE_PLAIN_TEXT);
    CPPUNIT_ASSERT_MESSAGE("Não retornou conteúdo", body.size() > 0);
}

void APIRestServerTest::teste_rota_verify() {
    // Instancia o roteador
    Poco::Net::HTTPRequestHandlerFactory::Ptr router(new APIRestRequestHandlerFactory(UPLOAD_PATH));

    // Instancia parâmetros default para o servidor
    Poco::Net::HTTPServerParams::Ptr http_server_params = new Poco::Net::HTTPServerParams;

    // Instancia um servidor simples para testar o core do rest
    Poco::Net::HTTPServer http_server(router, Poco::Net::ServerSocket(Poco::UInt16(DEFAULT_PORT)),
            http_server_params);

    // Inicializa o servidor sem travar a thread principal para fazer conexões de teste
    http_server.start();

    // Instancia cliente
    Poco::Net::HTTPClientSession session(LOCAL_IP, Poco::UInt16(DEFAULT_PORT));

    // Instancia request passando a rota a acessar
    Poco::Net::HTTPRequest request_header(Poco::Net::HTTPRequest::HTTP_POST, VERIFY_PATH,
            Poco::Net::HTTPRequest::HTTP_1_1);

    // Preenche o form multidata
    Poco::Net::HTMLForm form_data;
    form_data.setEncoding(Poco::Net::HTMLForm::ENCODING_MULTIPART);
    form_data.addPart(FILE_TO_VERIFY, new Poco::Net::FilePartSource(FILE_TO_VERIFY_PATH));
    form_data.addPart(CERTIFICATE, new Poco::Net::FilePartSource(CERTIFICATE_PATH));

    // Por segurança, a senha do arquivo PKCS12 é recebida criptografada usando algoritmo
    //  AES 256 CBC.
    form_data.add(PASSWORD, OpenSSLUtils::decrypt_aes_256_cbc(std::getenv(PKCS12_ENVVAR_PASSWORD), AES_KEY,
            reinterpret_cast<const unsigned char*>(AES_INITIALIZATION_VECTOR)));

    // Associa o form multidata ao request
    form_data.prepareSubmit(request_header);

    // Envia o cabeçalho da requisição e abre stream para o corpo da requisição
    std::ostream& request_body = session.sendRequest(request_header);

    // Escreve o form multidata no corpo da requisição
    form_data.write(request_body);
    Poco::Net::HTTPResponse response_header;

    // Abre stream para o corpo da resposta
    std::istream& response_body = session.receiveResponse(response_header);
    std::string body;

    // Recebe a resposta em uma string
    Poco::StreamCopier::copyToString(response_body, body);

    // Para o servidor
    http_server.stop();
    CPPUNIT_ASSERT_MESSAGE(PRINTF_MESSAGE("Status [%d], Reason [%s]", response_header.getStatus(),
            response_header.getReason().c_str()),
            response_header.getStatus() == Poco::Net::HTTPResponse::HTTP_OK);
    CPPUNIT_ASSERT_MESSAGE(PRINTF_MESSAGE("Content type %s incorreto",
            response_header.getContentType().c_str()),
            response_header.getContentType() == CONTENT_TYPE_JSON);
    CPPUNIT_ASSERT_MESSAGE("Não retornou conteúdo", body.size() > 0);
    CPPUNIT_ASSERT_NO_THROW_MESSAGE(PRINTF_MESSAGE("JSON inválido na resposta: [%s]", body.c_str()), [&body]{
            Poco::JSON::Parser parser;
            Poco::Dynamic::Var result = parser.parse(body);
            Poco::JSON::Object::Ptr object = result.extract<Poco::JSON::Object::Ptr>();
            CPPUNIT_ASSERT_MESSAGE(PRINTF_MESSAGE("Status incorreto: %s",
                    std::string(object->getValue<std::string>(STATUS)).c_str()),
                    object->getValue<std::string>(STATUS) == VALID);
    });
}

