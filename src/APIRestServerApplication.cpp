/*
 * Container.cpp
 *
 *  Created on: 24 de jun. de 2025
 *      Author: marcus.chaves
 */

#include <Poco/Net/HTTPServer.h>
#include "../include/APIRestServerApplication.h"

#define MAX_QUEUED 250
#define MAX_THREADS 50


int APIRestServerApplication::main(std::vector<std::string> & args) {
	auto http_server_params = new Poco::Net::HTTPServerParams();
	http_server_params->setMaxQueued(MAX_QUEUED);
	http_server_params->setMaxThreads(MAX_THREADS);
	Poco::Net::HTTPServer http_server(get_router(), Poco::Net::ServerSocket(Poco::UInt16(port_)), http_server_params);
	std::printf("Servidor iniciado na porta %d\n", port_);
	http_server.start();
	std::printf("Servidor encerrado\n");
	return Poco::Util::Application::EXIT_OK;
}
