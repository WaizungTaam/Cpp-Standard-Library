// #ifndef ZSTD_INTERNAL_NEW_OPERATOR_DELETE_H_
// #define ZSTD_INTERNAL_NEW_OPERATOR_DELETE_H_

// #include "nothrow.h"


// extern "C" void free(void*);

// __attribute__ ((weak))
// void operator delete(void* p, const zstd::nothrow_t&) noexcept {
//   free(p);
// }

// #endif  // ZSTD_INTERNAL_NEW_OPERATOR_DELETE_H_
