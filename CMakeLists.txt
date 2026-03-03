cmake_minimum_required(VERSION 3.20)
project(Velvet VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# try system SFML first
find_package(SFML 2.6 QUIET COMPONENTS graphics window system)

if(NOT SFML_FOUND)
    message(STATUS "SFML not found on system. Fetching 2.6.2...")

    include(FetchContent)

    FetchContent_Declare(
        SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 2.6.2
    )

    set(SFML_BUILD_AUDIO OFF CACHE BOOL "" FORCE)
    set(SFML_BUILD_NETWORK OFF CACHE BOOL "" FORCE)
    set(SFML_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

    FetchContent_MakeAvailable(SFML)
endif()

if(TARGET SFML::Graphics)
    set(SFML_GRAPHICS_TARGET SFML::Graphics)
    set(SFML_WINDOW_TARGET SFML::Window)
    set(SFML_SYSTEM_TARGET SFML::System)
else()
    set(SFML_GRAPHICS_TARGET sfml-graphics)
    set(SFML_WINDOW_TARGET sfml-window)
    set(SFML_SYSTEM_TARGET sfml-system)
endif()

file(GLOB_RECURSE VELVET_SOURCES
    src/*.cpp
)

add_library(velvet ${VELVET_SOURCES})

target_include_directories(velvet
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(velvet
    PUBLIC
        ${SFML_GRAPHICS_TARGET}
        ${SFML_WINDOW_TARGET}
        ${SFML_SYSTEM_TARGET}
)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(CMAKE_EXPORT_COMPILE_COMMANDS)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
    add_custom_target(copy_compile_commands ALL
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_BINARY_DIR}/compile_commands.json
        ${CMAKE_SOURCE_DIR}/compile_commands.json
        DEPENDS ${CMAKE_BINARY_DIR}/compile_commands.json
    )
endif()

add_executable(velvet_app examples/demo.cpp)
target_link_libraries(velvet_app PRIVATE velvet)
