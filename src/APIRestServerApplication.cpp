/*
 * Container.cpp
 *
 *  Created on: 24 de jun. de 2025
 *      Author: marcus.chaves
 */

#include "APIRestServerApplication.h"
#include "APIRestRequestHandlerFactory.h"
#include "Configuration/APIRestConfigurationKeys.h"

#include <functional>
#include <fstream>
#include <OpenSSLUtils.h>

#include <Poco/Logger.h>
#include <Poco/ConsoleChannel.h>
#include <Poco/AutoPtr.h>
#include <Poco/SplitterChannel.h>
#include <Poco/Path.h>
#include <Poco/File.h>

#include <Poco/Net/HTTPServer.h>
#include <Poco/Net/SSLManager.h>
#include <Poco/Net/Context.h>
#include <Poco/Net/SecureServerSocket.h>
#include <Poco/Util/OptionCallback.h>
#include <Poco/Util/PropertyFileConfiguration.h>
#include <Poco/Crypto/PKCS12Container.h>

#define MAX_QUEUED 250
#define MAX_THREADS 50
#define DEFAULT_BACKLOG 64

void APIRestServerApplication::initialize(Poco::Util::Application& self) {
    try {
        loadConfiguration();
        if (config().has(Configuration::APIRestConfigurationKeys::LOGGING_CHANNELS_FILE_PATH)) {
            Poco::Path log_file(config().getString(Configuration::APIRestConfigurationKeys::LOGGING_CHANNELS_FILE_PATH));
            Poco::File dir_log(log_file.parent());
            if (!dir_log.exists()) {
                dir_log.createDirectories();
            }
        }
        if (config().has(Configuration::APIRestConfigurationKeys::APIREST_UPLOAD_DIR)) {
            Poco::File upload_dir(config().getString(Configuration::APIRestConfigurationKeys::APIREST_UPLOAD_DIR));
            if (!upload_dir.exists()) {
                upload_dir.createDirectories();
            }
        }
        ServerApplication::initialize(self);
    } catch (Poco::Exception& e) {
        std::printf("Erro inicializando aplicação: %s\n", e.what());
    }
}

int APIRestServerApplication::main(const std::vector<std::string> &args) {
    logger().information("Inicializando APIRest");
    Poco::Net::SSLManager::instance().initializeServer(nullptr, nullptr, nullptr);
    if (!config().has(Configuration::APIRestConfigurationKeys::APIREST_PKCS12_PATH)) {
        logger().error("Certificado PKCS 12 não configurado, parando servidor");
        return Poco::Util::Application::EXIT_CONFIG;
    }
    std::ifstream pkcs12_stream(config().getString(Configuration::APIRestConfigurationKeys::APIREST_PKCS12_PATH), std::ios::binary);
    Poco::AutoPtr<Poco::Crypto::PKCS12Container> container;
    if (config().has(Configuration::APIRestConfigurationKeys::APIREST_PKCS12_PASSWORD_AES_256_CBC_BASE64)
            && config().has(Configuration::APIRestConfigurationKeys::APIREST_PKCS12_PASSWORD_AES_KEY)
            && config().has(Configuration::APIRestConfigurationKeys::APIREST_PKCS12_PASSOWRD_INITIALIZATION_VECTOR)) {
        container.reset(new Poco::Crypto::PKCS12Container(pkcs12_stream,
                OpenSSLUtils::decrypt_aes_256_cbc(config().getString(Configuration::APIRestConfigurationKeys::APIREST_PKCS12_PASSWORD_AES_256_CBC_BASE64),
                        config().getString(Configuration::APIRestConfigurationKeys::APIREST_PKCS12_PASSWORD_AES_KEY),
                        reinterpret_cast<const unsigned char*>(config().getString(Configuration::APIRestConfigurationKeys::APIREST_PKCS12_PASSOWRD_INITIALIZATION_VECTOR).c_str()))));
    } else {
        container.reset(new Poco::Crypto::PKCS12Container(pkcs12_stream));
    }
    Poco::Net::Context::Ptr context(new Poco::Net::Context(Poco::Net::Context::SERVER_USE, "", Poco::Net::Context::VERIFY_STRICT));
    context->useCertificate(container->getX509Certificate());
    context->usePrivateKey(container->getKey());
    set_port(DEFAULT_PORT);
    set_router(new APIRestRequestHandlerFactory(config().getString(Configuration::APIRestConfigurationKeys::APIREST_UPLOAD_DIR)));
    auto http_server_params = new Poco::Net::HTTPServerParams();
    http_server_params->setMaxQueued(MAX_QUEUED);
    http_server_params->setMaxThreads(MAX_THREADS);
    Poco::Net::HTTPServer http_server(get_router(),
            Poco::Net::SecureServerSocket(Poco::UInt16(port_), DEFAULT_BACKLOG, context), http_server_params);
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
