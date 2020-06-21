#include <mount.h>
#include <internal.h>
#include <error.h>
#include <string.h>

int register_filesystem(const struct file_system_type *fs) {
    // Check if name is valid.
    // 'name' must not be null.
    // 'name' must be longer than 1 character.
    if (!fs->name && !strlen(fs->name)) {
        return -EINVAL;
    }

    // Check if the file system type is available.
    // 'next' must be null
    if (fs->next) {
        return -EBUSY;
    }

    // If the list is uninitialized, set the fst as head and tail.
    if (!fs_type_head) {
        fs_type_tail = fs_type_head = fs;
    } 
    else {
        fs_type_tail->next = fs;
        fs_type_tail = fs;
    }

    // No error.
    return 0;
}