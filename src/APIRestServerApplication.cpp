
#include "APIRestServerApplication.h"
#include "APIRestRequestHandlerFactory.h"
#include "APIRestErrorHandler.h"

#include "Configuration/APIRestConfigurationKeys.h"

#include <fstream>
#include <OpenSSLUtils.h>

#include <Poco/Path.h>
#include <Poco/File.h>
#include <Poco/ErrorHandler.h>

#include <Poco/Net/HTTPServer.h>
#include <Poco/Net/SSLManager.h>
#include <Poco/Net/Context.h>
#include <Poco/Net/SocketAddress.h>
#include <Poco/Net/SecureServerSocket.h>
#include <Poco/Util/OptionCallback.h>
#include <Poco/Util/PropertyFileConfiguration.h>
#include <Poco/Crypto/PKCS12Container.h>

// Valor default para máximo de conexões possíveis em pilha.
#define MAX_QUEUED 250

// Valor default para máximo de threads possível
#define MAX_THREADS 50

// Valor default para máximo de conexões em fila para ser aceita.
#define DEFAULT_BACKLOG 64

// Chave de criptografia AES 256 CBC utilizada para descriptografar a senha do arquivo PKCS12
#define AES_KEY "b90XmFVR51L485rxXXCRhupVxva0yDFh"

// Vetor de inicialização AES 256 CBC utilizado para descriptografar a senha do arquivo PKCS12
#define AES_INITIALIZATION_VECTOR "NSVmgGXSm2jRTiyq"

void APIRestServerApplication::initialize(Poco::Util::Application& self) {
    try {
        // Carrega o arquivo de configurações
        loadConfiguration();

        // Se houver arquivo de log configurado, cria todos os diretórios parentes dele
        if (config().has(Configuration::APIRestConfigurationKeys::LOGGING_CHANNELS_FILE_PATH)) {
            Poco::Path log_file(config().getString(Configuration::APIRestConfigurationKeys::LOGGING_CHANNELS_FILE_PATH));
            Poco::File dir_log(log_file.parent());
            if (!dir_log.exists()) {
                dir_log.createDirectories();
            }
        }

        // Se houver diretório de upload configurado, cria todos os diretórios parentes dele
        if (config().has(Configuration::APIRestConfigurationKeys::APIREST_UPLOAD_DIR)) {
            Poco::File upload_dir(config().getString(Configuration::APIRestConfigurationKeys::APIREST_UPLOAD_DIR));
            if (!upload_dir.exists()) {
                upload_dir.createDirectories();
            }
        }

        // Inicializa a aplicação
        ServerApplication::initialize(self);
    } catch (Poco::Exception& e) {
        std::printf("Erro inicializando aplicação: %s\n", e.what());
    }
}

