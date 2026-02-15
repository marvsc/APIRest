/*
 * FilePartHandler.h
 *
 *  Created on: Feb 8, 2026
 *      Author: marcus
 */

#ifndef SRC_ROUTE_APIRESTFILEPARTHANDLER_H_
#define SRC_ROUTE_APIRESTFILEPARTHANDLER_H_

#include <functional>

#include <Poco/Net/PartHandler.h>

namespace Route {

class APIRestFilePartHandler : public Poco::Net::PartHandler {
public:
    APIRestFilePartHandler() : upload_dir_(""), on_key_callback_(nullptr) {}
    APIRestFilePartHandler(const std::string& upload_dir) :
        upload_dir_(upload_dir.back() == '/' ? upload_dir : upload_dir + "/"), on_key_callback_(nullptr) {}
    APIRestFilePartHandler(const std::string& upload_dir, std::function<void(const std::string&, const std::string&)> on_key_callback) :
            upload_dir_(upload_dir.back() == '/' ? upload_dir : upload_dir + "/"), on_key_callback_(on_key_callback) {}
    void set_upload_dir(const std::string& upload_dir) {
        upload_dir_ = upload_dir;
    }
    void set_on_key_callback(std::function<void(const std::string&, const std::string&)> on_key_callback) {
        on_key_callback_ = on_key_callback;
    }
    virtual ~APIRestFilePartHandler() {}
    void handlePart(const Poco::Net::MessageHeader& header, std::istream& stream) override;
private:
    std::string upload_dir_;
    std::function<void(const std::string&, const std::string&)> on_key_callback_;
};

} /* namespace Route */

#endif /* SRC_ROUTE_APIRESTFILEPARTHANDLER_H_ */
