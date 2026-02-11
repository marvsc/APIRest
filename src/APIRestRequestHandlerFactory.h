/*
 * Router.h
 *
 *  Created on: 24 de jun. de 2025
 *      Author: marcus.chaves
 */

#ifndef SRC_APIRESTREQUESTHANDLERFACTORY_H_
#define SRC_APIRESTREQUESTHANDLERFACTORY_H_

#include "Route/APIRestEndpoints.h"

#include <Poco/Net/HTTPRequestHandlerFactory.h>

class APIRestRequestHandlerFactory: public Poco::Net::HTTPRequestHandlerFactory {
public:
    APIRestRequestHandlerFactory(const std::string& upload_dir);
    Poco::Net::HTTPRequestHandler* createRequestHandler(
            const Poco::Net::HTTPServerRequest &request) override;
private:
    Route::APIRestEndpoints endpoints_;
};

#endif /* SRC_APIRESTREQUESTHANDLERFACTORY_H_ */
