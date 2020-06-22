add_executable(sample_basic basic.c)

target_link_libraries(sample_basic PUBLIC libv2fs)
target_link_libraries(sample_basic PUBLIC ramfs)