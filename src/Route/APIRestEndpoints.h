/*
 * @file APIRestEndpoints.h
 * @brief Declaração da classe APIRestEndpoints, métodos e atributos.
 * @author Marcus Chaves
 * @date 2026-01-27
 */

#ifndef SRC_ROUTE_APIRESTENDPOINTS_H_
#define SRC_ROUTE_APIRESTENDPOINTS_H_

#include "APIRestFilePartHandler.h"

#include <map>
#include <string>

#include <Poco/Net/HTMLForm.h>
#include <Poco/Net/HTTPServerRequest.h>
#include <Poco/Net/HTTPServerResponse.h>

// Diretório de upload default
#define DEFAULT_UPLOAD_DIRECTORY "."

namespace Route {

/*
 * @class APIRestEndpoints
 * @brief Classe para representar endpoints executando a rotina solicitada pelo cliente.
 */
class APIRestEndpoints {
public:

    /*
     * @brief Constrói a classe de forma simples.
     */
    APIRestEndpoints() : file_part_handler_(DEFAULT_UPLOAD_DIRECTORY,
            [&arquivos = arquivos_](const std::string& key, const std::string& value) {
        arquivos.insert_or_assign(key, value);
    }) {}

    /*
     * @brief Constrói a classe definindo o caminho para o diretório de upload.
     *
     * @param[in] upload_dir Caminho para o diretório de upload.
     */
    APIRestEndpoints(const std::string& upload_dir) :
        file_part_handler_(upload_dir,
                [&arquivos = arquivos_](const std::string& key, const std::string& value) {
        arquivos.insert_or_assign(key, value);
    }) {}

    /*
     * @brief Destrói a classe.
     */
    virtual ~APIRestEndpoints() {}

    /*
     * @brief Assina o arquivo e preenche a resposta com o conteúdo da assinatura em base 64 no formato
     *          texto.
     *
     * @param[in] request Requisição enviada pelo cliente.
     * @param[in] response Resposta a ser preenchida.
     */
    void signature(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response);

    /*
     * @brief Verifica a assinatura do arquivo e preenche a resposta com um json contendo o status da
     *          assinatura e dados adicionais.
     *
     * @param[in] request Requisição enviada pelo cliente.
     * @param[in] response Resposta a ser preenchida.
     */
    void verify(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response);
private:
    APIRestFilePartHandler file_part_handler_; ///< @brief Manipulador de multipart form data
    std::map<std::string, std::string> arquivos_; ///< @brief Mapeamento de arquivos com seu respectivo nome de chave passado no cabeçalho.

    /*
     * @brief Obtém o form data.
     *
     * @param[in] request Requisição enviada pelo cliente.
     * @return Multipart form data.
     */
    Poco::Net::HTMLForm* get_form_data(Poco::Net::HTTPServerRequest& request);
};

} /* namespace Route */

#endif /* SRC_ROUTE_APIRESTENDPOINTS_H_ */
