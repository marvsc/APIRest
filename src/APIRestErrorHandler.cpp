/*
 * MyErrorHandler.cpp
 *
 *  Created on: Apr 27, 2026
 *      Author: marcus
 */

#include "APIRestErrorHandler.h"

#include <Poco/Logger.h>

#define APPLICATION_LOGGER_NAME "APIRestLogger"

void APIRestErrorHandler::exception(const Poco::Exception& e) {
    Poco::Logger::get(APPLICATION_LOGGER_NAME).warning("Erro disparado pela libpoco na thread: %s", e.displayText());
}

void APIRestErrorHandler::exception(const std::exception& e) {
    Poco::Logger::get(APPLICATION_LOGGER_NAME).warning("Erro geral na thread: %s", std::string(e.what()));
}

void APIRestErrorHandler::exception() {
    Poco::Logger::get(APPLICATION_LOGGER_NAME).warning("Erro desconhecido na thread");
}

