/*
 * @file APIRestRequestHandler.h
 * @brief Declaração da classe APIRestRequestHandler, métodos e atributos.
 * @author Marcus Chaves
 * @date 2026-01-27
 */

#ifndef SRC_ROUTE_APIRESTREQUESTHANDLER_H_
#define SRC_ROUTE_APIRESTREQUESTHANDLER_H_

#include <map>
#include <functional>

#include <Poco/Net/HTTPRequestHandler.h>
#include <Poco/Net/HTTPServerRequest.h>
#include <Poco/Net/HTTPServerResponse.h>

namespace Route {

/*
 * @class APIRestRequestHandler
 * @brief Classe para manipular requisições recebidas pelo servidor.
 */
class APIRestRequestHandler: public Poco::Net::HTTPRequestHandler {
public:

    /*
     * @brief Constrói a classe de forma simples.
     */
    APIRestRequestHandler() {}

    /*
     * @brief Constrói a classe mapeando as rotas.
     *
     * @param[in] routes Mapa de rotas.
     */
    APIRestRequestHandler(std::map<std::string, std::function<void(Poco::Net::HTTPServerRequest&,
            Poco::Net::HTTPServerResponse&)>> routes) : routes_(routes) {}

    /*
     * @brief Destrói a classe limpando as rotas.
     */
    virtual ~APIRestRequestHandler() {
        routes_.clear();
    }

    /*
     * @brief Adiciona rota
     *
     * @param[in] rota Caminho da rota.
     * @param[in] callback Função chamada ao acessar a rota.
     */
    void add_route(const std::string &route, std::function<void(Poco::Net::HTTPServerRequest&,
            Poco::Net::HTTPServerResponse&)> callback) {
        routes_.emplace(route, callback);
    }

    /*
     * @brief Manipula a requisição recebida pelo servidor.
     *
     * @param[in] request Requisição recebida pelo servidor.
     * @param[in] response Resposta a ser enviada pelo servidor.
     */
    void handleRequest(Poco::Net::HTTPServerRequest &request,
            Poco::Net::HTTPServerResponse &response) override;
private:
    std::map<std::string, std::function<void(Poco::Net::HTTPServerRequest&,
            Poco::Net::HTTPServerResponse&)>> routes_; ///< @brief Rotas expostas pelo servidor.
};

} /* namespace Route */

#endif /* SRC_ROUTE_APIRESTREQUESTHANDLER_H_ */
