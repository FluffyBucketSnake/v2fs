#include <v2fs/inode.h>
#include <stdlib.h>

struct inode *inew(struct super_block *sb) {
    struct inode *new = malloc(sizeof(struct inode));

    new->i_count = 1;
    new->i_info = 0;
    new->i_op = 0;
    new->i_fop = 0;
    new->i_sb = sb;

    return new;
}

struct inode *iget(struct inode *ref) {
    ref->i_count++;
    return ref;
}

void iput(struct inode *ref) {
    if (!(--ref->i_count)) {
        free(ref);
    }
}