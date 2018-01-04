# Copyright (C) 2017-2018 Martin Moene.
#
# This code is licensed under the MIT License (MIT).

cmake_minimum_required( VERSION 3.0 )

project( string_view_lite )

option( STRINGVIEW_LITE_OPT_SELECT_STDSV    "Select std::string_view"    OFF )
option( STRINGVIEW_LITE_OPT_SELECT_NONSTDSV "Select nonstd::string_view" OFF )

option( STRINGVIEW_LITE_OPT_CONV_STD_STRING_CLASS_METHODS  "Provide conversion to/from std::string (class methods)"  ON )
option( STRINGVIEW_LITE_OPT_CONV_STD_STRING_FREE_FUNCTIONS "Provide conversion to/from std::string (free functions)" ON )

include( GNUInstallDirs )

add_library( string_view_lite INTERFACE )

enable_testing()

add_subdirectory( test )
#add_subdirectory( example )

install( DIRECTORY ${CMAKE_SOURCE_DIR}/include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR} )

# end of file
