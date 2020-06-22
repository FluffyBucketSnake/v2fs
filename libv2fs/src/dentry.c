#include <v2fs/dentry.h>
#include <v2fs/error.h>
#include <stdlib.h>
#include <string.h>
#include "internal.h"

struct dentry *dnew(const char *filename, struct dentry *parent) {
    // Allocate the new dentry.
    struct dentry *new = malloc(sizeof(struct dentry));
    new->d_name = filename;
    new->d_count = 1;
    new->d_hash.next = 0;
    new->d_hash.pprev = 0;

    if (parent) {
        // Connect the new dentry with its parent.
        new->d_parent = dget(parent);

        // Register the dentry on the dcache. Only necessary if the dentry is not root.
        // Get the dentry hash.
        hash_t hash = dhash(filename);

        // Get the bucket index.
        size_t i = hash % DC_BUCKETC;

        // Add the dentry to the head of the dcache bucket.
        new->d_hash.next = dcache.buckets[i];
        if (dcache.buckets[i]) 
            dcache.buckets[i]->d_hash.pprev = &new->d_hash.next;
        dcache.buckets[i] = new;
    }
    else {
        // This is a root dentry.
        new->d_parent = new;
    }

    return new;
}

struct dentry *dget(struct dentry *dentry) {
    dentry->d_count++;
    return dentry;
}

void *dput(struct dentry *dentry) {
    --dentry->d_count;
    return dentry;
}


static struct dentry *dcache_lookup(struct dentry *parent, const char *filename) {
    // Compute filename hash.
    hash_t hash = dhash(filename);

    // Get bucket index.
    size_t bucket_i = hash % DC_BUCKETC;

    // Attempt to find the dentry in the dcache.
    struct dentry *cur = dcache.buckets[bucket_i];
    while (cur) {
        if ((cur->d_parent == parent) && strcmp(cur->d_name, filename) == 0) {
            return dget(cur);
        }

        cur = cur->d_hash.next;
    }

    return 0;
}

struct dentry *dlookup(struct dentry *self, const char *filename) {
    struct dentry *target = dcache_lookup(self, filename);

    if (!target) {
        target = dnew(filename, self);
    }

    struct dentry *(*lookup)(struct inode *, struct dentry *) = self->d_inode->i_op->lookup;

    if (!lookup) {
        return 0;
    }
    else {
        lookup(self->d_inode, target);
        if (target->d_inode)
            target->d_inode->i_sb = self->d_inode->i_sb;
        return target;
    }
}

hash_t dhash(const char *str) {
    // Currently based on djb2 string hash algorithm.
    // Lookup to: http://www.cse.yorku.ca/~oz/hash.html
    unsigned long hash = 5381;
    int c;

    while (c = *(str++))
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return hash;
}

int path_lookup(const char *pathname, struct nameidata *nd) {
    size_t len;

    // Initialize traversal data.
    nd->current = dget(root_super->s_root);
    nd->parent = dget(root_super->s_root);
    
    // Ignore all initial '/'.
    while (*pathname == '/') {
        pathname++;
    }

    for (;;) {
        // Check if we reached the end of the pathname.
        if (!*pathname) {
            return 0;
        }

        // !!!TODO!!! Check for '.' and '..' filenames.

        // Get the length of the current filename.
        len = 0;
        while (*pathname != '/' && *pathname) {
            pathname++;
            len++;
        }

        // Make new filename string for dentry.
        // !!!TODO!!! Solve memory leak.
        char *filename = malloc(sizeof(char) * (len + 1));
        memcpy(filename, pathname - len, len);
        filename[len] = '\0';

        // Look for the new dentry.
        dput(nd->parent);
        nd->parent = nd->current;
        nd->current = dlookup(nd->current, filename);
        
        // Ignore all trailling '/'.
        while (*pathname == '/') {
            pathname++;
        }

        // See if dentry is negative.
        if (!nd->current->d_inode) {
            // Check if we reached the last component.
            if (*pathname) {
                return -ENOTFOUND;
            }

            // We reached the end.
            return 0;
        }
    }
}