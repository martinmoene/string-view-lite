# Copyright 2017-2018 by Martin Moene
#
# https://github.com/martinmoene/string-view-lite
#
# This code is licensed under the MIT License (MIT).

cmake_minimum_required( VERSION 2.8.12 )

project( test )

function( enable_msvs_guideline_checker target )
    set_target_properties( ${target} PROPERTIES
        VS_GLOBAL_EnableCppCoreCheck true
        VS_GLOBAL_CodeAnalysisRuleSet CppCoreCheckRules.ruleset
        VS_GLOBAL_RunCodeAnalysis true )
endfunction()

include_directories( "${PROJECT_SOURCE_DIR}/../include/nonstd" )

set( SOURCES string-view-lite.t.cpp string-view.t.cpp )

add_executable( string-view-lite.t ${SOURCES} )

set( HAS_STD_FLAGS  FALSE )
set( HAS_CPP11_FLAG FALSE )
set( HAS_CPP14_FLAG FALSE )
set( HAS_CPP17_FLAG FALSE )

set( HAS_MSVC_STD_FLAGS  FALSE )
set( HAS_MSVC_CPP11_FLAG FALSE )
set( HAS_MSVC_CPP14_FLAG FALSE )
set( HAS_MSVC_CPP17_FLAG FALSE )

