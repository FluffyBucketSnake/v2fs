#include <ramfs.h>
#include <super.h>
#include <error.h>
#include <stdlib.h>
#include <string.h>
#include "super.h"

static struct dentry *ramfs_make_root(struct ramfs_sb_info *super) {
    struct ramfs_inode *root_ri = ramfs_new_inode(super);
    root_ri->i_mode = RFM_DIR;
    
    struct inode * root_i = inew();
    root_i->i_info = root_ri;
    root_i->i_op = &ramfs_dir_inode_operations;
    root_i->i_fop = &ramfs_dir_operations;

    return dnew(0, root_i);
}

struct super_block ramfs_mount(void *data) {
    struct super_block result;

    // Set metadata.
    result.s_fs = &ramfs_file_system_type;
    
    // Create inode table.
    result.s_info = ramfs_make_sb_info();

    // Create root inode.
    result.s_root = ramfs_make_root(result.s_info);

    return result;
}

int ramfs_inode_create(struct inode *self, struct dentry *dest) {
    if (!self || !dest) {
        return -EINVAL;
    }

    struct ramfs_inode *info = self->i_info;

    // Check if inode is a directory.
    if (info->i_mode != RFM_DIR) {
        return -ENOTDIR;
    }
    struct ramfs_directory *dir = &info->i_dir;

    // Check if there's already a file with the same name.
    if (!ramfs_dir_lookup(dir, dest->d_name)) {
        return -EEXISTS;
    }

    // Create a new file inode.
    struct ramfs_inode *new_ri = ramfs_new_inode(self->i_sb);
    new_ri->i_mode = RFM_FILE;
    ramfs_file_init(&new_ri->i_file);

    struct inode *new_i = inew();
    new_i->i_info = new_ri;
    new_i->i_op = &ramfs_file_inode_operations;
    new_i->i_fop = &ramfs_file_operations;

    // Fill dentry.
    dest->d_inode = new_i;

    return 0;
}

int ramfs_file_write(struct file *self, char *buffer, int count) {
    // Get file inode.
    struct ramfs_inode *inode = &self->f_inode->i_info;
    struct ramfs_file *info = &inode->i_file;

    // Check current file size.
    if (self->f_off + count > info->f_size) {
        // Expand file.
        info->f_data = realloc(info->f_data, self->f_off + count);
    }

    // Copy characters from one buffer to another.
    memcpy(info->f_data + self->f_off, buffer, count);

    // Update f_off.
    self->f_off += count;

    // Return success.
    return 0;
}

int ramfs_file_read(struct file *self, char *buffer, int count) {
    size_t start;

    // Get file inode.
    struct ramfs_inode *inode = &self->f_inode->i_info;
    struct ramfs_file *info = &inode->i_file;

    // Limit count
    start = self->f_off;
    count = (count < info->f_size - start) ? count : info->f_size - start;

    // Read file until EOF.
    if (count > 0) {
        memcpy(buffer, info->f_data + start, count);
        return count;
    }
    else {
        return 0;
    }
}