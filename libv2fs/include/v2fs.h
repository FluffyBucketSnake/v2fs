#pragma once

#include "mount.h"
#include "super.h"
#include "dentry.h"
#include "inode.h"
#include "file.h"
#include "types.h"

#define MAX_SUPER_BLOCK 32
#define MAX_FILE 32

//
// Initializes and setups the V2FS library. It's require to call this function before any
// other function of this library is called.
// Returns 0 on success, or -1 on failure and sets the global error variable accordingly.
//
int v2fs_init();

//
// Mounts the root filesystem.
// fs_name: the root's file system type identifier.
// Returns 0 on success, or -1 on failure and sets the global error variable accordingly.
//
int v2fs_mount_root(const char *fs_name);

//
// Uninitializes the V2FS library.
//
void v2fs_close();