
#include "APIRestRequestHandler.h"

#include <Poco/URI.h>

namespace Route {

void APIRestRequestHandler::handleRequest(Poco::Net::HTTPServerRequest &request,
        Poco::Net::HTTPServerResponse &response) {
    // Extrai o caminho da rota
    std::string path(Poco::URI(request.getURI()).getPath());

    // Corrige o caminho da rota.
    if (!path.empty() && path.back() == '/') {
        path.pop_back();
    }

    // Dispara a rotina associada a rota solicitada.
    routes_.at(path)(request, response);
}

} /* namespace Route */
