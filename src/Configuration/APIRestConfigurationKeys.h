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
};

} /* namespace Configuration */

#endif /* SRC_CONFIGURATION_APIRESTCONFIGURATIONKEYS_H_ */
