#include <v2fs/v2fs.h>
#include <v2fs/error.h>
#include <internal.h>

int v2fs_init() {
    // Placeholder function
}

int v2fs_mount_root(const char *fs_name) {
    if (root_super) {
        return -EBUSY;
    }

    if (!fs_name) {
        return -EINVAL;
    }

    const struct file_system_type *fs = find_filesystem(fs_name);

    if (!fs) {
        return -ENOTFOUND;
    }

    // TODO: Replace with a function that finds a open slot in the table.
    super_block_table[sbt_count++] = fs->mount(0);
    root_super = super_block_table + sbt_count - 1;
    root_super->s_root->d_name = "/";

    // Update super block of the new inode.
    root_super->s_root->d_inode->i_sb = root_super;
}

void v2fs_close() {
    // !!!TODO!!! Clean mounted partitions.
}