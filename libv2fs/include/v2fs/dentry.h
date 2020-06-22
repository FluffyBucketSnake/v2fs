#pragma once

#include <v2fs/types.h>
#include <v2fs/inode.h>

//
// A linked list node of dentry hashmap.
//
struct dentry_hm_node {
    struct dentry *next;
    struct dentry **pprev;
};

//
// Represents a Directory Entry, which associates a filename with a inode, as well as
// holds the data associated with the directory entry itself and not the file.
//
struct dentry {
    const char *d_name;                 // The filename of the directory entry.
    struct inode *d_inode;              // The associated inode.
    size_t d_count;                     // The number of references to this dentry.
    struct dentry *d_parent;            // The parent of this dentry.
    struct dentry_hm_node d_hash;      // Points to the next node of the hash list.
};

#define DC_BUCKETC 16

//
// A hash table of dentries, used to accelerate lookup operations.
//
struct dcache{
    struct dentry *buckets[DC_BUCKETC];
};

//
// Creates a new dentry.
//
struct dentry *dnew(const char *filename, struct dentry *parent);

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

//
// Look for dentry with the specified filename in the sent dentry.
//
struct dentry *dlookup(struct dentry *self, const char *filename);

//
// Creates a hash value for the specified filename.
//
hash_t dhash(const char *str);

//
// Data structure used for pathname traversal.
//
struct nameidata {
    struct dentry *parent;
    struct dentry *current;
};

//
// Look for the dentry associated with the specified pathname.
//
int path_lookup(const char *pathname, struct nameidata *nd);