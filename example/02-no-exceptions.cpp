#include "nonstd/string_view.hpp"

using namespace nonstd;

int main()
{
    string_view svw( "Hello, world" );

    char c = svw.at( 12 );  // asserts (normally throws)
}

// cl -nologo -I../include 02-no-exceptions.cpp && 02-no-exceptions
// g++ -Wall -fno-exceptions -I../include -o 02-no-exceptions 02-no-exceptions.cpp && 02-no-exceptions
