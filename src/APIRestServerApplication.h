/*
 * @file Container.h
 * @brief Declaração da classe APIRestServerApplication, métodos e atributos.
 * @author Marcus Chaves
 * @date 2026-01-27
 */

#ifndef SRC_APIRESTSERVERAPPLICATION_H_
#define SRC_APIRESTSERVERAPPLICATION_H_

#include <iostream>

#include <Poco/Util/OptionSet.h>
#include <Poco/Util/ServerApplication.h>
#include <Poco/Net/HTTPRequestHandlerFactory.h>

// Porta de conexão default do servidor rest
#define DEFAULT_PORT 9000

/*
 * @class APIRestServerApplication
 * @brief Classe que representa a aplicação
 */
class APIRestServerApplication: public Poco::Util::ServerApplication {
public:

    /*
     * @brief Constrói a classe definindo a porta padrão para conexão.
     */
    APIRestServerApplication();

    /*
     * @brief Constrói a classe passando a porta de conexão do servidor.
     *
     * @param[in] port Porta de conexão do servidor
     */
    APIRestServerApplication(int port);

    /*
     * @brief Destrói a classe
     */
    ~APIRestServerApplication() override;

protected:

    /*
     * @brief Método principal da inicialização da aplicação.
     *
     * @param[in] args Argumentos passados na execução da aplicação.
     * @return EXIT_SUCCESS se houver sucesso na execução ou EXIT_FAILURE se houve alguma falha.
     */
    int main(const std::vector<std::string> &args) override;

    /*
     * @brief Define as opções que devem ser passadas via parâmetro na execução da aplicação.
     *
     * @param[in] options Parâmetros que devem ser passados na execução da aplicação.
     */
    void defineOptions(Poco::Util::OptionSet& options) override;

    /*
     * @brief Método executado durante a inicialização da aplicação.
     *
     * @param[in] self Aplicação que está sendo inicializada.
     */
    void initialize(Poco::Util::Application& self) override;
private:
    int port_; ///< @brief Porta de conexão do servidor.
    Poco::Net::HTTPRequestHandlerFactory::Ptr router_; ///< @brief Roteador do rest

    /*
     * @brief Callback para a definição de configurações a partir de parâmetros recebidos
     *          na execução da aplicação.
     *
     * @param[in] name Nome do parâmetro recebido na execução da aplicação.
     * @param[in] value Valor recebido via parâmetro na execução da aplicação.
     */
    void handleConfiguration(const std::string& name, const std::string& value);

    /*
     * @brief Define o roteador
     *
     * @param[in] router Roteador
     */
    void set_router(
            Poco::Net::HTTPRequestHandlerFactory::Ptr router) {
        router_ = router;
    }

    /*
     * @brief Define a porta de conexão do servidor
     *
     * @param[in] port Porta de conexão do servidor
     */
    void set_port(int port) {
        port_ = port;
    }

    /*
     * @brief Retorna o roteador definido na aplicação.
     *
     * @return Retorna o roteador definido na aplicação.
     */
    Poco::Net::HTTPRequestHandlerFactory::Ptr get_router() const {
        return router_;
    }
};

// Registra a classe como classe principal da aplicação.
POCO_SERVER_MAIN(APIRestServerApplication)

#endif /* SRC_APIRESTSERVERAPPLICATION_H_ */
