/*
 * Container.cpp
 *
 *  Created on: 24 de jun. de 2025
 *      Author: marcus.chaves
 */

#include "APIRestServerApplication.h"
#include "APIRestRequestHandlerFactory.h"

#include <functional>

#include <Poco/Logger.h>
#include <Poco/ConsoleChannel.h>
#include <Poco/AutoPtr.h>
#include <Poco/SplitterChannel.h>

#include <Poco/Net/HTTPServer.h>
#include <Poco/Util/OptionCallback.h>
#include <Poco/Util/PropertyFileConfiguration.h>

#define MAX_QUEUED 250
#define MAX_THREADS 50

int APIRestServerApplication::main(const std::vector<std::string> &args) {
    logger().information("Inicializando APIRest");
    set_port(DEFAULT_PORT);
    set_router(new APIRestRequestHandlerFactory);
    auto http_server_params = new Poco::Net::HTTPServerParams();
    http_server_params->setMaxQueued(MAX_QUEUED);
    http_server_params->setMaxThreads(MAX_THREADS);
    Poco::Net::HTTPServer http_server(get_router(),
            Poco::Net::ServerSocket(Poco::UInt16(port_)), http_server_params);
    logger().information("Servidor iniciado na porta %d", port_);
    http_server.start();
    waitForTerminationRequest();
    logger().information("Servidor encerrado");
    return Poco::Util::Application::EXIT_OK;
}

void APIRestServerApplication::defineOptions(Poco::Util::OptionSet& options) {
    ServerApplication::defineOptions(options);
    options.addOption(
            Poco::Util::Option("config", "c", "Specify a configuration file path")
                .required(false)
                .repeatable(false)
                .argument("<path>")
                .callback(Poco::Util::OptionCallback<APIRestServerApplication>(
                        this, &APIRestServerApplication::handleConfiguration)));
}

void APIRestServerApplication::handleConfiguration(const std::string& name, const std::string& value) {
    try {
        if (value.empty()) {
            return;
        }
        Poco::Util::PropertyFileConfiguration::Ptr configuration(new Poco::Util::PropertyFileConfiguration(value));
        config().add(configuration, Poco::Util::Application::PRIO_APPLICATION + 1);
    } catch (Poco::Exception& e) {
        std::printf("Erro definindo configuração: %s\n", e.displayText().c_str());
    }
}
