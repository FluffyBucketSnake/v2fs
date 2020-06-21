#include "dir.h"
#include <stdlib.h>
#include <string.h>

unsigned long ramfs_hash(const unsigned char *str)
{
    // Currently based on djb2 string hash algorithm.
    // Lookup to: http://www.cse.yorku.ca/~oz/hash.html
    unsigned long hash = 5381;
    int c;

    while (c = *(str++))
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return hash;
}

void ramfs_dir_bucket_init(struct ramfs_directory_bucket *self)
{
    self->b_count = 0;
    self->b_capacity = 16;
    self->b_dentries = malloc(sizeof(struct ramfs_dentry) * 16);
}

struct ramfs_dentry *ramfs_dir_bucket_find(struct ramfs_directory_bucket *self,
                                           const char *filename)
{
    unsigned int i;
    for (i = 0; i < self->b_count; i++)
    {
        if (strcmp(filename, self->b_dentries[i].d_name) == 0)
        {
            return &self->b_dentries[i];
        }
    }

    return 0;
}

void ramfs_dir_bucket_add(struct ramfs_directory_bucket *self, const char *filename,
                          struct ramfs_inode *inode)
{
    // Check capacity. If full, expand bucket.
    if (self->b_count == self->b_capacity)
    {
        self->b_capacity *= 2;
        self->b_dentries = realloc(self->b_dentries, self->b_capacity);
    }

    struct ramfs_dentry *new = &self->b_dentries[self->b_count++];
    new->d_name = filename;
    new->d_inode = inode;
}

void ramfs_dir_init(struct ramfs_directory *self)
{
    unsigned int i;

    self->d_bucketc = 16;
    self->d_buckets = malloc(sizeof(struct ramfs_directory_bucket) * 16);

    for (i = 0; i < 16; i++)
        ramfs_dir_bucket_init(self->d_buckets + i);
}

struct ramfs_dentry *ramfs_dir_lookup(struct ramfs_directory *self, const char *filename)
{
    // Get filename hash.
    unsigned long hash = ramfs_hash(filename);

    // Find bucket.
    unsigned int bucket = hash % self->d_bucketc;

    // Attempt to find entry.
    return ramfs_dir_bucket_find(&self->d_buckets[bucket], filename);
}

void ramfs_dir_add(struct ramfs_directory *self, const char *filename,
                   struct ramfs_inode *inode)
{
    // Get filename hash.
    unsigned long hash = ramfs_hash(filename);

    // Find bucket.
    unsigned int bucket = hash % self->d_bucketc;

    // Add dentry into the bucket.
    ramfs_dir_bucket_add(&self->d_buckets[bucket], filename, inode);
}