#include "string_view.hpp"
#include <iostream>

using namespace nonstd;
using namespace nonstd::literals;
using namespace std::literals;
    
void write( string_view sv )
{
    std::cout << sv;
}

int main()
{
    write( "hello"    );
    write( ", "s      );
    write( "world!"sv );
}

// g++ -Wall -std=c++14 -I../include/nonstd/ -o 01-basic.exe 01-basic.cpp && 01-basic.exe
