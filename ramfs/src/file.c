#include "file.h"
#include <stdlib.h>

void ramfs_file_init(struct ramfs_file *self) {
    // !!!TODO!!! : Add test for malloc failure.
    self->f_size = 256;
    self->f_data = malloc(sizeof(unsigned char) * 256);
}