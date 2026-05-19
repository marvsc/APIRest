/*
 * APIRestErrorHandlerTest.h
 *
 *  Created on: 19 de mai. de 2026
 *      Author: marcus.chaves
 */

#ifndef TEST_PACKAGE_SRC_UNITTESTS_INCLUDE_APIRESTERRORHANDLERTEST_H_
#define TEST_PACKAGE_SRC_UNITTESTS_INCLUDE_APIRESTERRORHANDLERTEST_H_

#include <cppunit/TestFixture.h>

#include <cppunit/extensions/HelperMacros.h>

class APIRestErrorHandlerTest: public CppUnit::TestFixture {
    CPPUNIT_TEST_SUITE(APIRestErrorHandlerTest);
    CPPUNIT_TEST(teste_nome_de_classe_desmanchado);
    CPPUNIT_TEST_SUITE_END();
public:
    void teste_nome_de_classe_desmanchado();
};

CPPUNIT_TEST_SUITE_REGISTRATION(APIRestErrorHandlerTest);

#endif /* TEST_PACKAGE_SRC_UNITTESTS_INCLUDE_APIRESTERRORHANDLERTEST_H_ */
