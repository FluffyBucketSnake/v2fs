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

struct file *fnew(fd_t fd) 
{
    struct file *file = &file_table[fd];

    if (!file->f_count) {
        file->f_count++;
        file->f_off = 0;
        file->f_op = 0;
        file->f_dentry = 0;

        return file;
    }
    else {
        return 0;
    }
}

struct file *fget(fd_t fd)
{
    struct file *file = &file_table[fd];

    if (file->f_count) {
        file->f_count++;
        return file;
    }
    else {
        return 0;
    }
}

struct file *fput(struct file *file) {
    if (!(--file->f_count)) {
        if (file->f_dentry) {
            dput(file->f_dentry);
        }
    }

    return 0;
}

fd_t open(const char *pathname)
{
    int err;

    if (!root_super)
    {
        return -1;
    }

    fd_t fd = fd_get_free();
    struct file *file = fnew(fd);

    struct nameidata nd;

    // Search for pathname.
    err = path_lookup(pathname, &nd);
    if (err) {
        return err;
    }

    // Test for negative dentry.
    if (!nd.current->d_inode)
    {
        // Create new file.
        int (*create)(struct inode *, struct dentry *) = nd.parent->d_inode->i_op->create;

        if (!create) {
            fput(file);
            return -1;
        }

        err = create(nd.parent->d_inode, nd.current);

        if (err) {
            fput(file);
            return err;
        }
    }
    
    file->f_dentry = nd.current;
    file->f_op = nd.current->d_inode->i_fop;
    file->f_dentry->d_inode->i_sb = nd.parent->d_inode->i_sb;

    return fd;
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
        fput(file);

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
        fput(file);
        return -1;
    }
    else
    {
        fput(file);
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
        fput(file);
        return -1;
    }
    else
    {
        fput(file);
        return write(file, buffer, count * size);
    }
}