#ifndef SHD_SHIM_SHIM_H_
#define SHD_SHIM_SHIM_H_

#include <stdatomic.h>
#include <sys/types.h>
#include <sys/ucontext.h>

#include "lib/shadow-shim-helper-rs/shim_helper.h"
#include "lib/shmem/shmem_allocator.h"
#include "main/core/support/definitions.h"

// Ensures that the shim is initialized for the current thread. Ok and cheap to
// call again. Any syscalls made by a process before this is called will not be
// intercepted.
//
// This currently gets called from "public" entry points (`shim_api.h`),
// which themselves are called from:
// * `libshadow_injector`'s global constructor.
// * `libshadow_libc`'s syscall wrappers.
void shim_ensure_init();

// To be called in parent thread before making the `clone` syscall.
// It sets up data for the new thread.
void shim_newThreadStart(const ShMemBlockSerialized* block);

// To be called in parent thread after making the `clone` syscall.
// It doesn't return until after the child has initialized itself.
void shim_newThreadFinish();

// To be called from a new *child* thread after clone, to notify
// the parent thread that it is now initialized.
void shim_newThreadChildInitd();

const ShimShmemThread* shim_threadSharedMem();
const ShimShmemProcess* shim_processSharedMem();
const ShimShmemHost* shim_hostSharedMem();
const ShimShmemManager* shim_managerSharedMem();

// Exposed for Rust
void _shim_parent_init_preload();
void _shim_child_init_preload();
#endif // SHD_SHIM_SHIM_H_
