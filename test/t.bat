@setlocal
@set std=%1
@if not "%std%"=="" set std=-std:%std%
cl -W3 -EHsc %std% -DNOMINMAX -Dnssv_STRING_VIEW_HEADER=\"../include/nonstd/string_view.hpp\" -I../include/nonstd string-view-lite.t.cpp string-view.t.cpp && string-view-lite.t.exe
@endlocal

