cmake_minimum_required(VERSION 3.15)
project(restapi CXX)

add_library(restapi
    src/APIRestServerApplication.cpp
    src/APIRestRequestHandlerFactory.cpp
    src/Route/APIRestRequestHandler.cpp
    src/Route/APIRestEndpoints.cpp)

target_include_directories(restapi PUBLIC include)

set_target_properties(restapi PROPERTIES PUBLIC_HEADER
    "include/APIRestServerApplication.h"
    "include/APIRestRequestHandlerFactory.h"
    "include/Route/APIRestRequestHandler.h"
    "include/Route/APIRestEndpoints.h"
    "include/configuration/ConfigurationKeys.h")

install(TARGETS restapi)
