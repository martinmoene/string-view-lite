#include "nonstd/string_view.hpp"
#include <iostream>

using namespace std::literals;
using namespace nonstd::literals;
using namespace nonstd;

void write( string_view sv )
{
    std::cout << sv;
}

int main()
{
    write( "hello"    );    // C-string
    write( ", "s      );    // std::string
    write( "world!"sv );    // nonstd::string_view
}

// g++ -Wall -std=c++14 -Dnssv_CONFIG_STD_SV_OPERATOR=1 -I../include -o 01-basic.exe 01-basic.cpp && 01-basic.exe
