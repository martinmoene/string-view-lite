// Copyright 2017-2018 by Martin Moene
//
// https://github.com/martinmoene/string-view-lite
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include "string-view-lite.t.h"

#define nssv_PRESENT( x ) \
    std::cout << #x << ": " << x << "\n"

#define nssv_ABSENT( x ) \
    std::cout << #x << ": (undefined)\n"

lest::tests & specification()
{
    static lest::tests tests;
    return tests;
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

CASE( "string-view-lite version" "[.version]" )
{
    nssv_PRESENT( string_view_lite_MAJOR   );
    nssv_PRESENT( string_view_lite_MINOR   );
    nssv_PRESENT( string_view_lite_PATCH   );
    nssv_PRESENT( string_view_lite_VERSION );
}

CASE( "string-view-lite configuration" "[.config]" )
{
#if nssv_HAVE_STD_STRING_VIEW
    std::cout << "Have std::string_view\n";
#else
    std::cout << "No std::string_view\n";
#endif

#if nssv_USES_STD_STRING_VIEW
    std::cout << "Using std::string_view\n";
#else
    std::cout << "Using nonstd::string_view\n";
#endif
}

#if !nssv_HAVE_STD_OPTIONAL

CASE( "compiler version" "[.compiler]" )
{
#if nssv_COMPILER_GNUC_VERSION
    nssv_PRESENT( nssv_COMPILER_GNUC_VERSION );
#else
    nssv_ABSENT(  nssv_COMPILER_GNUC_VERSION );
#endif

#if nssv_COMPILER_MSVC_VERSION
    nssv_PRESENT( nssv_COMPILER_MSVC_VERSION );
#else
    nssv_ABSENT(  nssv_COMPILER_MSVC_VERSION );
#endif
}

CASE( "presence of C++ language features" "[.stdlanguage]" )
{
#if nssv_HAVE_AUTO
    nssv_PRESENT( nssv_HAVE_AUTO );
#else
    nssv_ABSENT(  nssv_HAVE_AUTO );
#endif

#if nssv_HAVE_NULLPTR
    nssv_PRESENT( nssv_HAVE_NULLPTR );
#else
    nssv_ABSENT(  nssv_HAVE_NULLPTR );
#endif

#if nssv_HAVE_STATIC_ASSERT
    nssv_PRESENT( nssv_HAVE_STATIC_ASSERT );
#else
    nssv_ABSENT(  nssv_HAVE_STATIC_ASSERT );
#endif

#if nssv_HAVE_DEFAULT_FUNCTION_TEMPLATE_ARG
    nssv_PRESENT( nssv_HAVE_DEFAULT_FUNCTION_TEMPLATE_ARG );
#else
    nssv_ABSENT(  nssv_HAVE_DEFAULT_FUNCTION_TEMPLATE_ARG );
#endif

#if nssv_HAVE_ALIAS_TEMPLATE
    nssv_PRESENT( nssv_HAVE_ALIAS_TEMPLATE );
#else
    nssv_ABSENT(  nssv_HAVE_ALIAS_TEMPLATE );
#endif

#if nssv_HAVE_CONSTEXPR_11
    nssv_PRESENT( nssv_HAVE_CONSTEXPR_11 );
#else
    nssv_ABSENT(  nssv_HAVE_CONSTEXPR_11 );
#endif

#if nssv_HAVE_CONSTEXPR_14
    nssv_PRESENT( nssv_HAVE_CONSTEXPR_14 );
#else
    nssv_ABSENT(  nssv_HAVE_CONSTEXPR_14 );
#endif

#if nssv_HAVE_ENUM_CLASS
    nssv_PRESENT( nssv_HAVE_ENUM_CLASS );
#else
    nssv_ABSENT(  nssv_HAVE_ENUM_CLASS );
#endif

#if nssv_HAVE_ENUM_CLASS_CONSTRUCTION_FROM_UNDERLYING_TYPE
    nssv_PRESENT( nssv_HAVE_ENUM_CLASS_CONSTRUCTION_FROM_UNDERLYING_TYPE );
#else
    nssv_ABSENT(  nssv_HAVE_ENUM_CLASS_CONSTRUCTION_FROM_UNDERLYING_TYPE );
#endif

#if nssv_HAVE_EXPLICIT_CONVERSION
    nssv_PRESENT( nssv_HAVE_EXPLICIT_CONVERSION );
#else
    nssv_ABSENT(  nssv_HAVE_EXPLICIT_CONVERSION );
#endif

#if nssv_HAVE_INITIALIZER_LIST
    nssv_PRESENT( nssv_HAVE_INITIALIZER_LIST );
#else
    nssv_ABSENT(  nssv_HAVE_INITIALIZER_LIST );
#endif

#if nssv_HAVE_IS_DEFAULT
    nssv_PRESENT( nssv_HAVE_IS_DEFAULT );
#else
    nssv_ABSENT(  nssv_HAVE_IS_DEFAULT );
#endif

#if nssv_HAVE_IS_DELETE
    nssv_PRESENT( nssv_HAVE_IS_DELETE );
#else
    nssv_ABSENT(  nssv_HAVE_IS_DELETE );
#endif

#if nssv_HAVE_NOEXCEPT
    nssv_PRESENT( nssv_HAVE_NOEXCEPT );
#else
    nssv_ABSENT(  nssv_HAVE_NOEXCEPT );
#endif

#if nssv_HAVE_REF_QUALIFIER
    nssv_PRESENT( nssv_HAVE_REF_QUALIFIER );
#else
    nssv_ABSENT(  nssv_HAVE_REF_QUALIFIER );
#endif

#if nssv_HAVE_UNICODE_LITERALS
    nssv_PRESENT( nssv_HAVE_UNICODE_LITERALS );
#else
    nssv_ABSENT(  nssv_HAVE_UNICODE_LITERALS );
#endif
}

CASE( "presence of C++ library features" "[.stdlibrary]" )
{
#if nssv_HAVE_ARRAY
    nssv_PRESENT( nssv_HAVE_ARRAY );
#else
    nssv_ABSENT(  nssv_HAVE_ARRAY );
#endif

#if nssv_HAVE_CONDITIONAL
    nssv_PRESENT( nssv_HAVE_CONDITIONAL );
#else
    nssv_ABSENT(  nssv_HAVE_CONDITIONAL );
#endif

#if nssv_HAVE_CONTAINER_DATA_METHOD
    nssv_PRESENT( nssv_HAVE_CONTAINER_DATA_METHOD );
#else
    nssv_ABSENT(  nssv_HAVE_CONTAINER_DATA_METHOD );
#endif

#if nssv_HAVE_REMOVE_CV
    nssv_PRESENT( nssv_HAVE_REMOVE_CV );
#else
    nssv_ABSENT(  nssv_HAVE_REMOVE_CV );
#endif

#if nssv_HAVE_SIZED_TYPES
    nssv_PRESENT( nssv_HAVE_SIZED_TYPES );
#else
    nssv_ABSENT(  nssv_HAVE_SIZED_TYPES );
#endif

#if nssv_HAVE_TYPE_TRAITS
    nssv_PRESENT( nssv_HAVE_TYPE_TRAITS );
#else
    nssv_ABSENT(  nssv_HAVE_TYPE_TRAITS );
#endif

#if nssv_HAVE_WCHAR16_T
    nssv_PRESENT( nssv_HAVE_WCHAR16_T );
#else
    nssv_ABSENT(  nssv_HAVE_WCHAR16_T );
#endif

#if nssv_HAVE_WCHAR32_T
    nssv_PRESENT( nssv_HAVE_WCHAR32_T );
#else
    nssv_ABSENT(  nssv_HAVE_WCHAR32_T );
#endif

#if _HAS_CPP0X
    nssv_PRESENT( _HAS_CPP0X );
#else
    nssv_ABSENT(  _HAS_CPP0X );
#endif
}

#endif // nssv_HAVE_STD_OPTIONAL

CASE( "Configuration of string_view lite" "[.config]" )
{
#if nssv_CONFIG_SELECT_STD_STRING_VIEW
    nssv_PRESENT( nssv_CONFIG_SELECT_STD_STRING_VIEW );
#else
    nssv_ABSENT(  nssv_CONFIG_SELECT_STD_STRING_VIEW );
#endif

#if nssv_CONFIG_SELECT_NONSTD_STRING_VIEW
    nssv_PRESENT( nssv_CONFIG_SELECT_NONSTD_STRING_VIEW );
#else
    nssv_ABSENT(  nssv_CONFIG_SELECT_NONSTD_STRING_VIEW );
#endif

#if nssv_CONFIG_STD_SV_OPERATOR
    nssv_PRESENT( nssv_CONFIG_STD_SV_OPERATOR );
#else
    nssv_ABSENT(  nssv_CONFIG_STD_SV_OPERATOR );
#endif

#if nssv_CONFIG_USR_SV_OPERATOR
    nssv_PRESENT( nssv_CONFIG_USR_SV_OPERATOR );
#else
    nssv_ABSENT(  nssv_CONFIG_USR_SV_OPERATOR );
#endif

#if nssv_CONFIG_CONVERSION_STD_STRING
    nssv_PRESENT( nssv_CONFIG_CONVERSION_STD_STRING );
#else
    nssv_ABSENT(  nssv_CONFIG_CONVERSION_STD_STRING );
#endif

#if nssv_CONFIG_CONVERSION_STD_STRING_CLASS_METHODS
    nssv_PRESENT( nssv_CONFIG_CONVERSION_STD_STRING_CLASS_METHODS );
#else
    nssv_ABSENT(  nssv_CONFIG_CONVERSION_STD_STRING_CLASS_METHODS );
#endif

#if nssv_CONFIG_CONVERSION_STD_STRING_FREE_FUNCTIONS
    nssv_PRESENT( nssv_CONFIG_CONVERSION_STD_STRING_FREE_FUNCTIONS );
#else
    nssv_ABSENT(  nssv_CONFIG_CONVERSION_STD_STRING_FREE_FUNCTIONS );
#endif

}

int main( int argc, char * argv[] )
{
    return lest::run( specification(), argc, argv );
}

#if 0
g++            -I../include/nonstd -o string-view-lite.t.exe string-view-lite.t.cpp && string-view-lite.t.exe --pass
g++ -std=c++98 -I../include/nonstd -o string-view-lite.t.exe string-view-lite.t.cpp && string-view-lite.t.exe --pass
g++ -std=c++03 -I../include/nonstd -o string-view-lite.t.exe string-view-lite.t.cpp && string-view-lite.t.exe --pass
g++ -std=c++0x -I../include/nonstd -o string-view-lite.t.exe string-view-lite.t.cpp && string-view-lite.t.exe --pass
g++ -std=c++11 -I../include/nonstd -o string-view-lite.t.exe string-view-lite.t.cpp && string-view-lite.t.exe --pass
g++ -std=c++14 -I../include/nonstd -o string-view-lite.t.exe string-view-lite.t.cpp && string-view-lite.t.exe --pass
g++ -std=c++17 -I../include/nonstd -o string-view-lite.t.exe string-view-lite.t.cpp && string-view-lite.t.exe --pass

cl -EHsc -I../include/nonstd string-view-lite.t.cpp && string-view-lite.t.exe --pass
#endif

// end of file
