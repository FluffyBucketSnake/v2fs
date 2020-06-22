add_library(
    ramfs STATIC 
    src/dir.c
    src/file.c
    src/inode.c
    src/ramfs.c
    src/super.c
    )

target_link_libraries(ramfs PUBLIC libv2fs)

target_include_directories(ramfs PUBLIC include)
target_include_directories(ramfs PRIVATE src)