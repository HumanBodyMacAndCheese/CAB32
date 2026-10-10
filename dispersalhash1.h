/*

This is free and unencumbered software released into the public domain.

Anyone is free to copy, modify, publish, use, compile, sell, or
distribute this software, either in source code form or as a compiled
binary, for any purpose, commercial or non-commercial, and by any
means.

In jurisdictions that recognize copyright laws, the author or authors
of this software dedicate any and all copyright interest in the
software to the public domain. We make this dedication for the benefit
of the public at large and to the detriment of our heirs and
successors. We intend this dedication to be an overt act of
relinquishment in perpetuity of all present and future rights to this
software under copyright law.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
OTHER DEALINGS IN THE SOFTWARE.

For more information, please refer to <https://unlicense.org>

*/
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
