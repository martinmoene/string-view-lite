//
// string-view-lite, a C++17-like string_view for C++98 and later.
// For more information see https://github.com/martinmoene/string-view-lite
//
// Copyright (c) 2017-2018 Martin Moene
//
// This code is licensed under the MIT License (MIT).
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

#ifndef NONSTD_SV_LITE_H_INCLUDED
#define NONSTD_SV_LITE_H_INCLUDED

#define  string_view_lite_VERSION "0.1.0"

// String -View Lite configuration:

// Todo:
// - force use of std::string_view
// - force use of nonstd::string_view

// Compiler detection:

#define nssv_CPP11_OR_GREATER  ( __cplusplus >= 201103L )
#define nssv_CPP14_OR_GREATER  ( __cplusplus >= 201402L /* || _MSVC_LANG >= 201402L */ )
#define nssv_CPP17_OR_GREATER  ( __cplusplus >= 201703L    || _MSVC_LANG >= 201703L    )

// use C++17 std::string_view if available:

#if defined( __has_include )
# define nssv_HAS_INCLUDE( arg )  __has_include( arg )
#else
# define nssv_HAS_INCLUDE( arg )  0
#endif

#define nssv_HAVE_STD_STRING_VIEW  ( nssv_CPP17_OR_GREATER && nssv_HAS_INCLUDE(<string_view>) )
#define nssv_USES_STD_STRING_VIEW  ( 0 )

//
// Use C++17 std::string_view:
//

#if nssv_USES_STD_STRING_VIEW

#include <string_view>

namespace nonstd {

using std::string_view;
using std::wstring_view;
using std::u16string_view;
using std::u32string_view;
using std::basic_string_view;

// literal "sv"

using std::hash;

} // namespace nonstd

#else // nssv_HAVE_STD_STRING_VIEW

#if defined(_MSC_VER) && !defined(__clang__)
# define nssv_COMPILER_MSVC_VERSION   (_MSC_VER / 100 - 5 - (_MSC_VER < 1900))
#else
# define nssv_COMPILER_MSVC_VERSION   0
#endif

#if defined __GNUC__
# define nssv_COMPILER_GNUC_VERSION  __GNUC__
#else
# define nssv_COMPILER_GNUC_VERSION    0
#endif

// Presence of C++11 language features:

#if nssv_CPP11_OR_GREATER || nssv_COMPILER_MSVC_VERSION >= 10
# define nssv_HAVE_AUTO  1
# define nssv_HAVE_NULLPTR  1
# define nssv_HAVE_STATIC_ASSERT  1
# define nssv_HAVE_WCHAR16_T  1
# define nssv_HAVE_WCHAR32_T  1
#endif

#if nssv_CPP11_OR_GREATER || nssv_COMPILER_MSVC_VERSION >= 12
# define nssv_HAVE_DEFAULT_FUNCTION_TEMPLATE_ARG  1
# define nssv_HAVE_INITIALIZER_LIST  1
#endif

#if nssv_CPP11_OR_GREATER || nssv_COMPILER_MSVC_VERSION >= 14
# define nssv_HAVE_ALIAS_TEMPLATE  1
# define nssv_HAVE_CONSTEXPR_11  1
# define nssv_HAVE_ENUM_CLASS  1
# define nssv_HAVE_EXPLICIT_CONVERSION  1
# define nssv_HAVE_IS_DEFAULT  1
# define nssv_HAVE_IS_DELETE  1
# define nssv_HAVE_NOEXCEPT  1
# define nssv_HAVE_REF_QUALIFIER  1
#endif

// Presence of C++14 language features:

#if nssv_CPP14_OR_GREATER
# define nssv_HAVE_CONSTEXPR_14  1
#endif

// Presence of C++17 language features:

#if nssv_CPP17_OR_GREATER
# define nssv_HAVE_NODISCARD  1
#endif

// For the rest, consider VC14 as C++11 for optional-lite:

//#if      nssv_COMPILER_MSVC_VERSION >= 14
//# undef  nssv_CPP11_OR_GREATER
//# define nssv_CPP11_OR_GREATER  1
//#endif

// Presence of C++ library features:

#if nssv_CPP11_OR_GREATER || nssv_COMPILER_MSVC_VERSION >= 12
# define nssv_HAVE_STD_HASH  1
#endif

// C++ feature usage:

#if      nssv_HAVE_CONSTEXPR_11
# define nssv_constexpr  constexpr
#else
# define nssv_constexpr  /*constexpr*/
#endif

#if      nssv_HAVE_CONSTEXPR_14
# define nssv_constexpr14  constexpr
#else
# define nssv_constexpr14  /*constexpr*/
#endif

