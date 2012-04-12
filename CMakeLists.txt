cmake_minimum_required(VERSION 2.6)
project(nagios-check)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

set(CMAKE_CXX_FLAGS "-g -Wall")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

find_package(PkgConfig REQUIRED)
pkg_check_modules(LIBNOTIFY libnotify REQUIRED)

find_package(SFML 1.6 REQUIRED system window graphics network audio)

include_directories(${LIBNOTIFY_INCLUDE_DIRS})
include_directories(${SFML_INCLUDE_DIR})

set(mainLibs ${LIBNOTIFY_LIBRARIES} ${SFML_LIBRARIES})

file(
	GLOB_RECURSE
	MAIN_SOURCES
	src/*
)

add_executable(nagios-check ${MAIN_SOURCES})

target_link_libraries(nagios-check ${mainLibs})
