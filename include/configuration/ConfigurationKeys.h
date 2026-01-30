/*
 * ConfigurationKeys.h
 *
 *  Created on: 30 de jan. de 2026
 *      Author: marcus.chaves
 */

#ifndef INCLUDE_CONFIGURATION_CONFIGURATIONKEYS_H_
#define INCLUDE_CONFIGURATION_CONFIGURATIONKEYS_H_

namespace Configuration {

class ConfigurationKeys {
public:
    static const char* LOGGING_CHANNELS_CONSOLE = "logging.channels.console";
    static const char* LOGGING_CHANNELS_CONSOLE_COLORS = "logging.channels.console.colors";
    static const char* LOGGING_CHANNELS_FILE = "logging.channels.file";
    static const char* LOGGING_CHANNELS_FILE_PATH = "logging.channels.file.path";
    static const char* LOGGING_CHANNELS_FILE_ROTATION = "logging.channels.file.rotation";
    static const char* LOGGING_CHANNELS_FILE_ARCHIVE = "logging.channels.file.archive";
    static const char* LOGGING_CHANNELS_FILE_TIMES = "logging.channels.file.times";
    static const char* LOGGING_CHANNELS_FILE_COMPRESS = "logging.channels.file.compress";
    static const char* LOGGING_CHANNELS_FILE_PURGE_AGE = "logging.channels.file.purge.age";
    static const char* LOGGING_CHANNELS_FILE_PURGE_COUNT = "logging.channels.file.purge.count";
};

} /* namespace Configuration */

#endif /* INCLUDE_CONFIGURATION_CONFIGURATIONKEYS_H_ */
