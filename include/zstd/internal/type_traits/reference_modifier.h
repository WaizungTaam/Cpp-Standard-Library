#ifndef ZSTD_INTERNAL_TYPE_TRAITS_REFERENCE_MODIFIER_H_
#define ZSTD_INTERNAL_TYPE_TRAITS_REFERENCE_MODIFIER_H_

#include "composite_type_category.h"

namespace zstd {

/* remove_reference */
template <typename Tp>
struct remove_reference {
  typedef Tp type;
};
template <typename Tp>
struct remove_reference<Tp&> {
  typedef Tp type;
};
template <typename Tp>
struct remove_reference<Tp&&> {
  typedef Tp type;
};


/* add_lvalue_reference */
namespace internal {
template <typename Tp, bool = is_referenceable<Tp>::value>
struct add_lvalue_reference {
  typedef Tp type;
};
template <typename Tp>
struct add_lvalue_reference<Tp, true> {
  typedef Tp& type;
};
}  // namespace internal

template <typename Tp>
struct add_lvalue_reference : public internal::add_lvalue_reference<Tp> {};


/* add_rvalue_reference */
namespace internal {
template <typename Tp, bool = is_referenceable<Tp>::value>
struct add_rvalue_reference {
  typedef Tp type;
};
template <typename Tp>
struct add_rvalue_reference<Tp, true> {
  typedef Tp&& type;
};
}  // namespace internal

template <typename Tp>
struct add_rvalue_reference : public internal::add_rvalue_reference<Tp> {};


template <typename Tp>
using remove_reference_t = typename remove_reference<Tp>::type;

template <typename Tp>
using add_lvalue_reference_t = typename add_lvalue_reference<Tp>::type;

template <typename Tp>
using add_rvalue_reference_t = typename add_rvalue_reference<Tp>::type;

}  // namespace zstd

#endif  // ZSTD_INTERNAL_TYPE_TRAITS_REFERENCE_MODIFIER_H_
