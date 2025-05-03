cmake_minimum_required(VERSION 3.20)

project(LevelGeneration)

set(CMAKE_CXX_STANDARD 20)

set(SOURCES
    levelGeneration.cpp
)

set(HEADERS
    levelGeneration.hpp
    Tiles.hpp
)

add_library(LevelGeneration STATIC ${SOURCES} ${HEADERS})

find_package(SFML 2.5 COMPONENTS graphics REQUIRED)
target_link_libraries(LevelGeneration PUBLIC sfml-graphics)

target_include_directories(LevelGeneration PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
