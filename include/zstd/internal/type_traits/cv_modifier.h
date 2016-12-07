#ifndef ZSTD_INTERNAL_TYPE_TRAITS_CV_MODIFIER_H_
#define ZSTD_INTERNAL_TYPE_TRAITS_CV_MODIFIER_H_

namespace zstd {

/* remove_const */
template <typename Tp>
struct remove_const {
  typedef Tp type;
};
template <typename Tp>
struct remove_const<const Tp> {
  typedef Tp type;
};

/* remove_volatile */
template <typename Tp>
struct remove_volatile {
  typedef Tp type;
};
template <typename Tp>
struct remove_volatile<volatile Tp> {
  typedef Tp type;
};

/* remove_cv */
template <typename Tp>
struct remove_cv {
  typedef typename remove_const<typename remove_volatile<Tp>::type>::type
          type;
};


/* add_const */
template <typename Tp>
struct add_const {
  typedef const Tp type;
};

/* add_volatile */
template <typename Tp>
struct add_volatile {
  typedef volatile Tp type;
};

/* add_cv */
template <typename Tp>
struct add_cv {
  typedef typename add_const<typename add_volatile<Tp>::type>::type type;
};


template <typename Tp>
using remove_const_t = typename remove_const<Tp>::type;

template <typename Tp>
using remove_volatile_t = typename remove_volatile<Tp>::type;

template <typename Tp>
using remove_cv_t = typename remove_cv<Tp>::type;

template <typename Tp>
using add_const_t = typename add_const<Tp>::type;

template <typename Tp>
using add_volatile_t = typename add_volatile<Tp>::type;

template <typename Tp>
using add_cv_t = typename add_cv<Tp>::type;

}  // namespace zstd

#endif  // ZSTD_INTERNAL_TYPE_TRAITS_CV_MODIFIER_H_