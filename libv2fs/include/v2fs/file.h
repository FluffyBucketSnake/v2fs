#pragma once

#include <v2fs/types.h>
#include <v2fs/dentry.h>
#include <v2fs/inode.h>

struct file_operations;

//
// Represents a open file to a user. Holds the data to the access mode and another
// information needed to read/write the file.
//
struct file {
    size_t f_count;                             // Reference count.
    struct dentry *f_dentry;                    // Dentry used to open file.
    const struct file_operations *f_op;         // File operations.
    off_t f_off;                                // Read/writer pointer.
};

//
// Builds a new file object from the file descriptor.
//
struct file *fnew(fd_t fd);

//
// Gets file from file descriptor.
//
struct file *fget(fd_t fd);

//
// Frees file object reference and reduces the struct's refcount.
//
struct file *fput(struct file *file);

//
// Open file: opens a file in the specified path.
// Returns: if successeful, a valid file descriptor pointer. If not, returns -1 and sets
// the error global appropriately.
//
fd_t open(const char *pathname);

//
// Close file: closes a file descriptor.
// Returns: returns 0 on successeful. On error, returns -1 and sets the error global
// variable.
//
int close(fd_t fd);

//
// Make directory: creates a new directory
// Returns: returns 0 on success. On error, returns -1 and sets the error global
// variable.
//
int mkdir(const char *pathname);

//
// Read from file: reads a number of bytes of a file and stores it in the specified
// buffer.
// Returns: if the operation was successful, the a positive integer representing the 
// number of bytes read. Otherwise, returns -1.
//
int read(fd_t fd, void *buffer, int count, int size);

//
// Write into file: writes a number of bytes into a file from the given buffer.
// Returns: if the operation was successful, the a positive integer representing the 
// number of bytes written. Otherwise, returns -1.
//
int write(fd_t fd, const void *buffer, int count, int size);

//
// Seek file: sets the position of the read/write position of the file descriptor.
// If successeful, the resulting offset location, measured in bytes, relative to the
// beginning of the file. Otherwise, returns (off_t)-1.
//
long seek(fd_t fd, long offset, int whence);