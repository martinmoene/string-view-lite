@setlocal
@set std=%1
@if not "%std%"=="" set std=-std:%std%
set cppcorecheckinclude=%VCINSTALLDIR%/Auxiliary/VS/include
cl -W3 -EHsc %std% -Dnssv_CONFIG_SELECT_STD_STRING_VIEW=0 -Dnssv_CONFIG_SELECT_NONSTD_STRING_VIEW=1 -DNOMINMAX -Dnssv_STRING_VIEW_HEADER=\"string_view.hpp\" -I../include/nonstd -I"%cppcorecheckinclude%" string-view-lite.t.cpp string-view.t.cpp && string-view-lite.t.exe
@endlocal
