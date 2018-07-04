#include "DiskArray.h"

#define __USE_XOPEN_EXTENDED 
#include <ndbm.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define PEEK_ONLY true
enum { KEY, DAT };

struct _DiskArray {
	DBM  *db;
	datum dat[2];
};

static inline bool take_copy(const datum src, UserData *dst) {

	assert(dst);
	void *udata;

	if (!src.dptr || src.dsize <= 0 || !(udata = malloc(src.dsize)))
		return false;

	memcpy(udata, src.dptr, src.dsize);
	dst->data = udata;
	dst->size = src.dsize;

	return true;
}

static inline bool insert(DiskArray *s, uint32_t at, const UserData *dat) {

	assert(s && dat);
	s->dat[KEY].dptr  = (void *)&at;
	s->dat[KEY].dsize = sizeof at;
	s->dat[DAT].dptr  = dat->data;
	s->dat[DAT].dsize = dat->size;

	if (dbm_store(s->db, s->dat[KEY], s->dat[DAT], DBM_REPLACE) < 0)
		return false;

	return true;
}

static inline bool get(DiskArray *s, uint32_t at, UserData *dst, bool peek_only) {

	assert(s && dst);

	s->dat[KEY].dptr  = (void *)&at;
	s->dat[KEY].dsize = sizeof at;

	/* fetch data */
	s->dat[DAT] = dbm_fetch(s->db, s->dat[KEY]);

	/* no data found for this key */
	if (!s->dat[DAT].dptr || !take_copy(s->dat[DAT], dst))
		return false;

	/* retrieve & remove data */
	if (!peek_only) assert(dbm_delete(s->db, s->dat[KEY]) == 0);

	return true;
}


uint32_t diskarray_max_elements() {
	return UINT32_MAX-1;
}

DiskArray * diskarray_open(const char *file) {

	DiskArray *s;
	assert(file);

	if (!(s = calloc(sizeof(DiskArray), 1)))
		return NULL;

	/* dbm_open is defined like (char *) without const 
	i can't trust */

	char *to_free;
	if (!(to_free = strdup(file)))
		goto just_free;

	if (!(s->db = dbm_open(to_free, O_RDWR|O_CREAT, S_IRUSR|S_IWUSR))) {
		free(to_free);
just_free:
		free(s);
		return NULL;
	}
	free(to_free);

	return s;
}

UserData diskarray_access(DiskArray *s, uint32_t at) {
	assert(s);
	UserData ret = {0};
	get(s, at, &ret, PEEK_ONLY);
	return ret;
}

bool diskarray_insert(DiskArray *s, uint32_t at, UserData data) {
	assert(s && data.data);
	if (!insert(s, at, &data))
		return false;

	return true;
}

UserData diskarray_remove(DiskArray *s, uint32_t at) {
	assert(s);
	UserData ret = {0};
	get(s, at, &ret, !PEEK_ONLY);
	return ret;
}

void diskarray_close(DiskArray *s) {
	if (!s) return;
	dbm_close(s->db);
	free(s);
}
