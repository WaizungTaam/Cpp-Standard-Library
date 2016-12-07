#ifndef ZSTD_INTERNAL_MEMORY_ALLOCATOR_TRAITS_H_
#define ZSTD_INTERNAL_MEMORY_ALLOCATOR_TRAITS_H_

#include "pointer_traits.h"
#include "has_rebind.h"
#include "allocator.h"

#include "../cstddef/cstddef.h"
#include "../utility/forward.h"
#include "../utility/declval.h"
#include "../type_traits/type_traits_base.h"
#include "../type_traits/conditional_type.h"
#include "../type_traits/signed_modifier.h"
#include "../type_traits/class_property.h"
#include "../limits/numeric_limits.h"


namespace zstd {

namespace internal {

template <typename Alloc, typename Tp, bool = has_rebind<Alloc, Tp>::value>
struct allocator_traits_rebind;

template <typename Alloc, typename Tp>
struct allocator_traits_rebind<Alloc, Tp, true> {
	typedef typename Alloc::template rebind<Tp>::other type;
};

template <template <typename, typename...> class Alloc, typename Tp,
					typename Up, typename... Args>
struct allocator_traits_rebind<Alloc<Up, Args...>, Tp, false> {
	typedef Alloc<Tp, Args...> type;
};

}  // namespace internal

template <typename Alloc>
struct allocator_traits {

