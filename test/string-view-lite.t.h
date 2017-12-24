// Copyright (c) 2017-2018 Martin Moene
//
// https://github.com/martinmoene/string-view-lite
//
// This code is licensed under the MIT License (MIT).

#pragma once

#ifndef TEST_SV_LITE_H_INCLUDED
#define TEST_SV_LITE_H_INCLUDED

#include nssv_STRING_VIEW_HEADER
#include "lest_cpp03.hpp"

using namespace nonstd;

#define CASE( name ) lest_CASE( specification(), name )

extern lest::tests & specification();

namespace lest {

using ::nonstd::operator<<;

} // namespace lest

#endif // TEST_SV_LITE_H_INCLUDED

// end of file
