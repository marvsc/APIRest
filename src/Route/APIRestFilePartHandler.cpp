/*
 * FilePartHandler.cpp
 *
 *  Created on: Feb 8, 2026
 *      Author: marcus
 */

#include "APIRestFilePartHandler.h"

#include <fstream>

#include <Poco/Logger.h>
#include <Poco/StreamCopier.h>

#include <Poco/Net/MessageHeader.h>
#include <Poco/Net/NameValueCollection.h>

#define CONTENT_DISPOSITION "Content-Disposition"
#define FILENAME "filename"
#define KEY "name"

namespace Route {

static Poco::Logger& logger = Poco::Logger::get("FilePartHandler");

void APIRestFilePartHandler::handlePart(const Poco::Net::MessageHeader& header, std::istream& stream) {
    try {
        if (header.has(CONTENT_DISPOSITION)) {
            std::string dispositions;
            Poco::Net::NameValueCollection parameters;
            Poco::Net::MessageHeader::splitParameters(header.get(CONTENT_DISPOSITION), dispositions, parameters);
            std::string filename(parameters.get(FILENAME));
            std::string name(parameters.get(KEY));
            logger.information("Recebendo arquivo %s do parâmetro %s", filename, name);
            std::string file_path(upload_dir_ + filename);
            std::ofstream output_file_stream(file_path, std::ios::binary);
            Poco::StreamCopier::copyStream(stream, output_file_stream);
            logger.information("Arquivo %s salvo em %s", filename, upload_dir_);
            if (on_key_callback_) {
                on_key_callback_(name, upload_dir_ + filename);
                if (header.has(PASSWORD)) {
                    on_key_callback_(PASSWORD, header.get(PASSWORD));
                }
            }
        }
    } catch (Poco::NotFoundException& e) {
        logger.warning("Parâmetro não encontrado no cabeçalho do pacote: %s", e.message());
    }
}

} /* namespace Route */
