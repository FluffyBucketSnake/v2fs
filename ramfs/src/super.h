#pragma once
#include "inode.h"

struct ramfs_sb_info {
    unsigned int s_capacity;
    struct ramfs_inode *s_inodes;
};

struct ramfs_sb_info *ramfs_make_sb_info();