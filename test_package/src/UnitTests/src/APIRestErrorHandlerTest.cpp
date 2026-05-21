
#include "../include/APIRestErrorHandlerTest.h"

#include "../include/APIRestServerTestMacros.h"

#include "../../../../src/APIRestErrorHandler.h"

// Registra o suite de testes
CPPUNIT_TEST_SUITE_REGISTRATION(APIRestErrorHandlerTest);

void APIRestErrorHandlerTest::teste_nome_de_classe_desmanchado() {
    APIRestErrorHandler error_handler;

    // Desmancha o nome da classe gerado pela typeid
    std::string demangled_class_name(error_handler.get_demangled_class_name(typeid(*this).name()));
    CPPUNIT_ASSERT_MESSAGE(PRINTF_MESSAGE("Nome da classe desmanchado deveria ser %s, mas é %s", CLASS_NAME, demangled_class_name.c_str()), demangled_class_name == CLASS_NAME);
}

