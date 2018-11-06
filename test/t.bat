@setlocal
@set std=%1
@if not "%std%"=="" set std=-std:%std%
set cppcorecheckinclude=%VCINSTALLDIR%/Auxiliary/VS/include
cl -W3 -EHsc %std% -Dnssv_CONFIG_SELECT_STRING_VIEW=nssv_STRING_VIEW_NONSTD -Dnssv_CONFIG_STD_SV_OPERATOR=1 -Dnssv_CONFIG_USR_SV_OPERATOR=1 -Dnssv_STRING_VIEW_HEADER=\"string_view.hpp\" -I../include/nonstd -I"%cppcorecheckinclude%" string-view-lite.t.cpp string-view.t.cpp && string-view-lite.t.exe
@endlocal
