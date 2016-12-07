#ifndef ZSTD_INTERNAL_MEMORY_POINTER_TRAITS_H_
#define ZSTD_INTERNAL_MEMORY_POINTER_TRAITS_H_

#include "addressof.h"
#include "has_rebind.h"

#include "../cstddef/cstddef.h"
#include "../type_traits/type_traits_base.h"
#include "../type_traits/conditional_type.h"
#include "../type_traits/primary_type_category.h"

namespace zstd {

namespace internal {

/* pointer_traits_element_type */
template <typename Tp>
struct has_element_type_helper {
private:
	// TODO: Consider the _Wrap_type in libstdc++v3 type_traits :2264
	template <typename Up>
	static zstd::true_type test(typename Up::element_type*);

	static zstd::false_type test(...);

public:
	typedef decltype(test<Tp>(0)) type;
};

template <typename Tp>
struct has_element_type : public has_element_type_helper<Tp>::type {};

template <typename Tp, bool = has_element_type<Tp>::value>
struct pointer_traits_element_type;

template <typename Tp>
struct pointer_traits_element_type<Tp, true> {
	typedef typename Tp::element_type type;
};

template <template <typename, typename...> class Ptr, typename Tp, 
					typename... Args>
struct pointer_traits_element_type<Ptr<Tp, Args...>, false> {
	typedef Tp type;
};


/* pointer_traits_difference_type */
template <typename Tp>
struct has_difference_type_helper {
private:
	// TODO: Consider the _Wrap_type in libstdc++v3 type_traits :2264
	template <typename Up>
	static zstd::true_type test(typename Up::difference_type*);

	static zstd::false_type test(...);

public:
	typedef decltype(test<Tp>(0)) type;
};

template <typename Tp>
struct has_difference_type : public has_difference_type_helper<Tp>::type {};

template <typename Tp, bool = has_difference_type<Tp>::value>
struct pointer_traits_difference_type {
	typedef typename Tp::difference_type type;
};

template <typename Tp>
struct pointer_traits_difference_type<Tp, false> {
	typedef zstd::size_t type;
};


/* pointer_traits_rebind */
template <typename Tp, typename Up, bool = has_rebind<Tp, Up>::value>
struct pointer_traits_rebind;

template <typename Tp, typename Up>
struct pointer_traits_rebind<Tp, Up, true> {
	typedef typename Tp::template rebind<Up> type;
};

template <template <typename, typename...> class Ptr, typename Up, 
					typename Tp, typename... Args>
struct pointer_traits_rebind<Ptr<Tp, Args...>, Up, false> {
	typedef Ptr<Up, Args...> type;
};

}  // namespace internal

template <typename Ptr>
struct pointer_traits {
	typedef Ptr pointer;
	typedef typename internal::pointer_traits_element_type<Ptr>::type
	        element_type;
	// Note: element_type here can be void, which is different from the gcc
	// implementation, and is the closer to the clang version.
	typedef typename internal::pointer_traits_difference_type<Ptr>::type 
					difference_type;

	template <typename Other>
	struct rebind {
		typedef typename internal::pointer_traits_rebind<Ptr, Other>::type
						other;
	};

private:
	struct NAT {};

public:
	static Ptr pointer_to(typename zstd::conditional<
											  zstd::is_void<element_type>::value,
												NAT, element_type>::type& r) {
		return pointer::pointer_to(r);
	}
};

template <typename Tp>
struct pointer_traits<Tp*> {
	typedef Tp* pointer;
	typedef Tp element_type;
	typedef zstd::ptrdiff_t difference_type;

	template <typename Other>
	struct rebind { typedef Other* other; };

private:
	struct NAT {};

public:
	static pointer pointer_to(typename zstd::conditional<
											      zstd::is_void<element_type>::value,
												    NAT, element_type>::type& r) noexcept {
		return addressof(r);
	}

};

}  // namespace zstd

#endif  // ZSTD_INTERNAL_MEMORY_POINTER_TRAITS_H_
