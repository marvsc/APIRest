/*
 * MyErrorHandler.cpp
 *
 *  Created on: Apr 27, 2026
 *      Author: marcus
 */

#include "APIRestErrorHandler.h"

#include <cxxabi.h>

#include <Poco/Logger.h>

void APIRestErrorHandler::exception(const Poco::Exception& e) {
    Poco::Logger::get(get_demangled_class_name(typeid(*this).name())).warning("Erro disparado pela libpoco na thread: %s", e.displayText());
}

void APIRestErrorHandler::exception(const std::exception& e) {
    Poco::Logger::get(get_demangled_class_name(typeid(*this).name())).warning("Erro geral na thread: %s", std::string(e.what()));
}

void APIRestErrorHandler::exception() {
    Poco::Logger::get(get_demangled_class_name(typeid(*this).name())).warning("Erro desconhecido na thread");
}

std::string APIRestErrorHandler::get_demangled_class_name(const char* name) const {
    int status = 0;
    char* demangled = abi::__cxa_demangle(name, nullptr, nullptr, &status);
    std::string result = !status ? demangled : name;
    std::free(demangled);
    return result;
}

