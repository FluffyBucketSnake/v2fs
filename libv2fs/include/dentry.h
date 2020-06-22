#pragma once

#include <types.h>
#include <inode.h>

//
// Represents a Directory Entry, which associates a filename with a inode, as well as
// holds the data associated with the directory entry itself and not the file.
//
struct dentry {
    const char *d_name;             // The filename of the directory entry.
    struct inode *d_inode;    // The associated inode.
    size_t d_count;           // The number of references to this dentry.
};

//
// Creates a new dentry.
//
struct dentry *dnew(const char *filename, struct inode *inode);

//
// Used when dentry pointer is copied to another variable. Increases the reference count
// of the dentry.
//
struct dentry *dget(struct dentry *dentry);

//
// Used when a dentry pointer is being disposed off. Decreases the reference count of the
// dentry and, if it reaches zero, frees it.
//
void *dput(struct dentry *dentry);