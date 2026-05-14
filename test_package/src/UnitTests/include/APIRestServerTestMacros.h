/*
 * APIRestServerTestMacros.h
 *
 *  Created on: 14 de mai. de 2026
 *      Author: marcus.chaves
 */

#ifndef TEST_PACKAGE_SRC_UNITTESTS_INCLUDE_APIRESTSERVERTESTMACROS_H_
#define TEST_PACKAGE_SRC_UNITTESTS_INCLUDE_APIRESTSERVERTESTMACROS_H_

#define BUFFER_LENGTH 256
#define LOCAL_IP "127.0.0.1"
#define DEFAULT_PORT 9000
#define SIGNATURE_PATH "/signature"
#define VERIFY_PATH "/verify"
#define UPLOAD_PATH "."
#define FILE_TO_ASSIGN "File-To-Assign"
#define FILE_TO_ASSIGN_PATH "arquivos/doc.txt"
#define FILE_TO_VERIFY "File-To-Verify"
#define FILE_TO_VERIFY_PATH "assinaturas/signature.p7s"
#define CERTIFICATE "Certificate"
#define CERTIFICATE_PATH "certificados/certificado_teste_hub.pfx"
#define PASSWORD "Password"
#define AES_KEY "b90XmFVR51L485rxXXCRhupVxva0yDFh"
#define AES_INITIALIZATION_VECTOR "NSVmgGXSm2jRTiyq"
#define PKCS12_ENVVAR_PASSWORD "PKCS12_ENVVAR_PASSWORD"
#define CONTENT_TYPE_PLAIN_TEXT "text/plain; charset=utf-8"
#define CONTENT_TYPE_JSON "application/json"

#define PRINTF_MESSAGE(format, ...) \
    ([&]() { \
            char buffer[BUFFER_LENGTH]; \
            std::snprintf(buffer, BUFFER_LENGTH, format, ##__VA_ARGS__); \
            return std::string(buffer); \
    }())

#endif /* TEST_PACKAGE_SRC_UNITTESTS_INCLUDE_APIRESTSERVERTESTMACROS_H_ */
