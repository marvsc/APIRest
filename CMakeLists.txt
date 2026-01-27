cmake_minimum_required(VERSION 3.15)
project(restapi CXX)

find_package(poco CONFIG REQUIRED)



add_library(restapi src/restapi.cpp)
target_include_directories(restapi PUBLIC include)

target_link_libraries(restapi PRIVATE poco::poco)


set_target_properties(restapi PROPERTIES PUBLIC_HEADER "include/restapi.h")
install(TARGETS restapi)
