// Copyright (C) 2017-2018 Martin Moene.
//
// https://github.com/martinmoene/string-view-lite
//
// This code is licensed under the MIT License (MIT).
//

#include "string-view-lite.t.h"
#include <algorithm>

namespace {

using namespace nonstd;

typedef string_view::size_type size_type;

// Constructors:

CASE( "string_view: Allows to default construct an empty string_view" )
{
    string_view sv;

    // use parenthesis with data() to prevent lest from using sv.data() as C-string:

    EXPECT(  sv.size() == size_type( 0 ) );
    EXPECT( (sv.data() == nssv_nullptr)  );
}

CASE( "string_view: Allows to construct from pointer and size" )
{
    string_view sv( "hello world", 5 );

    EXPECT(   sv.size() == size_type( 5 ) );
    EXPECT( *(sv.data() + 0) == 'h'       );
    EXPECT( *(sv.data() + 4) == 'o'       );
}

CASE( "string_view: Allows to construct from C-string" )
{
    string_view sv( "hello world" );

    EXPECT(   sv.size() == size_type( 11 ) );
    EXPECT( *(sv.data() +  0) == 'h'       );
    EXPECT( *(sv.data() + 10) == 'd'       );
}

CASE( "string_view: Allows to copy-construct from empty string-view" )
{
    string_view sv1;

    string_view sv2( sv1 );

    // use parenthesis with data() to prevent lest from using sv.data() as C-string:

    EXPECT(  sv2.size() == size_type( 0 ) );
    EXPECT( (sv2.data() == nssv_nullptr)  );
}

CASE( "string_view: Allows to copy-construct from non-empty string-view" )
{
    string_view sv1( "hello world", 5 );

    string_view sv2( sv1 );

    EXPECT(   sv2.size()      == sv1.size()  );
    EXPECT(  (sv2.data()      == sv1.data()) );
    EXPECT( *(sv2.data() + 0) == 'h'         );
    EXPECT( *(sv2.data() + 4) == 'o'         );
}

// Assignment:

CASE( "string_view: Allows to copy-assign from empty string-view" )
{
    string_view sv1;
    string_view sv2;

    sv2 = sv1;

    // use parenthesis with data() to prevent lest from using sv.data() as C-string:

    EXPECT(  sv2.size() == size_type( 0 ) );
    EXPECT( (sv2.data() == nssv_nullptr) );
}

CASE( "string_view: Allows to copy-assign from non-empty string-view" )
{
    string_view sv1( "hello world", 5 );
    string_view sv2;

    sv2 = sv1;

    // use parenthesis with data() to prevent lest from using sv.data() as C-string:

    EXPECT(   sv2.size()      == sv1.size()  );
    EXPECT(  (sv2.data()      == sv1.data()) );
    EXPECT( *(sv2.data() + 0) == 'h'         );
    EXPECT( *(sv2.data() + 4) == 'o'         );
}

// Iteration:

CASE( "string_view: Allows forward iteration" )
{
    char hello[] = "hello";
    string_view sv( hello );

    for ( string_view::iterator pos = sv.begin(); pos != sv.end(); ++pos )
    {
        int i = std::distance( sv.begin(), pos );
        EXPECT( *pos == *(sv.data() + i) );
    }
}

CASE( "string_view: Allows const forward iteration" )
{
    char hello[] = "hello";
    string_view sv( hello );

    for ( string_view::const_iterator pos = sv.begin(); pos != sv.end(); ++pos )
    {
        int i = std::distance( sv.cbegin(), pos );
        EXPECT( *pos == *(sv.data() + i) );
    }
}

CASE( "string_view: Allows reverse iteration" )
{
    char hello[] = "hello";
    string_view sv( hello );

    for ( string_view::reverse_iterator pos = sv.rbegin(); pos != sv.rend(); ++pos )
    {
        int dist = std::distance( sv.rbegin(), pos );
        EXPECT( *pos == *(sv.data() + sv.size() - 1 - dist) );
    }
}

CASE( "string_view: Allows const reverse iteration" )
{
    char hello[] = "hello";
    string_view sv( hello );

    for ( string_view::const_reverse_iterator pos = sv.crbegin(); pos != sv.crend(); ++pos )
    {
        int dist = std::distance( sv.crbegin(), pos );
        EXPECT( *pos == *(sv.data() + sv.size() - 1 - dist) );
    }
}

// Capacity:

CASE( "string_view: Allows to obtain the size of the view via size()" )
{
    char hello[] = "hello";
    string_view sv( hello );

    EXPECT( sv.size() == std::char_traits<char>::length(hello) );
}

CASE( "string_view: Allows to obtain the size of the view via length()" )
{
    char hello[] = "hello";
    string_view sv( hello );

    EXPECT( sv.length() == std::char_traits<char>::length(hello) );
}

CASE( "string_view: Allows to obtain the maximum size a view can be via max_size()" )
{
    string_view sv( "hello" );

    EXPECT( sv.max_size() == std::numeric_limits< string_view::size_type >::max() );
}

// Element access:

CASE( "string_view: Allows to observe an element via array indexing" )
{
    char hello[] = "hello";
    string_view sv( hello );

    for ( size_type i = 0; i < sv.size(); ++i )
    {
        EXPECT( sv[i] == hello[i] );
    }
}

CASE( "string_view: Allows to observe an element via at()" )
{
    char hello[] = "hello";
    string_view sv( hello );

    for ( size_type i = 0; i < sv.size(); ++i )
    {
        EXPECT( sv.at(i) == hello[i] );
    }
}

CASE( "string_view: Allows to observe elements via data()" )
{
    char hello[] = "hello";
    string_view sv( hello );

    EXPECT( *sv.data() == *sv.begin() );

    for ( size_type i = 0; i < sv.size(); ++i )
    {
        EXPECT( sv.data()[i] == hello[i] );
    }
}

CASE( "string_view: . . .  and data() yields nullptr (or NULL) for an empty string_view" )
{
    string_view sv;

    // use parenthesis with data() to prevent lest from using sv.data() as C-string:

    EXPECT( (sv.data() == nssv_nullptr) );
}

// Modifiers:

CASE( "string_view: Allows to check for an empty string_view via empty()" )
{
    string_view sve;
    string_view svne("hello");

    EXPECT(      sve.size() == size_type( 0 ) );
    EXPECT(      sve.empty() );
    EXPECT_NOT( svne.empty() );
}

CASE( "string_view: Allows to remove a prefix of n elements" )
{
    char hello[] = "hello world";
    string_view sv( hello );

    sv.remove_prefix( 6 );

    EXPECT( sv.size() == size_type( 5 ) );
    EXPECT( std::equal( sv.begin(), sv.end(), hello + 6) );
}

CASE( "string_view: Allows to remove a suffix of n elements" )
{
    char hello[] = "hello world";
    string_view sv( hello );

    sv.remove_suffix( 6 );

    EXPECT( sv.size() == size_type( 5 ) );
    EXPECT( std::equal( sv.begin(), sv.end(), hello ) );
}

CASE( "string_view: Allows to swap with other string_view" )
{
    char hello[]  = "hello";
    char world[]  = "world";
    string_view sv1( hello );
    string_view sv2( world );

    sv1.swap( sv2 );

    EXPECT( std::equal( sv1.begin(), sv1.end(), world )  );
    EXPECT( std::equal( sv2.begin(), sv2.end(), hello )  );
}

// Comparison:

#if 0
CASE( "string_view: Allows to compare a string_view with another string_view" )
{
    char s[] = "hello";
    char t[] = "world";
    string_view sv( s );
    string_view tv( t );

    EXPECT( sv.length() == size_type( 5 ) );
    EXPECT( tv.length() == size_type( 5 ) );

    EXPECT( sv == sv );
    EXPECT( sv != tv );
    EXPECT( sv <= sv );
    EXPECT( sv <= tv );
    EXPECT( sv <  tv );
    EXPECT( tv >= tv );
    EXPECT( tv >= sv );
    EXPECT( tv >  sv );
}

CASE( "string_view: Allows to compare empty string_view-s as equal" )
{
    string_view a, b;

    EXPECT( a == b );
}
#endif // 0

// Streaming:

CASE ( "operator<<: Allows printing a string_view to an output stream" )
{
    std::ostringstream oss;
    char s[] = "hello";
    string_view sv( s );

    oss << sv << '\n'
        << std::left << std::setw(10) << sv << '\n'
        << sv << '\n'
        << std::setfill('.') << std::right << std::setw(10) << sv;

    EXPECT( oss.str() == "hello\n     hello\nhello\nhello....." );
}


} // anonymous namespace
