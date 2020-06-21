add_library(ramfs src/ramfs.c)

target_link_libraries(ramfs libv2fs)

target_include_directories(ramfs PUBLIC include/)
target_include_directories(ramfs PRIVATE src/)