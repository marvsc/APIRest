/*
 * Router.h
 *
 *  Created on: 24 de jun. de 2025
 *      Author: marcus.chaves
 */

#ifndef INCLUDE_APIRESTREQUESTHANDLERFACTORY_H_
#define INCLUDE_APIRESTREQUESTHANDLERFACTORY_H_

#include <Poco/Net/HTTPRequestHandlerFactory.h>

class APIRestRequestHandlerFactory: public Poco::Net::HTTPRequestHandlerFactory {
public:
	Poco::Net::HTTPRequestHandler* createRequestHandler(const Poco::Net::HTTPServerRequest& request) override;
};

#endif /* INCLUDE_APIRESTREQUESTHANDLERFACTORY_H_ */