int APIRestServerApplication::main(const std::vector<std::string> &args) {
    logger().information("Inicializando APIRest");

    // Define um manipulador de erros
    Poco::ErrorHandler::set(new APIRestErrorHandler);

    // Inicializa o motor SSL
    Poco::Net::initializeSSL();

    // Por segurança, é necessário haver um arquivo PKCS12 configurado para as conexões do servidor.
    //  Se não houver, encerra com erro.
    if (!config().has(Configuration::APIRestConfigurationKeys::APIREST_PKCS12_PATH)) {
        logger().error("Certificado PKCS 12 não configurado, parando servidor");
        return Poco::Util::Application::EXIT_CONFIG;
    }

    // Abre um stream para o arquivo PKCS12 configurado
    std::ifstream pkcs12_stream(config().getString(Configuration::APIRestConfigurationKeys::APIREST_PKCS12_PATH), std::ios::binary);
    if (!pkcs12_stream.good()) {
        logger().error("Certificado não encontrado em %s", config().getString(Configuration::APIRestConfigurationKeys::APIREST_PKCS12_PATH));
        return Poco::Util::Application::EXIT_CONFIG;
    }

    // Se houver senha configurada, carrega o conteúdo do arquivo PKCS12 passando senha, se não carrega
    //  sem senha.
    std::unique_ptr<Poco::Crypto::PKCS12Container> container(nullptr);
    if (config().has(Configuration::APIRestConfigurationKeys::APIREST_PKCS12_PASSWORD_AES_256_CBC_BASE64)) {
        container.reset(new Poco::Crypto::PKCS12Container(pkcs12_stream,
                OpenSSLUtils::decrypt_aes_256_cbc(config().getString(Configuration::APIRestConfigurationKeys::APIREST_PKCS12_PASSWORD_AES_256_CBC_BASE64),
                        AES_KEY, reinterpret_cast<const unsigned char*>(AES_INITIALIZATION_VECTOR))));
    } else {
        container.reset(new Poco::Crypto::PKCS12Container(pkcs12_stream));
    }

    // Instancia o contexto em modo servidor com verificação severa de certificados.
    Poco::Net::Context::Ptr context(new Poco::Net::Context(Poco::Net::Context::SERVER_USE, "", Poco::Net::Context::VERIFY_STRICT));

    // Adiciona os certificados da autoridade certificadora ao contexto.
    for (Poco::Crypto::X509Certificate ca_cert : container->getCACerts()) {
        context->addCertificateAuthority(ca_cert);
    }

    // Define o certificado do contexto.
    context->useCertificate(container->getX509Certificate());

    // Define a chave privada do contexto.
    context->usePrivateKey(container->getKey());

    // Inicializa o contexto no motos SSL.
    Poco::Net::SSLManager::instance().initializeServer(nullptr, nullptr, context);

    // Define a porta de conexão do servidor.
    set_port(DEFAULT_PORT);

    // Define o roteador passando o path do diretório de upload.
    set_router(new APIRestRequestHandlerFactory(config().getString(Configuration::APIRestConfigurationKeys::APIREST_UPLOAD_DIR)));

    // Seta os parametros de maximo de conexões em pilha e máximo de threads simultâneas para o servidor.
    Poco::Net::HTTPServerParams::Ptr http_server_params = new Poco::Net::HTTPServerParams;
    http_server_params->setMaxQueued(MAX_QUEUED);
    http_server_params->setMaxThreads(MAX_THREADS);

    // Instancia o servidor definindo o roteador. A conexão deve ser segura (HTTPS), deve ser passado o
    //  nome da máquina para evitar problemas na verificação severa de certificados.
    Poco::Net::HTTPServer http_server(get_router(),
            Poco::Net::SecureServerSocket(Poco::Net::SocketAddress(Poco::Environment::nodeName(), Poco::UInt16(port_)), DEFAULT_BACKLOG, context), http_server_params);
    logger().information("Servidor iniciado na porta %d", port_);

    // Inicializa o servidor.
    http_server.start();

    // Segura a thread principal enquando o servidor está em execução.
    waitForTerminationRequest();
    logger().information("Servidor encerrado");
    return Poco::Util::Application::EXIT_OK;
}

void APIRestServerApplication::defineOptions(Poco::Util::OptionSet& options) {
    ServerApplication::defineOptions(options);
    options.addOption(
            Poco::Util::Option("config", "c", "Specify a configuration file path")
                .required(false)
                .repeatable(false)
                .argument("<path>")
                .callback(Poco::Util::OptionCallback<APIRestServerApplication>(
                        this, &APIRestServerApplication::handleConfiguration)));
}

void APIRestServerApplication::handleConfiguration(const std::string& name, const std::string& value) {
    try {
        if (value.empty()) {
            return;
        }
        Poco::Util::PropertyFileConfiguration::Ptr configuration(new Poco::Util::PropertyFileConfiguration(value));
        config().add(configuration, Poco::Util::Application::PRIO_APPLICATION + 1);
    } catch (Poco::Exception& e) {
        std::printf("Erro definindo configuração: %s\n", e.displayText().c_str());
    }
}


