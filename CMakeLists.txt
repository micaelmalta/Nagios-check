cmake_minimum_required(VERSION 2.6)
project(nagios-check)

set(CMAKE_CXX_FLAGS "-g -Wall")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

find_package(PkgConfig REQUIRED)
pkg_check_modules(LIBNOTIFY libnotify REQUIRED)

include_directories(${LIBNOTIFY_INCLUDE_DIRS})

set(mainLibs ${LIBNOTIFY_LIBRARIES})

file(
	GLOB_RECURSE
	MAIN_SOURCES
	src/*
)

add_executable(nagios-check ${MAIN_SOURCES})

target_link_libraries(nagios-check ${mainLibs})
