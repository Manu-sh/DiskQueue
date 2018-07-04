#pragma once

/* you must call free() on .data member of 
an UserData structure returned by diskqueue_* functions */
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

typedef struct _DiskQueue DiskQueue;
uint32_t diskqueue_max_elements();

DiskQueue * diskqueue_open(const char *file);

/* you must always call diskqueue_empty() before diskqueue_front()
or diskqueue_pop() */

bool diskqueue_empty(DiskQueue *queue);
UserData diskqueue_front(DiskQueue *queue);
bool diskqueue_push(DiskQueue *queue, UserData data);
UserData diskqueue_pop(DiskQueue *queue);
void diskqueue_close(DiskQueue *queue);

#ifdef __cplusplus
}
#endif
