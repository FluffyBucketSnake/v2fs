#pragma once
#include "file.h"
#include "dir.h"

struct ramfs_sb_info;

enum ramfs_file_mode {
    RFM_FILE,
    RFM_DIR
};

struct ramfs_inode {
    unsigned char i_valid;
    unsigned int i_mode;
    union
    {
        struct ramfs_directory i_dir;
        struct ramfs_file i_file;
    };
};

void ramfs_clear_inodes(struct ramfs_inode *inodes, int count);

struct ramfs_inode *ramfs_new_inode(struct ramfs_sb_info *super);