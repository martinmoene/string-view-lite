# Copyright 2017-2018 by Martin Moene
#
# Distributed under the Boost Software License, Version 1.0.
# (See accompanying file LICENSE.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

cmake_minimum_required( VERSION 3.5 )

# string_view-lite project and version, updated by script/update-version.py:

project( string_view_lite LANGUAGES CXX )

set( string_view_lite_version "1.1.0" )

# Toplevel or subproject:

if ( CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR )
    set( string_view_IS_TOPLEVEL_PROJECT TRUE )
else()
    set( string_view_IS_TOPLEVEL_PROJECT FALSE )
endif()

# Enable building and performing of tests and building of examples:

option( STRINGVIEW_LITE_OPT_BUILD_TESTS     "Build and perform string-view-lite tests" ${string_view_IS_TOPLEVEL_PROJECT} )
option( STRINGVIEW_LITE_OPT_BUILD_EXAMPLES  "Build string-view-lite examples" OFF )

option( STRINGVIEW_LITE_OPT_SELECT_STD      "Select std::string_view"    OFF )
option( STRINGVIEW_LITE_OPT_SELECT_NONSTD   "Select nonstd::string_view" OFF )

option( STRINGVIEW_LITE_OPT_CONV_STD_STRING_CLASS_METHODS  "Provide conversion to/from std::string (class methods)"  ON )
option( STRINGVIEW_LITE_OPT_CONV_STD_STRING_FREE_FUNCTIONS "Provide conversion to/from std::string (free functions)" ON )

include( GNUInstallDirs )

set( package_name "string-view-lite" )
set( include_source_dir "${PROJECT_SOURCE_DIR}/include" )

# Interface library:

add_library(
    ${package_name} INTERFACE )

target_include_directories(
    ${package_name} INTERFACE "$<BUILD_INTERFACE:${include_source_dir}>" )

# Installation:

install(
    DIRECTORY ${CMAKE_SOURCE_DIR}/include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR} )

# If requested, build and perform tests, build examples:

enable_testing()

if ( STRINGVIEW_LITE_OPT_BUILD_TESTS )
    add_subdirectory( test )
endif()

if ( STRINGVIEW_LITE_OPT_BUILD_EXAMPLES )
    add_subdirectory( example )
endif()

# end of file
