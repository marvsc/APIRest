/*
 * @file JSONKeysVerify.h
 * @brief Macros que definem o nome das chaves do JSON de retorno
 * @author Marcus Chaves
 * @date 2026-10-27
 */

#ifndef SRC_ROUTE_JSONKEYSVERIFY_H_
#define SRC_ROUTE_JSONKEYSVERIFY_H_

namespace Route {

#define STATUS "STATUS"
#define VALID "VÁLIDO"
#define INVALID "INVÁLIDO"
#define SIGNER_NAME "Nome do Signatário"
#define SIGNING_DATE "Data da assinatura"
#define HASH "Hash do documento"
#define ALGORITHM_NAME "Nome do algoritmo de hash"

} /* namespace Route */

#endif /* SRC_ROUTE_JSONKEYSVERIFY_H_ */
