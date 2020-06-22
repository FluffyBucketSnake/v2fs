#include <file.h>
#include "internal.h"

unsigned int open_files = 0;

//
// Looks for a free file descriptor.
//
static fd_t fd_get_free()
{
    fd_t i;

    for (i = 0; i < MAX_FILE; i++)
    {
        if (!file_table[i].f_dentry)
        {
            return i;
        }
    }

    return -1;
}

struct file *fget(fd_t fd)
{
    struct file *file = &file_table[fd];

    return (!file->f_dentry) ? 0 : file;
}

fd_t open(const char *pathname)
{
    if (!root_super)
    {
        return -1;
    }

    struct dentry *parent = root_super->s_root;
    struct dentry *current = parent;
    struct dentry *(*lookup)(struct inode *, struct dentry *) = current->d_inode->i_op->lookup;
    struct dentry *target = dnew(pathname, 0);
    fd_t fd = fd_get_free();
    struct file *file = &file_table[fd];

    // Search for pathname.
    if ((current = lookup(current->d_inode, target)))
    {
        file->f_dentry = current;
        file->f_inode = current->d_inode;
        file->f_op = current->d_inode->i_fop;

        return fd;
    }
    else {
        // Create new file.
        int (*create)(struct inode *, struct dentry *) = parent->d_inode->i_op->create;

        if (!create) {
            return -1;
        }

        if (create(parent->d_inode, target) == 0) {
            file->f_dentry = target;
            file->f_inode = target->d_inode;
            file->f_op = target->d_inode->i_fop;
            file->f_inode->i_sb = parent->d_inode->i_sb;

            return fd;
        }

        return -1;
    }
}

int close(fd_t fd)
{
    struct file *file = fget(fd);

    if (!file)
    {
        return -1;
    }
    else
    {
        dput(file->f_dentry);
        file->f_dentry = 0;
        file->f_inode = 0;
        file->f_off = 0;
        file->f_op = 0;

        return 0;
    }
}

int read(fd_t fd, void *buffer, int count, int size)
{
    if (!buffer || count < 0 || size < 1) {
        return -1;
    }

    struct file *file = fget(fd);

    if (!file)
    {
        return -1;
    }

    int (*read)(struct file *, char *, int) = file->f_op->read;

    if (!read)
    {
        return -1;
    }
    else
    {
        return read(file, buffer, count * size);
    }
}

int write(fd_t fd, const void *buffer, int count, int size)
{
    if (!buffer || count < 0 || size < 1) {
        return -1;
    }

    struct file *file = fget(fd);

    if (!file)
    {
        return -1;
    }

    int (*write)(struct file *, const char *, int) = file->f_op->write;

    if (!write)
    {
        return -1;
    }
    else
    {
        return write(file, buffer, count * size);
    }
}