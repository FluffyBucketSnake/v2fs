add_library(libv2fs src/file.c)

target_include_directories(libv2fs PUBLIC include/file)
target_include_directories(libv2fs PRIVATE src/file)