#if      nssv_HAVE_NOEXCEPT
# define nssv_noexcept  noexcept
#else
# define nssv_noexcept  /*noexcept*/
#endif

#if      nssv_HAVE_REF_QUALIFIER
# define nssv_ref_qual  &
# define nssv_refref_qual  &&
#else
# define nssv_ref_qual  /*&*/
# define nssv_refref_qual  /*&&*/
#endif

#if nssv_HAVE_NULLPTR
# define nssv_nullptr  nullptr
#else
# define nssv_nullptr  NULL
#endif

#if      nssv_HAVE_NODISCARD
# define nssv_NODISCARD  [[nodiscard]]
#else
# define nssv_NODISCARD  /*[[nodiscard]]*/
#endif

// additional includes:

#if nssv_CPP11_OR_GREATER
#endif

//
// Before C++17: use string_view lite:
//

#include <cassert>
#include <limits>
#include <string>   // std::char_traits<>

namespace nonstd { namespace sv_lite {

template
<
    class CharT,
    class Traits = std::char_traits<CharT>
>
class basic_string_view;

//
// basic_string_view:
//

template
<
    class CharT,
    class Traits /* = std::char_traits<CharT> */
>
class basic_string_view
{
public:
    // Member types:

    typedef Traits traits_type;
    typedef CharT  value_type;

    typedef CharT *       pointer;
    typedef CharT const * const_pointer;
    typedef CharT &       reference;
    typedef CharT const & const_reference;

    typedef const_pointer iterator;
    typedef const_pointer const_iterator;
    typedef std::reverse_iterator< const_iterator > reverse_iterator;
    typedef	std::reverse_iterator< const_iterator > const_reverse_iterator;

    typedef std::size_t     size_type;
    typedef std::ptrdiff_t  difference_type;

    // Constructors:

    nssv_constexpr basic_string_view() nssv_noexcept
        : data_( nssv_nullptr )
        , size_( 0 )
    {}

#if nssv_CPP11_OR_GREATER
    nssv_constexpr basic_string_view( basic_string_view const & other ) nssv_noexcept = default;
#else
    nssv_constexpr basic_string_view( basic_string_view const & other ) nssv_noexcept
        : data_( other.data_)
        , size_( other.size_)
    {}
#endif

    nssv_constexpr basic_string_view( CharT const * s, size_type count )
        : data_( s )
        , size_( count )
    {}

    nssv_constexpr basic_string_view( CharT const * s)
        : data_( s )
        , size_( Traits::length(s) )
    {}

	// Assignment:

#if nssv_CPP11_OR_GREATER
    nssv_constexpr14 basic_string_view & operator=( basic_string_view const & view ) nssv_noexcept = default;
#else
    nssv_constexpr14 basic_string_view & operator=( basic_string_view const & view ) nssv_noexcept
    {
        data_ = view.data_;
        size_ = view.size_;
        return *this;
    }
#endif

    // Iterators:

    nssv_constexpr const_iterator begin()  const nssv_noexcept { return data_;         }
    nssv_constexpr const_iterator end()    const nssv_noexcept { return data_ + size_; }

    nssv_constexpr const_iterator cbegin() const nssv_noexcept { return begin(); }
    nssv_constexpr const_iterator cend()   const nssv_noexcept { return end();   }

    nssv_constexpr const_reverse_iterator rbegin()  const nssv_noexcept { return const_reverse_iterator( end() );   }
    nssv_constexpr const_reverse_iterator rend()    const nssv_noexcept { return const_reverse_iterator( begin() ); }

    nssv_constexpr const_reverse_iterator crbegin() const nssv_noexcept { return rbegin(); }
    nssv_constexpr const_reverse_iterator crend()   const nssv_noexcept { return rend();   }

    // Element access:

    nssv_constexpr const_reference operator[]( size_type pos ) const
    {
        return assert( pos < size() ),
            data_[pos];
    }

    nssv_constexpr const_reference at( size_type pos ) const
    {
        if ( pos < size() )
        {
            return data_[pos];
        }
        throw std::out_of_range( "nonst::string_view::at()" );
    }

    nssv_constexpr const_reference front() const { return assert( !empty() ), data_[0]; }
    nssv_constexpr const_reference back()  const { return assert( !empty() ), data_[size() - 1]; }

    nssv_constexpr const_pointer   data()  const nssv_noexcept { return data_; }

    // Capacity:

    nssv_constexpr size_type size()     const nssv_noexcept { return size_; }
    nssv_constexpr size_type length()   const nssv_noexcept { return size_; }
    nssv_constexpr size_type max_size() const nssv_noexcept { return std::numeric_limits< size_type >::max(); }

