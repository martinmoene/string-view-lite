# Copyright (C) 2017-2018 Martin Moene.
#
# This code is licensed under the MIT License (MIT).

cmake_minimum_required( VERSION 2.8 )

project( string_view_lite )

option( NSSV_SELECT_STDSV     "Select std::string_view"    OFF )
option( NSSV_SELECT_NONSTDSV  "Select nonstd::string_view" OFF )

enable_testing()

add_subdirectory( test )
#add_subdirectory( example )

# end of file
