#include "DiskArray.h"
#include "DiskQueue.h"

#include <assert.h>
#include <stdlib.h>

typedef struct {
	uint32_t front;
	uint32_t back;
} PairIndex;

struct _DiskQueue {
	DiskArray *array;
	PairIndex idx;
};


uint32_t diskqueue_max_elements() {
	return UINT32_MAX-1;
}

/* handle overflow: the slot 0 is reserved */
static inline uint32_t next(uint32_t i) {
	return (i % diskqueue_max_elements()) + 1;
}

DiskQueue * diskqueue_open(const char *file) {

	DiskQueue *queue;

	if (!(queue = calloc(1, sizeof(DiskQueue))))
		return NULL;

	if (!(queue->array = diskarray_open(file))) {
		free(queue);
		return NULL;
	}

	queue->idx.front = queue->idx.back = 1;
	UserData reserved_slot = diskarray_access(queue->array, 0);
	if (userdata_empty(reserved_slot))
		return queue;

	queue->idx = *((PairIndex *)reserved_slot.data);
	free(reserved_slot.data);
	return queue;
}

bool diskqueue_empty(DiskQueue *queue) {
	assert(queue);
	return queue->idx.back == queue->idx.front;
}

UserData diskqueue_front(DiskQueue *queue) {
	assert(queue && queue->idx.front != 0 && !diskqueue_empty(queue));
	return diskarray_access(queue->array, queue->idx.front);
}

bool diskqueue_push(DiskQueue *queue, UserData data) {
	assert(queue && queue->idx.back != 0);
	assert(diskarray_insert(queue->array, queue->idx.back, data));
	queue->idx.back = next(queue->idx.back);
	return true;
}

UserData diskqueue_pop(DiskQueue *queue) {

	assert(queue && queue->idx.front != 0 && !diskqueue_empty(queue));
	UserData ret = {0};

	ret = diskarray_remove(queue->array, queue->idx.front);
	assert(!userdata_empty(ret));

	queue->idx.front = next(queue->idx.front);
	return ret;
}

void diskqueue_close(DiskQueue *queue) {

	if (!queue) return;

	/* store indexs */
	UserData store = { .data = &queue->idx, .size = sizeof queue->idx };
	assert(diskarray_insert(queue->array, 0, store));
	diskarray_close(queue->array);
	free(queue);
}
