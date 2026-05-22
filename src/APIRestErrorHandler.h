/*
 * @file APIRestErrorHandler.h
 * @brief Declaração da classe APIRestErrorHandler, métodos e atributos.
 * @author Marcus Chaves
 * @date 2026-01-27
 */

#ifndef SRC_APIRESTERRORHANDLER_H_
#define SRC_APIRESTERRORHANDLER_H_

#include <Poco/ErrorHandler.h>

/*
 * @class APIRestErrorHandler
 * @brief Classe para manipular erros disparados por threads dentro da aplicação.
 */
class APIRestErrorHandler : public Poco::ErrorHandler {
public:

    /*
     * @brief Trata exceções da Poco disparadas por threads.
     *
     * @param[in] e Exceção disparada por threads.
     */
    void exception(const Poco::Exception& e) override;

    /*
     * @brief Trata exceções genéricas disparadas por threads.
     *
     * @param[in] e Exceção disparada por threads.
     */
    void exception(const std::exception& e) override;

    /*
     * @brief Trata exceções desconhecidas disparadas por threads.
     */
    void exception() override;
private:

    /*
     * @brief Retorna o nome da classe desmanchado a partir do nome da classe recebido a partir do typeid.
     *
     * @param[in] name Nome da classe retornado pelo typeid.
     */
    std::string get_demangled_class_name(const char* name) const;

    /*
     * @brief Classe de testes definida como amiga para acessar métodos e atributos privados.
     */
    friend class APIRestErrorHandlerTest;
};

#endif /* SRC_APIRESTERRORHANDLER_H_ */
