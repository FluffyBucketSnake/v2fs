#pragma once

struct ramfs_file {
    unsigned int f_size;
    unsigned char *f_data;
};

void ramfs_file_init(struct ramfs_file *self);