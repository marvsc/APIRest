cmake_minimum_required(VERSION 3.15)
project(apirest CXX)

find_package(assinaturadigital CONFIG REQUIRED)

add_executable(apirest
    src/APIRestServerApplication.cpp
    src/APIRestRequestHandlerFactory.cpp
    src/MyDetailedHandler.cpp
    src/MyErrorHandler.cpp
    src/Route/APIRestRequestHandler.cpp
    src/Route/APIRestEndpoints.cpp
    src/Route/APIRestFilePartHandler.cpp)

target_link_libraries(apirest PRIVATE assinaturadigital::assinaturadigital)

install(TARGETS apirest DESTINATION "."
        RUNTIME DESTINATION bin
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
        )

set(CONFIGURE_PATH ${CMAKE_INSTALL_PREFIX}/conf)
configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/resource/APIRest.properties.in
    conf/APIRest.properties
    @ONLY
)

install(FILES
            ${CMAKE_CURRENT_SOURCE_DIR}/resource/certificado_teste_hub.pfx
            ${CMAKE_BINARY_DIR}/conf/APIRest.properties
        DESTINATION conf/)
