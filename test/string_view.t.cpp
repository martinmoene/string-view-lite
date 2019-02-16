// Copyright 2017-2019 Martin Moene
//
// https://github.com/martinmoene/string-view-lite
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include "string_view-main.t.hpp"
#include <vector>

namespace {

using namespace nonstd;

template< class T >
T * data( std::vector<T> & v )
{
#if nssv_CPP11_OR_GREATER
    return v.data();
#else
    return &v[0];
#endif
}

typedef string_view::size_type size_type;

// 24.4.2.1 Construction and assignment:

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

CASE( "string_view: Allows to copy-construct from empty string_view" )
{
    string_view sv1;

    string_view sv2( sv1 );

    // use parenthesis with data() to prevent lest from using sv.data() as C-string:

    EXPECT(  sv2.size() == size_type( 0 ) );
    EXPECT( (sv2.data() == nssv_nullptr)  );
}

CASE( "string_view: Allows to copy-construct from non-empty string_view" )
{
    string_view sv1( "hello world", 5 );

    string_view sv2( sv1 );

    EXPECT(   sv2.size()      == sv1.size()  );
    EXPECT(  (sv2.data()      == sv1.data()) );
    EXPECT( *(sv2.data() + 0) == 'h'         );
    EXPECT( *(sv2.data() + 4) == 'o'         );
}

// Assignment:

CASE( "string_view: Allows to copy-assign from empty string_view" )
{
    string_view sv1;
    string_view sv2;

    sv2 = sv1;

    // use parenthesis with data() to prevent lest from using sv.data() as C-string:

    EXPECT(  sv2.size() == size_type( 0 ) );
    EXPECT( (sv2.data() == nssv_nullptr) );
}

CASE( "string_view: Allows to copy-assign from non-empty string_view" )
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

// 24.4.2.2 Iterator support:

CASE( "string_view: Allows forward iteration" )
{
    char hello[] = "hello";
    string_view sv( hello );

    for ( string_view::iterator pos = sv.begin(); pos != sv.end(); ++pos )
    {
        typedef std::iterator_traits< string_view::iterator >::difference_type difference_type;

        difference_type i = std::distance( sv.begin(), pos );
        EXPECT( *pos == *(sv.data() + i) );
    }
}

CASE( "string_view: Allows const forward iteration" )
{
    char hello[] = "hello";
    string_view sv( hello );

    for ( string_view::const_iterator pos = sv.begin(); pos != sv.end(); ++pos )
    {
        typedef std::iterator_traits< string_view::const_iterator >::difference_type difference_type;

        difference_type i = std::distance( sv.cbegin(), pos );
        EXPECT( *pos == *(sv.data() + i) );
    }
}

CASE( "string_view: Allows reverse iteration" )
{
    char hello[] = "hello";
    string_view sv( hello );

    for ( string_view::reverse_iterator pos = sv.rbegin(); pos != sv.rend(); ++pos )
    {
        typedef std::iterator_traits< string_view::reverse_iterator >::difference_type difference_type;

        difference_type dist = std::distance( sv.rbegin(), pos );
        EXPECT( *pos == *(sv.data() + sv.size() - 1 - dist) );
    }
}

CASE( "string_view: Allows const reverse iteration" )
{
    char hello[] = "hello";
    string_view sv( hello );

    for ( string_view::const_reverse_iterator pos = sv.crbegin(); pos != sv.crend(); ++pos )
    {
        typedef std::iterator_traits< string_view::const_reverse_iterator >::difference_type difference_type;

        difference_type  dist = std::distance( sv.crbegin(), pos );
        EXPECT( *pos == *(sv.data() + sv.size() - 1 - dist) );
    }
}

// 24.4.2.3 Capacity:

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
    // "large"
    EXPECT( string_view().max_size() >= (std::numeric_limits< string_view::size_type >::max)() / 10 );
}

CASE( "string_view: Allows to check for an empty string_view via empty()" )
{
    string_view sve;
    string_view svne("hello");

    EXPECT(      sve.size() == size_type( 0 ) );
    EXPECT(      sve.empty() );
    EXPECT_NOT( svne.empty() );
}

// 24.4.2.4 Element access:

