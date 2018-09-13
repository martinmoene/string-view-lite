@setlocal
@set std=%1
@if "%std%"=="" set std=c++11
g++ -std=%std% -O2 -Wall -Wextra -Wpedantic -Wconversion -Wsign-conversion -Wno-unused-parameter -Dnssv_CONFIG_STD_SV_OPERATOR=1 -Dnssv_CONFIG_USR_SV_OPERATOR=1 -Dnssv_STRING_VIEW_HEADER=\"string_view.hpp\" -I../include/nonstd -o string-view-lite.t.exe string-view-lite.t.cpp string-view.t.cpp && string-view-lite.t.exe
@endlocal

