#include <stdio.h>
#include <string.h>
#include <v2fs.h>
#include <ramfs.h>

int main() {
    // Initialize V2FS
    v2fs_init();

    // Init ramfs module.
    ramfs_init();

    // Mount the root filesystem.
    v2fs_mount_root("ramfs");

    // Create file.
    fd_t fd = open("arquivo0");

    // Write to the file.
    const char text0[] = "Texto Aleatório.";
    write(fd, text0, strlen(text0), sizeof(char));

    // Close file.
    close(fd);

    // Open the file again.
    fd = open("arquivo0");

    // Read the file
    int i = 0;
    char c;
    char text1[256];
    memset(text1, 0, 256);
    while (read(fd, &c, 1, sizeof(char)) > 0) {
        text1[i++] = c;
    }

    // Print contents.
    printf("%s", text1);

    // Close file.
    close(fd);

    // Uninitialize the V2FS.
    v2fs_close();

    return 0;
}