add_definitions( -Dnssv_STRING_VIEW_HEADER=\"../../string-view-lite/include/nonstd/string_view.hpp\" )

if( MSVC )
    set( HAS_MSVC_STD_FLAGS TRUE )

    if( NOT CMAKE_CXX_COMPILER_VERSION VERSION_LESS 19.00 )
        set( HAS_MSVC_CPP14_FLAG TRUE )
        set( HAS_MSVC_CPPLATEST_FLAG TRUE )
    endif()
    if( NOT CMAKE_CXX_COMPILER_VERSION VERSION_LESS 19.11 )
        set( HAS_MSVC_CPP17_FLAG TRUE )
    endif()

    add_executable( string-view-lite-cpp98.t ${SOURCES} )
    target_compile_options( string-view-lite-cpp98.t  PUBLIC )

    if( HAS_MSVC_CPP14_FLAG )
        add_executable( string-view-lite-cpp14.t ${SOURCES} )
        target_compile_options( string-view-lite-cpp14.t  PUBLIC -std:c++14 )
    endif()

    if( HAS_MSVC_CPP17_FLAG )
        add_executable( string-view-lite-cpp17.t ${SOURCES} )
        target_compile_options( string-view-lite-cpp17.t  PUBLIC -std:c++17 )
        enable_msvs_guideline_checker( string-view-lite-cpp17.t )
    endif()

    if( HAS_MSVC_CPPLATEST_FLAG )
        add_executable( string-view-lite-cpplatest.t ${SOURCES} )
        target_compile_options( string-view-lite-cpplatest.t  PUBLIC -std:c++latest )
    endif()

    add_compile_options( -W3 -EHsc )
    add_definitions( -D_SCL_SECURE_NO_WARNINGS -DNOMINMAX )

elseif( CMAKE_CXX_COMPILER_ID MATCHES GNU OR
        CMAKE_CXX_COMPILER_ID MATCHES Clang )

    set( HAS_STD_FLAGS TRUE )

    # GNU: available -std flags depends on version
    if( CMAKE_CXX_COMPILER_ID MATCHES "GNU" )
        if( NOT CMAKE_CXX_COMPILER_VERSION VERSION_LESS 4.8.0 )
            set( HAS_CPP11_FLAG TRUE )
        endif()
        if( NOT CMAKE_CXX_COMPILER_VERSION VERSION_LESS 4.9.2 )
            set( HAS_CPP14_FLAG TRUE )
        endif()
        if( NOT CMAKE_CXX_COMPILER_VERSION VERSION_LESS 7.1.0 )
            set( HAS_CPP17_FLAG TRUE )
        endif()
    endif()

    # Clang: available -std flags depends on version
    if( CMAKE_CXX_COMPILER_ID MATCHES Clang )
        if( NOT CMAKE_CXX_COMPILER_VERSION VERSION_LESS 3.3.0 )
            set( HAS_CPP11_FLAG TRUE )
        endif()
        if( NOT CMAKE_CXX_COMPILER_VERSION VERSION_LESS 3.4.0 )
            set( HAS_CPP14_FLAG TRUE )
        endif()
        if( NOT CMAKE_CXX_COMPILER_VERSION VERSION_LESS 5.0.0 )
            set( HAS_CPP17_FLAG TRUE )
        endif()
    endif()

    add_executable( string-view-lite-cpp98.t ${SOURCES} )
    target_compile_options( string-view-lite-cpp98.t  PUBLIC -std=c++98 )

    add_executable( string-view-lite-cpp03.t ${SOURCES} )
    target_compile_options( string-view-lite-cpp03.t  PUBLIC -std=c++03 )

    if( HAS_CPP11_FLAG )
        add_executable( string-view-lite-cpp11.t ${SOURCES} )
        target_compile_options( string-view-lite-cpp11.t  PUBLIC -std=c++11 )
    endif()

    if( HAS_CPP14_FLAG )
        add_executable( string-view-lite-cpp14.t ${SOURCES} )
        target_compile_options( string-view-lite-cpp14.t  PUBLIC -std=c++14 )
    endif()

    if( HAS_CPP17_FLAG )
        add_executable( string-view-lite-cpp17.t ${SOURCES} )
        target_compile_options( string-view-lite-cpp17.t  PUBLIC -std=c++17 )
    endif()

    add_compile_options( -Wall -Wno-missing-braces -Wno-unnamed-type-template-args -fno-elide-constructors )

elseif( CMAKE_CXX_COMPILER_ID MATCHES Intel )
# as is
else()
# as is
endif()

# add generic executable, unless -std flags can be specified:

if( NOT HAS_STD_FLAGS AND NOT HAS_MSVC_STD_FLAGS )
    add_executable( string-view-lite.t ${SOURCES} )
    target_link_libraries( string-view-lite.t string-view-lite )
endif()

# with C++17, honour explicit request for std::string_view or nonstd::string_view:

if( HAS_CPP17_FLAG OR HAS_MSVC_CPP17_FLAG )
    if ( NSSV_SELECT_STDSV )
        target_compile_definitions( string-view-lite-cpp17.t PUBLIC nssv_CONFIG_SELECT_STD_STRING_VIEW=1 )
    endif()

    if ( NSSV_SELECT_NONSTDSV )
        target_compile_definitions( string-view-lite-cpp17.t PUBLIC nssv_CONFIG_SELECT_NONSTD_STRING_VIEW=1 )
    endif()
endif()

# configure unit tests via CTest:

enable_testing()

if( HAS_MSVC_STD_FLAGS )
    add_test(     NAME test-cpp98     COMMAND string-view-lite-cpp98.t )

    if( HAS_MSVC_CPP14_FLAG )
        add_test( NAME test-cpp14     COMMAND string-view-lite-cpp14.t )
    endif()
    if( HAS_MSVC_CPP17_FLAG )
        add_test( NAME test-cpp17     COMMAND string-view-lite-cpp17.t )
    endif()
    if( HAS_MSVC_CPPLATEST_FLAG )
        add_test( NAME test-cpplatest COMMAND string-view-lite-cpplatest.t )
    endif()
elseif( HAS_STD_FLAGS )
    add_test(     NAME test-cpp98     COMMAND string-view-lite-cpp98.t )
    add_test(     NAME test-cpp03     COMMAND string-view-lite-cpp03.t )
    if( HAS_CPP11_FLAG )
        add_test( NAME test-cpp11     COMMAND string-view-lite-cpp11.t )
    endif()
    if( HAS_CPP14_FLAG )
        add_test( NAME test-cpp14     COMMAND string-view-lite-cpp14.t )
    endif()
    if( HAS_CPP17_FLAG )
        add_test( NAME test-cpp17     COMMAND string-view-lite-cpp17.t )
    endif()
else()
    add_test(     NAME test           COMMAND gsl-lite.t --pass )
    add_test(     NAME list_version   COMMAND gsl-lite.t --version )
    add_test(     NAME list_tags      COMMAND gsl-lite.t --list-tags )
    add_test(     NAME list_tests     COMMAND gsl-lite.t --list-tests )
endif()

# end of file
