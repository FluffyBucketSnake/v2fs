#pragma once

#include <v2fs/types.h>

struct dentry;
struct file;
struct inode;
struct super_block;

//
// Holds the pointers for the implmentation of each inode method.
//
struct inode_operations
{
    // Create file on dentry.
    int (*create) (struct inode *self, struct dentry *dest);
    // Unlink inode from dentry.
    int (*unlink) (struct inode *self, struct dentry *dest);
    // Look for an inode associated with a directory entry.
    struct dentry *(*lookup)(struct inode *self, struct dentry *target);
    // Look for an inode associated with a directory entry.
    int (*mkdir)(struct inode *self, struct dentry *target);
};

//
// SEEK_SET: the offset of the file is set relative to the beggining of the file.
// SEEK_CUR: the offset of the file is set relative to its current position.
// SEEK_END: the offset of the file is set relative to the end of the file.
//
enum whence {
    VSEEK_SET,
    VSEEK_CUR,
    VSEEK_END
};

//
// Holds the pointers to the implementation-specific functions that operate over this
// file.
//
struct file_operations
{
    int (*seek)(struct file *self, long offset, int whence);
    int (*read)(struct file *self, char *buffer, int count);
    int (*write)(struct file *self, const char *buffer, int count);
};

struct inode {
    unsigned int i_ino;                     // Inode number.
    unsigned int i_count;                   // Reference count.
    const struct inode_operations *i_op;    // Inode operations.
    const struct file_operations *i_fop;    // File operations.
    struct super_block *i_sb;               // Filesystem in which this file belongs.
    void *i_info;                           // Filesystem-specific inode information.
};

struct inode *inew();

struct inode *iget(struct inode *ref);

void iput(struct inode *ref);