@setlocal
@set std=%1
@if "%std%"=="" set std=c++11
g++ -std=%std% -O2 -Wall -Wextra -Wno-unused-parameter -Dnssv_STRING_VIEW_HEADER=\"string_view.hpp\" -I../include/nonstd -o string-view-lite.t.exe string-view-lite.t.cpp string-view.t.cpp && string-view-lite.t.exe
@endlocal

