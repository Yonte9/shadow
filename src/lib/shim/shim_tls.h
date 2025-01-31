#ifndef SHIM_TLS_H_
#define SHIM_TLS_H_

#include "lib/shim/shim_api.h"

// Return a pointer to a native thread-local instance of
// `ShimThreadLocalStorage`. The full implementation (in Rust), uses this as a
// backing store when native thread local storage is available.
ShimThreadLocalStorage* shim_native_tls();

#endif