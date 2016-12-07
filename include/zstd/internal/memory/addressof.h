#ifndef ZSTD_INTERNAL_MEMORY_ADDRESSOF_H_
#define ZSTD_INTERNAL_MEMORY_ADDRESSOF_H_

namespace zstd {

template <typename Tp>
inline Tp* addressof(Tp& r) noexcept {
  return reinterpret_cast<Tp*>(&const_cast<char&>(
         reinterpret_cast<const volatile char&>(r)));
}

template <typename Tp>
const Tp* addressof(const Tp&&) = delete;

}  // namespace zstd

#endif  // ZSTD_INTERNAL_MEMORY_ADDRESSOF_H_