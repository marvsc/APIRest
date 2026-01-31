/*
 * Container.cpp
 *
 *  Created on: 24 de jun. de 2025
 *      Author: marcus.chaves
 */

#include "../include/APIRestServerApplication.h"
#include "../include/configuration/ConfigurationKeys.h"

#include <functional>

#include <Poco/Logger.h>
#include <Poco/ConsoleChannel.h>
#include <Poco/AutoPtr.h>
#include <Poco/SplitterChannel.h>

#include <Poco/Net/HTTPServer.h>

#define MAX_QUEUED 250
#define MAX_THREADS 50

int APIRestServerApplication::main(const std::vector<std::string> &args) {
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
    Poco::SplitterChannel::Ptr splitter_channel(new Poco::SplitterChannel);
    if (config().getBool(Configuration::ConfigurationKeys::LOGGING_CHANNELS_CONSOLE, true)) {
        if (config().getBool(Configuration::ConfigurationKeys::LOGGING_CHANNELS_CONSOLE_COLORS, false)) {
            Poco::ColorConsoleChannel::Ptr color_console_channel(new Poco::ColorConsoleChannel);
            splitter_channel->addChannel(color_console_channel);
        } else {
            Poco::ConsoleChannel::Ptr console_channel(new Poco::ConsoleChannel);
            splitter_channel->addChannel(console_channel);
        }
    }
    if (config().getBool(Configuration::ConfigurationKeys::LOGGING_CHANNELS_FILE, false)) {
        Poco::FileChannel::Ptr file_channel(new Poco::FileChannel);
        std::map<std::string, std::function<void()>> getter = {
                { Configuration::ConfigurationKeys::LOGGING_CHANNELS_FILE_PATH, []() { config().getString(Configuration::ConfigurationKeys::LOGGING_CHANNELS_FILE_PATH); } },
                { Configuration::ConfigurationKeys::LOGGING_CHANNELS_FILE_ROTATION, []() { config().getString(Configuration::ConfigurationKeys::LOGGING_CHANNELS_FILE_ROTATION); } },
                { Configuration::ConfigurationKeys::LOGGING_CHANNELS_FILE_ARCHIVE, []() { config().getString(Configuration::ConfigurationKeys::LOGGING_CHANNELS_FILE_ARCHIVE); } },
                { Configuration::ConfigurationKeys::LOGGING_CHANNELS_FILE_TIMES, []() { config().getString(Configuration::ConfigurationKeys::LOGGING_CHANNELS_FILE_TIMES); } },
                { Configuration::ConfigurationKeys::LOGGING_CHANNELS_FILE_COMPRESS, []() { config().getBool(Configuration::ConfigurationKeys::LOGGING_CHANNELS_FILE_COMPRESS); } },
                { Configuration::ConfigurationKeys::LOGGING_CHANNELS_FILE_PURGE_AGE, []() { config().getString(Configuration::ConfigurationKeys::LOGGING_CHANNELS_FILE_PURGE_AGE); } },
                { Configuration::ConfigurationKeys::LOGGING_CHANNELS_FILE_PURGE_COUNT, []() { config().getInt(Configuration::ConfigurationKeys::LOGGING_CHANNELS_FILE_PURGE_COUNT); } }
        };
        for (const auto& get : getter) {
            if (config().hasProperty(get.first)) {
                get.second();
            }
        }
        splitter_channel->addChannel(file_channel);
    }
    Poco::Logger::root().setChannel(splitter_channel);
    logger().information("APIRest inicializado");
}
