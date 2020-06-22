#pragma once

#include <types.h>
#include <dentry.h>
#include <inode.h>

struct file_operations;

//
// Represents a open file to a user. Holds the data to the access mode and another
// information needed to read/write the file.
//
struct file {
    struct dentry *f_dentry;
    const struct file_operations *f_op;
    struct inode *f_inode;
    off_t f_off;
};

//
// Get file from file descriptor.
//
struct file *fget(fd_t fd);

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