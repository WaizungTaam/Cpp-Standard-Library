// #ifndef ZSTD_INTERNAL_NEW_OPERATOR_NEW_H_
// #define ZSTD_INTERNAL_NEW_OPERATOR_NEW_H_

// #include "nothrow.h"

// #include "../cstddef/cstddef.h"


// extern "C" void* malloc (zstd::size_t);

// __attribute__ ((weak))
// void* operator new(zstd::size_t size, const zstd::nothrow_t&) noexcept {
//   void* p;
//   if (size == 0) size = 1;
//   p = (void*) malloc (size);
//   // TODO
//   return p;
// }

// #endif  // ZSTD_INTERNAL_NEW_OPERATOR_NEW_H_
