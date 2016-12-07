#ifndef ZSTD_INTERNAL_MEMORY_TEMPORARY_BUFFER_H_
#define ZSTD_INTERNAL_MEMORY_TEMPORARY_BUFFER_H_

#include "../cstddef/cstddef.h"
#include "../utility/pair.h"
#include "../limits/numeric_limits.h"
// #include "../new/nothrow.h"
// #include "../new/operator_new.h"
// #include "../new/operator_delete.h"

namespace zstd {

template <typename Tp>
zstd::pair<Tp*, zstd::ptrdiff_t>
get_temporary_buffer(zstd::ptrdiff_t len) noexcept {
  const zstd::ptrdiff_t max = 
    zstd::numeric_limits<zstd::ptrdiff_t>::max() / sizeof(Tp);
  if (len > max) {
    len = max;
  }
  while (len > 0) {
    // Tp* address = static_cast<Tp*>(::operator new(
    //               len * sizeof(Tp), zstd::nothrow));
    Tp* address = static_cast<Tp*>(::operator new(len * sizeof(Tp)));
    if (address) {
      return zstd::pair<Tp*, zstd::ptrdiff_t>(address, len);
    }
    len /= 2;
  }
  return zstd::pair<Tp*, zstd::ptrdiff_t>(static_cast<Tp*>(0), 0);
}

template <typename Tp>
inline void return_temporary_buffer(Tp* p) {
  // ::operator delete(p, zstd::nothrow);
  ::operator delete(p);
}

}  // namespace zstd

#endif  // ZSTD_INTERNAL_MEMORY_TEMPORARY_BUFFER_H_