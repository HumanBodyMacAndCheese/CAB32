#ifndef DISPERSALHASH_H
#define DISPERSALHASH_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>

#define DISPERSAL_STARTER (unsigned long)51203
#define DISPERSAL_ADDER (unsigned long)100669

/* Name is a pun on "seed dispersal" */
unsigned long dispersal(const unsigned char* data, size_t len, unsigned long seed) {
	unsigned long hash = DISPERSAL_STARTER ^ seed;

	/* Loop */
	size_t i;
	for (i = 0; i < len; i++) {
		hash ^= hash >> 16;
		hash += (unsigned long)data[i] + DISPERSAL_ADDER;
		hash ^= hash << 8;

	}

	/* Small finalizer to improve distribution with small strings */
	hash ^= hash << 16;
	hash ^= seed;
	hash ^= hash >> 8;

	return hash;

}

#ifdef __cplusplus
}
#endif
#endif		/* DISPERSALHASH_H */
