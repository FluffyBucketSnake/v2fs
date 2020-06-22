#include <v2fs/mount.h>
#include <v2fs/error.h>
#include "internal.h"
#include <string.h>

int register_filesystem(struct file_system_type *fs) {
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

// !TODO: Add error codes.
const struct file_system_type *find_filesystem(const char *name) {
    if (!name) {
        return 0;
    }

    const struct file_system_type *cur = fs_type_head;
    while (cur) {
        // Compare names.
        if (strcmp(name, cur->name) == 0) {
            return cur;
        }

        // Check next.
        cur = cur->next;
    }

    return 0;
}