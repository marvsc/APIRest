/*
 * @file Router.h
 * @brief Declaração da classe APIRestRequestHandlerFactory, métodos e atributos.
 * @author Marcus Chaves
 * @date 2026-01-27
 */

#ifndef SRC_APIRESTREQUESTHANDLERFACTORY_H_
#define SRC_APIRESTREQUESTHANDLERFACTORY_H_

#include "Route/APIRestEndpoints.h"

#include <Poco/Net/HTTPRequestHandlerFactory.h>

/*
 * @class APIRestRequestHandlerFactory
 * @brief Classe roteadora para criar o manipulador de requisições.
 */
class APIRestRequestHandlerFactory: public Poco::Net::HTTPRequestHandlerFactory {
public:

    /*
     * @brief Constrói a classe definindo um diretório de upload.
     *
     * @param[in] upload_dir Path para o diretório de upload.
     */
    APIRestRequestHandlerFactory(const std::string& upload_dir);

    /*
     * @brief Método para criar o manipulador de requisições.
     *
     * @param[in] request Requisição recebida pelo servidor.
     */
    Poco::Net::HTTPRequestHandler* createRequestHandler(
            const Poco::Net::HTTPServerRequest &request) override;
private:
    Route::APIRestEndpoints endpoints_; ///< @brief Objeto que representa os endpoints
};

#endif /* SRC_APIRESTREQUESTHANDLERFACTORY_H_ */
