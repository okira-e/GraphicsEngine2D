cmake_minimum_required(VERSION 3.27)
project(graphics_engine_2d)

set(CMAKE_CXX_STANDARD 20)

file(GLOB_RECURSE SOURCES src/*.*pp)
add_executable(graphics_engine_2d ${SOURCES})

IF (WIN32)
    find_package(SFML 2.6.1 COMPONENTS graphics window system audio REQUIRED PATHS ${CMAKE_SOURCE_DIR}/vendor/SFML-2.6.1_WINDOWS)
ELSEIF (UNIX AND NOT APPLE)
    find_package(SFML 2.6.1 COMPONENTS graphics window system audio REQUIRED PATHS ${CMAKE_SOURCE_DIR}/vendor/SFML-2.6.1_LINUX)
ELSEIF (APPLE)
    find_package(SFML 2.6.1 COMPONENTS graphics window system audio REQUIRED PATHS ${CMAKE_SOURCE_DIR}/vendor/SFML-2.6.1_APPLE)
ENDIF ()

target_link_libraries(graphics_engine_2d PRIVATE sfml-graphics sfml-window sfml-system sfml-audio)
