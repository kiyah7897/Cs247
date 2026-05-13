#ifndef SMALLMALLOC_H
#define SMALLMALLOC_H

#include <stddef.h>

// Small malloc enforces that your size for dynamic memory
// allocation does not exceed MAXPERMISSIBLESIZE
#define MAXPERMISSIBLESIZE      256
void* smallmalloc(size_t size);

#endif // SMALLMALLOC_H
