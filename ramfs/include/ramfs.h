#pragma once

#include <v2fs.h>

struct super_block ramfs_mount(void *data);

int ramfs_inode_create(struct inode *self, struct dentry *dest);
struct dentry *ramfs_inode_lookup(struct inode *self, struct dentry *dest);

int ramfs_file_write(struct file *self, const char *buffer, int count);
int ramfs_file_read(struct file *self, char *buffer, int count);

int ramfs_init();