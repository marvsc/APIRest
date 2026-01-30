/*
 * Container.cpp
 *
 *  Created on: 24 de jun. de 2025
 *      Author: marcus.chaves
 */

#include "../include/APIRestServerApplication.h"
#include "../include/configuration/ConfigurationKeys.h"

#include <Poco/Logger.h>
#include <Poco/ConsoleChannel.h>
#include <Poco/AutoPtr.h>
#include <Poco/SplitterChannel.h>

#include <Poco/Net/HTTPServer.h>

#define MAX_QUEUED 250
#define MAX_THREADS 50

int APIRestServerApplication::main(std::vector<std::string> &args) {
    auto http_server_params = new Poco::Net::HTTPServerParams();
    http_server_params->setMaxQueued(MAX_QUEUED);
    http_server_params->setMaxThreads(MAX_THREADS);
    Poco::Net::HTTPServer http_server(get_router(),
            Poco::Net::ServerSocket(Poco::UInt16(port_)), http_server_params);
    std::printf("Servidor iniciado na porta %d\n", port_);
    http_server.start();
    waitForTerminationRequest();
    std::printf("Servidor encerrado\n");
    return Poco::Util::Application::EXIT_OK;
}

void APIRestServerApplication::initialize(Application& self) {
    loadConfiguration();
    ServerApplication::initialize(self);
    Poco::AutoPtr<Poco::SplitterChannel> splitter(new Poco::SplitterChannel);
    if (config().getBool(Configuration::ConfigurationKeys::LOGGING_CHANNELS_CONSOLE, true)) {
        Poco::AutoPtr<Poco::Channel> console(config().getBool(Configuration::ConfigurationKeys::LOGGING_CHANNELS_CONSOLE_COLORS, false) ? new Poco::ColorConsoleChannel : Poco::ConsoleChannel);
        splitter->addChannel(console);
    }
    if (config().getBool("", false)) {
        // TODO: file
    }
    Poco::Logger::root().setChannel(splitter);
    logger().information("APIRest inicializado");
}

void APIRestServerApplication::set_log_properties(const Poco::FileChannel& file_channel) const {
    std::map<std::string, std::function<void()>> getter = {
            {Configuration::ConfigurationKeys::LOGGING_CHANNELS_FILE_PATH, []() {  }},
            {}
    };
}
