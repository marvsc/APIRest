cmake_minimum_required(VERSION 3.15)
project(PackageTest CXX)


find_package(assinaturadigital CONFIG REQUIRED)
find_package(verificaassinatura CONFIG REQUIRED)
find_package(OpenSSL CONFIG REQUIRED)
find_package(cppunit CONFIG REQUIRED)
find_package(Poco CONFIG REQUIRED)

add_executable(teste src/teste.cpp
                    src/UnitTests/src/APIRestServerTest.cpp
                    ../src/APIRestRequestHandlerFactory.cpp
                    ../src/Route/APIRestEndpoints.cpp
                    ../src/Route/APIRestFilePartHandler.cpp
                    ../src/Route/APIRestRequestHandler.cpp)
target_link_libraries(teste
                            Poco::Poco
                            openssl::openssl
                            verificaassinatura::verificaassinatura
                            cppunit::cppunit
                            assinaturadigital::assinaturadigital)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/resources/certificado_teste_hub.pfx
${CMAKE_CURRENT_BINARY_DIR}/certificados/certificado_teste_hub.pfx
COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/resources/doc.txt
${CMAKE_CURRENT_BINARY_DIR}/arquivos/doc.txt
COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/resources/signature.p7s
${CMAKE_CURRENT_BINARY_DIR}/assinaturas/signature.p7s
COPYONLY)

