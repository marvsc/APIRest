cmake_minimum_required(VERSION 3.15)
project(apirest CXX)

find_package(assinaturadigital CONFIG REQUIRED)

add_executable(apirest
    src/APIRestServerApplication.cpp
    src/APIRestRequestHandlerFactory.cpp
    src/Route/APIRestRequestHandler.cpp
    src/Route/APIRestEndpoints.cpp
    src/Route/APIRestFilePartHandler.cpp)

target_link_libraries(apirest PRIVATE assinaturadigital::assinaturadigital)

target_compile_definitions(apirest PRIVATE POCO_STATIC)

install(TARGETS apirest DESTINATION "."
        RUNTIME DESTINATION bin
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
        )

install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/resource/APIRest.properties
        DESTINATION conf/)