CASE( "string_view: Allows to observe an element via array indexing" )
{
    // Requires: index < sv.size()

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

CASE( "string_view: Throws at observing an element via at() with an index of size() or larger" )
{
    string_view sv("hello");

    EXPECT_THROWS(   sv.at( sv.size()     ) );
    EXPECT_NO_THROW( sv.at( sv.size() - 1 ) );
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

CASE( "string_view: Yields nullptr (or NULL) with data() for an empty string_view" )
{
    string_view sv;

    // use parenthesis with data() to prevent lest from using sv.data() as C-string:

    EXPECT( (sv.data() == nssv_nullptr) );
}

// 24.4.2.5 Modifiers:

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

// 24.4.2.6 String operations:

CASE( "string_view: Allows to copy a substring of length n, starting at position pos (default: 0) via copy()" )
{
    char hello[]  = "hello world";
    string_view sv( hello );

    {
        std::vector<string_view::value_type> vec( sv.size() );

        sv.copy( data(vec), vec.size() );

        EXPECT( std::equal( vec.begin(), vec.end(), hello )  );
    }{
        std::size_t offset = 3u; std::size_t length = 4u;
        std::vector<string_view::value_type> vec( length );

        sv.copy( data(vec), length, offset );

        EXPECT( std::equal( vec.begin(), vec.end(), hello + offset )  );
    }
}

CASE( "string_view: Throws if requested position of copy() exceeds string_view's size()" )
{
    string_view sv("hello world");
    std::vector<string_view::value_type> vec( sv.size() );

    EXPECT_THROWS(   sv.copy( data(vec), sv.size() - 4, sv.size() + 1 ) );
    EXPECT_NO_THROW( sv.copy( data(vec), sv.size() - 4, sv.size() + 0 ) );
}

CASE( "string_view: Allow to obtain a sub string, starting at position pos (default: 0) and of length n (default full), via substr()" )
{
    char hello[] = "hello world";
    string_view sv( hello );

    {
#if nssv_USES_STD_STRING_VIEW && defined(__GNUC__)
        EXPECT( !!"std::string_view::substr(), with default pos, count is not available with GNU C" );
#else
        EXPECT( std::equal( sv.begin(), sv.end(), sv.substr().begin() ) );
#endif
    }{
        string_view subv = sv.substr( 6 );

        EXPECT( std::equal( subv.begin(), subv.end(), hello + 6 ) );
    }{
        string_view subv = sv.substr( 3, 4 );

        EXPECT( std::equal( subv.begin(), subv.end(), hello + 3 ) );
    }
}

CASE( "string_view: Throws if requested position of substr() exceeds string_view's size()" )
{
    string_view sv("hello world");

    EXPECT_THROWS(   sv.substr( sv.size() + 1 ) );
    EXPECT_NO_THROW( sv.substr( sv.size() + 0 ) );
}

CASE( "string_view: Allows to lexically compare to another string_view via compare(), (1)" )
{
    char hello[] = "hello";
    char world[] = "world";

    EXPECT( string_view( hello ).compare( string_view( hello ) ) == 0 );
    EXPECT( string_view( hello ).compare( string_view( world ) ) <  0 );
    EXPECT( string_view( world ).compare( string_view( hello ) ) >  0 );

    char hello_sp[] = "hello ";

    EXPECT( string_view( hello    ).compare( string_view( hello_sp ) ) < 0 );
    EXPECT( string_view( hello_sp ).compare( string_view( hello    ) ) > 0 );
}

CASE( "string_view: Allows to compare empty string_views as equal via compare(), (1)" )
{
    EXPECT( string_view().compare( string_view() ) == 0 );
}

CASE( "string_view: Allows to compare a sub string to another string_view via compare(), (2)" )
{
    string_view sv1("hello world");
    string_view sv2("world");

    EXPECT( sv1.compare ( 0, sv1.length(), sv1 ) == 0 );
    EXPECT( sv1.compare ( 6, 5, sv2 ) == 0 );
    EXPECT( sv1.compare ( 0, 5, sv2 ) <  0 );
    EXPECT( sv2.compare ( 0, 5, sv1 ) >  0 );
}

CASE( "string_view: Allows to compare a sub string to another string_view sub string via compare(), (3)" )
{
    string_view sv1("hello world");

    EXPECT( sv1.compare ( 0, sv1.length(), sv1 ) == 0 );
    EXPECT( sv1.compare ( 6, 5, sv1, 6, 5 ) ==  0 );
    EXPECT( sv1.compare ( 0, 5, sv1, 6, 5 )  <  0 );
    EXPECT( sv1.compare ( 6, 5, sv1, 0, 5 )  >  0 );
}

CASE( "string_view: Allows to compare to a C-string via compare(), (4)" )
{
    char hello[] = "hello";
    char world[] = "world";

    EXPECT( string_view( hello ).compare( hello ) == 0 );
    EXPECT( string_view( hello ).compare( world ) <  0 );
    EXPECT( string_view( world ).compare( hello ) >  0 );
}

CASE( "string_view: Allows to compare a sub string to a C-string via compare(), (5)" )
{
    char hello[] = "hello world";
    char world[] = "world";

    EXPECT( string_view( hello ).compare( 6, 5, world ) == 0 );
    EXPECT( string_view( hello ).compare( world ) <  0 );
    EXPECT( string_view( world ).compare( hello ) >  0 );
}

CASE( "string_view: Allows to compare a sub string to a C-string prefix via compare(), (6)" )
{
    char hello[] = "hello world";
    char world[] = "world";

    EXPECT( string_view( hello ).compare( 6, 5, world, 5 ) == 0 );
    EXPECT( string_view( hello ).compare( 0, 5, world, 5 ) <  0 );
    EXPECT( string_view( hello ).compare( 6, 5, hello, 5 ) >  0 );
}

// 24.4.2.7 Searching:

#if nssv_HAVE_STARTS_WITH

CASE( "string_view: Allows to check for a prefix string_view via starts_with(), (1)" )
{
    char hello[] = "hello world";

    EXPECT(     string_view( hello ).starts_with( string_view( hello ) ) );
    EXPECT(     string_view( hello ).starts_with( string_view("hello") ) );
    EXPECT_NOT( string_view( hello ).starts_with( string_view("world") ) );
}

CASE( "string_view: Allows to check for a prefix character via starts_with(), (2)" )
{
    char hello[] = "hello world";

    EXPECT(     string_view( hello ).starts_with( 'h' ) );
    EXPECT_NOT( string_view( hello ).starts_with( 'e' ) );
}

CASE( "string_view: Allows to check for a prefix C-string via starts_with(), (3)" )
{
    char hello[] = "hello world";

    EXPECT(     string_view( hello ).starts_with( hello ) );
    EXPECT(     string_view( hello ).starts_with("hello") );
    EXPECT_NOT( string_view( hello ).starts_with("world") );
}

#endif // nssv_HAVE_STARTS_WITH

#if nssv_HAVE_ENDS_WITH

CASE( "string_view: Allows to check for a suffix string_view via ends_with(), (1)" )
{
    char hello[] = "hello world";

    EXPECT(     string_view( hello ).ends_with( string_view( hello ) ) );
    EXPECT(     string_view( hello ).ends_with( string_view("world") ) );
    EXPECT_NOT( string_view( hello ).ends_with( string_view("hello") ) );
}

CASE( "string_view: Allows to check for a suffix character via ends_with(), (2)" )
{
    char hello[] = "hello world";

    EXPECT(     string_view( hello ).ends_with( 'd' ) );
    EXPECT_NOT( string_view( hello ).ends_with( 'l' ) );
}

CASE( "string_view: Allows to check for a suffix C-string via ends_with(), (3)" )
{
    char hello[] = "hello world";

    EXPECT(     string_view( hello ).ends_with( hello ) );
    EXPECT(     string_view( hello ).ends_with("world") );
    EXPECT_NOT( string_view( hello ).ends_with("hello") );
}

#endif // nssv_HAVE_ENDS_WITH

CASE( "string_view: Allows to search for a string_view substring, starting at position pos (default: 0) via find(), (1)" )
{
    char hello[] = "hello world";
    string_view sv( hello );

    EXPECT( sv.find( sv    ) == size_type( 0 ) );
    EXPECT( sv.find( sv, 1 ) == string_view::npos );
    EXPECT( sv.find( string_view("world" )    ) == size_type( 6 ) );
    EXPECT( sv.find( string_view("world" ), 6 ) == size_type( 6 ) );
    EXPECT( sv.find( string_view("world" ), 7 ) == string_view::npos );
}

CASE( "string_view: Allows to search for a character, starting at position pos (default: 0) via find(), (2)" )
{
    char hello[] = "hello world";
    string_view sv( hello );

    EXPECT( sv.find('h'    ) == size_type( 0 )    );
    EXPECT( sv.find('h', 1 ) == string_view::npos );
    EXPECT( sv.find('w'    ) == size_type( 6 )    );
    EXPECT( sv.find('w', 6 ) == size_type( 6 )    );
    EXPECT( sv.find('w', 7 ) == string_view::npos );
}

CASE( "string_view: Allows to search for a C-string substring, starting at position pos and of length n via find(), (3)" )
{
    char hello[] = "hello world";
    string_view sv( hello );

    EXPECT( sv.find( hello , 0, sv.size() ) == size_type( 0 )    );
    EXPECT( sv.find( hello , 1, sv.size() ) == string_view::npos );
    EXPECT( sv.find("world", 0, 5 ) == size_type( 6 )    );
    EXPECT( sv.find("world", 6, 5 ) == size_type( 6 )    );
    EXPECT( sv.find("world", 7, 4 ) == string_view::npos );
    EXPECT( sv.find("world", 3, 0 ) == size_type( 3 )    );
}

CASE( "string_view: Allows to search for a C-string substring, starting at position pos (default: 0) via find(), (4)" )
{
    char hello[] = "hello world";
    string_view sv( hello );

    EXPECT( sv.find( hello     ) == size_type( 0 )    );
    EXPECT( sv.find( hello , 1 ) == string_view::npos );
    EXPECT( sv.find("world"    ) == size_type( 6 )    );
    EXPECT( sv.find("world", 6 ) == size_type( 6 )    );
    EXPECT( sv.find("world", 7 ) == string_view::npos );
}

CASE( "string_view: Allows to search backwards for a string_view substring, starting at position pos (default: npos) via rfind(), (1)" )
{
    char hello[] = "hello world";
    string_view sv( hello );

    EXPECT( sv.rfind( sv    ) == size_type( 0 ) );
    EXPECT( sv.rfind( sv, 3 ) == size_type( 0 ) );
    EXPECT( sv.rfind( string_view(        )    ) == size_type(11 ) );
    EXPECT( sv.rfind( string_view("world" )    ) == size_type( 6 ) );
    EXPECT( sv.rfind( string_view("world" ), 6 ) == size_type( 6 ) );
    EXPECT( sv.rfind( string_view("world" ), 5 ) == string_view::npos );
    EXPECT( sv.rfind( string_view("hello world, a longer text" ) ) == string_view::npos );
}

CASE( "string_view: Allows to search backwards for a character, starting at position pos (default: npos) via rfind(), (2)" )
{
    char hello[] = "hello world";
    string_view sv( hello );

    EXPECT( sv.rfind('h'    ) == size_type( 0 )    );
    EXPECT( sv.rfind('e'    ) == size_type( 1 )    );
    EXPECT( sv.rfind('e', 0 ) == string_view::npos );
    EXPECT( sv.rfind('w'    ) == size_type( 6 )    );
    EXPECT( sv.rfind('w', 6 ) == size_type( 6 )    );
    EXPECT( sv.rfind('w', 5 ) == string_view::npos );
}

CASE( "string_view: Allows to search backwards for a C-string substring, starting at position pos and of length n via rfind(), (3)" )
{
    char hello[] = "hello world";
    string_view sv( hello );

    EXPECT( sv.rfind( hello         ) == size_type( 0 ) );
    EXPECT( sv.rfind( hello ,  0, 5 ) == size_type( 0 ) );
    EXPECT( sv.rfind( hello ,  1, 5 ) == size_type( 0 ) );
    EXPECT( sv.rfind("world", 10, 5 ) == size_type( 6 ) );
    EXPECT( sv.rfind("world",  6, 5 ) == size_type( 6 ) );
    EXPECT( sv.rfind("world",  5, 5 ) == string_view::npos );
}

CASE( "string_view: Allows to search backwards for a C-string substring, starting at position pos (default: 0) via rfind(), (4)" )
{
    char hello[] = "hello world";
    string_view sv( hello );

    EXPECT( sv.rfind( hello     ) == size_type( 0 ) );
    EXPECT( sv.rfind( hello , 3 ) == size_type( 0 ) );
    EXPECT( sv.rfind("world"    ) == size_type( 6 ) );
    EXPECT( sv.rfind("world", 6 ) == size_type( 6 ) );
    EXPECT( sv.rfind("world", 5 ) == string_view::npos );
}

CASE( "string_view: Allows to search for the first occurrence of any of the characters specified in a string view, starting at position pos (default: 0) via find_first_of(), (1)" )
{
    char hello[] = "hello world";
    string_view sv( hello );

    EXPECT( sv.find_first_of( sv    ) == size_type( 0 ) );
    EXPECT( sv.find_first_of( sv, 3 ) == size_type( 3 ) );
    EXPECT( sv.find_first_of( string_view("xwo" )    ) == size_type( 4 ) );
    EXPECT( sv.find_first_of( string_view("wdx" ), 6 ) == size_type( 6 ) );
    EXPECT( sv.find_first_of( string_view("wxy" ), 7 ) == string_view::npos );
}

CASE( "string_view: Allows to search for a character, starting at position pos (default: 0) via find_first_of(), (2)" )
{
    char hello[] = "hello world";
    string_view sv( hello );

    EXPECT( sv.find_first_of('h'    ) == size_type( 0 )    );
    EXPECT( sv.find_first_of('h', 1 ) == string_view::npos );
    EXPECT( sv.find_first_of('w'    ) == size_type( 6 )    );
    EXPECT( sv.find_first_of('w', 6 ) == size_type( 6 )    );
    EXPECT( sv.find_first_of('w', 7 ) == string_view::npos );
}

CASE( "string_view: Allows to search for the first occurrence of any of the characters specified in a C-string, starting at position pos and of length n via find_first_of(), (3)" )
{
    char hello[] = "hello world";
    string_view sv( hello );

    EXPECT( sv.find_first_of( hello , 0, sv.size() ) == size_type( 0 ) );
    EXPECT( sv.find_first_of( hello , 1, sv.size() ) == size_type( 1 ) );
    EXPECT( sv.find_first_of(  "xwy", 0, 3 ) == size_type( 6 )    );
    EXPECT( sv.find_first_of(  "xwy", 6, 3 ) == size_type( 6 )    );
    EXPECT( sv.find_first_of(  "xwy", 7, 3 ) == string_view::npos );
    EXPECT( sv.find_first_of(  "xyw", 0, 2 ) == string_view::npos );
}

CASE( "string_view: Allows to search for the first occurrence of any of the characters specified in a C-string, starting at position pos via find_first_of(), (4)" )
{
    char hello[] = "hello world";
    string_view sv( hello );

    EXPECT( sv.find_first_of( hello , 0 ) == size_type( 0 )    );
    EXPECT( sv.find_first_of( hello , 1 ) == size_type( 1 )    );
    EXPECT( sv.find_first_of(  "xwy", 0 ) == size_type( 6 )    );
    EXPECT( sv.find_first_of(  "xwy", 6 ) == size_type( 6 )    );
    EXPECT( sv.find_first_of(  "xwy", 7 ) == string_view::npos );
}

CASE( "string_view: Allows to search backwards for the last occurrence of any of the characters specified in a string view, starting at position pos (default: npos) via find_last_of(), (1)" )
{
    char hello[] = "hello world";
    char empty[] = "";
    string_view sv( hello );
    string_view sve( empty );

    EXPECT( sv.find_last_of( sv    ) == size_type( 10 ) );
    EXPECT( sv.find_last_of( sv, 3 ) == size_type(  3 ) );
    EXPECT( sv.find_last_of( string_view("xwo" )    ) == size_type( 7 ) );
    EXPECT( sv.find_last_of( string_view("wdx" ), 6 ) == size_type( 6 ) );
    EXPECT( sv.find_last_of( string_view("wxy" ), 7 ) == size_type( 6 ) );

    EXPECT( sve.find_last_of( string_view("x") ) == string_view::npos );    // issue 20 (endless loop)
}

CASE( "string_view: Allows to search backwards for a character, starting at position pos (default: 0) via find_last_of(), (2)" )
{
    char hello[] = "hello world";
    string_view sv( hello );

    EXPECT( sv.find_last_of('h'    ) == size_type( 0 )    );
    EXPECT( sv.find_last_of('l', 1 ) == string_view::npos );
    EXPECT( sv.find_last_of('w'    ) == size_type( 6 )    );
    EXPECT( sv.find_last_of('w', 6 ) == size_type( 6 )    );
    EXPECT( sv.find_last_of('w', 5 ) == string_view::npos );
}

CASE( "string_view: Allows to search backwards for the first occurrence of any of the characters specified in a C-string, starting at position pos and of length n via find_last_of(), (3)" )
{
    char hello[] = "hello world";
    string_view sv( hello );

    EXPECT( sv.find_last_of( hello , 0, sv.size() ) == size_type( 0 ) );
    EXPECT( sv.find_last_of( hello , 1, sv.size() ) == size_type( 1 ) );
    EXPECT( sv.find_last_of("xwy", 10, 3 ) == size_type( 6 )    );
    EXPECT( sv.find_last_of("xwy",  6, 3 ) == size_type( 6 )    );
    EXPECT( sv.find_last_of("xwy",  5, 3 ) == string_view::npos );
    EXPECT( sv.find_last_of("xyw", 10, 2 ) == string_view::npos );
}

CASE( "string_view: Allows to search backwards for the first occurrence of any of the characters specified in a C-string, starting at position pos via find_last_of(), (4)" )
{
    char hello[] = "hello world";
    string_view sv( hello );

    EXPECT( sv.find_last_of( hello ,  0 ) == size_type( 0 )    );
    EXPECT( sv.find_last_of( hello ,  1 ) == size_type( 1 )    );
    EXPECT( sv.find_last_of(  "xwy", 10 ) == size_type( 6 )    );
    EXPECT( sv.find_last_of(  "xwy",  6 ) == size_type( 6 )    );
    EXPECT( sv.find_last_of(  "xwy",  5 ) == string_view::npos );
}

CASE( "string_view: Allows to search for the first character not specified in a string view, starting at position pos (default: 0) via find_first_not_of(), (1)" )
{
    char hello[] = "hello world";
    string_view sv( hello );

    EXPECT( sv.find_first_not_of( sv    ) == string_view::npos );
    EXPECT( sv.find_first_not_of( sv, 3 ) == string_view::npos );
    EXPECT( sv.find_first_not_of( string_view("helo "   )    ) == size_type(  6 ) );
    EXPECT( sv.find_first_not_of( string_view("helo "   ), 6 ) == size_type(  6 ) );
    EXPECT( sv.find_first_not_of( string_view("helo "   ), 7 ) == size_type(  8 ) );
    EXPECT( sv.find_first_not_of( string_view("helo wr" )    ) == size_type( 10 ) );
}

CASE( "string_view: Allows to search for the first character not equal to the specified character, starting at position pos (default: 0) via find_first_not_of(), (2)" )
{
    char hello[] = "hello world";
    string_view sv( hello );

    EXPECT( sv.find_first_not_of('h'     ) == size_type( 1 )    );
    EXPECT( sv.find_first_not_of('h',  1 ) == size_type( 1 )    );
    EXPECT( sv.find_first_not_of('w'     ) == size_type( 0 )    );
    EXPECT( sv.find_first_not_of('w',  6 ) == size_type( 7 )    );
    EXPECT( sv.find_first_not_of('d', 10 ) == string_view::npos );
}

CASE( "string_view: Allows to search for  the first character not equal to any of the characters specified in a C-string, starting at position pos and of length n via find_first_not_of(), (3)" )
{
    char hello[] = "hello world";
    string_view sv( hello );

    EXPECT( sv.find_first_not_of( hello, 0, sv.size() ) == string_view::npos );
    EXPECT( sv.find_first_not_of( hello, 3, sv.size() ) == string_view::npos );
    EXPECT( sv.find_first_not_of( "helo "  , 0, 5     ) == size_type(  6 ) );
    EXPECT( sv.find_first_not_of( "helo "  , 6, 5     ) == size_type(  6 ) );
    EXPECT( sv.find_first_not_of( "helo "  , 7, 5     ) == size_type(  8 ) );
    EXPECT( sv.find_first_not_of( "helo wr", 0, 7     ) == size_type( 10 ) );
    EXPECT( sv.find_first_not_of( "he"     , 0, 1     ) == size_type(  1 ) );
}

CASE( "string_view: Allows to search for  the first character not equal to any of the characters specified in a C-string, starting at position pos via find_first_not_of(), (4)" )
{
    char hello[] = "hello world";
    string_view sv( hello );

    EXPECT( sv.find_first_not_of( hello    , 0 ) == string_view::npos );
    EXPECT( sv.find_first_not_of( hello    , 3 ) == string_view::npos );
    EXPECT( sv.find_first_not_of( "helo "  , 0 ) == size_type(  6 ) );
    EXPECT( sv.find_first_not_of( "helo "  , 6 ) == size_type(  6 ) );
    EXPECT( sv.find_first_not_of( "helo "  , 7 ) == size_type(  8 ) );
    EXPECT( sv.find_first_not_of( "helo wr", 0 ) == size_type( 10 ) );
}

CASE( "string_view: Allows to search backwards for the first character not specified in a string view, starting at position pos (default: npos) via find_last_not_of(), (1)" )
{
    char hello[] = "hello world";
    char empty[] = "";
    string_view sv( hello );
    string_view sve( empty );

    EXPECT( sv.find_last_not_of( sv    ) == string_view::npos );
    EXPECT( sv.find_last_not_of( sv, 3 ) == string_view::npos );
    EXPECT( sv.find_last_not_of( string_view("world " )    ) == size_type(  1 ) );
    EXPECT( sv.find_last_not_of( string_view("heo "   ), 4 ) == size_type(  3 ) );
    EXPECT( sv.find_last_not_of( string_view("heo "   ), 3 ) == size_type(  3 ) );
    EXPECT( sv.find_last_not_of( string_view("heo "   ), 2 ) == size_type(  2 ) );
    EXPECT( sv.find_last_not_of( string_view("x"      )    ) == size_type( 10 ) );

    EXPECT( sve.find_last_not_of( string_view("x") ) == string_view::npos );    // issue 20 (endless loop)
}

CASE( "string_view: Allows to search backwards for the first character not equal to the specified character, starting at position pos (default: npos) via find_last_not_of(), (2)" )
{
    char hello[] = "hello world";
    string_view sv( hello );

    EXPECT( sv.find_last_not_of('d'     ) == size_type( 9 ) );
    EXPECT( sv.find_last_not_of('d', 10 ) == size_type( 9 ) );
    EXPECT( sv.find_last_not_of('d',  9 ) == size_type( 9 ) );
    EXPECT( sv.find_last_not_of('d',  8 ) == size_type( 8 ) );
    EXPECT( sv.find_last_not_of('d',  0 ) == size_type( 0 ) );
}

CASE( "string_view: Allows to search backwards for  the first character not equal to any of the characters specified in a C-string, starting at position pos and of length n via find_last_not_of(), (3)" )
{
    char hello[] = "hello world";
    string_view sv( hello );

    EXPECT( sv.find_last_not_of( hello, 0, sv.size() ) == string_view::npos );
    EXPECT( sv.find_last_not_of( hello, 3, sv.size() ) == string_view::npos );
    EXPECT( sv.find_last_not_of( "world ", 10, 6 ) == size_type(  1 ) );
    EXPECT( sv.find_last_not_of( "heo "  ,  4, 4 ) == size_type(  3 ) );
    EXPECT( sv.find_last_not_of( "heo "  ,  3, 4 ) == size_type(  3 ) );
    EXPECT( sv.find_last_not_of( "heo "  ,  2, 4 ) == size_type(  2 ) );
    EXPECT( sv.find_last_not_of( "x"             ) == size_type( 10 ) );
}

CASE( "string_view: Allows to search backwards for  the first character not equal to any of the characters specified in a C-string, starting at position pos via find_last_not_of(), (4)" )
{
    char hello[] = "hello world";
    string_view sv( hello );

    EXPECT( sv.find_last_not_of( hello    , 0 ) == string_view::npos );
    EXPECT( sv.find_last_not_of( hello    , 3 ) == string_view::npos );
    EXPECT( sv.find_last_not_of( "world ", 10 ) == size_type(  1 ) );
    EXPECT( sv.find_last_not_of( "heo "  ,  4 ) == size_type(  3 ) );
    EXPECT( sv.find_last_not_of( "heo "  ,  3 ) == size_type(  3 ) );
    EXPECT( sv.find_last_not_of( "heo "  ,  2 ) == size_type(  2 ) );
    EXPECT( sv.find_last_not_of( "x"          ) == size_type( 10 ) );
}

CASE( "string_view: Allows to create a string_view, wstring_view, u16string_view, u32string_view via literal \"sv\"" )
{
#if nssv_CONFIG_STD_SV_OPERATOR
#if nssv_STD_SV_OR( nssv_HAVE_STD_DEFINED_LITERALS )
    using namespace nonstd::literals::string_view_literals;

    string_view sv1 =  "abc"sv;
    wstring_view sv2 = L"abc"sv;

    EXPECT( sv1.size() == size_type( 3 ) );
    EXPECT( sv2.size() == size_type( 3 ) );

#if nssv_HAVE_WCHAR16_T
    u16string_view sv3 = u"abc"sv;
    EXPECT( sv3.size() == size_type( 3 ) );
#endif
#if nssv_HAVE_WCHAR32_T
    u32string_view sv4 = U"abc"sv;
    EXPECT( sv4.size() == size_type( 3 ) );
#endif
#else
    EXPECT( !!"Literal operator 'sv' for string_view not available (no C++11)." );
#endif
#else
    EXPECT( !!"Literal operator 'sv' for string_view not available (nssv_CONFIG_STD_SV_OPERATOR=0)." );
#endif
}

CASE( "string_view: Allows to create a string_view via literal \"sv\", using namespace nonstd::literals::string_view_literals" )
{
#if nssv_CONFIG_STD_SV_OPERATOR
#if nssv_STD_SV_OR( nssv_HAVE_STD_DEFINED_LITERALS )
    using namespace nonstd::literals::string_view_literals;

    string_view sv1 = "abc\0\0def";
    string_view sv2 = "abc\0\0def"sv;

    EXPECT( sv1.size() == size_type( 3 ) );
    EXPECT( sv2.size() == size_type( 8 ) );
#else
    EXPECT( !!"Literal operator 'sv' for string_view not available (no C++11)." );
#endif
#else
    EXPECT( !!"Literal operator 'sv' for string_view not available (nssv_CONFIG_STD_SV_OPERATOR=0)." );
#endif
}

CASE( "string_view: Allows to create a string_view via literal \"sv\", using namespace nonstd::string_view_literals" )
{
#if nssv_CONFIG_STD_SV_OPERATOR
#if nssv_STD_SV_OR( nssv_HAVE_STD_DEFINED_LITERALS )
#if nssv_STD_SV_OR( nssv_HAVE_INLINE_NAMESPACE )
    using namespace nonstd::string_view_literals;

    string_view sv1 = "abc\0\0def";
    string_view sv2 = "abc\0\0def"sv;

    EXPECT( sv1.size() == size_type( 3 ) );
    EXPECT( sv2.size() == size_type( 8 ) );
#else
    EXPECT( !!"Inline namespaces for literal operator 'sv' for string_view not available (no C++11)." );
#endif
#else
    EXPECT( !!"Literal operator 'sv' for string_view not available (no C++11)." );
#endif
#else
    EXPECT( !!"Literal operator 'sv' for string_view not available (nssv_CONFIG_STD_SV_OPERATOR=0)." );
#endif
}

CASE( "string_view: Allows to create a string_view via literal \"sv\", using namespace nonstd::literals" )
{
#if nssv_CONFIG_STD_SV_OPERATOR
#if nssv_STD_SV_OR( nssv_HAVE_STD_DEFINED_LITERALS )
#if nssv_STD_SV_OR( nssv_HAVE_INLINE_NAMESPACE )
    using namespace nonstd::literals;

    string_view sv1 = "abc\0\0def";
    string_view sv2 = "abc\0\0def"sv;

    EXPECT( sv1.size() == size_type( 3 ) );
    EXPECT( sv2.size() == size_type( 8 ) );
#else
    EXPECT( !!"Inline namespaces for literal operator 'sv' for string_view not available (no C++11)." );
#endif
#else
    EXPECT( !!"Literal operator 'sv' for string_view not available (no C++11)." );
#endif
#else
    EXPECT( !!"Literal operator 'sv' for string_view not available (nssv_CONFIG_STD_SV_OPERATOR=0)." );
#endif
}

CASE( "string_view: Allows to create a string_view, wstring_view, u16string_view, u32string_view via literal \"_sv\"" )
{
#if nssv_CONFIG_USR_SV_OPERATOR
#if nssv_STD_SV_OR( nssv_HAVE_USER_DEFINED_LITERALS )
    using namespace nonstd::literals::string_view_literals;

    string_view sv1 =  "abc"_sv;
    wstring_view sv2 = L"abc"_sv;

    EXPECT( sv1.size() == size_type( 3 ) );
    EXPECT( sv2.size() == size_type( 3 ) );

#if nssv_HAVE_WCHAR16_T
    u16string_view sv3 = u"abc"_sv;
    EXPECT( sv3.size() == size_type( 3 ) );
#endif
#if nssv_HAVE_WCHAR32_T
    u32string_view sv4 = U"abc"_sv;
    EXPECT( sv4.size() == size_type( 3 ) );
#endif
#else
    EXPECT( !!"Literal operator '_sv' for string_view not available (no C++11)." );
#endif
#else
    EXPECT( !!"Literal operator '_sv' for string_view not available (nssv_CONFIG_USR_SV_OPERATOR=0)." );
#endif
}

CASE( "string_view: Allows to create a string_view via literal \"_sv\", using namespace nonstd::literals::string_view_literals" )
{
#if nssv_CONFIG_USR_SV_OPERATOR
#if nssv_STD_SV_OR( nssv_HAVE_USER_DEFINED_LITERALS )
    using namespace nonstd::literals::string_view_literals;

    string_view sv1 = "abc\0\0def";
    string_view sv2 = "abc\0\0def"_sv;

    EXPECT( sv1.size() == size_type( 3 ) );
    EXPECT( sv2.size() == size_type( 8 ) );
#else
    EXPECT( !!"Literal operator '_sv' for string_view not available (no C++11)." );
#endif
#else
    EXPECT( !!"Literal operator '_sv' for string_view not available (nssv_CONFIG_USR_SV_OPERATOR=0)." );
#endif
}

CASE( "string_view: Allows to create a string_view via literal \"_sv\", using namespace nonstd::string_view_literals" )
{
#if nssv_CONFIG_USR_SV_OPERATOR
#if nssv_STD_SV_OR( nssv_HAVE_USER_DEFINED_LITERALS )
#if nssv_STD_SV_OR( nssv_HAVE_INLINE_NAMESPACE )
    using namespace nonstd::string_view_literals;

    string_view sv1 = "abc\0\0def";
    string_view sv2 = "abc\0\0def"_sv;

    EXPECT( sv1.size() == size_type( 3 ) );
    EXPECT( sv2.size() == size_type( 8 ) );
#else
    EXPECT( !!"Inline namespaces for literal operator '_sv' for string_view not available (no C++11)." );
#endif
#else
    EXPECT( !!"Literal operator '_sv' for string_view not available (no C++11)." );
#endif
#else
    EXPECT( !!"Literal operator '_sv' for string_view not available (nssv_CONFIG_USR_SV_OPERATOR=0)." );
#endif
}

CASE( "string_view: Allows to create a string_view via literal \"_sv\", using namespace nonstd::literals" )
{
#if nssv_CONFIG_USR_SV_OPERATOR
#if nssv_STD_SV_OR( nssv_HAVE_USER_DEFINED_LITERALS )
#if nssv_STD_SV_OR( nssv_HAVE_INLINE_NAMESPACE )
    using namespace nonstd::literals;

    string_view sv1 = "abc\0\0def";
    string_view sv2 = "abc\0\0def"_sv;

    EXPECT( sv1.size() == size_type( 3 ) );
    EXPECT( sv2.size() == size_type( 8 ) );
#else
    EXPECT( !!"Inline namespaces for literal operator '_sv' for string_view not available (no C++11)." );
#endif
#else
    EXPECT( !!"Literal operator '_sv' for string_view not available (no C++11)." );
#endif
#else
    EXPECT( !!"Literal operator '_sv' for string_view not available (nssv_CONFIG_USR_SV_OPERATOR=0)." );
#endif
}

// 24.4.3 Non-member comparison functions:

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

CASE( "string_view: Allows to compare a string_view with an object with implicit conversion to string_view" )
{
#if nssv_CPP11_OR_GREATER
#if _MSC_VER != 1900
    char s[] = "hello";
    string_view sv( s );

    EXPECT( sv == "hello"       );
    EXPECT(       "hello" == sv );

    EXPECT( sv != "world"       );
    EXPECT(       "world" != sv );

    EXPECT( sv <= "hello"       );
    EXPECT(       "hello" <= sv );
    EXPECT( sv <= "world"       );
    EXPECT(       "aloha" <= sv );

    EXPECT( sv <  "world"       );
    EXPECT(       "aloha" <  sv );

    EXPECT( sv >= "hello"       );
    EXPECT(       "hello" >= sv );
    EXPECT( sv >= "aloha"       );
    EXPECT(       "world" >= sv );

    EXPECT( sv >  "aloha"       );
    EXPECT(       "world"  >  sv );
#else
    EXPECT( !!"Comparison for types with implicit conversion to string_view not available (insufficient C++11 support of MSVC)." );
#endif
#else
    EXPECT( !!"Comparison for types with implicit conversion to string_view not available (no C++11)." );
#endif
}

CASE( "string_view: Allows to compare empty string_view-s as equal" )
{
    string_view a, b;

    EXPECT( a == b );
}

// 24.4.4 Inserters and extractors:

CASE ( "operator<<: Allows printing a string_view to an output stream" )
{
    std::ostringstream oss;
    char s[] = "hello";
    string_view sv( s );

    oss << sv << '\n'
        << std::right << std::setw(10) << sv << '\n'
        << sv << '\n'
        << std::setfill('.') << std::left << std::setw(10) << sv;

    EXPECT( oss.str() == "hello\n     hello\nhello\nhello....." );
}

// 24.4.5 Hash support (C++11):

CASE ( "std::hash<>: Hash value of string_view equals hash value of corresponding string object" )
{
#if nssv_HAVE_STD_HASH
    EXPECT( std::hash<string_view>()( "Hello, world!" ) == std::hash<std::string>()( "Hello, world!" ) );
#else
    EXPECT( !!"std::hash is not available (no C++11)" );
#endif
}

CASE ( "std::hash<>: Hash value of wstring_view equals hash value of corresponding string object" )
{
#if nssv_HAVE_STD_HASH
    EXPECT( std::hash<wstring_view>()( L"Hello, world!" ) == std::hash<std::wstring>()( L"Hello, world!" ) );
#else
    EXPECT( !!"std::hash is not available (no C++11)" );
#endif
}

CASE ( "std::hash<>: Hash value of u16string_view equals hash value of corresponding string object" )
{
#if nssv_HAVE_STD_HASH
#if nssv_HAVE_WCHAR16_T
#if nssv_HAVE_UNICODE_LITERALS
    EXPECT( std::hash<u16string_view>()( u"Hello, world!" ) == std::hash<std::u16string>()( u"Hello, world!" ) );
#else
    EXPECT( !!"Unicode literal u\"...\" is not available (no C++11)" );
#endif
#else
    EXPECT( !!"std::u16string is not available (no C++11)" );
#endif
#else
    EXPECT( !!"std::hash is not available (no C++11)" );
#endif
}

CASE ( "std::hash<>: Hash value of u32string_view equals hash value of corresponding string object" )
{
#if nssv_HAVE_STD_HASH
#if nssv_HAVE_WCHAR16_T
#if nssv_HAVE_UNICODE_LITERALS
    EXPECT( std::hash<u32string_view>()( U"Hello, world!" ) == std::hash<std::u32string>()( U"Hello, world!" ) );
#else
    EXPECT( !!"Unicode literal U\"...\" is not available (no C++11)" );
#endif
#else
    EXPECT( !!"std::u32string is not available (no C++11)" );
#endif
#else
    EXPECT( !!"std::hash is not available (no C++11)" );
#endif
}

// nonstd extension: conversions from and to std::basic_string

CASE( "string_view: construct from std::string " "[extension]" )
{
#if nssv_USES_STD_STRING_VIEW
    EXPECT( !!"Conversion to/from std::string is not available (nssv_USES_STD_STRING_VIEW=1)." );
#elif nssv_CONFIG_CONVERSION_STD_STRING_CLASS_METHODS
    char hello[]  = "hello world";
    std::string s =  hello;

    string_view sv( hello );

    EXPECT( sv.size() == s.size() );
    EXPECT( sv.compare( s ) == 0  );
#else
    EXPECT( !!"Conversion to/from std::string is not available (nssv_CONFIG_CONVERSION_STD_STRING_CLASS_METHODS=0)." );
#endif
}

CASE( "string_view: convert to std::string via explicit operator " "[extension]" )
{
#if nssv_USES_STD_STRING_VIEW
    EXPECT( !!"Conversion to/from std::string is not available (nssv_USES_STD_STRING_VIEW=1)." );
#elif nssv_CONFIG_CONVERSION_STD_STRING_CLASS_METHODS
#if nssv_HAVE_EXPLICIT_CONVERSION
    char hello[] = "hello world";
    string_view sv( hello );

    std::string s( sv );
//  std::string t{ sv };

    EXPECT( sv.size() == s.size() );
    EXPECT( sv.compare( s ) == 0  );
#else
    EXPECT( !!"explicit conversion is not available (no C++11)." );
#endif
#else
    EXPECT( !!"Conversion to/from std::string is not available (nssv_CONFIG_CONVERSION_STD_STRING_CLASS_METHODS=0)." );
#endif
}

CASE( "string_view: convert to std::string via to_string() " "[extension]" )
{
#if nssv_USES_STD_STRING_VIEW
    EXPECT( !!"Conversion to/from std::string is not available (nssv_USES_STD_STRING_VIEW=1)." );
#elif nssv_CONFIG_CONVERSION_STD_STRING_CLASS_METHODS
    char hello[] = "hello world";
    string_view sv( hello );

    std::string s1 = sv.to_string();

    EXPECT( sv.size() == s1.size() );
    EXPECT( sv.compare( s1 ) == 0  );

    std::string s2 = sv.to_string( std::string::allocator_type() );

    EXPECT( sv.size() == s2.size() );
    EXPECT( sv.compare( s2 ) == 0  );
#else
    EXPECT( !!"Conversion to/from std::string is not available (nssv_CONFIG_CONVERSION_STD_STRING_CLASS_METHODS=0)." );
#endif
}

CASE( "to_string(): convert to std::string via to_string() " "[extension]" )
{
#if nssv_CONFIG_CONVERSION_STD_STRING_FREE_FUNCTIONS
    char hello[] = "hello world";
    string_view sv( hello );

    std::string s1 = to_string( sv );

    EXPECT( sv.size() == s1.size() );
    EXPECT( sv.compare( s1 ) == 0  );

    std::string s2 = to_string( sv, std::string::allocator_type() );

    EXPECT( sv.size() == s2.size() );
    EXPECT( sv.compare( s2 ) == 0  );

#else
    EXPECT( !!"Conversion to/from std::string is not available (nssv_CONFIG_CONVERSION_STD_STRING_FREE_FUNCTIONS=0)." );
#endif
}

CASE( "to_string_view(): convert from std::string via to_string_view() " "[extension]" )
{
#if nssv_CONFIG_CONVERSION_STD_STRING_FREE_FUNCTIONS
    char hello[] = "hello world";
    std::string s = hello;

    string_view sv = to_string_view( s );

    EXPECT( sv.size() == s.size() );
    EXPECT( sv.compare( s ) == 0  );
#else
    EXPECT( !!"Conversion to/from std::string is not available (nssv_CONFIG_CONVERSION_STD_STRING_FREE_FUNCTIONS=0)." );
#endif
}

} // anonymous namespace
