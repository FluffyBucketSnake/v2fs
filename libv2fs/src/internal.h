#pragma once

#include <v2fs/v2fs.h>

//
// Represents the head of the linked list of the registered file system types.
//
extern struct file_system_type *fs_type_head;

//
// Represents the tail of the linked list of the registered file system types.
//
extern struct file_system_type *fs_type_tail;

//
// Holds the amount of open super blocks in the super block table.
//
extern size_t sbt_count;

//
// A table holding all open super blocks within the V2FS.
//
extern struct super_block super_block_table[MAX_SUPER_BLOCK];

#define DC_BUCKETC 16

//
// A hash table of dentries, used to accelerate lookup operations.
//
extern struct dcache dcache;

//
// Holds the amount of open files in the file table.
//
extern size_t ft_count;

//
// Holds the data of all open files inside the V2FS library.
//
extern struct file file_table[];

//
// Holds the data of the mounted root filesystem.
//
extern struct super_block *root_super;