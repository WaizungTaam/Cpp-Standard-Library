#ifndef ZSTD_INTERNAL_TYPE_TRAITS_CONDITIONAL_TYPE_H_
#define ZSTD_INTERNAL_TYPE_TRAITS_CONDITIONAL_TYPE_H_

namespace zstd {

/* enable_if */
template <bool, typename Tp = void>
struct enable_if {};

template <typename Tp>
struct enable_if<true, Tp> {
	typedef Tp type;
};

/* conditional */
template <bool Condition, typename TrueBranch, typename FalseBranch>
struct conditional {
	typedef TrueBranch type;
};

template <typename TrueBranch, typename FalseBranch>
struct conditional<false, TrueBranch, FalseBranch> {
	typedef FalseBranch type;
};

}  // namespace zstd

#endif  // ZSTD_INTERNAL_TYPE_TRAITS_CONDITIONAL_TYPE_H_
