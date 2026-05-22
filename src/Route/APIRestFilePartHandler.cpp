
#include "APIRestFilePartHandler.h"

#include <fstream>

#include <Poco/Logger.h>
#include <Poco/StreamCopier.h>

#include <Poco/Net/MessageHeader.h>
#include <Poco/Net/NameValueCollection.h>

// Chave do cabeçalho para arquivos em multipart form data
#define CONTENT_DISPOSITION "Content-Disposition"

// Chave para o nome do arquivo nos parâmetros do cabeçalho
#define FILENAME "filename"

// Chave para o nome do parâmetro
#define KEY "name"

namespace Route {

// Obtém o log da aplicação.
static Poco::Logger& logger = Poco::Logger::get("FilePartHandler");

void APIRestFilePartHandler::handlePart(const Poco::Net::MessageHeader& header, std::istream& stream) {
    try {
        if (header.has(CONTENT_DISPOSITION)) {
            std::string dispositions;

            // Divide os parâmetros recebidos no cabeçalho.
            Poco::Net::NameValueCollection parameters;
            Poco::Net::MessageHeader::splitParameters(header.get(CONTENT_DISPOSITION), dispositions, parameters);

            // Obtém o nome do arquivo recebido no multipart form data
            std::string filename(parameters.get(FILENAME));

            // Obtém o nome do parâmetro correspondente ao arquivo recebido
            std::string name(parameters.get(KEY));
            logger.information("Recebendo arquivo %s do parâmetro %s", filename, name);

            // Salva o arquivo localmente
            std::string file_path(upload_dir_ + filename);
            std::ofstream output_file_stream(file_path, std::ios::binary);
            Poco::StreamCopier::copyStream(stream, output_file_stream);
            logger.information("Arquivo %s salvo em %s", filename, upload_dir_);

            // Se o calback estiver definido, ele é disparado passando o nome do parâmetro e o
            // caminho completo para o arquivo salvo localmente.
            if (on_key_callback_) {
                on_key_callback_(name, upload_dir_ + filename);
            }
        }
    } catch (Poco::NotFoundException& e) {
        logger.warning("Parâmetro não encontrado no cabeçalho do pacote: %s", e.message());
    }
}

} /* namespace Route */
