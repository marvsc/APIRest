/*
 * Container.h
 *
 *  Created on: 24 de jun. de 2025
 *      Author: marcus.chaves
 */

#ifndef SRC_APIRESTSERVERAPPLICATION_H_
#define SRC_APIRESTSERVERAPPLICATION_H_

#include <iostream>

#include <Poco/FileChannel.h>

#include <Poco/Util/ServerApplication.h>
#include <Poco/Net/HTTPRequestHandlerFactory.h>
#include <Poco/Util/OptionSet.h>

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
protected:
    int main(const std::vector<std::string> &args) override;
    void defineOptions(Poco::Util::OptionSet& options) override;
private:
    int port_;
    Poco::Net::HTTPRequestHandlerFactory::Ptr router_;

    void handleConfiguration(const std::string& name, const std::string& value);
    void set_router(
            Poco::Net::HTTPRequestHandlerFactory::Ptr router) {
        router_ = router;
    }
    void set_port(int port) {
        port_ = port;
    }
    Poco::Net::HTTPRequestHandlerFactory::Ptr get_router() const {
        return router_;
    }
};

POCO_SERVER_MAIN(APIRestServerApplication)

#endif /* SRC_APIRESTSERVERAPPLICATION_H_ */
