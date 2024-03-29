#include <stdio.h>
#include <string.h>
#include <v2fs/v2fs.h>
#include <ramfs.h>

int main() {
    //
    // Initialization.
    //

    // Initialize V2FS
    v2fs_init();

    // Init ramfs module.
    ramfs_init();
    
    // Mount the root filesystem.
    v2fs_mount_root("ramfs");

    //
    // Creating and writing to a file.
    //

    // Create file.
    fd_t fd = open("arquivo0");

    // Write to the file.
    const char text0[] = "Texto Aleatório.";
    write(fd, text0, strlen(text0), sizeof(char));

    // Close file.
    close(fd);

    //
    // Reading from a file
    //

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
    printf("%s\n", text1);

    // Close file.
    close(fd);

    //
    // Creating a folder and a file inside it.
    //

    // MaKe DIRectory.
    mkdir("pasta0");

    // Create and open a file inside the new directory.
    fd = open("pasta0/arquivo0");

    // Write some stuff inside it.
    const char text2[] = "Lorem Ipsum";
    write(fd, text2, strlen(text2), sizeof(char));
    
    // Close file.
    close(fd);

    //
    // Opening a file inside a directory.
    //

    // Open the file again.
    fd = open("pasta0/arquivo0");

    // Read the file
    i = 0;
    memset(text1, 0, 256);
    while (read(fd, &c, 1, sizeof(char)) > 0) {
        text1[i++] = c;
    }

    // Print contents.
    printf("%s\n", text1);

    // Close file.
    close(fd);

    //
    // Unitializing a file.
    //

    // Uninitialize the V2FS.
    v2fs_close();

    return 0;
}