#pragma once

//
// Holds the pointers for the implmentation of each inode method.
//
struct inode_operations
{
    // Create file on dentry.
    int (*create) (struct inode *self, struct dentry *dest);
    // Unlink inode from dentry.
    int (*unlink) (struct inode *self, struct dentry *dest);
};


struct inode {
    unsigned int *i_count;          // The number of dentries referencing this inode.
    const inode_operations *i_op;   // Inode operations.
    void *i_info;                   // Filesystem-specific inode information.
};