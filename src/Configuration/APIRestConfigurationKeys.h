/*
 * APIRestConfigurationKeys.h
 *
 *  Created on: 10 de fev. de 2026
 *      Author: marcus.chaves
 */

#ifndef SRC_CONFIGURATION_APIRESTCONFIGURATIONKEYS_H_
#define SRC_CONFIGURATION_APIRESTCONFIGURATIONKEYS_H_

namespace Configuration {

class APIRestConfigurationKeys {
public:
    static constexpr const char* APIREST_UPLOAD_DIR = "apirest.upload.dir";
    static constexpr const char* LOGGING_CHANNELS_FILE_PATH = "logging.channels.file.path";
    static constexpr const char* APIREST_PKCS12_PATH = "apirest.pkcs12.path";
    static constexpr const char* APIREST_PKCS12_PASSWORD_AES_256_CBC_BASE64 = "apirest.pkcs12.password.aes.256.cbc.base64";
    static constexpr const char* APIREST_PKCS12_PASSWORD_AES_KEY = "apirest.pkcs12.password.aes.key";
    static constexpr const char* APIREST_PKCS12_PASSOWRD_INITIALIZATION_VECTOR = "apirest.pkcs12.passowrd.aes.initialization.vector";
};

} /* namespace Configuration */

#endif /* SRC_CONFIGURATION_APIRESTCONFIGURATIONKEYS_H_ */
