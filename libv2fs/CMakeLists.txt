add_library(
    libv2fs
    src/file.c 
    src/mount.c
    "src/internal.c"
    src/v2fs.c
    )

target_include_directories(libv2fs PUBLIC include/file)
target_include_directories(libv2fs PRIVATE src/file)