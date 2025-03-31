cmake_minimum_required(VERSION 3.20)
project(MasterHelper)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(button)

find_package(SFML 2.5 COMPONENTS graphics window system audio REQUIRED)

add_executable(MasterHelper
    main.cpp
    menu.cpp
    soundPad.cpp
)

target_link_libraries(MasterHelper
    PRIVATE
        button
        sfml-graphics
        sfml-window
        sfml-system
        sfml-audio
)

target_include_directories(MasterHelper PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

add_custom_command(TARGET MasterHelper POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/assets $<TARGET_FILE_DIR:MasterHelper>/assets)
