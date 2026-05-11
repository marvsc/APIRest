cmake_minimum_required(VERSION 3.15)
project(PackageTest CXX)


find_package(assinaturadigital CONFIG REQUIRED)
find_package(verificaassinatura CONFIG REQUIRED)
find_package(OpenSSL CONFIG REQUIRED)
find_package(cppunit CONFIG REQUIRED)
find_package(Poco CONFIG REQUIRED)

add_executable(teste src/teste.cpp
                    src/UnitTests/src/APIRestServerTest.cpp)
target_link_libraries(teste
    Poco::Poco
    openssl::openssl
    verificaassinatura::verificaassinatura
    cppunit::cppunit
    assinaturadigital::assinaturadigital)

