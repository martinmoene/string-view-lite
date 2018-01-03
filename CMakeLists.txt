# Copyright (C) 2017-2018 Martin Moene.
#
# This code is licensed under the MIT License (MIT).

cmake_minimum_required( VERSION 3.0 )

project( string_view_lite )

option( NSSV_SELECT_STDSV     "Select std::string_view"    OFF )
option( NSSV_SELECT_NONSTDSV  "Select nonstd::string_view" OFF )

include( GNUInstallDirs )

add_library( string_view_lite INTERFACE )

enable_testing()

add_subdirectory( test )
#add_subdirectory( example )

install( DIRECTORY ${CMAKE_SOURCE_DIR}/include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR} )

# end of file
