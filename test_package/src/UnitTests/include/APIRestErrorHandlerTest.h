/*
 * @file APIRestErrorHandlerTest.h
 * @brief Declaração da classe APIRestErrorHandlerTest
 * @author Marcus Chaves
 * @date 2026-01-27
 */

#ifndef TEST_PACKAGE_SRC_UNITTESTS_INCLUDE_APIRESTERRORHANDLERTEST_H_
#define TEST_PACKAGE_SRC_UNITTESTS_INCLUDE_APIRESTERRORHANDLERTEST_H_

#include <cppunit/TestFixture.h>

#include <cppunit/extensions/HelperMacros.h>

/*
 * @class APIRestErrorHandlerTest
 * @brief Classe de testes unitários para o APIRestErrorHandler
 */
class APIRestErrorHandlerTest: public CppUnit::TestFixture {
    // Declaração do suite de testes
    CPPUNIT_TEST_SUITE(APIRestErrorHandlerTest);
    // Adicionando steps
    CPPUNIT_TEST(teste_nome_de_classe_desmanchado);
    CPPUNIT_TEST_SUITE_END();
public:

    /*
     * @brief Teste para validar desmanche de nome de classe.
     */
    void teste_nome_de_classe_desmanchado();
};

#endif /* TEST_PACKAGE_SRC_UNITTESTS_INCLUDE_APIRESTERRORHANDLERTEST_H_ */
