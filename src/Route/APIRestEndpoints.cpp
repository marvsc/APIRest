
#include "APIRestEndpoints.h"
#include "JSONKeysVerify.h"

#include <CMSSigner.h>
#include <SignatureRetriever.h>

#include <Poco/Logger.h>

#include <Poco/JSON/Object.h>
#include <Poco/JSON/Array.h>

// Chave do parâmetro correspondente ao nome do arquivo a assinar
#define FILE_TO_ASSIGN "File-To-Assign"

// Chave do parâmetro correspondente ao nome do arquivo PKCS12
#define CERTIFICATE "Certificate"

// Chave do parâmetro correspondente á senha do arquivo PKCS12
#define PASSWORD "Password"

// Chave do parâmetro correspondente ao nome do arquivo a verificar a assinatura
#define FILE_TO_VERIFY "File-To-Verify"

namespace Route {

// Tipos de conteúdo
static const std::string CONTENT_TYPE_JSON = "application/json";
static const std::string CONTENT_TYPE_PLAIN_TEXT = "text/plain; charset=utf-8";

// Obtém o log da aplicação.
static Poco::Logger& logger = Poco::Logger::get("APIRestEndpoints");

void APIRestEndpoints::signature(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response) {
    try {
        std::unique_ptr<Poco::Net::HTMLForm> form(get_form_data(request));
        std::string certificate(arquivos_.at(CERTIFICATE));
        std::string file_to_assign(arquivos_.at(FILE_TO_ASSIGN));
        logger.debug("Assinando arquivo %s com o certificado %s", file_to_assign, certificate);

        // Instancia o assinador passando o arquivo a ser assinado, o arquivo PKCS12 e a senha.
        CMSSigner signer(file_to_assign, certificate, form->get(PASSWORD));

        // Assina o arquivo utilizando algoritmo CMS attached obtendo a assinatura em base 64.
        std::string body(signer.assign());

        // Define parâmetros do cabeçalho de resposta.
        response.setStatus(Poco::Net::HTTPServerResponse::HTTP_OK);
        response.setContentType(CONTENT_TYPE_PLAIN_TEXT);

        // Envia o cabeçalho e escreve o conteúdo da assinatura em base 64 no corpo da resposta.
        response.send().write(body.c_str(), body.size());

        // Limpa o mapeamento de arquivos.
        arquivos_.clear();
    } catch (Poco::Exception& e) {
        // Define parâmetros do cabeçalho para erro disparado pelo Poco.
        response.setStatus(Poco::Net::HTTPServerResponse::HTTP_INTERNAL_SERVER_ERROR);
        response.setContentType(CONTENT_TYPE_PLAIN_TEXT);

        // Envia o cabeçalho e escreve a mensgem de erro no corpo da resposta.
        response.send().write(e.displayText().c_str(), e.displayText().length());
        logger.error("Erro no processo de assinatura de arquivo: %s", e.displayText());
    } catch (std::exception& e) {
        // Define parâmetros do cabeçalho para erro genérico.
        response.setStatus(Poco::Net::HTTPServerResponse::HTTP_INTERNAL_SERVER_ERROR);
        response.setContentType(CONTENT_TYPE_PLAIN_TEXT);

        // Envia o cabeçalho e escreve a mensagem de erro no corpo da resposta
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

        // Instancia o recuperador de dados da assinatura passando o arquivo PKCS12, a senha e o arquivo
        // de assinatura a verificar.
        SignatureRetriever signature_retriever(certificate, form->get(PASSWORD), file_to_verify);

        // Instancia o json de resposta preserevando a ordem de inserção das chaves.
        Poco::JSON::Object body(Poco::JSON_PRESERVE_KEY_ORDER);

        // Verifica a assinatura digital.
        if (signature_retriever.verify()) {
            // Define o status como válido
            body.set(STATUS, VALID);

            // Obtém os nomes de assinantes e adiciona ao json de resposta
            std::set<std::string> names = signature_retriever.get_signer_names();
            Poco::JSON::Array json_names;
            for (std::string name : names) {
                json_names.add(name);
            }
            body.set(SIGNER_NAME, json_names);

            // Obtém os momentos de assinatura e adiciona ao json de resposta
            std::set<std::string> times = signature_retriever.get_signing_times();
            Poco::JSON::Array json_times;
            for (std::string time : times) {
                json_times.add(time);
            }
            body.set(SIGNING_DATE, json_times);

            // Obtém o hash do arquivo presente na assinatura e adiciona ao json de resposta.
            body.set(HASH, signature_retriever.get_hash());

            // Obtém os algoritmos utilizados para gerar o hash presente no arquivo de assinatura e adiciona
            // ao json de resposta.
            std::set<std::string> algorithms = signature_retriever.get_algorithms();
            Poco::JSON::Array json_algorithms;
            for (std::string algorithm : algorithms) {
                json_algorithms.add(algorithm);
            }
            body.set(ALGORITHM_NAME, json_algorithms);
        } else {
            // Define o status como inválido
            body.set(STATUS, INVALID);
        }

        // Define parâmetros do cabeçalho de resposta
        response.setStatus(Poco::Net::HTTPServerResponse::HTTP_OK);
        response.setContentType(CONTENT_TYPE_JSON);

        // Envia o cabeçalho de resposta e obtém um stream para o corpo da resposta
        std::ostream& response_stream = response.send();

        // Escreve o json no corpo da respota.
        body.stringify(response_stream);

        // Lima o mapeamento de arquivos.
        arquivos_.clear();
    } catch (Poco::Exception& e) {
        // Define parâmetros de cabeçalho para erro disparado pelo Poco.
        response.setStatus(Poco::Net::HTTPServerResponse::HTTP_INTERNAL_SERVER_ERROR);
        response.setContentType(CONTENT_TYPE_PLAIN_TEXT);

        // Envia o cabeçalho e escreve a mensagem de erro no corpo da resposta.
        response.send().write(e.displayText().c_str(), e.displayText().length());
        logger.error("Erro no processo de verificação de arquivo: %s", e.displayText());
    } catch (std::exception& e) {
        // Define parâmetros de cabeçalho para erro genérico.
        response.setStatus(Poco::Net::HTTPServerResponse::HTTP_INTERNAL_SERVER_ERROR);
        response.setContentType(CONTENT_TYPE_PLAIN_TEXT);

        // Envia o cabeçalho e escreve a mensagem de erro no corpo da resposta.
        response.send().write(e.what(), std::strlen(e.what()));
        logger.error("Erro no processo de verificação de arquivo: %s", std::string(e.what()));
    }
}

Poco::Net::HTMLForm* APIRestEndpoints::get_form_data(Poco::Net::HTTPServerRequest& request) {
    // Instancia o multiform data
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