    nssv_NODISCARD nssv_constexpr bool empty() const nssv_noexcept  // C++20
    {
        return 0 == size_;
    }

    // Modifiers:

    nssv_constexpr14 void remove_prefix(size_type n);
    nssv_constexpr14 void remove_suffix(size_type n);
    nssv_constexpr14 void swap(basic_string_view& v) nssv_noexcept;

    // Operations:

    size_type copy( CharT * dest, size_type count, size_type pos = 0) const;
    nssv_constexpr basic_string_view substr(size_type pos = 0, size_type count = npos ) const;

    nssv_constexpr int compare(basic_string_view v) const nssv_noexcept;  // (1) (since C++17)
    nssv_constexpr int compare(size_type pos1, size_type count1, basic_string_view v) const; // (2) (since C++17)
    nssv_constexpr int compare(size_type pos1, size_type count1, basic_string_view v, size_type pos2, size_type count2) const; // (3) (since C++17)
    nssv_constexpr int compare(const CharT* s) const; // (4) (since C++17)
    nssv_constexpr int compare(size_type pos1, size_type count1, const CharT* s) const; // (5) (since C++17)
    nssv_constexpr int compare(size_type pos1, size_type count1, const CharT* s, size_type count2) const; // (6)

    nssv_constexpr bool starts_with(basic_string_view x) const nssv_noexcept;  // (1) (since C++20)
    nssv_constexpr bool starts_with(CharT x) const nssv_noexcept;  // (2) (since C++20)
    nssv_constexpr bool starts_with(const CharT* x) const;  // (3) (since C++20)

    nssv_constexpr bool ends_with(basic_string_view x) const nssv_noexcept; // (1)(since C++20)
    nssv_constexpr bool ends_with(CharT x) const nssv_noexcept; // (2) (since C++20)
    nssv_constexpr bool ends_with(const CharT* x) const;  // (3) (since C++20)

    nssv_constexpr size_type find(basic_string_view v, size_type pos = 0) const nssv_noexcept; // (1) (since C++17)
    nssv_constexpr size_type find(CharT ch, size_type pos = 0) const nssv_noexcept; // (2) (since C++17)
    nssv_constexpr size_type find(const CharT* s, size_type pos, size_type count) const;  // (3) (since C++17)
    nssv_constexpr size_type find(const CharT* s, size_type pos = 0) const;  // (4) (since C++17)

    nssv_constexpr size_type rfind(basic_string_view v, size_type pos = npos) const nssv_noexcept;  // (1) (since C++17)
    nssv_constexpr size_type rfind(CharT c, size_type pos = npos) const nssv_noexcept;  // (2) (since C++17)
    nssv_constexpr size_type rfind(const CharT* s, size_type pos, size_type count) const;  // (3) (since C++17)
    nssv_constexpr size_type rfind(const CharT* s, size_type pos = npos) const;  // (4) (since C++17)

    nssv_constexpr size_type find_first_of(basic_string_view v, size_type pos = 0) const nssv_noexcept;  // (1) (since C++17)
    nssv_constexpr size_type find_first_of(CharT c, size_type pos = 0) const nssv_noexcept;  // (2) (since C++17)
    nssv_constexpr size_type find_first_of(const CharT* s, size_type pos, size_type count) const;  // (3) (since C++17)
    nssv_constexpr size_type find_first_of(const CharT* s, size_type pos = 0) const;  // (4) (since C++17)

    nssv_constexpr size_type find_last_of(basic_string_view v, size_type pos = npos) const nssv_noexcept;  // (1) (since C++17)
    nssv_constexpr size_type find_last_of(CharT c, size_type pos = npos) const nssv_noexcept;  // (2) (since C++17)
    nssv_constexpr size_type find_last_of(const CharT* s, size_type pos, size_type count) const;  // (3) (since C++17)
    nssv_constexpr size_type find_last_of(const CharT* s, size_type pos = npos) const;  // (4) (since C++17)

    nssv_constexpr size_type find_first_not_of(basic_string_view v, size_type pos = 0) const nssv_noexcept;  // (1) (since C++17)
    nssv_constexpr size_type find_first_not_of(CharT c, size_type pos = 0) const nssv_noexcept;  // (2) (since C++17)
    nssv_constexpr size_type find_first_not_of(const CharT* s, size_type pos, size_type count) const;  // (3) (since C++17)
    nssv_constexpr size_type find_first_not_of(const CharT* s, size_type pos = 0) const;  // (4) (since C++17)

