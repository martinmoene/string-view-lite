// Copyright 2017-2019 by Martin Moene
//
// https://github.com/martinmoene/string-view-lite
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include "string_view-main.t.hpp"

#define nssv_PRESENT( x ) \
    std::cout << #x << ": " << x << "\n"

#define nssv_ABSENT( x ) \
    std::cout << #x << ": (undefined)\n"

lest::tests & specification()
{
    static lest::tests tests;
    return tests;
}

CASE( "string-view-lite version" "[.string-view][.version]" )
{
    nssv_PRESENT( string_view_lite_MAJOR   );
    nssv_PRESENT( string_view_lite_MINOR   );
    nssv_PRESENT( string_view_lite_PATCH   );
    nssv_PRESENT( string_view_lite_VERSION );
}

CASE( "string-view-lite configuration" "[.string-view][.config]" )
{
    nssv_PRESENT( nssv_HAVE_STD_STRING_VIEW );
    nssv_PRESENT( nssv_USES_STD_STRING_VIEW );
    nssv_PRESENT( nssv_STRING_VIEW_DEFAULT );
    nssv_PRESENT( nssv_STRING_VIEW_NONSTD );
    nssv_PRESENT( nssv_STRING_VIEW_STD );
    nssv_PRESENT( nssv_CONFIG_SELECT_STRING_VIEW );
    nssv_PRESENT( nssv_CONFIG_STD_SV_OPERATOR );
    nssv_PRESENT( nssv_CONFIG_USR_SV_OPERATOR );
//  nssv_PRESENT( nssv_CONFIG_CONVERSION_STD_STRING );
    nssv_PRESENT( nssv_CONFIG_CONVERSION_STD_STRING_CLASS_METHODS );
    nssv_PRESENT( nssv_CONFIG_CONVERSION_STD_STRING_FREE_FUNCTIONS );
    nssv_PRESENT( nssv_CONFIG_NO_EXCEPTIONS );
    nssv_PRESENT( nssv_CPLUSPLUS );
}

CASE( "__cplusplus" "[.stdc++]" )
{
    nssv_PRESENT( __cplusplus );

#if _MSVC_LANG
    nssv_PRESENT( _MSVC_LANG );
#else
    nssv_ABSENT(  _MSVC_LANG );
#endif
}

CASE( "Compiler version" "[.compiler]" )
{
#if nssv_USES_STD_STRING_VIEW
    std::cout << "(Compiler version not available: using std::string_view)\n";
#else
    nssv_PRESENT( nssv_COMPILER_CLANG_VERSION );
    nssv_PRESENT( nssv_COMPILER_GNUC_VERSION );
    nssv_PRESENT( nssv_COMPILER_MSVC_VERSION );
#endif
}

CASE( "presence of C++ language features" "[.stdlanguage]" )
{
#if nssv_USES_STD_STRING_VIEW
    std::cout << "(Compiler version not available: using std::string_view)\n";
#else
    nssv_PRESENT( nssv_HAVE_CONSTEXPR_11 );
    nssv_PRESENT( nssv_HAVE_CONSTEXPR_14 );
    nssv_PRESENT( nssv_HAVE_EXPLICIT_CONVERSION );
    nssv_PRESENT( nssv_HAVE_NODISCARD );
    nssv_PRESENT( nssv_HAVE_NOEXCEPT );
    nssv_PRESENT( nssv_HAVE_NULLPTR );
    nssv_PRESENT( nssv_HAVE_REF_QUALIFIER );
    nssv_PRESENT( nssv_HAVE_UNICODE_LITERALS );
    nssv_PRESENT( nssv_HAVE_USER_DEFINED_LITERALS );
    nssv_PRESENT( nssv_HAVE_WCHAR16_T );
    nssv_PRESENT( nssv_HAVE_WCHAR32_T );
#endif

}

CASE( "presence of C++ library features" "[.stdlibrary]" )
{
#if nssv_USES_STD_STRING_VIEW
    std::cout << "(Compiler version not available: using std::string_view)\n";
#else
    nssv_PRESENT( nssv_HAVE_STD_HASH );
#endif

#if _HAS_CPP0X
    nssv_PRESENT( _HAS_CPP0X );
#else
    nssv_ABSENT(  _HAS_CPP0X );
#endif
}

int main( int argc, char * argv[] )
{
    return lest::run( specification(), argc, argv );
}

#if 0
g++            -I../include -o string_view-main.t.exe string_view-main.t.cpp && string_view-main.t.exe --pass
g++ -std=c++98 -I../include -o string_view-main.t.exe string_view-main.t.cpp && string_view-main.t.exe --pass
g++ -std=c++03 -I../include -o string_view-main.t.exe string_view-main.t.cpp && string_view-main.t.exe --pass
g++ -std=c++0x -I../include -o string_view-main.t.exe string_view-main.t.cpp && string_view-main.t.exe --pass
g++ -std=c++11 -I../include -o string_view-main.t.exe string_view-main.t.cpp && string_view-main.t.exe --pass
g++ -std=c++14 -I../include -o string_view-main.t.exe string_view-main.t.cpp && string_view-main.t.exe --pass
g++ -std=c++17 -I../include -o string_view-main.t.exe string_view-main.t.cpp && string_view-main.t.exe --pass

cl -EHsc -I../include string_view-main.t.cpp && string_view-main.t.exe --pass
#endif

// end of file
