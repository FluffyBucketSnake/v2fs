add_library(
    libv2fs STATIC
    src/dentry
    src/file.c 
    src/inode.c
    src/internal.c
    src/mount.c
    src/v2fs.c
    )

target_include_directories(libv2fs PUBLIC include)
target_include_directories(libv2fs PRIVATE src)