/*
 * @file APIRestConfigurationKeys.h
 * @brief Declaração da classe APIRestConfigurationKeys e atributos.
 * @author Marcus Chaves
 * @date 2026-01-27
 */

#ifndef SRC_CONFIGURATION_APIRESTCONFIGURATIONKEYS_H_
#define SRC_CONFIGURATION_APIRESTCONFIGURATIONKEYS_H_

namespace Configuration {

/*
 * @class APIRestConfigurationKeys
 * @brief Classe que define valores estáticos que correspondem às chaves de configuração.
 */
class APIRestConfigurationKeys {
public:
    static constexpr const char* APIREST_UPLOAD_DIR = "apirest.upload.dir"; ///< @brief Chave de configuração do diretório de upload.
    static constexpr const char* LOGGING_CHANNELS_FILE_PATH = "logging.channels.file.path"; ///< @brief Chave de configuração do caminho do arquivo de log.
    static constexpr const char* APIREST_PKCS12_PATH = "apirest.pkcs12.path"; ///< @brief Chave de configuração do caminho do arquivo PKCS12.
    static constexpr const char* APIREST_PKCS12_PASSWORD_AES_256_CBC_BASE64 = "apirest.pkcs12.password.aes.256.cbc.base64"; ///< @brief Chave de configuração da senha do arquivo PKCS12 criptografada em base 64.
};

} /* namespace Configuration */

#endif /* SRC_CONFIGURATION_APIRESTCONFIGURATIONKEYS_H_ */
