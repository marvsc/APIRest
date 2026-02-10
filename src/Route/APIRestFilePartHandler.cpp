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

namespace Route {

static Poco::Logger& logger = Poco::Logger::get("FilePartHandler");

void APIRestFilePartHandler::handlePart(const Poco::Net::MessageHeader& header, std::istream& stream) {
    try {
        if (header.has(CONTENT_DISPOSITION)) {
            std::string dispositions;
            Poco::Net::NameValueCollection parameters;
            Poco::Net::MessageHeader::splitParameters(header.get(CONTENT_DISPOSITION), dispositions, parameters);
            std::string filename(parameters.get(FILENAME));
            logger.information("Recebendo arquivo: %s", filename);
            std::ofstream output_file_stream(upload_dir_ + filename, std::ios::binary);
            Poco::StreamCopier::copyStream(stream, output_file_stream);
            logger.information("Arquivo %s salvo em %s", filename, upload_dir_);
        }
    } catch (Poco::NotFoundException& e) {
        logger.warning("O nome do arquivo não foi encontrado no cabeçalho do pacote: %s", e.message());
    }
}

} /* namespace Route */
