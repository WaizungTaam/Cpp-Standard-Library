#ifndef ZSTD_INTERNAL_NEW_NOTHROW_H_
#define ZSTD_INTERNAL_NEW_NOTHROW_H_

namespace zstd {

struct nothrow_t {
  explicit nothrow_t() = default;
};

extern const nothrow_t nothrow;

}  // namespace zstd

#endif  // ZSTD_INTERNAL_NEW_NOTHROW_H_