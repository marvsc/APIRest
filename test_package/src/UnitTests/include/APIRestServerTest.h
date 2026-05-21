/*
 * @file APIRestServerTest.h
 * @brief Declaração da classe APIRestServerTest
 * @author Marcus Chaves
 * @date 2026-01-27
 */

#ifndef TEST_PACKAGE_SRC_UNITTESTS_INCLUDE_APIRESTSERVERTEST_H_
#define TEST_PACKAGE_SRC_UNITTESTS_INCLUDE_APIRESTSERVERTEST_H_

#include <cppunit/TestFixture.h>

#include <cppunit/extensions/HelperMacros.h>

/*
 * @class APIRestServerTest
 * @brief Classe de testes unitários para a APIRestServer
 */
class APIRestServerTest: public CppUnit::TestFixture {
    // Declaração do suite de testes
    CPPUNIT_TEST_SUITE(APIRestServerTest);
    // Adiconando steps
    CPPUNIT_TEST(teste_rota_signature);
    CPPUNIT_TEST(teste_rota_verify);
    CPPUNIT_TEST_SUITE_END();
public:

    /*
     * @brief Testa a rota signature.
     *          Esse teste não representa o real conceito de teste unitário
     *          porque não testa a menor parcela possível de uma funcionalidade,
     *          considerando a rota como uma unidade do teste.
     */
    void teste_rota_signature();

    /*
     * @brief Testa a rota verify.
     *          Esse teste não representa o real conceito de teste unitário
     *          porque não testa a menor parcela possível de uma funcionalidade,
     *          considerando a rota como uma unidade do teste.
     */
    void teste_rota_verify();
};

CPPUNIT_TEST_SUITE_REGISTRATION(APIRestServerTest);

#endif /* TEST_PACKAGE_SRC_UNITTESTS_INCLUDE_APIRESTSERVERTEST_H_ */
