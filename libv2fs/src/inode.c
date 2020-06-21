#include <inode.h>
#include <stdlib.h>

struct inode *inew(const struct inode_operations *op) {
    struct inode *new = malloc(sizeof(struct inode));

    new->i_count = 1;
    new->i_info = 0;
    new->i_op = op;

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