#pragma once

struct super_block;

//
// Holds the data of a file system type implementation, such as the mount function.
//
struct file_system_type {
    const char* name;                                       // Unique identifier of file system type.
    struct super_block (*mount) (void *data);               // Mounts a filesystem using the specified data 
    void (*kill_sb) (struct super_block *super_block);      // Umounts the specified file system.
    struct file_system_type *next;                          // Holds the pointer to the next registered entry.
};

//
// Registers the file system type into the V2FS library.
//
int register_filesystem(struct file_system_type *fs);

//
// Finds the filesystem with the specified name.
//
const struct file_system_type *find_filesystem(const char *name);

//
// Unregisters the file system type from the V2FS library.
//
// int uregister_filesystem(const struct file_system_type *fs);
