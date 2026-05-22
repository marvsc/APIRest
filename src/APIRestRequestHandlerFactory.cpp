
#include "APIRestRequestHandlerFactory.h"

#include "Route/APIRestRequestHandler.h"

APIRestRequestHandlerFactory::APIRestRequestHandlerFactory(const std::string& upload_dir) :
        endpoints_(upload_dir), HTTPRequestHandlerFactory::HTTPRequestHandlerFactory() {}

Poco::Net::HTTPRequestHandler* APIRestRequestHandlerFactory::createRequestHandler(
        const Poco::Net::HTTPServerRequest &request) {
    // Lambda disparado para a rota signature
    auto signature = [&endpoints = endpoints_](Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response) {
        // Dispara o método signature do endpoint.
        endpoints.signature(request, response);
    };

    // Lambda disparado para a rota verify
    auto verify = [&endpoints = endpoints_](Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response) {
        // Dispara o método verify do endpoint.
        endpoints.verify(request, response);
    };

    // Instancia o manipulador de requisição passando um map com as rotas e seus respectivos lambdas.
    return new Route::APIRestRequestHandler({
        { "/signature", signature },
        { "/verify", verify }
    });
}
