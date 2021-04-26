@setlocal
@set std=%1
@if not "%std%"=="" set std=-std:%std%
clang-cl -m32 -W3 -EHsc %std% -Dnssv_STRING_VIEW_HEADER=\"nonstd/string_view.hpp\" -Dnssv_CONFIG_SELECT_STRING_VIEW=nssv_STRING_VIEW_NONSTD -I../include -I. string-view-main.t.cpp string-view.t.cpp && string-view-main.t.exe
@endlocal
