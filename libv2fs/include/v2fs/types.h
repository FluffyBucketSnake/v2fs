#pragma once

//
// Short for file descriptor handle. It's an index to the open files table of an user.
// Used to identify which is being operated on.
//
typedef int fd_t;

//
// Used for array counting and indexing.
//
typedef unsigned long size_t;

//
// Represents a offset amount.
//
typedef long off_t;

//
// Represents an inode number.
//
typedef unsigned long ino_t;