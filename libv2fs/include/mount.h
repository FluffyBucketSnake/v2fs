#pragma once

struct super_block;

//
// Holds the data of a file system type implementation, such as the mount function.
//
struct file_system_type {
    const char* name;                               // Unique identifier of file system type.
    super_block *(*mount) (void *data);             // Mounts a filesystem using the specified data 
    void (*kill_sb) (super_block *super_block);     // Umounts the specified file system.
};

//
// Registers the file system type into the V2FS library.
//
extern int register_filesystem(const struct file_system_type *fs);

//
// Unregisters the file system type from the V2FS library.
//
extern int unregister_filesystem(const struct file_system_type *fs);
