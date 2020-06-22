#include "inode.h"
#include "super.h"
#include <stdlib.h>

void ramfs_clear_inodes(struct ramfs_inode *inodes, int count) {
    unsigned int i;
    for (i = 0; i < count; i++) {
        (inodes++)->i_valid = 0;
    }
}

struct ramfs_inode *ramfs_new_inode(struct ramfs_sb_info *super) {
    unsigned int i;
    struct ramfs_inode *result;
    
    // Look for a free inode.
    for (i = 0; i < super->s_capacity; i++) {
        result = &super->s_inodes[i];

        if (!result->i_valid) {
            result->i_valid = 1;
            return result;
        }
    }

    // If there was none found, attempt to expand the table.
    super->s_inodes = realloc(super->s_inodes, super->s_capacity * 2);
    if (!super->s_inodes) {
        return 0;
    }
    ramfs_clear_inodes(super->s_inodes + i, super->s_capacity);
    super->s_capacity *= 2;

    // Return first new inode.
    super->s_inodes[i].i_valid = 1;
    return &super->s_inodes[i];
}