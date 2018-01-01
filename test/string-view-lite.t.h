// Copyright (c) 2017-2018 Martin Moene
//
// https://github.com/martinmoene/string-view-lite
//
// This code is licensed under the MIT License (MIT).

#pragma once

#ifndef TEST_SV_LITE_H_INCLUDED
#define TEST_SV_LITE_H_INCLUDED

#include nssv_STRING_VIEW_HEADER

// Limit C++ Core Guidelines checking to GSL Lite:

#if defined(_MSC_VER) && _MSC_VER >= 1910
# include <CppCoreCheck\Warnings.h>
# pragma warning(disable: ALL_CPPCORECHECK_WARNINGS)
#endif

#include "lest_cpp03.hpp"

#if nssv_USES_STD_STRING_VIEW
# define nssv_nullptr  nullptr
#endif

using namespace nonstd;

#define CASE( name ) lest_CASE( specification(), name )

extern lest::tests & specification();

namespace lest {

using ::nonstd::operator<<;

} // namespace lest

#endif // TEST_SV_LITE_H_INCLUDED

// end of file