	/* typedef */
	typedef Alloc allocator_type;
	typedef typename Alloc::value_type value_type;

#define ALLOC_TRAITS_TYPE_DEF(NESTED, ALT) \
private: \
	template <typename Tp> \
	static typename Tp::NESTED NESTED##_test(Tp*); \
	static ALT NESTED##_test(...); \
	typedef decltype(NESTED##_test((Alloc*)0)) NESTED##_helper; \
public:

	ALLOC_TRAITS_TYPE_DEF(pointer, value_type*)
	typedef pointer_helper pointer;

	ALLOC_TRAITS_TYPE_DEF(const_pointer, 
		typename pointer_traits<pointer>::template rebind<const value_type>)
	typedef const_pointer_helper const_pointer;

	ALLOC_TRAITS_TYPE_DEF(void_pointer,
		typename pointer_traits<pointer>::template rebind<void>)
	typedef void_pointer_helper void_pointer;

	ALLOC_TRAITS_TYPE_DEF(const_void_pointer,
		typename pointer_traits<pointer>::template rebind<const void>)
	typedef const_void_pointer_helper const_void_pointer;

	ALLOC_TRAITS_TYPE_DEF(difference_type,
		typename pointer_traits<pointer>::difference_type)
	typedef difference_type_helper difference_type;

	ALLOC_TRAITS_TYPE_DEF(size_type,
		typename zstd::make_unsigned<difference_type>::type)
	typedef size_type_helper size_type;

	ALLOC_TRAITS_TYPE_DEF(propagate_on_container_copy_assignment,
		zstd::false_type)
	typedef propagate_on_container_copy_assignment_helper
					propagate_on_container_copy_assignment;

	ALLOC_TRAITS_TYPE_DEF(propagate_on_container_move_assignment,
		zstd::false_type)
	typedef propagate_on_container_move_assignment_helper
					propagate_on_container_move_assignment;

	ALLOC_TRAITS_TYPE_DEF(propagate_on_container_swap, zstd::false_type)
	typedef propagate_on_container_swap_helper propagate_on_container_swap;

#undef ALLOC_TRAITS_TYPE_DEF


	template <typename Tp>
	using rebind_alloc = typename 
		internal::allocator_traits_rebind<Alloc, Tp>::type;

	template <typename Tp>
	using rebind_traits = allocator_traits<rebind_alloc<Tp>>;
	

  /* allocate() */
private:
	template <typename Alloc1>
	struct allocate_helper {
		template <typename Alloc2,
							typename = decltype(zstd::declval<Alloc2*>()->allocate(
							zstd::declval<size_type>(), 
							zstd::declval<const_void_pointer>()))>
		static zstd::true_type test(int);

		template <typename>
		static zstd::false_type test(...);

		using type = decltype(test<Alloc>(0));
	};

	template <typename Alloc1>
	using has_allocate = typename allocate_helper<Alloc1>::type;

	template <typename Alloc1, 
						typename = 
						typename zstd::enable_if<has_allocate<Alloc1>::value>::type>
  static pointer allocate_impl(Alloc1& alloc, size_type n, 
  														 const_void_pointer hint) {
  	return alloc.allocate(n, hint);
  }

	template <typename Alloc1, 
						typename Hint,
						typename = 
						typename zstd::enable_if<!has_allocate<Alloc1>::value>::type>
  static pointer allocate_impl(Alloc1& alloc, size_type n, Hint) {
  	return alloc.allocate(n);
  }

public:
	static pointer allocate(Alloc& alloc, size_type n, const_void_pointer hint) {
		return allocate_impl(alloc, n, hint);
	}


  /* deallocate() */
	static void deallocate(Alloc& alloc, pointer p, size_type n) {
		alloc.deallocate(p, n);
	}

  /* construct() */
private:
  template <typename Tp, typename... Args>
  struct construct_helper {
  	template <typename Alloc1,
  						typename = decltype(zstd::declval<Alloc1*>()->construct(
  						zstd::declval<Tp*>(), zstd::declval<Args>()...))>
    static zstd::true_type test(int);

    template <typename>
    static zstd::false_type test(...);

    using type = decltype(test<Alloc>(0));
  };

  template <typename Tp, typename... Args>
  using has_construct = typename construct_helper<Tp, Args...>::type;

  template <typename Tp, typename... Args>
  static typename zstd::enable_if<has_construct<Tp, Args...>::value>::type
  construct_impl(Alloc& alloc, Tp* p, Args&&... args) {
  	alloc.construct(p, zstd::forward<Args>(args)...);
  }

  template <typename Tp, typename... Args>
  static typename zstd::enable_if<
  									!has_construct<Tp, Args...>::value &&
  									zstd::is_constructible<Tp, Args...>::value>::type
  construct_impl(Alloc&, Tp* p, Args&&... args) {
  	::new((void*)p) Tp(zstd::forward<Args>(args)...);
  }

public:
	template <typename Tp, typename... Args>
	static auto construct(Alloc& alloc, Tp* p, Args&&... args) 
	  -> decltype(construct_impl(alloc, p, zstd::forward<Args>(args)...)) {
		return construct_impl(alloc, p, zstd::forward<Args>(args)...);
	}


/* destroy */
private:
	template <typename Tp>
	struct destroy_helper {
		template <typename Alloc1,
							typename = decltype(zstd::declval<Alloc1*>()->destroy(
							zstd::declval<Tp*>()))>
    static zstd::true_type test(int);

    template <typename>
    static zstd::false_type test(...);

    using type = decltype(test<Alloc>(0));
	};

	template <typename Tp>
	using has_destroy = typename destroy_helper<Tp>::type;

	template <typename Tp>
	static typename zstd::enable_if<has_destroy<Tp>::value>::type
	destroy_impl(Alloc& alloc, Tp* p) {
		alloc.destroy(p);
	}

	template <typename Tp>
	static typename zstd::enable_if<!has_destroy<Tp>::value>::type
	destroy_impl(Alloc& alloc, Tp* p) {
		p->~Tp();
	}

public:
	template <typename Tp>
	static void destroy(Alloc& alloc, Tp* p) {
		destroy_impl(alloc, p);
	}


	/* max_size() */
private:
	template <typename Alloc1>
	struct max_size_helper {
		template <typename Alloc2,
							typename = decltype(zstd::declval<Alloc2>()->max_size())>
		static zstd::true_type test(int);

		template <typename>
		static zstd::false_type test(...);

		using type = decltype(test<Alloc1>(0));
	};

	template <typename Alloc1>
	using has_max_size = typename max_size_helper<Alloc1>::type;

	template <typename Alloc1,
						typename = 
						typename zstd::enable_if<has_max_size<Alloc1>::value>::type>
	static size_type max_size_impl(Alloc1& alloc, int) {
		return alloc.max_size();
	}

	template <typename Alloc1,
					  typename = 
					  typename zstd::enable_if<!has_max_size<Alloc1>::value>::type>
	static size_type max_size_impl(Alloc1&, ...) {
		return zstd::numeric_limits<size_type>::max();
	}

public:
	static size_type max_size(const Alloc& alloc) noexcept {
		return max_size_impl(alloc, 0);
	}


/* select_on_container_copy_construction() */
private:
	template <typename Alloc1>
	struct select_helper {
		template <typename Alloc2,
							typename = decltype(zstd::declval<Alloc2*>()->
							select_on_container_copy_construction())>
		static zstd::true_type test(int);

		template <typename>
		static zstd::false_type test(...);

		using type = decltype(test<Alloc1>(0));
	};

	template <typename Alloc1>
	using has_select = typename select_helper<Alloc1>::type;

	template <typename Alloc1,
						typename =
						typename zstd::enable_if<has_select<Alloc1>::value>::type>
	static Alloc1 select_impl(Alloc1& alloc, int) {
		return alloc.select_on_container_copy_construction();
	}

	template <typename Alloc1,
						typename =
						typename zstd::enable_if<!has_select<Alloc1>::value>::type>
	static Alloc1 select_impl(Alloc1& alloc, ...) {
		return alloc;
	}

public:
	static Alloc select_on_container_copy_construction(
		const Alloc& other) noexcept {
		return select_impl(other, 0);
	}
};


template <typename Tp>
struct allocator_traits<allocator<Tp>> {
	typedef allocator<Tp> allocator_type;
	typedef Tp value_type;
	typedef Tp* pointer;
	typedef const Tp* const_pointer;
	typedef void* void_pointer;
	typedef const void* const_void_pointer;
	typedef zstd::size_t size_type;
	typedef zstd::ptrdiff_t difference_type;
	typedef zstd::false_type propagate_on_container_copy_assignment;
	typedef zstd::true_type propagate_on_container_move_assignment;
	typedef zstd::false_type propagate_on_container_swap;

	template <typename Other>
	using rebind_alloc = allocator<Other>;
	template <typename Other>
	using rebind_traits = allocator_traits<allocator<Other>>;

	static pointer allocate(allocator_type& alloc, size_type n) {
		return alloc.allocate(n);
	}
	static pointer allocate(allocator_type& alloc, size_type n, 
													const_void_pointer hint) {
		return alloc.allocate(n, hint);
	}
	static void deallocate(allocator_type& alloc, pointer p, size_type n) {
		alloc.deallocate(p, n);
	}

	template <typename Other, typename... Args>
	static void construct(allocator_type& alloc, Other* p, Args&&... args) {
		alloc.construct(p, zstd::forward<Args>(args)...);
	}
	template <typename Other>
	static void destroy(allocator_type& alloc, Other* p) {
		alloc.destroy(p);
	}

	static size_type max_size(const allocator_type& alloc) noexcept {
		return alloc.max_size();
	}

	static allocator_type select_on_container_copy_construction(
		const allocator_type& rhs) {
		return rhs;
	}
};

}  // namespace zstd

#endif  // ZSTD_INTERNAL_MEMORY_ALLOCATOR_TRAITS_H_