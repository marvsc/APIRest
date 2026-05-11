/*
 * APIRestServerTest.h
 *
 *  Created on: 11 de mai. de 2026
 *      Author: marcus.chaves
 */

#ifndef TEST_PACKAGE_SRC_UNITTESTS_INCLUDE_APIRESTSERVERTEST_H_
#define TEST_PACKAGE_SRC_UNITTESTS_INCLUDE_APIRESTSERVERTEST_H_

#include <cppunit/TestFixture.h>

#include <cppunit/extensions/HelperMacros.h>

class APIRestServerTest: public CppUnit::TestFixture {
    CPPUNIT_TEST_SUITE(APIRestServerTest);
    CPPUNIT_TEST(teste_rota_signature);
    CPPUNIT_TEST(teste_rota_verify);
    CPPUNIT_TEST_SUITE_END();
public:
    void teste_rota_signature();
    void teste_rota_verify();
};

CPPUNIT_TEST_SUITE_REGISTRATION(APIRestServerTest);

#endif /* TEST_PACKAGE_SRC_UNITTESTS_INCLUDE_APIRESTSERVERTEST_H_ */
