#include <stdlib.h>
#include <assert.h>
#include "smallmalloc.h"


void* smallmalloc(size_t size) {
    assert(size < MAXPERMISSIBLESIZE);
    return malloc(size);
}
