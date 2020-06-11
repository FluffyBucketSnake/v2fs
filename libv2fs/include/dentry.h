#pragma once

#include <inode.h>

//
// Represents a Directory Entry, which associates a filename with a inode, as well as
// holds the data associated with the directory entry itself and not the file.
//
struct dentry {
    const char *d_name;     // The filename of the directory entry.
    const inode *d_inode;   // The associated inode.
};