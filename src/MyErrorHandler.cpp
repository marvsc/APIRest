/*
 * MyErrorHandler.cpp
 *
 *  Created on: Apr 27, 2026
 *      Author: marcus
 */

#include "MyErrorHandler.h"

void MyErrorHandler::exception(const Poco::Exception& e) {
    std::printf("Erro na thread: %s\n", e.displayText().c_str());
}

void MyErrorHandler::exception(const std::exception& e) {
    std::printf("Erro geral: %s\n", e.what());
}

void MyErrorHandler::exception() {
    std::printf("Erro genérico\n");
}

