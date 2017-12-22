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

namespace nonstd { namespace sv_lite {

// use oparator<< instead of to_string() overload;
// see  http://stackoverflow.com/a/10651752/437272

template< typename CharT >
inline std::ostream & operator<<( std::ostream & os, basic_string_view<CharT> const & sv )
{
    return os << "'" << (sv.data() ? "(content)" : "[empty]") << "'";
}

}} // namespace nonstd::optfun_lite

namespace lest {

using ::nonstd::sv_lite::operator<<;

} // namespace lest

#endif // TEST_SV_LITE_H_INCLUDED

// end of file
