#include <dentry.h>
#include <stdlib.h>
#include <string.h>
#include "internal.h"
#include <error.h>

struct dentry *dnew(const char *filename, struct inode *inode) {
    struct dentry *new = malloc(sizeof(struct dentry));
    new->d_name = filename;
    new->d_inode = inode;
    new->d_count;
    return new;
}

struct dentry *dget(struct dentry *dentry) {
    dentry->d_count++;
    return dentry;
}

void *dput(struct dentry *dentry) {
    if ((--dentry->d_count) == 0) {
        if (dentry->d_inode)
            iput(dentry->d_inode);

        free(dentry);
    }
    return dentry;
}

struct dentry *dlookup(struct dentry *self, const char *filename) {
    struct dentry *target = dnew(filename, 0);

    struct dentry *(*lookup)(struct inode *, struct dentry *) = self->d_inode->i_op->lookup;

    if (!lookup) {
        return 0;
    }
    else {
        return lookup(self->d_inode, target);
    }
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