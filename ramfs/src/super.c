#include "super.h"
#include <stdlib.h>

struct ramfs_sb_info *ramfs_make_sb_info() {
    struct ramfs_sb_info *new;
    new = malloc(sizeof(struct ramfs_sb_info));
    new->s_capacity = 16;
    new->s_inodes = malloc(sizeof(struct ramfs_inode) * 16);
    ramfs_clear_inodes(new->s_inodes, 16);
    return new;
}