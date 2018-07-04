#pragma once

/* you must call free() on .data member of 
an UserData structure returned by diskarray_* functions */
#include "UserData.h"

#ifdef __cplusplus
#include <cstdint>
#include <cstdlib>
extern "C" {
#else
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#endif

typedef struct _DiskArray DiskArray;

/* since the underlying data structure is dbm UINT32_MAX is accessible
however you shouldn't use so diskarray_max_elements() return UINT32_MAX-1 */
uint32_t diskarray_max_elements();

/* open/create a diskarray with 0600 permission */
DiskArray * diskarray_open(const char *file);
bool diskarray_insert(DiskArray *s, uint32_t at, UserData data);
UserData diskarray_access(DiskArray *s, uint32_t at);
UserData diskarray_remove(DiskArray *s, uint32_t at);

void diskarray_close(DiskArray *vct);

#ifdef __cplusplus
}
#endif
