cmake_minimum_required(VERSION 2.6)
project(nagios-check)


set(CMAKE_CXX_FLAGS "-g -Wall")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

find_package(PkgConfig REQUIRED)
#pkg_check_modules(LIBNOTIFY libnotify REQUIRED)

pkg_check_modules(GTKMM gtkmm-2.4 REQUIRED)

#include_directories(${LIBNOTIFY_INCLUDE_DIRS})
include_directories(${GTKMM_INCLUDE_DIRS})

set(mainLibs ${GTKMM_LIBRARIES})

file(
	GLOB_RECURSE
	MAIN_SOURCES
	src/*
)

add_executable(nagios-check ${MAIN_SOURCES})

target_link_libraries(nagios-check ${mainLibs})

configure_file(res/config.cfg config.cfg COPYONLY)
