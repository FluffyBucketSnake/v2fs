#include "internal.h"

struct file_system_type *fs_type_head = 0;
struct file_system_type *fs_type_tail = 0;

size_t sbt_count = 0;
struct super_block super_block_table[MAX_SUPER_BLOCK] = { 0 };

struct dcache dcache = { 0 };

size_t ft_count = 0;
struct file file_table[MAX_FILE] = { 0 };

struct dentry *root_dentry = 0;
struct super_block *root_super = 0;