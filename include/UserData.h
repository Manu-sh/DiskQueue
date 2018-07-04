#pragma once

#ifdef __cplusplus
#include <cstdint>
extern "C" {
#else
#include <stdint.h>
#include <stdbool.h>
#endif

 /* you must call free() on .data member of 
an UserData structure returned by disk* functions */

typedef struct {
	void *data;
	uint32_t size;
} UserData;

static inline bool userdata_empty(UserData data) {
	return !(data.data && data.size > 0); 
}

#ifdef __cplusplus
}
#endif
