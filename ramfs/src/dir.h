#pragma once

struct ramfs_inode;

struct ramfs_dentry
{
    char *d_name;
    struct ramfs_inode *d_inode;
};

struct ramfs_directory_bucket
{
    unsigned int b_count;
    unsigned int b_capacity;
    struct ramfs_dentry *b_dentries;
};

struct ramfs_directory
{
    unsigned int d_bucketc;
    struct ramfs_directory_bucket *d_buckets;
};

unsigned long ramfs_hash(const unsigned char *str);

void ramfs_dir_bucket_init(struct ramfs_directory_bucket *self);
struct ramfs_dentry *ramfs_dir_bucket_find(struct ramfs_directory_bucket *self,
                                           const char *filename);
void ramfs_dir_bucket_add(struct ramfs_directory_bucket *self, const char *filename,
                          struct ramfs_inode *inode);

void ramfs_dir_init(struct ramfs_directory *self);
struct ramfs_dentry *ramfs_dir_lookup(struct ramfs_directory *self, const char *filename);
void ramfs_dir_add(struct ramfs_directory *self, const char *filename, struct ramfs_inode *inode);