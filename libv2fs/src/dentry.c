#include <dentry.h>
#include <stdlib.h>

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