    nssv_constexpr size_type find_last_not_of(basic_string_view v, size_type pos = npos) const nssv_noexcept;  // (1) (since C++17)
    nssv_constexpr size_type find_last_not_of(CharT c, size_type pos = npos) const nssv_noexcept;  // (2) (since C++17)
    nssv_constexpr size_type find_last_not_of(const CharT* s, size_type pos, size_type count) const;  // (3) (since C++17)
    nssv_constexpr size_type find_last_not_of(const CharT* s, size_type pos = npos) const;  // (4) (since C++17)

    // Constants:

#if nssv_CPP17_OR_GREATER
    static nssv_constexpr size_type npos = size_type(-1);
#elif nssv_CPP11_OR_GREATER
    enum : size_type { npos = size_type(-1) };
#else
    enum { npos = size_type(-1) };
#endif

private:
    const_pointer data_;
    size_type     size_;
};

// Non-member functions
// lexicographically compares two string views (function template)

template< class CharT, class Traits >
nssv_constexpr bool operator==(
    basic_string_view <CharT, Traits> lhs,
    basic_string_view <CharT, Traits> rhs ) nssv_noexcept;

template< class CharT, class Traits >
nssv_constexpr bool operator!=(
    basic_string_view <CharT, Traits> lhs,
    basic_string_view <CharT, Traits> rhs ) nssv_noexcept;

template< class CharT, class Traits >
nssv_constexpr bool operator<(
    basic_string_view <CharT, Traits> lhs,
    basic_string_view <CharT, Traits> rhs ) nssv_noexcept;

template< class CharT, class Traits >
nssv_constexpr bool operator<=(
    basic_string_view <CharT, Traits> lhs,
    basic_string_view <CharT, Traits> rhs ) nssv_noexcept;

template< class CharT, class Traits >
nssv_constexpr bool operator>(
    basic_string_view <CharT, Traits> lhs,
    basic_string_view <CharT, Traits> rhs ) nssv_noexcept;

template< class CharT, class Traits >
nssv_constexpr bool operator>=(
    basic_string_view <CharT, Traits> lhs,
    basic_string_view <CharT, Traits> rhs ) nssv_noexcept;

// Input/output
template< class CharT, class Traits >
std::basic_ostream<CharT, Traits> &
operator<<(
    std::basic_ostream<CharT, Traits>& os,
    basic_string_view <CharT, Traits> sv );

// Literals - Defined in inline namespace std::literals::string_view_literals

namespace string_view_literals {

// msvc warning C4455: 'operator ""sv': literal suffix identifiers that do not start with an underscore are reserved

//nssv_constexpr string_view operator "" sv(const char* str, size_t len) nssv_noexcept;  // (1) (since C++17)
//nssv_constexpr u16string_view operator "" sv(const char16_t* str, size_t len) nssv_noexcept;  // (2) (since C++17)
//nssv_constexpr u32string_view operator "" sv(const char32_t* str, size_t len) nssv_noexcept;  // (3) (since C++17)
//nssv_constexpr wstring_view   operator "" sv(const wchar_t* str, size_t len) nssv_noexcept;  // (4) (since C++17)

} // namespace string_view_literals

}} // namespace nonstd::sv_lite

// Several typedefs for common character types are provided:
//
// Defined in header <string_view>
// Type Definition
namespace nonstd { namespace sv_lite {

typedef basic_string_view<char>      string_view;
typedef basic_string_view<wchar_t>   wstring_view;
#if nssv_HAVE_WCHAR16_T
typedef basic_string_view<char16_t>  u16string_view;
typedef basic_string_view<char32_t>  u32string_view;
#endif

}} // namespace nonstd::sv_lite

namespace nonstd {

using sv_lite::basic_string_view;
using sv_lite::string_view;
using sv_lite::wstring_view;
#if nssv_HAVE_WCHAR16_T
using sv_lite::u16string_view;
using sv_lite::u32string_view;
#endif

// literal "sv"

} // namespace nonstd

#if nssv_HAVE_STD_HASH

#include <functional>

namespace std {

template<>
struct hash< nonstd::string_view >
{
public:
    std::size_t operator()( nonstd::string_view v ) const nssv_noexcept;
};

template<>
struct hash< nonstd::wstring_view >
{
public:
    std::size_t operator()( nonstd::wstring_view v ) const nssv_noexcept;
};

template<>
struct hash< nonstd::u16string_view >
{
public:
    std::size_t operator()( nonstd::u16string_view v ) const nssv_noexcept;
};

template<>
struct hash< nonstd::u32string_view >
{
public:
    std::size_t operator()( nonstd::u32string_view v ) const nssv_noexcept;
};

} // namespace std

#endif // nssv_HAVE_STD_HASH
#endif // nssv_HAVE_STD_STRING_VIEW
#endif // NONSTD_SV_LITE_H_INCLUDED
