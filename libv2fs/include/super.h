#pragma once

#include <mount.h>

//
// Represents a mounted file system and holds the data and operations necessary to
// operate the file system directly.
//
struct super_block
{
    const struct file_system_type *s_fs;    // The file system type.
    void *s_info;                           // File system implementation specific data.
};