/*
 * Router.h
 *
 *  Created on: 24 de jun. de 2025
 *      Author: marcus.chaves
 */

#ifndef INCLUDE_ROUTER_H_
#define INCLUDE_ROUTER_H_

#include <Poco/Net/HTTPRequestHandlerFactory.h>

class Router: public Poco::Net::HTTPRequestHandlerFactory {
public:
	Router();
	void add_route(const std::string& route, const std::string& factory);
	std::shared_ptr<Poco::Net::HTTPRequestHandler> create_request_handler()
};

#endif /* INCLUDE_ROUTER_H_ */
