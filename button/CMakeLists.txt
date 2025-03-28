cmake_minimum_required(VERSION 3.20)

set(project "button")
project(${project})

set(CMAKE_CXX_STANDARD 20)

set(${project}_SOURCES
        button.cpp)

set(${project}_HEADERS
        button.hpp)

set(${project}_SOURCE_LIST
        ${${project}_SOURCES}
        ${${project}_HEADERS})

add_library(${project}
        STATIC
        ${${project}_SOURCE_LIST})

find_package(SFML 2.5 COMPONENTS graphics REQUIRED)
target_link_libraries(button PUBLIC sfml-graphics)
