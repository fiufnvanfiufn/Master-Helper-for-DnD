cmake_minimum_required(VERSION 3.20)

project(button)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCES
    button.cpp
)

set(HEADERS
    button.hpp
)

add_library(button STATIC ${SOURCES} ${HEADERS})

find_package(SFML 2.5 COMPONENTS graphics REQUIRED)
target_link_libraries(button PUBLIC sfml-graphics)

target_include_directories(button PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
