#include <v2fs.h>
#include <error.h>
#include <internal.h>

int v2fs_init() {

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

    root_super = fs->mount(0);
    root_super->s_root->d_name = "/";
}

void v2fs_close() {
    
}