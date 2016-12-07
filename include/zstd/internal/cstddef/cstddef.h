#ifndef ZSTD_INTERNAL_CSTDDEF_CSTDDEF_H_
#define ZSTD_INTERNAL_CSTDDEF_CSTDDEF_H_

namespace zstd {

#define NULL nullptr

typedef long unsigned int size_t;
typedef long int ptrdiff_t;

#define offsetof(TYPE, MEMBER) size_t(&((TYPE*)0)->MEMBER)

typedef decltype(nullptr) nullptr_t;
typedef long double max_align_t;

}  // namespace zstd

#endif  // ZSTD_INTERNAL_CSTDDEF_CSTDDEF_H_