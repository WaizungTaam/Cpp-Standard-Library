#ifndef ZSTD_INTERNAL_TYPE_TRAITS_SIGNED_PROPERTY_H_
#define ZSTD_INTERNAL_TYPE_TRAITS_SIGNED_PROPERTY_H_

#include "cv_modifier.h"
#include "conditional_type.h"
#include "primary_type_category.h"
#include "type_property.h"

namespace zstd {

namespace internal {

template <typename Unqualified, bool IsConst, bool IsVoltile>
struct conditional_add_cv;

template <typename Unqualified>
struct conditional_add_cv<Unqualified, false, false> {
  typedef Unqualified type;
};
template <typename Unqualified>
struct conditional_add_cv<Unqualified, true, false> {
  typedef const Unqualified type;
};
template <typename Unqualified>
struct conditional_add_cv<Unqualified, false, true> {
  typedef volatile Unqualified type;
};
template <typename Unqualified>
struct conditional_add_cv<Unqualified, true, true> {
  typedef const volatile Unqualified type;
};

template <typename Qualified, typename Unqualified, 
          bool IsConst = zstd::is_const<Qualified>::value,
          bool IsVoltile = zstd::is_volatile<Qualified>::value>
struct qualify_cv {
  typedef typename conditional_add_cv<Unqualified, IsConst, IsVoltile>::type
          type;
};

}  // namespace internal

/* make_signed */
namespace internal {

template <typename Tp> struct make_signed { typedef Tp type; };
template <> struct make_signed<char> { typedef signed char type; };
template <> struct make_signed<unsigned char> { typedef signed char type; };
template <> struct make_signed<unsigned short> { typedef signed short type; };
template <> struct make_signed<unsigned int> { typedef signed int type; };
template <> struct make_signed<unsigned long> { typedef signed long type; };
template <> struct make_signed<unsigned long long> 
{ typedef signed long long type; };

template <typename Tp, 
          bool IsInt = zstd::is_integral<Tp>::value,
          bool IsEnum = zstd::is_enum<Tp>::value>
struct make_signed_selector;

template <typename Tp>
struct make_signed_selector<Tp, true, false> {
private:
  typedef typename internal::make_signed<
          typename zstd::remove_cv<Tp>::type>::type unqualified_signed;
  typedef typename qualify_cv<Tp, unqualified_signed>::type cv_signed;
public:
  typedef cv_signed type;
};

template <typename Tp>
struct make_signed_selector<Tp, false, true> {
  typedef signed char smallest_t;
  static const bool le_smallest = (sizeof(Tp) <= sizeof(smallest_t));
  static const bool le_short = (sizeof(Tp) <= sizeof(signed short));
  static const bool le_int = (sizeof(Tp) <= sizeof(signed int));
  typedef typename zstd::conditional<le_int, 
          signed int, signed long>::type ble_int;
  typedef typename zstd::conditional<le_short,
          signed short, ble_int>::type ble_short;
public:
  typedef typename conditional<le_smallest, smallest_t, ble_short>::type
          type;
};

}  // namespace internal

template <typename Tp>
struct make_signed {
	typedef typename internal::make_signed_selector<Tp>::type type;
};

template <>
struct make_signed<bool>;



/* make_unsigned */
namespace internal {

template <typename Tp> struct make_unsigned { typedef Tp type; };
template <> struct make_unsigned<char> { typedef unsigned char type; };
template <> struct make_unsigned<signed char> { typedef unsigned char type; };
template <> struct make_unsigned<short> { typedef unsigned short type; };
template <> struct make_unsigned<int> { typedef unsigned int type; };
template <> struct make_unsigned<long> { typedef unsigned long type; };
template <> struct make_unsigned<long long>
{ typedef unsigned long long type; };

template <typename Tp, 
          bool IsInt = zstd::is_integral<Tp>::value,
          bool IsEnum = zstd::is_enum<Tp>::value>
struct make_unsigned_selector;

template <typename Tp>
struct make_unsigned_selector<Tp, true, false> {
private:
  typedef typename internal::make_unsigned<
          typename zstd::remove_cv<Tp>::type>::type unqualified_unsigned;
  typedef typename qualify_cv<Tp, unqualified_unsigned>::type cv_unsigned;
public:
  typedef cv_unsigned type;
};

template <typename Tp>
struct make_unsigned_selector<Tp, false, true> {
  typedef unsigned char smallest_t;
  static const bool le_smallest = (sizeof(Tp) <= sizeof(smallest_t));
  static const bool le_ushort = (sizeof(Tp) <= sizeof(unsigned short));
  static const bool le_uint = (sizeof(Tp) <= sizeof(unsigned int));
  typedef typename zstd::conditional<le_uint, 
          unsigned int, unsigned long>::type ble_uint;
  typedef typename zstd::conditional<le_ushort,
          unsigned short, ble_uint>::type ble_ushort;
public:
  typedef typename conditional<le_smallest, smallest_t, ble_ushort>::type
          type;
};

}  // namespace internal

template <typename Tp>
struct make_unsigned {
  typedef typename internal::make_unsigned_selector<Tp>::type type;
};

template <>
struct make_unsigned<bool>;



template <typename Tp>
using make_signed_t = typename make_signed<Tp>::type;

template <typename Tp>
using make_unsigned_t = typename make_unsigned<Tp>::type;

}  // namespace zstd

#endif  // ZSTD_INTERNAL_TYPE_TRAITS_SIGNED_PROPERTY_H_
