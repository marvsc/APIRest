/*
 * Container.h
 *
 *  Created on: 24 de jun. de 2025
 *      Author: marcus.chaves
 */

#ifndef INCLUDE_APIRESTSERVERAPPLICATION_H_
#define INCLUDE_APIRESTSERVERAPPLICATION_H_

#include <Poco/FileChannel.h>

#include <Poco/Util/ServerApplication.h>
#include <Poco/Net/HTTPRequestHandlerFactory.h>

#define DEFAULT_PORT 9000

class APIRestServerApplication: public Poco::Util::ServerApplication {
public:
    APIRestServerApplication() :
            port_(DEFAULT_PORT) {}
    APIRestServerApplication(int port) :
            port_(port) {}
    ~APIRestServerApplication() override {
        router_.reset();
    }
    void set_port(int port) {
        port_ = port;
    }
    Poco::Net::HTTPRequestHandlerFactory::Ptr get_router() const {
        return router_;
    }
    void set_router(
            std::shared_ptr<Poco::Net::HTTPRequestHandlerFactory> router) {
        router_ = router;
    }
protected:
    int main(const std::vector<std::string> &args) override;
    void initialize(Application& self) override;
private:
    int port_;
    Poco::Net::HTTPRequestHandlerFactory::Ptr router_;
};

#endif /* INCLUDE_APIRESTSERVERAPPLICATION_H_ */
