#pragma once

#include <file.h>

//
// Initializes and setups the V2FS library. It's require to call this function before any
// other function of this library is called.
// Returns 0 on success, or -1 on failure and sets the global error variable accordingly.
//
int v2fs_init();

//
// Gets the error code stored in the error global variable.
//
int v2fs_get_error();

//
// Fetches the text of the specified error code.
//
const char *v2fs_get_error_text();