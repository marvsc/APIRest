/*
 * @file FilePartHandler.h
 * @brief Declaração da classe APIRestFilePartHandler, métodos e atributos.
 * @author Marcus Chaves
 * @date 2026-01-27
 */

#ifndef SRC_ROUTE_APIRESTFILEPARTHANDLER_H_
#define SRC_ROUTE_APIRESTFILEPARTHANDLER_H_

#include <functional>

#include <Poco/Net/PartHandler.h>

namespace Route {

/*
 * @class APIRestFilePartHandler
 * @brief Classe para tratar arquivos recebidos via form multidata
 */
class APIRestFilePartHandler : public Poco::Net::PartHandler {
public:

    /*
     * @brief Constrói a classe de forma simples.
     */
    APIRestFilePartHandler() : upload_dir_(""), on_key_callback_(nullptr) {}

    /*
     * @brief Constrói a classe definindo o diretório de upload.
     *
     * @param[in] upload_dir Path para o diretório de upload.
     */
    APIRestFilePartHandler(const std::string& upload_dir) :
        upload_dir_(upload_dir.back() == '/' ? upload_dir : upload_dir + "/"), on_key_callback_(nullptr) {}

    /*
     * @brief Constrói a classe definindo o diretório de upload e uma função a ser executada após
     *          salvar o arquivo em disco.
     *
     * @param[in] upload_dir Path para o diretório de upload.
     * @param[in] on_key_callback Função a ser executada após salvar o arquivo em disco. A função deve
     *                              receber o nome do parâmetro e o caminho completo onde ele foi salvo.
     */
    APIRestFilePartHandler(const std::string& upload_dir, std::function<void(const std::string&, const std::string&)> on_key_callback) :
            upload_dir_(upload_dir.back() == '/' ? upload_dir : upload_dir + "/"), on_key_callback_(on_key_callback) {}

    /*
     * @brief Define o diretório de upload.
     *
     * @param[in] upload_dir Path para o diretório de upload.
     */
    void set_upload_dir(const std::string& upload_dir) {
        upload_dir_ = upload_dir;
    }

    /*
     * @brief Define a função a ser executada após salvar o arquivo em disco.
     *
     * @param[in] on_key_callback Função a ser executada após salvar o arquivo em disco. A função deve
     *                              receber o nome do parâmetro e o caminho completo onde ele foi salvo.
     */
    void set_on_key_callback(std::function<void(const std::string&, const std::string&)> on_key_callback) {
        on_key_callback_ = on_key_callback;
    }

    /*
     * @brief Destrói a classe.
     */
    virtual ~APIRestFilePartHandler() {}

    /*
     * @brief Manipula o multipart form data
     *
     * @param[in] header Cabeçalho da requisição.
     * @param[in] stream Stream para o arquivo recebido via multipart form data.
     */
    void handlePart(const Poco::Net::MessageHeader& header, std::istream& stream) override;
private:
    std::string upload_dir_; ///< @brief Path para o diretório de upload.
    std::function<void(const std::string&, const std::string&)> on_key_callback_; ///< @brief Função a ser executada após salvar o arquivo em disco.
};

} /* namespace Route */

#endif /* SRC_ROUTE_APIRESTFILEPARTHANDLER_H_ */
