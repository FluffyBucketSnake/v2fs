#include <mount.h>
#include <file.h>

struct super_block ramfs_mount(void *data);

const struct file_system_type ramfs_file_system_type = {
    .name = "ramfs",
    .mount = ramfs_mount
};

int ramfs_inode_create(struct inode *self, struct dentry *dest);
struct dentry *ramfs_inode_lookup(struct inode *self, struct dentry *dest);

int ramfs_file_write(struct file *self, char *buffer, int count);
int ramfs_file_read(struct file *self, char *buffer, int count);

const struct inode_operations ramfs_file_inode_operations = { 
    .create = 0,
    .lookup = 0
};
const struct inode_operations ramfs_dir_inode_operations = { 
    .create = ramfs_inode_create,
    .lookup = ramfs_inode_lookup
};

const struct file_operations ramfs_file_operations = {
    .write = ramfs_file_write,
    .read = ramfs_file_read
};
const struct file_operations ramfs_dir_operations = {
    .write = 0,
    .read = 0
};